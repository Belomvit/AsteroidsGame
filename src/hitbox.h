#ifndef HB1
#define HB1

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
class Object;
using namespace std;


///Coordinates (x,y)
class crd
{
public:
	void set(const float & x, const float & y);

	float x_crd, y_crd;
};


///Hitboxes for different objects
class Hitbox
{
public:
	virtual ~Hitbox();
	virtual int check_collision(const vector<Object*> & v) = 0;
	virtual void set(const float & x, const float & y) = 0;
	int getID()const;
	int getHit()const;
	void setHit(const int x);

	crd L_up, L_down, R_up, R_down;
	int id;
	int ImHit;
};


class Ship_H : public Hitbox
{
public:
	Ship_H();
	~Ship_H();
	int check_collision(const vector<Object*> & v);
	void set(const float & x, const float & y);


};

class Asteroid_H : public Hitbox
{
public:
	Asteroid_H();
	~Asteroid_H();
	int check_collision(const vector<Object*> & v);
	void set(const float & x, const float & y);
	

};

class Bullet_H : public Hitbox
{
public:
	Bullet_H();
	~Bullet_H();
	int check_collision(const vector<Object*> & v);
	void set(const float & x, const float & y);

	crd point;
};


class Bonus_H : public Hitbox
{
public:
	Bonus_H();
	~Bonus_H();
	int check_collision(const vector<Object*> & v);
	void set(const float & x, const float & y);
		
};


#endif /*HB1*/