#include <iostream>
#include "Tourism.h"
int main() {
    Tourism tourism;

    int menu_selection=-1;
    while(menu_selection!=0){

        std::cout<<"=====������Ϣ����ϵͳ====="<<std::endl;
        std::cout<<"1.������������ͼ"<<std::endl;
        std::cout<<"2.��ѯ������Ϣ"<<std::endl;
        std::cout<<"3.���ξ��㵼��"<<std::endl;
        std::cout<<"4.�������·��"<<std::endl;
        std::cout<<"5.�����·�滮"<<std::endl;
        std::cout<<"0.�˳�"<<std::endl;
        std::cout<<"�����빦�����:";
        std::cin>>menu_selection;
        switch(menu_selection){
            case 1:
                int returncode;
                returncode=
                        tourism.creatGraph();
                if(returncode==tourism.FILE_NOT_EXIST){
                    std::cout<<"���ļ�ʧ��,Vex.txt��Edge.txt������"<<std::endl;
                }else{
                    std::cout<<"ͼ�����ɹ�"<<std::endl;
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
                std::cout<<"��л����ʹ��,�ټ�!";
                return 0;
                break;
            default:
                std::cout<<"��Чѡ��"<<std::endl;

        }
    }

    return 0;
}
