#ifndef GUI_CLASS_FOR_PLAYER_INPUT
#define GUI_CLASS_FOR_PLAYER_INPUT


#include "SFML/Graphics.hpp"
#include <iostream> // �������� ���� ���� ��������Դϴ�.
#include <string>

class Menu
{
	const int buttonSize = 200; // ��ư�� ũ�⸦ �����մϴ�.
	const int minimumScail = 100; // ������ ���� ���� ���� ũ�⸦ ���մϴ�.

	// ȭ���� �����ϱ� ���� offset�Դϴ�.
	int gridOffsetX; 
	int gridOffsetY;
	// ��ư�� ������ �����մϴ�.
	int numebrOfButtons;
	// �������� ũ�⸦ �����մϴ�.
	unsigned int width;
	unsigned int height;

	bool sortType; // true -> r����, false -> ����, ��ư���� ���� ����� �����մϴ�.


	sf::Vector2f intervalForDesign; // �������� ���� �����Դϴ�.
	sf::Font font; // ��Ʈ ���Դϴ�.
	sf::Text* buttons; // �ؽ�Ʈ�� �迭�Դϴ�.
	sf::RectangleShape* buttonSquare; // ������ �迭�Դϴ�.

public :
	Menu(unsigned int width, unsigned int height, int numebrOfButtons, std::string nameOfButtons[]);
	~Menu();
	
	void draw(sf::RenderWindow &windows); // window�� ��ư(����+�ؽ�Ʈ)�� �׸��ϴ�.
	void highLight(sf::Vector2i mousePosition); // ���콺�� ������ ������ ������ ���ڿ� �ؽ�Ʈ�� ������ �ٲߴϴ�.
	int getClickedButton(sf::Vector2i mousePosition); // Ŭ���� ���ڸ� ������ �ĺ��ڸ� ��ȯ�մϴ�.
	void setAlign( bool sortType); // ���� ��Ŀ� ���� �����մϴ�.
	void move(int gridPositionX, int gridPositionY); // direction�� ����(true)/�¿�(false) ����
	int getBottonline() { return gridOffsetY - 1; } // ����ϴ� y�� �ִ� grid���� ��ȯ�մϴ�.
	int getRightMostLine() { return gridOffsetX - 1; } // ����ϴ� x�� �ִ� grid���� ��ȯ�մϴ�.
	void setButtonString(std::string name, int button); // ���õ� ��ư�� �ؽ�Ʈ�� ��ȭ�մϴ�.
};

#endif