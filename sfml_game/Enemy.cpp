#include "Enemy.h"
#include <algorithm>

float Enemy::counting() {
	usedCard[viewCard] = false;
	
	int numberOfCardThatLargerThanViewCard = 0;
	for (int i = 0; i < viewCard%10; i++) {
		if (usedCard[i])
			numberOfCardThatLargerThanViewCard++;

		if (usedCard[i + 10])
			numberOfCardThatLargerThanViewCard++;
	}

	return (float)numberOfCardThatLargerThanViewCard /(20-numberOfUsedCard) * 100; // ���ų� ū ī�� �� / ���� ī���
}

Enemy::Enemy(std::string emotions[], int numberOfEmotions)
{
	this->numberOfEmotions = numberOfEmotions;

	emotionsWeight = new int[numberOfEmotions];
	emotionsType = new int[numberOfEmotions];
	this->emotions = new std::string[numberOfEmotions];

	for (int i = 0; i < numberOfEmotions; i++) 
		this->emotions[i] = emotions[i];
	

	std::fill_n(usedCard, 20, true);
	std::srand(std::time(NULL)); // ���� ������ ���� �õ尪�� �־��ݴϴ�.
}


Enemy::~Enemy()
{
	delete[] emotionsWeight;
	delete[] emotionsType;
}

int Enemy::betting(int money) {
	int bettingMoney = 0;
	chooseOne = 0;

	//1���� ������ �̱�ų� ���.
	if (viewCard % 10 + 1 == 1) {
		bettingMoney = money * 3;
		bettingMoney = this->loseMoney(bettingMoney);
		chooseOne = 3;
		return bettingMoney;
	}

	if (winRate > 90) {
		bettingMoney = money;
		chooseOne = 4;
	}
	else if (winRate > 80) {
		bettingMoney = money * 3;
		chooseOne = 3;
	}
	else if (winRate > 70) {
		bettingMoney = money * 2;
		chooseOne = 2;
	}
	else if (winRate > 50) {
		bettingMoney = money;
		chooseOne = 1;
	}

	// ����ġ 
	winRate += rand() % 2 * 10;

	bettingMoney = this->loseMoney(bettingMoney); // All in ���� �Ǵ�
	return bettingMoney;
}

void Enemy::setEmotion(int emotionType) {
	emotionsType[emotionType]++;
}

void Enemy::updateWhanTurnStart() {
	winRate = counting();
	for (int i = 0; i < numberOfEmotions; i++)
		winRate -= emotionsWeight[i];
}

void Enemy::updateWhenTurnEnd(const bool win, int enemyCardNumber) {
	int type;
	if (win)
		type = 1;
	else
		type = -1;

	for (int i = 0; i < numberOfEmotions; i++) 
		emotionsWeight[i] += emotionsType[i] * type;

	usedCard[enemyCardNumber] = false;

	numberOfUsedCard += 2;
}

std::string Enemy::getEmotion() {

	
	return emotions[rand()%numberOfEmotions];
}

void Enemy::resetCard() {
	for (int i = 0; i < 20; i++) {
		usedCard[i] = true;
	}
}

void Enemy::reset() {
	for (int i = 0; i < 20; i++)
		usedCard[i] = true;
	numberOfUsedCard = 0;
	Player::reset();
}

std::string Enemy::getChoosesString() { // 5���� �ϵ��� �ߴµ� ��ġ���� �ٰ��ľ� �Ǽ� Ȯ�强�� ���� �Լ��Դϴ�.
	switch (chooseOne) {
	case 4:
		return "Well...";
	case 3:
		return "Go Triple";
	case 2:
		return "Go double";
	case 1:
		return "Call";
	default:
		return "Die";
	}
}