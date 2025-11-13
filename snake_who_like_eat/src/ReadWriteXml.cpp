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
    auto* decl = _doc.allocate_node(rapidxml::node_type::node_pi,
                               _doc.allocate_string("xml version=\"1.0\" encoding=\"UTF-8\""));
    _doc.append_node(decl);
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
    rapidxml::xml_document<> _doc;
    auto* _root = _doc.allocate_node(rapidxml::node_type::node_element, "GameData");
    _doc.append_node(_root);
    return false;
}

bool ReadWriteXml::writeAndUpdataScoreList(const std::vector<int>& score_list_)
{
    rapidxml::xml_document<> _doc;
    auto* decl = _doc.allocate_node(rapidxml::node_type::node_pi,
                               _doc.allocate_string("xml version=\"1.0\" encoding=\"UTF-8\""));
    _doc.append_node(decl);
    auto* _root = _doc.allocate_node(rapidxml::node_type::node_element, "GameData");
    _doc.append_node(_root);

    auto* _score_list = _doc.allocate_node(rapidxml::node_type::node_element, "ScoreList");
    _root->append_node(_score_list);
    for (auto it : score_list_)
    {
        auto* _score_node = _doc.allocate_node(rapidxml::node_type::node_element, "score");
        std::string _temp_score = std::to_string(it);
        _score_node->value(_doc.allocate_string(_temp_score.c_str()));
        _score_list->append_node(_score_node);
    }
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
