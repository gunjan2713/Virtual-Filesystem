#include<iostream>
#include<sstream>
#include<stdlib.h>
#include "vfs.hpp"
using namespace std;


int main()
{
	VFS vfs;
	vfs.help(); 

	while(true)
	{
		string user_input;
		string command;
		string parameter1;
		string parameter2;
		cout<<">";
		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter1,' ');
		getline(sstr,parameter2);

		try
		{
			// Required commands
			if(command=="help")		vfs.help();
			else if(command=="pwd")			cout<<vfs.pwd()<<endl;
			else if(command=="ls") 			vfs.ls();
			else if(command=="mkdir")		vfs.mkdir(parameter1);
			else if(command=="touch")		vfs.touch(parameter1,stoi(parameter2));
			else if(command=="cd")			vfs.cd(parameter1);
			else if(command=="rm")			vfs.rm(parameter1);
			else if(command=="size")		vfs.size(parameter1);
			else if(command=="showbin")		vfs.showbin();
			else if(command=="emptybin")	vfs.emptybin();
			else if (command == "recover")  vfs.recover();
			// else if(command == "find") 		vfs.find(parameter1);
			else if(command=="exit")		{vfs.exit(); return(EXIT_SUCCESS);}

			//optional commands
			// else if(command=="find")		vfs.find(parameter1);
			// else if(command=="mv")			vfs.mv(parameter1, parameter2);
			// else if(command=="recover")		vfs.recover();
			// else if(command=="clear")		system("clear");
			else 							cout<<command<<": command not found"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	 }
}