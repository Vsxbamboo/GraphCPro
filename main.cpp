#include <iostream>
#include "Tourism.h"
int main() {
    Tourism tourism;

    int menu_selection=-1;
    while(menu_selection!=0){

        std::cout<<"=====景区信息管理系统====="<<std::endl;
        std::cout<<"1.创建景区景点图"<<std::endl;
        std::cout<<"2.查询景点信息"<<std::endl;
        std::cout<<"3.旅游景点导航"<<std::endl;
        std::cout<<"4.搜索最短路径"<<std::endl;
        std::cout<<"5.铺设电路规划"<<std::endl;
        std::cout<<"0.退出"<<std::endl;
        std::cout<<"请输入功能序号:";
        std::cin>>menu_selection;
        switch(menu_selection){
            case 1:
                int returncode;
                returncode=
                        tourism.creatGraph();
                if(returncode==tourism.FILE_NOT_EXIST){
                    std::cout<<"打开文件失败,Vex.txt或Edge.txt不存在"<<std::endl;
                }else{
                    std::cout<<"图创建成功"<<std::endl;
                }
                break;
            case 2:
                tourism.getSpotInfo();
                break;
            case 3:
                tourism.travelPath();
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                std::cout<<"感谢您的使用,再见!";
                return 0;
                break;
            default:
                std::cout<<"无效选项"<<std::endl;

        }
    }

    return 0;
}
