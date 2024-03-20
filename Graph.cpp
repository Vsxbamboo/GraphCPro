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

Status Graph::DFStraverse(int startpoint,Path *& pathList) {
    pathList=new Path(vexnum);
    bool *visited=new bool[vexnum]{0};
    pathList->push(startpoint);
    visited[startpoint]=true;
    Path *pList=pathList;
    DFS(pList,visited);
    delete[] visited;
    return 0;
}

void Graph::DFS(Path *&pList,bool *visited) {
    //先循环找下一个，如果找不到就回退，如果找得到，就push，判断是否满了，如果满了就记录且回退，如果不满就递归DFS
    for(int i=0;i<vexnum;i++){
        if(adjMatrix[pList->getLast()][i]!=-1 && !visited[i]){

            pList->push(i);

            visited[i]=true;
            if(pList->getLength()==vexnum){
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

Status Graph::findShortPath(int startpoint, int endpoint, Path *&pathp) {
    pathp=new Path(vexnum);

    //访问数组
    bool *visited=new bool[vexnum]{0};
    visited[startpoint]=true;
    //距离数组
    int *distance=new int[vexnum];
    //中间路径数组
    int *closet=new int[vexnum];
    //初始化
    for(int i=0;i<vexnum;i++){
        distance[i]=adjMatrix[startpoint][i];
        closet[i]=-1;
    }

    int min=-1,minvex=-1;
    //Dijkstra
    //每次找一个点,找n-1次
    for(int i=0;i<vexnum-1;i++){

        min=-1;
        //先找出当前最短的,贪心?
        for(int j=0;j<vexnum;j++){
            if( (min>distance[j] || min==-1 )&& distance[j]!=-1 && !visited[j]){
                min=distance[j];
                minvex=j;
            }
        }
        //找到就记录且更新
        if(min!=-1){
            //记录
            visited[minvex]=true;
            //更新未选中的
            for(int j=0;j<vexnum;j++){
                if(!visited[j] && adjMatrix[minvex][j]!=-1
                && (distance[j]>min+adjMatrix[minvex][j] || distance[j]==-1) ){
                    distance[j]=min+adjMatrix[minvex][j];
                    closet[j]=minvex;
                }
            }
        }
    }
    //如果没有路径
    if(distance[endpoint]==-1){
        return NO_SHORT_PATH;
    }

    auto temp=new Path(vexnum);
    temp->push(endpoint);
    while(closet[temp->getLast()]!=-1){
        temp->push(closet[temp->getLast()]);
    }
    temp->push(startpoint);
    int i=temp->p-1,j=0;
    while(i>=0){
        pathp->push(temp->pathnum[i]);
        i--;
        j++;
    }

    delete[] visited;
    delete[] distance;
    return 0;
}

Status Graph::findMinTree(Edge* &edges) {
    edges=new Edge[vexnum-1];
    int edge_counter=0;

    int closet[vexnum];//记录最短边
    int lowcost[vexnum];//判断是否已经纳入该顶点
    for(int i=0;i<vexnum;i++){
        closet[i]=0;
        lowcost[i]=adjMatrix[0][i];
    }
    //从0号顶点开始查找
    lowcost[0]=0;
    int min=-1,minvex=-1;
    for(int i=0;i<vexnum-1;i++){
        min=-1;
        for(int j=0;j<vexnum;j++){
            if(lowcost[j]!=0 && lowcost[j]!=-1 && (min>lowcost[j] || min==-1)){
                min=lowcost[j];
                minvex=j;
            }
        }
        if(min!=-1){
            lowcost[minvex]=0;
            for(int j=0;j<vexnum;j++){
                if(adjMatrix[minvex][j]!=-1 && adjMatrix[minvex][j]!=-1 && (lowcost[j]>adjMatrix[minvex][j] || lowcost[j]==-1)){
                    lowcost[j]=adjMatrix[minvex][j];
                    closet[j]=minvex;
                }
            }
        }
    }
    for(int i=0;i<vexnum;i++){
        if(i==0){
            continue;
        }
        edges[edge_counter]=Edge(closet[i],i,adjMatrix[closet[i]][i]);
        edge_counter++;
    }
    //额外排序一下
    int tempnum;
    for(int i=0;i<edge_counter;i++){
        if(edges[i].vexnum1>edges[i].vexnum2){
            tempnum=edges[i].vexnum1;
            edges[i].vexnum1=edges[i].vexnum2;
            edges[i].vexnum2=tempnum;
        }
    }
    Edge tempedge;
    for(int i=0;i<edge_counter-1;i++){
        for(int j=i+1;j<edge_counter;j++){
            if(edges[i].vexnum1>edges[j].vexnum1){
                tempedge=edges[i];
                edges[i]=edges[j];
                edges[j]=tempedge;
            }
        }
    }
    return 0;
}
