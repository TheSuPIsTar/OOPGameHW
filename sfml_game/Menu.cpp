#include "Menu.h"

// Menu ������. ������ â�� ũ��� ������ ��ư�� ����, ��ư�� �������� ��ư�� ����
// ��ư�� ���η� ���ĵǴ� ���� default�̴�. 
Menu::Menu(unsigned int width, unsigned int height, int numebrOfButtons, std::string nameOfButtons[]){
	if (numebrOfButtons <= 0) { // ��ư�� �ȸ���Ÿ� �������� ������ŵ�ϴ�.
		std::cout << "Button must be more than 1" << std::endl;
		system("pause");
	}

	sortType = false;// ���� default
	
	buttons = new sf::Text[numebrOfButtons];
	buttonSquare = new sf::RectangleShape[numebrOfButtons];
	
	//ȭ���� �����մϴ�.
	gridOffsetX = width / minimumScail;
	gridOffsetY = height / minimumScail;
	
	this->width = width;
	this->height = height;


	if (!font.loadFromFile("Font/NanumGothic.ttf")) {
		std::cout << "Can't get the font file" << std::endl;
		system("pause");
	}

	int offsetX = width / gridOffsetX;
	int offsetY = height / (numebrOfButtons + 1) / 2; // ������ ���� �Ʒ��ʿ� ��ư�� �����մϴ�. ��ư ������ ���� ũ�Ⱑ �޶����� �ϹǷ� ��ư�� ���� + 1���� ������ ������ �и��մϴ�.

	intervalForDesign.x = (width - width/numebrOfButtons * (numebrOfButtons - 1) - buttonSize)/2;


	for (int i = 0; i < numebrOfButtons; i++) {
		sf::Vector2f temp(10.f, (offsetY + 10.f)*i + height / 2);
		buttons[i].setFont(font);
		buttons[i].setPosition(temp + sf::Vector2f(50.f, buttons[i].getCharacterSize()/2-5) );
		buttons[i].setString(nameOfButtons[i]);

		buttonSquare[i].setSize(sf::Vector2f(buttonSize, offsetY));
		buttonSquare[i].setFillColor(sf::Color::Black);
		buttonSquare[i].setPosition(temp);
		buttonSquare[i].setOutlineColor(sf::Color::Green); // ���߿� ���ð����� �� ǥ����.
	}

	this->numebrOfButtons = numebrOfButtons;
}

Menu::~Menu()
{
	delete[] buttons;
	delete[] buttonSquare;
}

void Menu::highLight(sf::Vector2i mousePosition) {

	// ���콺�� ��ư ���� �ö���� ���� ��ȯ�մϴ�.
	// ���콺�� ���� ������ ������ ������� �ٽ� ��ȯ�մϴ�.
	for (int i = 0; i < numebrOfButtons; i++) {
		if (buttonSquare[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
			buttons[i].setFillColor(sf::Color::Black);
			buttonSquare[i].setFillColor(sf::Color::White);
		}
		else {
			buttons[i].setFillColor(sf::Color::White);
			buttonSquare[i].setFillColor(sf::Color::Black);
		}
	}
}

// ��ư���� �׸��ϴ�.
void Menu::draw(sf::RenderWindow &windows) {
	for (int i = 0; i < numebrOfButtons; i++) {
		windows.draw(buttonSquare[i]);
		windows.draw(buttons[i]);
	}
}

//Ŭ���� ��ư�� ����ϴ�.
int Menu::getClickedButton(sf::Vector2i mousePosition) {
	for (int i = 0; i < numebrOfButtons; i++) {
		if (buttonSquare[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			return i;
	}
	return -1;
}

// ������ �ٽ� ���ִ� �Լ�. ���� ���� �����߿� ������ �� �ִ�.
void Menu::setAlign(bool sortType) { // sortType == false => ����/ true => ����
	
	int offsetX = width / (numebrOfButtons);
	int offsetY = height/2 / (numebrOfButtons+1);
	sf::Vector2f temp(10.f, 10.f);

	for (int i = 0; i < numebrOfButtons; i++) {
		if (sortType)
			temp.x = offsetX * i + intervalForDesign.x;
		else
			temp.y = (offsetY + 10.f)*i + height / 2;

	
		buttons[i].setPosition(temp + sf::Vector2f(20.f,20.f));//+sf::Vector2f(50.f, offsetY / 2 - buttons[i].getCharacterSize() / 2 - 5));
		
		buttonSquare[i].setPosition(temp);
	}
}

//offset ������ ���� �Լ�. ��ü�� ��ġ�� �̵��Ѵ�.
void Menu::move(int gridPositionX,int gridPositionY) {

	sf::Vector2f position;
	if (gridPositionY >= this->gridOffsetY) {
		std::cout << "can't not move" << std::endl;
		return;
	}
	position.y = height / this->gridOffsetY * gridPositionY;

	if (gridPositionX >= this->gridOffsetX) {
		std::cout << "can't not move" << std::endl;
		return;
	}
	position.x = width / gridOffsetX * gridPositionX;

	for (int i = 0; i < numebrOfButtons; i++) {
		buttons[i].setPosition(buttons[i].getPosition() + position);
		buttonSquare[i].setPosition(buttonSquare[i].getPosition() + position);
	}
}

void Menu::setButtonString(std::string name, int button) {
	buttons[button].setString(name);
}
