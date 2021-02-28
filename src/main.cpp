#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <string.h>
#include <windows.h>

DIR *pdir = NULL;
struct dirent *pent = NULL;
int items_count = 0;
bool items_count_bool = true;
std::string _pent[300] = {};
std::string path_history[50] = {};
int path_h_index = 0;
std::string path = "";
std::string stringa = "";
int _index = 0;
char input = 'x';
int index = 0;

void print() {
	system("CLS");
	for(int _index = 0; _index < sizeof(_pent)/sizeof(*_pent); _index++) {
		if(_pent[_index] == "") continue;
		if(items_count_bool) items_count++;
		
		stringa += "  " + _pent[_index] + "\n";
	}

	std::cout << "Current Path:    " << path_history[path_h_index] << "\n\n";
	std::cout << stringa;
}

void resetScrolling(int y) {
	COORD dwCursorPosition = {0, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), dwCursorPosition);
}

void readDirectory(std::string _dir) {
	if(_dir == "/..") {
		path_h_index--;
		pdir=opendir(path_history[path_h_index].c_str());
	} else {
		path_h_index++;
		path_history[path_h_index] = path_history[path_h_index-1] + _dir;
		pdir=opendir(path_history[path_h_index].c_str());
	}
	int i = 0;
	for(int _i = 0; _i < sizeof(_pent)/sizeof(*_pent); _i++) {
		_pent[_i] = "";
	}
	while ((pent=readdir(pdir))){
		_pent[i] = pent->d_name;
		i++;
	}
	items_count = 0;
	items_count_bool = true;
	closedir(pdir);
}

int main() {
	path_history[0] = "";
	readDirectory("C:/");

	print();
	resetScrolling(0);

	while(input != 'q') {
		stringa = "";
		_index = 0;
		if((int) input == 13 || (int) input == 77) {
			readDirectory("/"+_pent[index]);
			print();
			resetScrolling(0);
			index = 0;
		} else if ((int) input == 75) {
			readDirectory("/..");
			print();
			resetScrolling(0);
			index = 0;
		}else if( input == 'H') {
			if(index == 0) {
				index = items_count-1;
			} else index--;
		}
		else if( input == 'P') {
			if(index == items_count-1) {
				index = 0;
				resetScrolling(0);
			} else index++;
		}
		
		
		if (!pdir){
			std::cout << "opendir() failure; terminating";
			exit(1);
		}
			
		resetScrolling(index+2);
		input = getch();
		items_count_bool = false;
	}
}
