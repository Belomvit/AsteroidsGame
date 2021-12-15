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
#include <GL/glut.h>


#include "object.h"
#include "hitbox.h"
#include "files.h"
#include "global.h"



using namespace std;



void display(){
	if(!stop){
		glClear(GL_COLOR_BUFFER_BIT);
		for (unsigned int i = 0; i < bullet_list.size(); ++i){
			bullet_list[i].move();
			bullet_list[i].draw();	
			if(bullet_list[i].del() == 1){
				bullet_list[i].clean();
				bullet_list.erase(bullet_list.begin()+i); 
			}
		}

		for(unsigned int i = 0; i < all_objects.size(); i++){
			all_objects[i]->move();
			all_objects[i]->draw();
			if(all_objects[i]->del() == 2){
				all_objects[i]->del(2);
			}
			if(all_objects[i]->del() == 3)
				all_objects[i]->del(3);
		}
		glFlush();
	}
}


void keyDown(int key, int a, int b)
{
	
    switch (key){
	    case GLUT_KEY_UP:
	        keys[0] = true;
	        break;
	    case GLUT_KEY_DOWN:
	        keys[1] = true;
	        break;
	    case GLUT_KEY_LEFT:
			keys[2] = true;
	        break;
	    case GLUT_KEY_RIGHT:
	        keys[3] = true;
	        break;
    }
}

void keyUp(int key, int a, int b)
{
    switch (key){
	    case GLUT_KEY_UP:
	        keys[0] = false;
	        break;
	    case GLUT_KEY_DOWN:
	        keys[1] = false;
	        break;
	    case GLUT_KEY_LEFT:
	        keys[2] = false;
	        break;
	    case GLUT_KEY_RIGHT:
	        keys[3] = false;
	        break;
    }
}


void Game_start(){
	system("clear");
	cout << "^\n|       - Speed-up ship\n\n";
	cout << "|       - Slow-down ship\nv\n\n";
	cout << "<-  ->  - Turn ship\n\n";
	cout << "Space   - Fire\n\n";
	cout << "Q       - Exit\n\n";
	cout << "R       - Restart\n\n";
	if(Get_TOP() == -1){
		exit(1);
	}
	cout << "Max score: " << Get_TOP() << endl;

	Object *shp = new Ship();
	all_objects.push_back(shp);

	for (int i = 0; i < conf.getAsteroids_max(); ++i){
		Object *as = new Asteroid;
		all_objects.push_back(as);
	}
}

void Game_reset(){
	if(Get_TOP() == -1){
		Game_reset();
		exit(1);
	}
	if(score > Get_TOP()){
		if( !Write_TOP() ){
			Game_reset();
			exit(1);
		}
	}

	for(unsigned int i = 0; i < all_objects.size(); i++){
		all_objects[i]->clean();
		delete all_objects[i];
	}
	for(unsigned int i = 0; i < bullet_list.size(); i++){
		bullet_list[i].clean();
	}
	all_objects.erase(all_objects.begin(), all_objects.end());
	bullet_list.erase(bullet_list.begin(), bullet_list.end());
	attack_speed = 500;
	max_speed = 3;
	accel_speed = 0.2;
	score = 0;
	stop = false;
}


void otherKeysDown(unsigned char key, int a, int b){
	switch (key){	
		case ' ':
			keys[4] = true;
	        break;
	    case 'r':
	    	Game_reset();
	    	Game_start();
	    	break;

	    case 'q':
			glutDestroyWindow(Win_id);
			Game_reset();
	    	exit(0);
	    	
	    	break;
	}
}


void otherKeysUp(unsigned char key, int a, int b){
	switch (key){
		case ' ':
			keys[4] = false;
	        break;	
	}
}



void timer(int = 0){
	display();
	glutTimerFunc(20,timer,0);
}




int main(int argc, char  **argv)
{
  	if(! conf.readConfig()){
  		cout << "Config error\n";
  		return 1;
  	}
	keys.resize(6,false);

  	
	Game_start();

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(conf.getWidth(), conf.getHeight());
	Win_id = glutCreateWindow("Game");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,conf.getWidth(),0,conf.getHeight());
	glutDisplayFunc(display);
    glutSpecialUpFunc(keyUp);
	glutSpecialFunc(keyDown);
    glutKeyboardFunc(otherKeysDown);
    glutKeyboardUpFunc(otherKeysUp);
	glutTimerFunc(20,timer,0);

	glutMainLoop();

	
	return 0;
}