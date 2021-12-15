#include "object.h"
#include "hitbox.h"
#include "files.h"
#include "global.h"
using namespace std;



Object::Object(){
	x_crd = 0;
	y_crd = 0;
}
Object::~Object(){}

void Object::clean(){
	delete box;
}


Bullet::Bullet(float & x, float & y, int & Nangle ){
	x_crd = x;
	y_crd = y;
	angle = Nangle;
	done = 0;
	box = new Bullet_H();
	box->set(x_crd,y_crd);
}
Bullet::~Bullet(){}


void Bullet::draw()const{
   	glPushMatrix();
    glTranslatef(x_crd+12*cos(angle*3.14 / 180), y_crd+12*sin(angle*3.14 / 180), 0);
    glRotatef(angle - 90, 0, 0, 1);
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 0); glVertex2f(0, 10);
    glEnd();
   	glBegin(GL_LINES);
    glColor3f(0, 1, 1);
    glVertex2f(0, 10); glVertex2f(0, 9);
    glEnd();
    glPopMatrix();
}

void Bullet::move(){
	x_crd+=9*cos(angle*3.14 / 180);
    y_crd+=9*sin(angle*3.14 / 180);
    box->set(x_crd,y_crd);
    if(box->check_collision(all_objects) == 1){
    	done = 1;
    }

	if(x_crd > conf.getWidth() || x_crd < 0 || y_crd > conf.getHeight() || y_crd < 0){
		done = 1;
	} 
}

int Bullet::del(const int & x){
		return done;
}








Ship::Ship(){
	x_crd = conf.getWidth()/2;
	y_crd = conf.getHeight()/2;
	speed = 0;
	angle_ship = 0;
	as_timer = 0;
	moving_angle = 0;
	box = new Ship_H();
	box->set(x_crd,y_crd);
}

Ship::~Ship(){}

void Ship::draw()const{
   	glPushMatrix();
    glTranslatef(x_crd, y_crd, 0);
    glRotatef(angle_ship - 90, 0, 0, 1);
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 20);
    glVertex2f(10, -10);
    glVertex2f(0, 0);
    glVertex2f(-10, -10);
    glEnd();
    glPopMatrix();
}

void Ship::move(){
	if(as_timer > 0){
		if(attack_speed > 10000) attack_speed = 10000;
		as_timer-=attack_speed;
	} 
	x_crd+=speed*cos(moving_angle*3.14 / 180);
	y_crd+=speed*sin(moving_angle*3.14 / 180);
	if(x_crd > conf.getWidth()) x_crd-=conf.getWidth();
	if(x_crd < 0) x_crd+=conf.getWidth();
	if(y_crd > conf.getHeight()) y_crd-=conf.getHeight();
	if(y_crd < 0) y_crd+=conf.getHeight();
	box->set(x_crd,y_crd);

	if(box->check_collision(all_objects) == 1){
		system("clear");
		cout << "Ship destroyed\n\nYour score: " << score << endl;
		if(score > Get_TOP()) cout << "Best score!!!\n";
		cout << "\n\nPress R to restart\n";
		stop = true;
	}



	if(keys[0] == true){
		float force;
		int reverce;
		if(speed < max_speed) speed+=accel_speed;

		if(angle_ship - moving_angle > moving_angle - angle_ship){
			reverce=angle_ship - moving_angle;
		}
		else{
			reverce=moving_angle - angle_ship;
		}
		if(reverce < 0) reverce*=-1;
		if(reverce == 356) reverce = 4;
		if(reverce > 135 && reverce < 225 &&  keys[2] == false && keys[3] == false){
			if(reverce > 155 && reverce < 205 &&  keys[2] == false && keys[3] == false){
				speed-=accel_speed/2;
			}
			speed-=accel_speed;
		}

		if(moving_angle != angle_ship){
			force=angle_ship - moving_angle;
			force = tan(force*3.14/360);
			if(force > 0){
				if(reverce < 155 || reverce > 205) moving_angle+=4;
				if(angle_ship - moving_angle > moving_angle - angle_ship){
					force=angle_ship - moving_angle;
				}
				else{
					force=moving_angle - angle_ship;
				}
				force = sin(force*3.14/360);
				if(force > 0 ){
					if(!(moving_angle == 360 && angle_ship == 0)){
						speed/=1.07;
					}
				}

			}
			if(force < 0){
				if(reverce < 155 || reverce > 205) moving_angle-=4;
				if(angle_ship - moving_angle > moving_angle - angle_ship){
					force=angle_ship - moving_angle;
				}
				else{
					force=moving_angle - angle_ship;
				}
				force = sin(force*3.14/360);
				if(force > 0){
					if(!(moving_angle == -4 && angle_ship == 356)){
						speed/=1.07;
					}
				}
			}
		}
		if(speed < 1) moving_angle = angle_ship;
		moving_angle%=360;
		if(moving_angle == -4 ){
			moving_angle=356;	
		}
	}
	if(keys[1] == true) {
		 if(speed > 0) speed -= accel_speed;
		 if(speed < 0) speed = 0;

	}
	if(keys[2] == true){
		angle_ship+=4;
		angle_ship%=360;
	} 
	if(keys[3] == true)	{
		if(angle_ship == 0){
			angle_ship=356;	
		} 
		else{
			angle_ship-=4;
			angle_ship%=360;	
		}
	}
	if(keys[4] == true){
		if(as_timer <= 0){
			Bullet new_bullet(x_crd, y_crd, angle_ship);
			bullet_list.push_back(new_bullet);
			//cout << " ------------ ship fire\n";
			as_timer = 10000;
		}
	}	
}

int Ship::del(const int & x){
		return 0;
}











Asteroid::Asteroid(){
	active_bonus = 0;
	box = new Asteroid_H();
	asteroid_respawn();
}

Asteroid::~Asteroid(){}

void Asteroid::draw()const{

	if(active_bonus == 1) as_bon.draw();
	if(active_bonus == 2) sp_bon.draw();
	if(active_bonus == 0){	
		glPushMatrix();
	    glTranslatef(x_crd, y_crd, 0);
	    glColor3f(0.5, 0.5, 0.5);
	    glBegin(GL_QUADS);
	    glVertex2f(20, 20);
	    glVertex2f(-20, 20);
	    glVertex2f(-20, -20);
	    glVertex2f(20, -20);
	    glEnd();
	    glPopMatrix();
	}
}

void Asteroid::move(){
	if(active_bonus == 1){
		as_bon.move();
		if(as_bon.box->check_collision(all_objects) == 1){
			attack_speed += 500;
			active_bonus = 0;
			system("clear");
			cout << "Attack speed++" << endl;
		}
		if(as_bon.del() == 1) active_bonus = 0;
	} 
	if(active_bonus == 2){
		sp_bon.move();
		if(sp_bon.box->check_collision(all_objects) == 1){
			max_speed+=0.5;
			accel_speed+=0.1;
			active_bonus = 0;
			system("clear");
			cout << "Ship speed++" << endl;
		}
		if(sp_bon.del() == 1) active_bonus = 0;
	} 
	if(active_bonus == 0){	
		x_crd+=speed*cos(angle*3.14 / 180);
	    y_crd+=speed*sin(angle*3.14 / 180);
	    box->set(x_crd,y_crd);
	    if(box->check_collision(all_objects) == 1){
			done = 2;
		}
		if(x_crd > conf.getWidth()+30 || x_crd < -30 || y_crd > conf.getHeight()+30 || y_crd < -30){
			done = 3;
		} 
	}
}

void Asteroid::asteroid_respawn(){
	done = 0;
	speed = rand() % 2 + 1;
	int choose_side = rand() % 4;

	switch (choose_side){
		case 0:{	
			x_crd = rand() % conf.getWidth();
			y_crd = conf.getHeight()+20;
			angle = rand() % 180 + 180;
			break;
		}
		case 1:{
			x_crd = rand() % conf.getWidth();
			y_crd = -20;
			angle = rand() % 180;
			break;
		}
		case 2:{
			x_crd = -20;
			y_crd = rand() % conf.getHeight()+20;
			angle = rand() % 180 + 270;
			if(angle > 359) angle-=360;
			break;
		}
		case 3:{
			x_crd = conf.getWidth()+20;
			y_crd = rand() % conf.getHeight()+20;
			angle = rand() % 180 + 90;
			break;
		}
	}

	box->set(x_crd,y_crd);
}

int Asteroid::choose_bonus(){
	int x = rand() % 100;
	
	if(x < 80) return 0;
	if(x >= 80 && x < 90){
		as_bon.set(x_crd, y_crd);
		return 1;
	} 
	if(x >= 90 && x < 100){
		sp_bon.set(x_crd, y_crd);
		return 2;
	} 

	return -1;
}


int Asteroid::del(const int & x){
	if(x == 0)
		return done;
	if(x == 2){
		active_bonus = choose_bonus();
		asteroid_respawn();
		return -1;
	}
	if(x == 3){
		asteroid_respawn();
		return -1;
	}
	return -2;
}

void Asteroid::clean(){
	delete as_bon.box;
	delete sp_bon.box;
	delete box;
}









AS_Bonus::AS_Bonus(){
	box = new Bonus_H();
	set(0,0);
}

AS_Bonus::~AS_Bonus(){}

void AS_Bonus::draw()const{
   	glPushMatrix();
    glTranslatef(x_crd, y_crd, 0);
    glColor3f(1, 0.2, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-5, 20);
    glVertex2f(5, 20);
    glVertex2f(5, 5);
    glVertex2f(20, 5);
    glVertex2f(20, -5);
    glVertex2f(5, -5);
    glVertex2f(5, -20);
    glVertex2f(-5, -20);
    glVertex2f(-5, -5);
    glVertex2f(-20, -5);
    glVertex2f(-20, 5);
    glVertex2f(-5, 5);
    glEnd();
    glPopMatrix();
}

void AS_Bonus::move(){
	Life_time--;
	if(Life_time == 0){
		done = 1;
	}
}

int AS_Bonus::del(const int & x){
	return done;
}

void AS_Bonus::set(const float & x, const float & y){
	x_crd = x;
	y_crd = y;
	done = 0;
	Life_time = 250;
	box->set(x_crd,y_crd);
}








Speed_Bonus::Speed_Bonus(){
	box = new Bonus_H();
	set(0,0);
}
Speed_Bonus::~Speed_Bonus(){}

void Speed_Bonus::draw()const{
   	glPushMatrix();
    glTranslatef(x_crd, y_crd, 0);
    glColor3f(0, 0.2, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-5, 20);
    glVertex2f(5, 20);
    glVertex2f(5, 5);
    glVertex2f(20, 5);
    glVertex2f(20, -5);
    glVertex2f(5, -5);
    glVertex2f(5, -20);
    glVertex2f(-5, -20);
    glVertex2f(-5, -5);
    glVertex2f(-20, -5);
    glVertex2f(-20, 5);
    glVertex2f(-5, 5);
    glEnd();
    glPopMatrix();
}

void Speed_Bonus::move(){
	Life_time--;
	if(Life_time == 0){
		done = 1;
	}
}

int Speed_Bonus::del(const int & x){
	return done;
}

void Speed_Bonus::set(const float & x, const float & y){
	x_crd = x;
	y_crd = y;
	done = 0;
	Life_time = 250;
	box->set(x_crd,y_crd);
}