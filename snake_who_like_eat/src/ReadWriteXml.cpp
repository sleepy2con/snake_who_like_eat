//
// Created by vampo on 25-11-10.
//
#include "ReadWriteXml.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <iostream>
#include <fstream>

#include <qscreen_platform.h>

ReadWriteXml::ReadWriteXml()
{
}

ReadWriteXml::~ReadWriteXml()
{
}

bool ReadWriteXml::writeScore()
{
    rapidxml::xml_document<> _doc;
    auto* _root = _doc.allocate_node(rapidxml::node_type::node_element, "GameData");
    _doc.append_node(_root);

    auto* _user_info_list = _doc.allocate_node(rapidxml::node_type::node_element, "UserInfo");
    _root->append_node(_user_info_list);

    std::ofstream _file("gamedata.xml");
    if (_file.is_open())
    {
        _file << _doc;
        _file.close();
        std::cout << "write data success\n";
    }
    else
    {
        std::cout << "write data failed\n";
    }
    return true;
}

bool ReadWriteXml::readScore()
{
    return false;
}
