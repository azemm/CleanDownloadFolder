#include <iostream>
#include "directorymonitor.h"

using namespace std;

int main(int argc, char** argv)
{
    if(argc >= 3){
        DirectoryMonitor directoryMonitor = DirectoryMonitor(argv[1]);
        directoryMonitor.loadXMLConfiguration(argv[2]);
        directoryMonitor.monitor();
    } else {
        cout << "Missing argument, add path of the directory to monitor and path of the xml configuration file" << endl;
    }
    return 0;
}
