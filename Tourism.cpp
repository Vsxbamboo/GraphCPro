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
            std::cout<<"����ʧ��,�ļ���ʽ����"<<std::endl;
            return FILE_FORMAT_ERROR;
        }
    }
//    g.showVex();
    //��ȡEdge
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
            std::cout<<"����ʧ��,�ļ���ʽ����"<<std::endl;
            return FILE_FORMAT_ERROR;
        }
    }
//    g.showEdge();

    //�ر��ļ�
    vexfile.close();
    edgefile.close();

    //��������
    return 0;
}

Status Tourism::getSpotInfo() {
    if(!g.isInit()){
        std::cout<<"��������ͼ��δ����,����ʹ��ѡ��1������������ͼ"<<std::endl;
        return SPOT_NOT_CREAT;
    }
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

Status Tourism::travelPath() {
    if(!g.isInit()){
        std::cout<<"��������ͼ��δ����,����ʹ��ѡ��1������������ͼ"<<std::endl;
        return SPOT_NOT_CREAT;
    }
    //�г����о������
    int vexnum=g.getVexnum();
    Vex vex;
    std::cout<<"=====���ξ��㵼��====="<<std::endl;
    for(int i=0;i<vexnum;i++){
        g.getVex(i,vex);
        std::cout<<vex.num<<"-"<<vex.name<<std::endl;
    }
    std::cout<<"��������ʼ����:";
    int vexindex;
    std::cin>>vexindex;
    if(vexindex<0 || vexindex>=vexnum){
        std::cout<<"��Ŵ���"<<std::endl;
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
    //�ͷ�
    while(pList2!=nullptr){
        auto p=pList2;
        pList2=pList2->next;
        delete p;
    }
    return 0;
}

Status Tourism::findShortPath() {
    if(!g.isInit()){
        std::cout<<"��������ͼ��δ����,����ʹ��ѡ��1������������ͼ"<<std::endl;
        return SPOT_NOT_CREAT;
    }
    std::cout<<"=====�������·��====="<<std::endl;
    //�г�������
    int vexnum=g.getVexnum();
    Vex vex;
    for(int i=0;i<vexnum;i++){
        g.getVex(i,vex);
        std::cout<<vex.num<<"-"<<vex.name<<std::endl;
    }
    int startpoint,endpoint;
    std::cout<<"���������ı��:";
    std::cin>>startpoint;
    if(startpoint<0 || startpoint>=vexnum){
        std::cout<<"��Ŵ���"<<std::endl;
        return 0;
    }
    std::cout<<"�������յ�ı��:";
    std::cin>>endpoint;
    if(endpoint<0 || endpoint>=vexnum){
        std::cout<<"��Ŵ���"<<std::endl;
        return 0;
    }
    Path *pathp;
    int returncode=
    g.findShortPath(startpoint,endpoint,pathp);
    if(returncode==g.NO_SHORT_PATH){
        std::cout<<"û���ҵ����·��"<<std::endl;
        return 0;
    }
    std::cout<<"���·��Ϊ:";
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
    std::cout<<"��̾���Ϊ:"<<pathlength<<std::endl;
    delete pathp;
    return 0;
}

Status Tourism::designPath() {
    if(!g.isInit()){
        std::cout<<"��������ͼ��δ����,����ʹ��ѡ��1������������ͼ"<<std::endl;
        return SPOT_NOT_CREAT;
    }
    std::cout<<"=====�����·�滮====="<<std::endl;
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
    std::cout<<"�����·���ܳ���Ϊ:"<<totalweight<<std::endl;
    return 0;
}


