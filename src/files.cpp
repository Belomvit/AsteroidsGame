#include "object.h"
#include "hitbox.h"
#include "files.h"
#include "global.h"

using namespace std;


Config::Config(){
	width_str = "width= ";
	height_str = "height= ";
	start_aseroids_str = "asteroids_at_start= "; 
}

bool Config::readConfig(){
	char sym;
	ifstream fileIn ("examples/config", ios::in|ios::binary);
  	if (!fileIn.is_open()){
   		return false;
  	}
  	stringstream word;
  	stringstream cislo;
	while (1){
	    fileIn.read(&sym, 1);
	    word << sym;
	    if(sym == ' '){
	    	fileIn.read(&sym, 1);
	    	fileIn.read(&sym, 1);
	    	while (sym != '"'){
	    		cislo << sym;
	    		fileIn.read(&sym, 1);
	    	}
	    	fileIn.read(&sym, 1);

	    	int ok = 0;
	    	if(word.str() == width_str) {cislo >> width; ok=1;}
	    	if(word.str() == height_str) {cislo >> height;ok=1;}
	    	if(word.str() == start_aseroids_str) {cislo >> start_aseroids;ok=1;}
	    	if(ok == 0) return false;
	    	

	    	word.str(""); word.clear();
	    	cislo.str(""); cislo.clear();
	    }

	    if (fileIn.eof()){  
	       break;
	    }
	}
	fileIn.close();
	return true;
}

int Config::getHeight() {return height;}
int Config::getWidth() {return width;}
int Config::getAsteroids_max() {return start_aseroids;}




int Get_TOP(){
	ifstream fileIn ("examples/Top_score", ios::in|ios::binary);
  	if (!fileIn.is_open()){
   		return -1;
  	}
  	char sym;
  	stringstream top;
  	int top_score;
  	while(1){
	    fileIn.read(&sym, 1);
	    top << sym;

	    if (fileIn.eof()){  
	 	    break;
	    }
  	}
  	fileIn.close();
  	top >> top_score;
  	top_score/=10;
  	top.str(""); top.clear();
  	return top_score;
}


bool Write_TOP(){
	ofstream myfile;
	myfile.open("Top_score");
  	if (!myfile.is_open()){
   		return false;
  	}
  	stringstream top;

  	top << score;
  	myfile << top.str();
  	myfile.close();
  	top.str(""); top.clear();
  	return true;
}
