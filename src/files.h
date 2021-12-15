#ifndef FILE
#define FILE

#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cerrno>
#include <cfenv>

using namespace std;



///Data from Config file
class Config
{
public:
	Config();

	bool readConfig();

	int getHeight();
	int getWidth();
	int getAsteroids_max();

private:
	int height;
	int width;
	int start_aseroids;
	string width_str;
	string height_str;
	string start_aseroids_str;
	
};


int Get_TOP();
bool Write_TOP();





#endif /*FILE*/