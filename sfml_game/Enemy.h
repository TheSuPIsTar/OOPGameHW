#pragma once
#include "Player.h"
#include <string>
#include <cstdlib>

class Enemy : public Player
{
private:
	int* emotionsWeight; // ������ �� ������ ���� ����ġ
	int* emotionsType; // ������ Ÿ��
	int numberOfEmotions; // ���� ������ ��
	bool usedCard[20]; // true -> �Ⱦ�, false -> ��
	int numberOfUsedCard = 0; // ����� ī��
	float counting(); // ���� ���ڵ��� ������ �̱� Ȯ���� ����մϴ�.
	int winRate; // �̱� Ȯ���Դϴ�.
	int chooseOne = 0; // ������ ������ ������ ��ȯ�մϴ�.

	std::string* emotions; // ������ �����Դϴ�.

public:
	Enemy(std::string emotions[], int numberOfEmotions = 0);
	~Enemy();
	virtual int betting(int money) override;
	void setEmotion(int emotionType);
	void updateWhanTurnStart(); // �� �����Ҷ� ī�� ���ڸ� ���� �̱� Ȯ���� ����մϴ�.
	void updateWhenTurnEnd(bool win, int enemyCardNumber);// �� ���� ���������� ���п��θ� ����Ͽ� ����� �մϴ�. 
	virtual void reset() override; // ������ �ٽ� �����Ҷ� �ʱ�ȭ�մϴ�.
	std::string getEmotion(); // ������ ������ �����մϴ�.
	void resetCard(); // ī������ ���� ī�带 reset�մϴ�.
	std::string getChoosesString(); // ������ ������ ���� ���� ������ ��ȯ�մϴ�.
	int getChooses() { // ������ ������ ��ȯ�մϴ�.
		return chooseOne;
	}
};

