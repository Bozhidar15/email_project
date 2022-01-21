#include <iostream>
#include <string>
#include <cstring>
#include "createDir.h"
#pragma warning(disable : 4996)
using namespace std;
char* create_directory(int number, char* name)
{
	char txt[] = ".txt", digit[256], middle[] = "\\";
	string tmp = to_string(number);
	char const* num_char = tmp.c_str();
	strcpy(digit, num_char);
	digit[strlen(digit)] = '\0';
	strcat(digit, txt);
	strcat(name, middle);
	strcat(name, digit);
	return name;
}