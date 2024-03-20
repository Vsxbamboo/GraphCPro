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
    int vex_max_num=0,num=-1;
    std::string name,desc;
    vexfile>>vex_max_num;
    g.init(vex_max_num);
    for(int i=0;i<vex_max_num;i++){
        vexfile>>num;
        vexfile>>name;
        vexfile>>desc;
        if(0<=num && num<vex_max_num && !name.empty() && !desc.empty()){
            g.insertVex(Vex(num,name,desc));
        }else{
            std::cout<<"创建失败,文件格式错误"<<std::endl;
            return FILE_FORMAT_ERROR;
        }
    }
//    g.showVex();
    //读取Edge
    int vexnum1=-1,vexnum2=-1,weight=-1;
    while(getline(edgefile,line)){
        std::stringstream stream(line);
        stream>>vexnum1;
        stream>>vexnum2;
        stream>>weight;
        if(0<=vexnum1 && 0<=vexnum2 && 0<=weight
        && vexnum1<vex_max_num && vexnum2<vex_max_num){
            g.insertEdge(Edge(vexnum1,vexnum2,weight));
        }else{
            std::cout<<"创建失败,文件格式错误"<<std::endl;
            return FILE_FORMAT_ERROR;
        }
    }
//    g.showEdge();

    //关闭文件
    vexfile.close();
    edgefile.close();

    //正常返回
    return 0;
}

Status Tourism::getSpotInfo() {
    if(!g.isInit()){
        std::cout<<"景区景点图尚未创建,请先使用选项1创建景区景点图"<<std::endl;
        return SPOT_NOT_CREAT;
    }
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

Status Tourism::travelPath() {
    if(!g.isInit()){
        std::cout<<"景区景点图尚未创建,请先使用选项1创建景区景点图"<<std::endl;
        return SPOT_NOT_CREAT;
    }
    //列出所有景点序号
    int vexnum=g.getVexnum();
    Vex vex;
    std::cout<<"=====旅游景点导航====="<<std::endl;
    for(int i=0;i<vexnum;i++){
        g.getVex(i,vex);
        std::cout<<vex.num<<"-"<<vex.name<<std::endl;
    }
    std::cout<<"请输入起始点编号:";
    int vexindex;
    std::cin>>vexindex;
    if(vexindex<0 || vexindex>=vexnum){
        std::cout<<"编号错误"<<std::endl;
        return 0;
    }
    Path *pList;
    g.DFStraverse(vexindex,pList);

    auto pList2=pList;
    while(pList!=nullptr){
        for(int i=0;i<pList->p;i++){
            g.getVex(pList->pathnum[i],vex);
            std::cout<<vex.name;
            if(i!=pList->p-1)
                std::cout<<"->";
        }
        std::cout<<std::endl;
        pList=pList->next;
    }
    //释放
    while(pList2!=nullptr){
        auto p=pList2;
        pList2=pList2->next;
        delete p;
    }
    return 0;
}

Status Tourism::findShortPath() {
    if(!g.isInit()){
        std::cout<<"景区景点图尚未创建,请先使用选项1创建景区景点图"<<std::endl;
        return SPOT_NOT_CREAT;
    }
    std::cout<<"=====搜索最短路径====="<<std::endl;
    //列出景点编号
    int vexnum=g.getVexnum();
    Vex vex;
    for(int i=0;i<vexnum;i++){
        g.getVex(i,vex);
        std::cout<<vex.num<<"-"<<vex.name<<std::endl;
    }
    int startpoint,endpoint;
    std::cout<<"请输入起点的编号:";
    std::cin>>startpoint;
    if(startpoint<0 || startpoint>=vexnum){
        std::cout<<"编号错误"<<std::endl;
        return 0;
    }
    std::cout<<"请输入终点的编号:";
    std::cin>>endpoint;
    if(endpoint<0 || endpoint>=vexnum){
        std::cout<<"编号错误"<<std::endl;
        return 0;
    }
    Path *pathp;
    int returncode=
    g.findShortPath(startpoint,endpoint,pathp);
    if(returncode==g.NO_SHORT_PATH){
        std::cout<<"没有找到最短路径"<<std::endl;
        return 0;
    }
    std::cout<<"最短路径为:";
    for(int i=0;i<pathp->p;i++){
        g.getVex(pathp->pathnum[i],vex);
        std::cout<<vex.name;
        if(i!=pathp->p-1){
            std::cout<<"->";
        }
    }
    std::cout<<std::endl;

    int pathlength=0;
    Edge edge;
    for(int i=0;i<pathp->p-1;i++){
        g.getEdge(pathp->pathnum[i],pathp->pathnum[i+1],edge);
        pathlength+=edge.weight;
    }
    std::cout<<"最短距离为:"<<pathlength<<std::endl;
    delete pathp;
    return 0;
}

Status Tourism::designPath() {
    if(!g.isInit()){
        std::cout<<"景区景点图尚未创建,请先使用选项1创建景区景点图"<<std::endl;
        return SPOT_NOT_CREAT;
    }
    std::cout<<"=====铺设电路规划====="<<std::endl;
    Edge *edges = nullptr;
    g.findMinTree(edges);
    int vexnum=g.getVexnum();
    Vex vex;
    int totalweight=0;
    for(int i=0;i<vexnum-1;i++){
        g.getVex(edges[i].vexnum1,vex);
        std::cout<<vex.name<<"-";
        g.getVex(edges[i].vexnum2,vex);
        std::cout<<vex.name<<" "<<edges[i].weight<<std::endl;
        totalweight+=edges[i].weight;
    }
    std::cout<<"铺设电路的总长度为:"<<totalweight<<std::endl;
    return 0;
}


