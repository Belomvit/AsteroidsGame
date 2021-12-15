#ifndef Objects1
#define Objects1


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

#include "hitbox.h"

using namespace std;


class Object
{
public:
	Object();
	virtual ~Object();
	virtual void draw() const = 0;
	virtual void move() = 0;
	virtual int del(const int & x = 0) = 0;
	virtual void clean();

	
	float x_crd,y_crd;
	Hitbox *box;
};


class Bullet : public Object
{
public: 
	Bullet(float & x, float & y, int & Nangle );
	~Bullet();
	void draw() const;
	void move();
	int del(const int & x = 0);

private:
	int angle;
	int done;
};


class Ship : public Object
{
public:
	Ship();
	~Ship();
	void draw() const;
	void move();
	int del(const int & x = 0);

private:
	int angle_ship;
	float speed;
	int moving_angle;
	int as_timer;
};


class AS_Bonus : public Object
{
public:
	AS_Bonus();
	~AS_Bonus();
	void draw() const;
	void move();
	int del(const int & x = 0 );
	void set(const float & x, const float & y);
	
	int Life_time;
	int done;
};



class Speed_Bonus : public Object
{
public:
	Speed_Bonus();
	~Speed_Bonus();
	void draw() const;
	void move();
	int del(const int & x = 0 );
	void set(const float & x, const float & y);

	int Life_time;
	int done;
};



class Asteroid : public Object
{
public:
	Asteroid();
	~Asteroid();
	void draw() const;
	void move();
	int del(const int & x = 0);
	void clean();
	
private:
	void asteroid_respawn();
	int choose_bonus();
	
	int angle;
	int done;
	int speed;
	int active_bonus;
	AS_Bonus as_bon;
	Speed_Bonus sp_bon;
};




#endif /*Objects1*/