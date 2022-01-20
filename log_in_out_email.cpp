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

void reverse(unsigned &number)
{
	unsigned number2=0;
	while (number)
	{
		(number2 *= 10) += (number % 10);
		number /= 10;
	}
	number = number2;
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
			//log.close();
			//delete[] username_check1;
			char read[]= "\\info.txt",name_copy[256];
			strcpy(name_copy, name);
			strcat(name, read);
			ifstream get_info;
			get_info.open(name);
			unsigned count;
			get_info >> count;
			count++;
			get_info.close();
			fstream change;
			change.open(name, fstream::out | fstream::trunc);
			change << count;
			change.close();
			char number_file[256],txt[]=".txt",middle[]="\\";
			string tmp = to_string(count);
			char const* num_char = tmp.c_str();
			cout << num_char << endl;
			strcpy(number_file,num_char);
			unsigned needed_len = strlen(number_file);
			number_file[needed_len] = '\0';
			cout << number_file<<endl;
			strcat(number_file,txt);
			strcat(name_copy,middle);
			strcat(name_copy,number_file);
			ofstream topic_mess;
			topic_mess.open(name_copy);
			topic_mess << topic << endl << message;
			topic_mess.close();
			cout << "The email has been sent." << endl;
		}
			
	}
	log.close();
}
void createFolder(const char* username)
{
	char temp[256], add[256] = "\\",info[]="\\info.txt";
	strcat(add, username);
	//cout << add<<endl;
	_getcwd(temp, 256);
	strcat(temp, add);
	//cout << "Current working directory: " << temp << endl;
	_mkdir(temp);
	strcat(temp, info);
	ofstream inf;
	inf.open(temp);
	inf << 0;
	inf.close();
	
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
		//return start();
		break;
	case 'O':
	case 'o':
		system("cls");
		break;
	case 'S':
	case's':
		system("cls");
		send();
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
		break;
	case 'R':
	case 'r':
		system("cls");
		registration();
		inside();
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
	//inside();
	return 0;
}