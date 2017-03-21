#include "Game.h"

Game::Game(int money, int lifePoints){
	Money = money;
	LifePoints = lifePoints;
	ActualWave = 0;
	PreparingTime = true;
}

int Game::getMoney() const{
	return Money;
}
int Game::getLifePoints() const{
	return LifePoints;
}
int Game::getActualWave() const{
	return ActualWave;
}
bool Game::getPreparingTime(){
	return PreparingTime;
}

void Game::setMoney(int money){
	Money = money;
}
void Game::LifePointsDecrase(){
	LifePoints--;
}
void Game::WaveIncrease(){
	ActualWave++;
}
void Game::PrepTimeChange(){
	if(getPreparingTime() == true){
		PreparingTime = false;
	}
	else{
		PreparingTime = true;
	}
}