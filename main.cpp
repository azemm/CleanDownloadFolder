#include <iostream>
#include "directorymonitor.h"
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

int main(int argc, char** argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("dir", po::value<std::string>(), "path of the directory to monitor")
            ("conf", po::value<std::string>(), "path of the xml configuration file");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help")){
        cout << desc << endl;
        return 1;
    }

    if(vm.count("dir") && vm.count("conf")){
        DirectoryMonitor directoryMonitor(vm["dir"].as<std::string>());
        directoryMonitor.loadXMLConfiguration(vm["conf"].as<std::string>());
        directoryMonitor.monitor();
    } else {
        cout << "Incorrect options passed, consult help with --help option" << endl;
    }
    return 0;
}
