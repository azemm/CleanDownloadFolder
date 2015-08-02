#include "directorymonitor.h"
#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

boost::filesystem::path const & DirectoryMonitor::getDirectory() const
{
    return directory;
}

void DirectoryMonitor::setDirectory(const std::string &dir)
{
    directory = boost::filesystem::path(dir);
}

void DirectoryMonitor::setFileAssociation(FileAssociation &fileAssociation)
{
    this->fileAssociation = fileAssociation;
}

void DirectoryMonitor::loadXMLConfiguration(const std::string &path)
{
    this->fileAssociation.load(path);
}

void DirectoryMonitor::scan()
{
    boost::filesystem::directory_iterator it{directory};
    while (it != boost::filesystem::directory_iterator{}){
        moveFile(it->path());
        *it++;
    }
}

void DirectoryMonitor::monitor()
{
    scan();
    char buffer[BUF_LEN];
    int fd = inotify_init();
    int wd;
    if(fd > 0){
        wd = inotify_add_watch(fd, directory.string().c_str(), IN_CREATE);
        while(true){
            int i=0;
            int length = read(fd, buffer, BUF_LEN);
            if(length > 0){
                while(i < length){
                    struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
                    if ( event->len ) {
                        if ( event->mask & IN_CREATE ) {
                            if (!( event->mask & IN_ISDIR ) ) {
                                auto path = boost::filesystem::path(directory.string() + "/" + event->name);
                                moveFile(path);
                            }
                        }
                    }
                    i += EVENT_SIZE + event->len;
                }
            }
        }
        inotify_rm_watch(fd, wd);
        close(fd);
    }
}

bool DirectoryMonitor::moveFile(boost::filesystem::path const &path)
{
    if(boost::filesystem::is_regular_file(path)
            && boost::starts_with(path.string(), directory.string())){
        std::string pathToMove = fileAssociation.getPath(path.extension().string());
        auto dirToMove = boost::filesystem::path(pathToMove);
        if(pathToMove.length() > 0 && boost::filesystem::exists(dirToMove) && boost::filesystem::is_directory(dirToMove)){
            auto dest = boost::filesystem::path(pathToMove + "/" + path.filename().string());
            boost::filesystem::rename(path, dest);
            std::cout << "File " << path.filename() << " moved to " << pathToMove << std::endl;
            return true;
        }
    }
    return false;
}


