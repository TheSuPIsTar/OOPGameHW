#include "Card.h"

Card::Card() {
	// get cardset Image
	if (!cardImage.loadFromFile("Texture/turmpCardColorSet.png")) {
		std::cout << "Can't find the card Images" << std::endl;
		system("pause");
	}

	// get each of card size from card size.
	// this int values below are image dependent which means that according to image, the int values are diverse.
	cardSize = cardImage.getSize();
	cardSize.x /= 5;
	cardSize.y = cardSize.y/3;


	// get gridPosition of back of the card
	gridCardPosition[0] = sf::Vector2u(4, 2);

	// get gridPosition of each card(1~10)
	for (int y = 0, i = 1; y < 2; y++) {
		for (int x = 0; x < 5; x++) {
			gridCardPosition[i++] = sf::Vector2u(x, y);
		}
	}

	// set all card be usable;
	std::fill_n(usedCard, NUMBER_OF_TOTAL_CARD, true);

	// set random seed
	std::srand(std::time(NULL));
}

// 0~19������ ���ڸ� �����ϰ� ����� ����ϴ�.
int Card::getCard() {
	
	while (true) {
		int index = std::rand()%20;
		if (usedCard[index]) {
			usedCard[index] = false;
			return index;
		}
	}


	return -1;
}


// shape�� number�� �ش��ϴ� texture�� ���� window�� ����ݴϴ�.
void Card::showCard( sf::RectangleShape shape, sf::RenderWindow& window, int number){
	if (number%11 > 10 || number < -1) {
		std::cout << "Out of array range" << std::endl;
		return;
	}

	int gridposition;
	if (number == -1)
		gridposition = 0;
	else
		gridposition = number % 10 + 1;

	shape.setTexture(&cardImage, true);
	shape.setTextureRect(sf::IntRect(gridCardPosition[gridposition].x * cardSize.x,  gridCardPosition[gridposition].y * cardSize.y, cardSize.x, cardSize.y));
	window.draw(shape);
}

//ī�带 �� ��� �� �˻��ϰ� �ٽ����� �ٽ� ���� �� �ֵ��� ����ϴ�.
bool Card::checkUseAllAndThenReset() {
	for (int i = 0; i < NUMBER_OF_TOTAL_CARD; i++)
		if (usedCard[i]) return false;// �ϳ��� ī�������� ����

	for (int i = 0; i < NUMBER_OF_TOTAL_CARD; i++) //�ٽ����� �����·� ����.
		usedCard[i] = true;

	return true;
}