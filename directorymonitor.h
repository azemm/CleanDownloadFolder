#ifndef DIRECTORYMONITOR_H
#define DIRECTORYMONITOR_H

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "fileassociation.h"
#include <sys/inotify.h>
#include <sys/types.h>


class DirectoryMonitor
{
public:
    DirectoryMonitor(const std::string &dir) : directory(dir), fileAssociation() {}
    boost::filesystem::path const & getDirectory() const;
    void setDirectory(const std::string &dir);
    void setFileAssociation(FileAssociation & fileAssociation);
    void loadXMLConfiguration(const std::string & path);
    void scan();
    void monitor();
private:
    bool moveFile(boost::filesystem::path const & path);

    boost::filesystem::path directory;
    FileAssociation fileAssociation;
};

#endif // DIRECTORYMONITOR_H
