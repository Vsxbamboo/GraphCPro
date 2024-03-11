//
// Created by vsx on 2024/3/8.
//

#include "Tourism.h"

Tourism::Tourism() {

}

Status Tourism::creatGraph() {
    //打开文件
    std::fstream vexfile,edgefile;
    vexfile.open(vexfilepath,std::ios::in);
    edgefile.open(edgefilepath,std::ios::in);

    //判断文件是否存在
    if(!vexfile.is_open() || !edgefile.is_open()){
        return FILE_NOT_EXIST;
    }
    //读取文件部分
    std::string line;
    //读取Vex
    int num;
    std::string name,desc;
    while(getline(vexfile,line)){
        std::stringstream stream(line);
        stream>>num;
        stream>>name;
        stream>>desc;
        g.insertVex(Vex(num,name,desc));
    }
    g.showVex();
    //读取Edge
    int vexnum1,vexnum2,weight;
    while(getline(edgefile,line)){
        std::stringstream stream(line);
        stream>>vexnum1;
        stream>>vexnum2;
        stream>>weight;
        g.insertEdge(Edge(vexnum1,vexnum2,weight));
    }
    g.showEdge();

    //关闭文件
    vexfile.close();
    edgefile.close();

    //正常返回
    return 0;
}

Status Tourism::getSpotInfo() {
    int returncode;
    //列出所有景点序号
    int vexnum=g.getVexnum();
    Vex vex;
    std::cout<<"=====查询景点信息====="<<std::endl;
    for(int i=0;i<vexnum;i++){
        g.getVex(i,vex);
        std::cout<<vex.num<<"-"<<vex.name<<std::endl;
    }

    //单个景点查询
    std::cout<<"请输入想要查询的景点编号:";
    int vexindex;
    std::cin>>vexindex;
    returncode=
            g.getVex(vexindex,vex);
    if(returncode==g.INDEX_OUTOFBOUND){
        std::cout<<"编号输入错误"<<std::endl;
        return 0;
    }
    std::cout<<vex.num<<"-"<<vex.name<<std::endl<<vex.desc<<std::endl;

    //周边景点展示
    std::cout<<"-----周边景点-----"<<std::endl;
    Vex nearvex;
    Edge edge;
    for(int i=0;i<vexnum;i++){
        if(g.getEdge(vexindex,i,edge)!=g.EDGE_NOT_EXIST){
            g.getVex(i,nearvex);
            std::cout<<vex.name<<"->"<<nearvex.name<<" "<<edge.weight<<std::endl;
        }
    }
    return 0;
}


