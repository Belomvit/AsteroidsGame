#include "global.h"

std::vector<Object*> all_objects;
Config conf;
std::vector<bool> keys;
int Win_id;
std::vector<Bullet> bullet_list;
int attack_speed = 500;
float max_speed = 2;
float accel_speed = 0.1;
int score = 0;
bool stop = false;