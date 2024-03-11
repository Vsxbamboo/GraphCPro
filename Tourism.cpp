//
// Created by vsx on 2024/3/8.
//

#include "Tourism.h"

Tourism::Tourism() {

}

Status Tourism::creatGraph() {
    //���ļ�
    std::fstream vexfile,edgefile;
    vexfile.open(vexfilepath,std::ios::in);
    edgefile.open(edgefilepath,std::ios::in);

    //�ж��ļ��Ƿ����
    if(!vexfile.is_open() || !edgefile.is_open()){
        return FILE_NOT_EXIST;
    }
    //��ȡ�ļ�����
    std::string line;
    //��ȡVex
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
    //��ȡEdge
    int vexnum1,vexnum2,weight;
    while(getline(edgefile,line)){
        std::stringstream stream(line);
        stream>>vexnum1;
        stream>>vexnum2;
        stream>>weight;
        g.insertEdge(Edge(vexnum1,vexnum2,weight));
    }
    g.showEdge();

    //�ر��ļ�
    vexfile.close();
    edgefile.close();

    //��������
    return 0;
}

Status Tourism::getSpotInfo() {
    int returncode;
    //�г����о������
    int vexnum=g.getVexnum();
    Vex vex;
    std::cout<<"=====��ѯ������Ϣ====="<<std::endl;
    for(int i=0;i<vexnum;i++){
        g.getVex(i,vex);
        std::cout<<vex.num<<"-"<<vex.name<<std::endl;
    }

    //���������ѯ
    std::cout<<"��������Ҫ��ѯ�ľ�����:";
    int vexindex;
    std::cin>>vexindex;
    returncode=
            g.getVex(vexindex,vex);
    if(returncode==g.INDEX_OUTOFBOUND){
        std::cout<<"����������"<<std::endl;
        return 0;
    }
    std::cout<<vex.num<<"-"<<vex.name<<std::endl<<vex.desc<<std::endl;

    //�ܱ߾���չʾ
    std::cout<<"-----�ܱ߾���-----"<<std::endl;
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


