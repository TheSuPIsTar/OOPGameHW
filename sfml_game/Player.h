#ifndef PLAYER_CLASS_FOR_USER_AND_ENEMY
#define PLAYER_CLASS_FOR_USER_AND_ENEMY
#include <SFML/Graphics.hpp>

class Player
{
protected:
	int money = 20; // ���� 20���� �����ϴ�.
	int viewCard = 0; // ���� �ִ� ī���, ����� ī���Դϴ�.
	bool isAll_In = false; //���� ���θ� �����ϴ�.

public:
	Player();
	~Player();
	int loseMoney(int money); // ���ÿ��� �������� �ƴ��� �Ǻ��� ���� ���Ǿ� boolŸ�� �Դϴ�.
	void earnMoney(int money); //���� ���մϴ�.
	virtual int betting(int money); //�����մϴ�.
	void setCardNumber(int viewCard); //�ڽ��� �����ִ� ī�带 �����մϴ�.
	virtual void reset(); // ���� �ٽ� ������ �� �ʱ�ȭ�մϴ�.
	int getCardNumber(); // �ڽ��� �����ִ� ī�带 ��ȯ�մϴ�.
	int getLeftMoney(); // �ڽ��� ���� ������ �ִ� ���� ��ȯ�մϴ�.
	bool isAllin(); //���ο��θ� ��ȯ�մϴ�.
};

#endif
