#include <iostream>
#include <cstring>
#include <string>
#include <functional>
#include <fstream>
#include <vector>
#include <direct.h>
#include <filesystem>
#include "createF.h"
#include "createDir.h"
#pragma warning(disable : 4996)
using namespace std;
// if you are using linux these are the lines where I am using "system" function:
// line 68
// line 71
// line 110
// line 115
// line 223
// line 287
// line 447 , 452 , 458 , 462 , 468 , 473
// line 492 , 499 , 506

string remember_password,remember_username,remember_row;
bool quit = false;

void open()
{
	cout << "Enter the ID of wanted email" << endl;
	
	char read[] = "\\info.txt",final[256];
	unsigned ln = remember_username.length(),digit;
	for (unsigned i = 0; i < ln; i++)
	{
		final[i] = remember_username[i];
	}final[ln] = '\0';
	strcat(final, read);
	ifstream info_num;
	info_num.open(final);
	info_num >> digit;
	info_num.close();
	cout << "from 1 to " << digit << endl;
	int number;
	cin >> number;
	if (number < 1||number>digit)
		return open();
	unsigned len = remember_username.length();
	char name[256];
	for (unsigned i = 0; i < len; i++)
	{
		name[i] = remember_username[i];
	}name[len] = '\0';
	char dir[256];
	strcpy(dir, create_directory(number, name));
	string row;
	ifstream open_inf;
	open_inf.open(dir);
	getline(open_inf, row);
	cout << "From:"<<row<<endl;
	getline(open_inf, row);
	cout << "Subject:" << row<<endl;
	getline(open_inf, row);
	cout << "Content:" << row<<endl;
	cout << "Do you want to open another one Y/N:";
	char ans;
	cin >> ans;
	if (ans == 'Y' || ans == 'y')
	{
		system("cls");
		return open();
	}
	system("cls");
}
void inbox(unsigned number)
{
	unsigned counter = 0;
	while (number)
	{
		if (counter==number)
		{
			break;
		}
		counter++;
		unsigned len = remember_username.length();
		char name[256];
		for (unsigned i = 0; i < len; i++)
		{
			name[i] = remember_username[i];
		}name[len] = '\0';
		char all[256];
		strcpy(all, create_directory(counter,name));
		ifstream read_topic;
		read_topic.open(all);
		string topic,row;
		for (unsigned z = 0; z < 2; z++)
		{
			getline(read_topic, row);
			if (z == 1)
			{
				cout << counter << ". " << row<<endl;
				break;
			}
		}
		read_topic.close();
	}
	cout << "Do you want to read one of them Y/N:";
	char ans;
	cin >> ans;
	if (ans=='Y'||ans=='y')
	{
		system("cls");
		return open();
	}
	else
	{
		system("cls");
	}
}
void send()
{
	char name[256],topic[256],message[256];
	cout << "Enter recipient:";
	cin.ignore();
	cout<<endl;
	cin.getline(name, 256);
	cout << "Enter topic:";
	cout << endl;
	cin.getline(topic,256);
	cout << "Enter the message:";
	cout << endl;
	cin.getline(message, 256);
	string row;
	ifstream log;
	log.open("users.txt");
	if (log.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	while (log >> row)
	{
		unsigned len = row.length(), i = 0, p = 0;
		while (row[p] != ':')
		{
			p++;
		}
		char username_check1[256];
		for (; i < p; i++)
		{
			username_check1[i] = row[i];
		}
		username_check1[p] = '\0';
		bool equel = true;
		unsigned len_name = strlen(name);
		if (len_name != p)
		{
			equel = false;
		}
		else {
			for (unsigned i = 0; i < p; i++)
			{
				if (username_check1[i] != name[i])
				{
					equel = false;
					break;
				}
			}
		}
		if (equel)
		{
			char read[] = "\\info.txt";
			char name_copy[256];
			strcpy(name_copy, name);
			strcat(name, read);
			ifstream get_info;
			get_info.open(name);
			int count;
			get_info >> count;
			count++;
			get_info.close();
			fstream change;
			change.open(name, fstream::out | fstream::trunc);
			change << count;
			change.close();
			char dir[256];
			strcpy(dir,create_directory(count,name_copy));
			ofstream topic_mess;
			topic_mess.open(dir);
			topic_mess <<remember_username <<endl<<topic << endl << message;
			topic_mess.close();
			cout << "The email has been sent." << endl;
			break;
		}
			
	}
	log.close();
}

void close_acc()
{
	cout << "confirm your password:";
	string entered_password,row;
	cin >> entered_password;
	hash<string> Password;
	entered_password = to_string(Password(entered_password));
	if (entered_password==remember_password)
	{
		ifstream users;
		ofstream users1;
		users.open("users.txt");
		users1.open("users1.txt", ofstream::app);
		while (users>>row)
		{
			if (row != remember_row)
				users1 << row << endl;

		}
		users.close();
		users1.close();
		remove("users.txt");
		rename("users1.txt", "users.txt");
		
		
		string a = "rmdir /s /q " + remember_username;
		system(a.c_str());
		
	}
	else
	{
		cout << "Wrong password!" << endl;
		return close_acc();
	}
}
void login()
{
	ifstream log;
	log.open("users.txt");
	string username_check, password_check,entered_user,entered_pass,row;
	cout << "username:";
	cin >> entered_user;
	cout << "password:";
	cin >> entered_pass;
	if (log.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	hash<string> Password;
	entered_pass = to_string(Password(entered_pass));
	bool happened = false; 
	while (log >> row) 
	{

		unsigned len = row.length(), i = 0, z = 0;
		unsigned  p = 0;
		while (row[p] != ':')
		{
			p++;
		}
		char* username_check1 = new char[p+1];
		char* password_check1 = new char[len-p];
		for (; i < p;i++ )
		{
			username_check1[i] = row[i];
		}
		username_check1[p] = '\0';
		i += 1;
		for (; i < len; i++)
		{
			password_check1[z] = row[i];
			z++;
		}
		password_check1[z] = '\0';
		
		if (username_check1 == entered_user && password_check1 == entered_pass) {
			cout << "user found!" << endl;
			happened = true;
			remember_row = row;
			remember_password = entered_pass;
			remember_username = entered_user;
			delete[] username_check1;
			delete[] password_check1;
			break;
		}
		delete[] username_check1;
		delete[] password_check1;
	}
	if (!happened)
	{
		system("cls");
		cout << "Your username or password is wrong" << endl;
		return login();
	}
}
bool check_username_registration(string& username)
{
	if (username[0]=='\0')
	{
		return true;
	}
	unsigned i = 0;
	while (username[i]!='\0')
	{
		if (username[i]<48|| (username[i] > 57 && username[i] < 65) || (username[i] > 90 && username[i] < 97)||username[i]>122)
		{
			return true;
		}
		i++;
	}
	if (i<6)
	{
		return true;
	}
	string row;
	ifstream log;
	log.open("users.txt");
	if (log.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	while (log >> row)
	{
		unsigned len = row.length(), i = 0, p = 0;
		while (row[p] != ':')
		{
			p++;
		}
		char* username_check1 = new char[p + 1];
		for (; i < p; i++)
		{
			username_check1[i] = row[i];
		}
		username_check1[p] = '\0';
		if (username==username_check1)
		{
			log.close();
			delete[] username_check1;
			cout << "This username is already taken. Please enter another one." << endl;
			return true;
		}
		delete[] username_check1;
	}
	log.close();
	return false;
}
string reg_pass(const string& user)
{
	cout << "username:"<<user<<endl;
	cout << "password:";
	string password1;
	cin >> password1;
	bool requirements = true;
	if (password1[0] == '\0')
	{
		requirements = false;
	}
	unsigned i = 0, counter_digits = 0,counter_little_letter=0,counter_large_letter=0, counter_sybols=0;
	while (password1[i] != '\0')
	{
		if (password1[i] >= 48 && password1[i] <= 57 )
		{
			counter_digits++;
		}
		else if (password1[i] >= 65 && password1[i] <= 90)
		{
			counter_large_letter++;
		}
		else if (password1[i] >= 97&& password1[i] <= 122)
		{
			counter_little_letter++;
		}
		else if (password1[i] == 38 || password1[i] == 42 || password1[i] == 60 || password1[i] == 62 || password1[i] == 63 || password1[i] == 46 || password1[i] == 43 || password1[i] == 45)
		{
			counter_sybols++;
		}
		else
		{
			requirements = false;
		}
		i++;
	}
	if (i < 6)
	{
		requirements = false;
	}
	if (counter_digits<1||counter_large_letter<1||counter_little_letter<1||counter_sybols<1)
	{
		requirements = false;
	}
	if (!requirements)
	{
		cout << "Incorrect data! Try again.." << endl;
		return reg_pass(user);
	}
	hash<string> hashedPassword;
	password1 = to_string(hashedPassword(password1));
	return password1;
}
void registration()
{
	ofstream username_and_pass;
	username_and_pass.open("users.txt", ofstream::app);
	string username1;
	cout << "username(a-z,0-9):";
	cin >> username1;
	if (check_username_registration(username1))
	{
		cout << "Incorrect data! Try again.." << endl;
		return registration();
	}
	char* user=new char[username1.size()+1];
	unsigned i = 0;
	while (username1[i]!='\0')
	{
		user[i] = username1[i];
		i++;
	}
	user[i] = '\0';

	createFolder(user);
	delete[] user;
	remember_password = reg_pass(username1);
	remember_username = username1;
	username_and_pass << username1 << ":" << remember_password<<"\n";
	username_and_pass.close();
}
void inside()
{
	ifstream my_dir;
	char after[] = "\\info.txt", direction[256];
	unsigned len = remember_username.length(), i = 0;
	for (; i < len; i++)
	{
		direction[i] = remember_username[i];
	}
	direction[i] = '\0';
	strcat(direction, after);
	my_dir.open(direction);
	int number, counter = 0;
	my_dir >> number;
	my_dir.close();
	cout << "You have " << number << " mails. Choose one of the following options:" << endl;
	cout << "C - close account\nI - inbox\nL - logout\nO - open\nS - send" << endl;
	char select;
	cin >> select;
	switch (select)
	{
	case 'C':
	case 'c':
		system("cls");
		close_acc();
		break;
	case 'I':
	case 'i':
		system("cls");
		inbox(number);
		return inside();
		break;
	case 'L':
	case 'l':
		system("cls");
		break;
	case 'O':
	case 'o':
		system("cls");
		open();
		return inside();
		break;
	case 'S':
	case's':
		system("cls");
		send();
		return inside();
		break;
	default:
		system("cls");
		cout << "Incorrect data! Try again.." << endl;
		return inside();
		break;
	}
	
}
void start()
{
	cout << "Select one of the following." << endl;
	cout << "L - login" << endl;
	cout << "R - register" << endl;
	cout << "Q - quit" << endl;
	char select;
	cin >> select;
	switch (select)
	{
	case 'L':
	case 'l':
		system("cls");
		login();
		inside();
		return start();
		break;
	case 'R':
	case 'r':
		system("cls");
		registration();
		inside();
		return start();
		break;
	case 'Q':
	case 'q':
		system("cls");
		quit= true;
		break;
	default:
		cout << "Incorrect data! Try again.." << endl;
		return start();
		break;
	}
}

int main()
{
	start();
	if (quit)
		return -1;
	return 0;
}