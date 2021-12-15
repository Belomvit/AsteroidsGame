#include "object.h"
#include "hitbox.h"
#include "files.h"
#include "global.h"


using namespace std;

void crd::set(const float & x, const float & y){
	x_crd = x;	
	y_crd = y;	
}

int Hitbox::getID()const{
	return id;
}
Hitbox::~Hitbox(){}

int Hitbox::getHit()const{
	return ImHit;
}

void Hitbox::setHit(const int x){
	ImHit = x;
}

Ship_H::Ship_H(){
	id = 0;
	ImHit = 0;
}

Ship_H::~Ship_H(){}

int Ship_H::check_collision(const vector<Object*> & v){
	for (unsigned int i = 0; i < v.size(); ++i){
		if(v[i]->box->id == 2){
			int crossX=0;
			int crossY=0;


			if(v[i]->box->L_up.x_crd > L_up.x_crd && v[i]->box->L_up.x_crd < R_up.x_crd ) crossX++;
			if(v[i]->box->R_up.x_crd > L_up.x_crd && v[i]->box->R_up.x_crd < R_up.x_crd ) crossX++;
			
			if(v[i]->box->L_up.y_crd < L_up.y_crd && v[i]->box->L_up.y_crd > L_down.y_crd ) crossY++;
			if(v[i]->box->L_down.y_crd < L_up.y_crd && v[i]->box->L_down.y_crd > L_down.y_crd ) crossY++;

			if(crossX > 0 && crossY > 0){
				return 1;
			}
		}
	}
	return 0;
}

void Ship_H::set(const float & x, const float & y){
	L_up.set(x-10, y+10);
	L_down.set(x-10, y-10);
	R_up.set(x+10, y+10);
	R_down.set(x+10, y-10);
}


Asteroid_H::Asteroid_H(){
	ImHit = 0;
	id = 2;
}
Asteroid_H::~Asteroid_H(){}

int Asteroid_H::check_collision(const vector<Object*> & v){
	if(getHit() == 1){
		setHit(0);
		return 1;
	}
	return 0;
}

void Asteroid_H::set(const float & x, const float & y){
	L_up.set(x-20, y+20);
	L_down.set(x-20, y-20);
	R_up.set(x+20, y+20);
	R_down.set(x+20, y-20);
}


Bullet_H::Bullet_H(){
	id = 1;
	ImHit = 0;
}
Bullet_H::~Bullet_H(){}

int Bullet_H::check_collision(const vector<Object*> & v){
	for (unsigned int i = 0; i < v.size(); ++i){
		if(v[i]->box->id == 2){
			int crossX=0;
			int crossY=0;
			if(point.x_crd > v[i]->box->L_down.x_crd && point.x_crd < v[i]->box->R_down.x_crd) crossX++;
			
			if(point.y_crd > v[i]->box->R_down.y_crd && point.y_crd < v[i]->box->R_up.y_crd) crossY++;
			
			if(crossX > 0 && crossY > 0){
				v[i]->box->setHit(1);
				score+=100;
				system("clear");
				cout << "Score: " << score << endl;
				if(score % 200 == 0){
					Object *as = new Asteroid;
					all_objects.push_back(as);
				}
				return 1;
			}
		}
	}
	return 0;
}

void Bullet_H::set(const float & x, const float & y){
	point.set(x,y);
}




Bonus_H::Bonus_H(){
	id = 3;
	ImHit = 0;
}
Bonus_H::~Bonus_H(){}

int Bonus_H::check_collision(const vector<Object*> & v){
	for (unsigned int i = 0; i < v.size(); ++i){
		if(v[i]->box->id == 0){
			int crossX=0;
			int crossY=0;
			if(v[i]->box->L_up.x_crd > L_up.x_crd && v[i]->box->L_up.x_crd < R_up.x_crd ) crossX++;
			if(v[i]->box->R_up.x_crd > L_up.x_crd && v[i]->box->R_up.x_crd < R_up.x_crd ) crossX++;
			
			if(v[i]->box->L_up.y_crd < L_up.y_crd && v[i]->box->L_up.y_crd > L_down.y_crd ) crossY++;
			if(v[i]->box->L_down.y_crd < L_up.y_crd && v[i]->box->L_down.y_crd > L_down.y_crd ) crossY++;
			
			if(crossX > 0 && crossY > 0){
				return 1;
			}
		}
	}
	return 0;
}

void Bonus_H::set(const float & x, const float & y){
	L_up.set(x-20, y+20);
	L_down.set(x-20, y-20);
	R_up.set(x+20, y+20);
	R_down.set(x+20, y-20);
}