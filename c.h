#ifndef C_H
#define C_H

#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
using namespace std;

void Interface();       //ระบบหน้าจอ อาจจะรวมlogin?
void Login();
void Menu();
void Announce(string ); //Show some text then refresh
void Loading();
void Fill();void Fill(string ); //Fill the empty space of each line , and printout
void Skip();void Skip(int ); //Fill all lines , Skip n lines
string Count(string );  //function for printout string and save strlen to fill the empty

//void MU_Logo();         //Too big for this interface's version

int Screen_Width=52;    //16:9
int Screen_height=31;

class User{ //สร้างไปงั้นยังไม่รู้ทำทำไม
        int ID;
        string name;
        string faculty;
    public:
        User(int id,string n,string f) : ID(id), name(n), faculty(f) {}
        void info(){
            cout<<"Name : "<<name;
        }
};

void Interface(){
    system("clear");
    cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t-Enter to continue-\n\n\n\n\n\n\n\n\n";
    cout<<"\n ______ _    _ _      _         _____  _____ _____  ______ ______ _   _ \n|  ____| |  | | |    | |       / ____|/ ____|  __ \\|  ____|  ____| \\ | |\n| |__  | |  | | |    | |      | (___ | |    | |__) | |__  | |__  |  \\| |\n|  __| | |  | | |    | |       \\___ \\| |    |  _  /|  __| |  __| | . ` |\n| |    | |__| | |____| |____   ____) | |____| | \\ \\| |____| |____| |\\  |\n|_|     \\____/|______|______| |_____/ \\_____|_|  \\_\\______|______|_| \\_|\n\n\n";
    cin.get();
    system("clear");
    Loading();
    Login();
}

void Login(){
    cout<<setfill('-')<<setw(54)<<"\n";
    Skip(14);
    Fill("|          -->     Press 1 to Sign In ");
    Skip(1);
    Fill("|          -->     Press 2 to Sign Up ");
    Skip();

    int ch;
    cin>>ch;
    switch (ch) {
        case 1 :Announce("|                    Successful!");
                Menu();
                break;
        case 2 :Announce("|                    Successful!");
                Menu();
                break;
        default:system("clear");
                Login();
                break;
    }
}

void Menu(){
    cout<<setfill('-')<<setw(54)<<"\n";
    Skip(3);
    Fill("|                      Skibidi");
    Skip(3);
    cout<<"|"<<setfill('-')<<setw(53)<<"|\n";
    Screen_height--,Skip();
}

void Announce(string word){
    system("clear");
    cout<<setfill('-')<<setw(54)<<"\n";
    Skip(15);
    Fill(word);
    Skip(14);
    Fill("|                Enter to continue...");
    Skip();
    cin.get();
    cin.get();
    system("clear");
}

void Loading(){
    int i;
    string load=" ";
    for (i=0;i<18;i++){
    cout<<setfill('-')<<setw(54)<<"\n";
    Skip(14);
    Fill("|                     Loading...");
    Fill("|                __________________");
    cout<<"|"<<Count("               |")<<"\033[42m"<<Count(load)<<"\033[0m",Fill();
    Fill("|                ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\t\t    ");
    Skip();
    load+=" ";
    usleep(100000);
    system("clear");
    }
}

void Fill(string word){
    int remain=Screen_Width-word.size()+1;
    cout<<word<<setfill(' ')<<setw(remain)<<"|"<<endl;
    Screen_height--;
}
void Fill(){
    cout<<setfill(' ')<<setw(Screen_Width)<<"|"<<endl;
    Screen_Width=52;
    Screen_height--;
}

void Skip(){
    while (Screen_height>0) {
        Fill("|");
    }
    cout<<setfill('-')<<setw(54)<<"\n";
    Screen_height=31;
}
void Skip(int n){
    for (n;n>0;n--){
        Fill("|");
    }
}

string Count(string word){ 
    Screen_Width=Screen_Width-word.size();
    return word;
}

/*void MU_Logo(){  
    int i;
    for (i=0;i<11;i++){
        cout<<
        Fill();
    }
}*/ 

#endif