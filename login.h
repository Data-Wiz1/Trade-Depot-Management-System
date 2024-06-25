#include <iostream>
#include <sstream> 
#include <iomanip>
#include<windows.h>
using namespace std;

void Color(int color)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void login(){
	system("cls");
	string username,usrnm="admin";
	string password,pswrd="admin";
	int i=1;
	Color(3);
	cout<<"\n\n\t\t\t Trade Depot Management System "<<endl;
	cout<<"\t\t\t \xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\n"<<endl;
	while(i!=0)
	{
		Color(8);
		cout<<"\n\tEnter username: ";
		Color(7);
		cin>>username;
		Color(8);
		cout<<"\tEnter password: ";
		Color(7);
		cin>>password;
		Color(3);
		
		if(((username.compare(usrnm))==0) && ((password.compare(pswrd))==0))
		{
			Color(2);
			cout<<"\n \t \t \t \t Login successful!"<<endl;
			i=0;
			cout<<endl;
			system("pause");
			Color(7);
		}else{
			Color(4);
			cout<<"\n \t \t \t \t Wrong credentials, Please try again"<<endl;
			Color(3);
			continue;
		}
    }
}
