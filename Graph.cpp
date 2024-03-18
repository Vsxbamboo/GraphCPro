//
// Created by vsx on 2024/3/8.
//

#include "Graph.h"

void Graph::init(int VEX_MAX_NUM){

    this->VEX_MAX_NUM=VEX_MAX_NUM;
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
    ifinit=true;
}

Status Graph::insertVex(const Vex& vex) {
    if(!ifinit){
        return NOT_INIT;
    }
    if(vexnum==VEX_MAX_NUM){
        return VEX_NUM_FULL;
    }
    vexs[vexnum]=vex;
    vexnum++;
    return 0;
}

Status Graph::insertEdge(const Edge& edge) {
    if(!ifinit){
        return NOT_INIT;
    }
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
    if(!ifinit){
        return NOT_INIT;
    }
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
    if(!ifinit){
        return NOT_INIT;
    }
    if(adjMatrix[vexnum1][vexnum2]==-1)
        return EDGE_NOT_EXIST;
    edge=Edge(vexnum1,vexnum2,adjMatrix[vexnum1][vexnum2]);
    return 0;
}

Graph::Graph() {
    ifinit=false;
}

bool Graph::isInit() const {
    return ifinit;
}

Graph::~Graph() {
    delete[] vexs;
    delete[] adjMatrix;
}

Status Graph::DFStraverse(int startpoint, Path &path) {
    path=Path(vexnum);
    bool *visited=new bool[vexnum];
    path.push(startpoint);
    visited[startpoint]=true;
    Path *pList=&path;
    DFS(pList,visited);
    return 0;
}

void Graph::DFS(Path *&pList,bool *visited) {
    //先循环找下一个，如果找不到就回退，如果找得到，就push，判断是否满了，如果满了就记录且回退，如果不满就递归DFS
    for(int i=0;i<vexnum;i++){

        if(adjMatrix[pList->getLast()][i]!=-1 && !visited[i]){
            pList->push(i);

            visited[i]=true;
            if(pList->getLength()==vexnum){
                //调试输出
                std::cout<<"find:"<<pList->toString()<<std::endl;

                pList->next=new Path(vexnum);
                *(pList->next)=*pList;
                pList=pList->next;
                visited[i]=false;
                pList->pop();
                pList->next=nullptr;


            }else{
                DFS(pList,visited);
            }
        }
    }
    visited[pList->getLast()]=false;
    pList->pop();
}
