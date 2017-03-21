#include "Enemy.h"

Enemy::Enemy(std::string name, int hp, int speed, int gold){
	Name = name;
	Hp = hp;
	Speed = speed;
	Gold = gold;
}
std::string Enemy::getName() const{
	return Name;
}
int Enemy::getHealth() const{
	return Hp;
}
int Enemy::getSpeed() const{
	return Speed;
}
int Enemy::getGold() const{
	return Gold;
}
void Enemy::HpLower(int value){
	Hp -= value;
}