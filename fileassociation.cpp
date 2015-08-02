#include "fileassociation.h"

void FileAssociation::add(std::string ext, std::string path)
{
    map[ext] = path;
}

void FileAssociation::del(std::string ext)
{
    map.erase(ext);
}

const std::string FileAssociation::getPath(std::string const &ext)
{
    std::unordered_map<std::string, std::string>::iterator it = map.find(ext);
    if(it == map.end()){
        return std::string("");
    } else {
        return it->second;
    }
}

void FileAssociation::load(std::string const & path)
{
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(path, pt);

    for(boost::property_tree::ptree::value_type const& v : pt.get_child("root")){
        if(v.first == "association"){
            add(v.second.get<std::string>("ext"), v.second.get<std::string>("path"));
        }
    }
}
