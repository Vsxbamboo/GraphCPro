//
// Created by vsx on 2024/3/8.
//

#ifndef GRAPHCPRO_TOURISM_H
#define GRAPHCPRO_TOURISM_H

#include <fstream>
#include <sstream>
#include <iostream>
#include "Graph.h"

/*
 * 定义Vex.txt表示标准
 * 数量(int)
 * 编号(int)
 * 名字(string)
 * 介绍(string)
 *
 * 定义Edge.txt表示标准
 * 编号1(int) 编号2(int) 权值(int)
 * */

class Tourism {
private:
    const std::string vexfilepath="C:\\E\\cpp\\GraphCPro\\Vex.txt";
    const std::string edgefilepath="C:\\E\\cpp\\GraphCPro\\Edge.txt";
    Graph g;
public:
    const int FILE_NOT_EXIST=-1;
    const int FILE_FORMAT_ERROR=-2;
    const int SPOT_NOT_CREAT=-3;
    Tourism();
    Status creatGraph();
    Status getSpotInfo();
    Status travelPath();
    Status findShortPath();
    Status designPath();
};


#endif //GRAPHCPRO_TOURISM_H
