//
// Created by vsx on 2024/3/8.
//

#ifndef GRAPHCPRO_GRAPH_H
#define GRAPHCPRO_GRAPH_H

#include <string>
#include <iostream>

#define Status int

struct Vex{
    int num;
    std::string name;
    std::string desc;
    Vex():num(-1),name(""),desc(""){}
    //实现构造函数，防止对变量名的修改影响外部代码
    Vex(const int num,const std::string& name,const std::string& desc):
        num(num),name(name),desc(desc){

    }
    Vex& operator=(const Vex& rv){
        if(this==&rv){
            return *this;
        }
        num=rv.num;
        name=rv.name;
        desc=rv.desc;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os,const Vex& vex){
        os<<vex.num<<" "<<vex.name<<" "<<vex.desc;
        return os;
    }
};

struct Edge{
    int vexnum1;
    int vexnum2;
    int weight;
    Edge():vexnum1(-1),vexnum2(-1),weight(-1){}
    //实现构造函数，防止对变量名的修改影响外部代码
    Edge(const int vexnum1,const int vexnum2,const int weight):
        vexnum1(vexnum1),vexnum2(vexnum2),weight(weight){

    }
    Edge& operator=(const Edge& re){
        if(this==&re){
            return *this;
        }
        vexnum1=re.vexnum1;
        vexnum2=re.vexnum2;
        weight=re.weight;
        return *this;
    }
};

class Graph {
private:
    int** adjMatrix;
    Vex* vexs;
    int vexnum;
    bool ifinit;
public:
    int VEX_MAX_NUM;
    const int VEX_NUM_FULL=-1;
    const int EDGE_OVERRIDE=-2;
    const int EDGE_OUTOFBOUND=-3;
    const int INDEX_OUTOFBOUND=-4;
    const int EDGE_NOT_EXIST=-5;
    const int NOT_INIT=-6;
    Graph();
    void init(int VEX_MAX_NUM);
    Status insertVex(const Vex& vex);
    Status insertEdge(const Edge& edge);
    Status getVex(int index,Vex& vex)const;
    int getVexnum()const;
    Status getEdge(int vexnum1,int vexnum2,Edge& edge)const;
    void showVex()const;
    void showEdge()const;
    bool isInit()const;
};
#endif //GRAPHCPRO_GRAPH_H
