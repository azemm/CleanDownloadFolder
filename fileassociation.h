#ifndef FILEASSOCIATION_H
#define FILEASSOCIATION_H

#include <iostream>
#include <unordered_map>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

class FileAssociation
{
public:
    FileAssociation() : map() {}
    void add(std::string ext, std::string path);
    void del(std::string ext);
    const std::string getPath(std::string const & ext);
    void load(const std::string &path);
private:
    std::unordered_map<std::string, std::string> map;
};

#endif // FILEASSOCIATION_H
