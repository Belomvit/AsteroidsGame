#ifndef G
#define G

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

#include "object.h"
#include "files.h"

using namespace std;

extern std::vector<Object*> all_objects;
extern std::vector<Bullet> bullet_list;
extern Config conf;
extern std::vector<bool> keys;
extern int Win_id;
extern int attack_speed;
extern float max_speed;
extern float accel_speed;
extern int score;
extern bool stop;





#endif /*G*/