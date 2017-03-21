#include "Tower.h"

Tower::Tower(std::string Type, int Range, int Damage, int RateOfFire){
	Type = Type;
	Range=Range;
	Damage=Damage;
	RateOfFire = RateOfFire;
}

int Tower::getRateOfFire() const{
	return RateOfFire;
}
std::string Tower::getType() const {
	return Type;
}
int Tower::getRange() const{
	return Range;
}
int Tower::getDamage() const{
	return Damage;
}