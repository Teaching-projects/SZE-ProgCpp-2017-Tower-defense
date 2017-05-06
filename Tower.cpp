#include "Tower.h"


Tower::Tower(std::string Type, int Range, int Damage, int RateOfFire, int x, int y){
	this->Type = Type;
	this->Range=Range;
	this->Damage=Damage;
	this->RateOfFire = RateOfFire;
	X=x;
	Y=y;
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

void Tower::kirajzol(int TOWER_UNIT) const{
	glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2i(X,Y);
		glVertex2i(X + TOWER_UNIT, Y);
		glVertex2i(X + TOWER_UNIT, Y + TOWER_UNIT);
		glVertex2i(X, Y + TOWER_UNIT);
	glEnd();
}

int Tower::getX() const{
	return X;
}

int Tower::loves(Enemy** e, int nulla){
	if (X - Range < (*e)->GetX() && (*e)->GetX() < X + Range && (*e)->getHealth()>0){
		if (nulla % RateOfFire == 0){		//nem a legjobb megoldás, mert itt az i változót adjuk át a mainbõl amit csak azért hagytunk ott hogy minden lefutásnál növeljük és itt minden 3. belépésnél (növelésnél) lõ
			(*e)->HpLower(getDamage());
		}
		return 1;
	}
}