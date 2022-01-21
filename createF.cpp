#include <iostream>
#include <cstring>
#include <direct.h>
#include <fstream>
#include "createF.h"
#pragma warning(disable : 4996)
using namespace std;
void createFolder(const char* username)
{
	char temp[256], add[256] = "\\", info[] = "\\info.txt";
	strcat(add, username);
	//cout << add<<endl;
	_getcwd(temp, 256);
	strcat(temp, add);
	//cout << "Current working directory: " << temp << endl;
	_mkdir(temp);
	strcat(temp, info);
	int num = 0;
	ofstream inf;
	inf.open(temp);
	inf << num;
	inf.close();
}