//
// Created by vsx on 2024/3/8.
//

#include "Graph.h"

Graph::Graph() {
    vexs=new Vex[VEX_MAX_NUM];
    adjMatrix=new int*[VEX_MAX_NUM];
    for(int i=0;i<VEX_MAX_NUM;i++){
        adjMatrix[i]=new int[VEX_MAX_NUM];
    }
    for(int i=0;i<VEX_MAX_NUM;i++){
        for(int j=0;j<VEX_MAX_NUM;j++){
            adjMatrix[i][j]=-1;
        }
    }
    vexnum=0;
}

Status Graph::insertVex(const Vex& vex) {
    if(vexnum==VEX_MAX_NUM){
        return VEX_NUM_FULL;
    }
    vexs[vexnum]=vex;
    vexnum++;
    return 0;
}

Status Graph::insertEdge(const Edge& edge) {
    if(edge.vexnum1<0 || edge.vexnum1>=VEX_MAX_NUM
    || edge.vexnum2<0 || edge.vexnum2>=VEX_MAX_NUM
    || edge.weight<0){
        return EDGE_OUTOFBOUND;
    }
    if(adjMatrix[edge.vexnum1][edge.vexnum2]!=-1){
        return EDGE_OVERRIDE;
    }
    adjMatrix[edge.vexnum1][edge.vexnum2]=edge.weight;
    adjMatrix[edge.vexnum2][edge.vexnum1]=edge.weight;
    return 0;
}

void Graph::showVex() const{
    std::cout<<"Graph.Vex:"<<std::endl;
    for(int i=0;i<vexnum;i++){
        std::cout<<vexs[i]<<std::endl;
    }
}

void Graph::showEdge() const{
    std::cout<<"Graph.Edge:"<<std::endl;
    for(int i=0;i<vexnum;i++){
        for(int j=0;j<vexnum;j++){
            if(adjMatrix[i][j]!=-1){
                std::cout<<i<<" "<<j<<" "<<adjMatrix[i][j]<<std::endl;
            }
        }
    }
}

Status Graph::getVex(const int index, Vex &vex) const{
    if(index<0 || index>=vexnum){
        return INDEX_OUTOFBOUND;
    }
    vex=vexs[index];
    return 0;
}

int Graph::getVexnum() const{
    return vexnum;
}

Status Graph::getEdge(const int vexnum1, const int vexnum2,Edge& edge) const {
    if(adjMatrix[vexnum1][vexnum2]==-1)
        return EDGE_NOT_EXIST;
    edge=Edge(vexnum1,vexnum2,adjMatrix[vexnum1][vexnum2]);
    return 0;
}
