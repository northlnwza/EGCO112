#include "U_menu.cpp"
#include "T_menu.cpp"
#include "S_menu.cpp"

int main(){

    while(1){
    int choice;
    cout<<endl<<"\t--Welcome to EGCO menu hub.--\n"<<endl;
    cout<<"  Press 1 for Student."<<endl;
    cout<<"  Press 2 for Teacher."<<endl;
    cout<<"  Press 3 for Staff."<<endl;
    cin>>choice;
    if (choice==1) u_menu("u1000");
    else if (choice==2) t_menu("t1000");
    else if (choice==3) s_menu("s1008");
    else cout<<"Invalid input please try again.";
    }

    return 0;
}