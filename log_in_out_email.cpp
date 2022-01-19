#include <iostream>
#include <cstring>
#include <string>
#include <functional>
#include <fstream>
#include <vector>
#include <direct.h>
#include <filesystem>
#pragma warning(disable : 4996)
using namespace std;

string remember_password,remember_username,remember_row;
bool quit = false;
void send()
{
	
}
void createFolder(const char* username)
{
	char temp[256], add[] = "/";
	strcat(add, username);
	_getcwd(temp, 256);
	strcat(temp, add);
	//cout << "Current working directory: " << temp << endl;
	_mkdir(temp);
	
}
void close_acc()
{
	//da se iztriqt vsichi failove
	cout << "confirm your password:";
	string entered_password,row;
	cin >> entered_password;
	
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
		
	}
	else
	{
		cout << "Wrong password!" << endl;
		return close_acc();
	}
}
void login()
{
	//username.eof()- end of file
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
	bool happened = false; 
	while (log >> row) 
	{

		unsigned len = row.length(), i = 0, z = 0;
		unsigned  p = 0;
		while (row[p] != ':')
		{
			p++;
		}
		//unsigned formassive1 = p + 1,formassive2=len-p;
		char* username_check1 = new char[p+1];
		char* password_check1 = new char[len-p];
		for (; i < p;i++ )//for (; i < len ;i++ )
		{
			//username_check[i] = row[i];
			username_check1[i] = row[i];
			/*if (row[i+1] == ':')
			{
				break;
			}*/
		}
		username_check1[p] = '\0';
		i += 1;
		//cout << username_check1;
		for (; i < len; i++)
		{
			//password_check[z] = row[i];
			password_check1[z] = row[i];
			z++;
		}
		password_check1[z] = '\0';
		//cout << password_check1;
		if (username_check1 == entered_user && password_check1 == entered_pass) {//if (username_check == entered_user && password_check == entered_pass) {
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
	//system("cls");
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
	remember_password = reg_pass(username1);
	remember_username = username1;
	username_and_pass << username1 << ":" << remember_password<<"\n";

	username_and_pass.close();
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
		break;
	case 'R':
	case 'r':
		system("cls");
		registration();
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
void inside()
{
	cout << "You have " << "X" << " mails. Choose one of the following options:" << endl;
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
		
		break;
	case 'L':
	case 'l':
		system("cls");
		return start();
		break;
	case 'O':
	case 'o':
		system("cls");
		break;
	case 'S':
	case's':
		system("cls");
		break;
	default:
		system("cls");
		cout << "Incorrect data! Try again.." << endl;
		return inside();
		break;
	}
}

int main()
{
	start();
	if (quit)
		return -1;
	inside();
	return 0;
}