//
// Created by vampo on 25-11-10.
//

#ifndef READ_WRITE_XML_H
#define READ_WRITE_XML_H


#include <vector>

class ReadWriteXml
{
public:
    ReadWriteXml();
    ~ReadWriteXml();

    bool writeScore();
    bool readScore();

    bool writeAndUpdataScoreList(const std::vector<int>&);
private:
    std::vector<int> m_score_list;
};


#endif //READ_WRITE_XML_H
