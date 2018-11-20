/*
* program name: Indian Poker Game
* program explanation: Implementing Indian PokerGame with SFML
*/

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Card.h"
#include "Player.h"
#include "Enemy.h"
using namespace sf;


int main(void) {
	// �÷��̾� ������ Ȯ�� 
	bool playerTurn = true;
	bool enemyTurn = false;

	// ���� ���� �ð�
	bool emotionTime = true;

	// ���� ����
	bool gameStart = false;
	bool gameOver = false;

	// �� ����
	bool TurnOver = false;
	bool TurnStart = false;
	bool TurnProceed = false;

	// �ǵ�����
	int bettedMoney = 0;
	int lastBettedMoney = 0;

	//������ ������ ����
	const int videoSizeX = 1280;
	const int videoSizeY = 800;
	RenderWindow window(VideoMode(videoSizeX, videoSizeY), "The Indian PokerGame!");
	
	// Menu for user input
	const int emotionsIndex = 4;
	const int bettingIndex = 5;
	std::string emotions[emotionsIndex] = { "Well...", "Good!", "OMG","idiot" };
	std::string betting[bettingIndex] = { "Die", "Call","Double", "Triple", "All IN" };
	
	RectangleShape enemyAlert(Vector2f(200.f, 150.f));
	enemyAlert.setFillColor(Color::Black);
	enemyAlert.setPosition(Vector2f(window.getSize().x * 1/7, window.getSize().y /2 - enemyAlert.getSize().y / 2));
	
	//���� �޴���
	std::string game[2] = {"Game\nStart", "Betted\nMoney"};
	Menu emotionAndBettingMoney(window.getSize().x, window.getSize().y, 2, game);
	emotionAndBettingMoney.setAlign(true);
	emotionAndBettingMoney.move(0, emotionAndBettingMoney.getBottonline() / 2);
	// �÷��̾� ������
	Menu menu(window.getSize().x, window.getSize().y, emotionsIndex, emotions);
	menu.setAlign(true); // true -> ��������
	menu.move(0, menu.getBottonline());
	Menu bettingMenu(window.getSize().x, window.getSize().y, bettingIndex, betting);
	bettingMenu.setAlign(true);
	bettingMenu.move(0, menu.getBottonline());

	//ī���

	Vector2f cardSize(150, 200);
	RectangleShape playerCard(cardSize);
	playerCard.setFillColor(Color::Black);
	playerCard.setPosition((window.getSize().x - cardSize.x)/2, window.getSize().y * 3 / 5);
	RectangleShape enemyCard(cardSize);
	enemyCard.setFillColor(Color::Black);
	enemyCard.setPosition(window.getSize().x / 2 - cardSize.x/2, 50.f);

	//���� �÷��̾� ������
	std::string enemyMoneyAndEmotions[2] = { "Left\nMoney: ", "Emotion:\n" };
	Menu enemyPanel(window.getSize().x, window.getSize().y, 2, enemyMoneyAndEmotions);
	enemyPanel.setAlign(true);
	//�÷��̾� ������
	RectangleShape playerMoney(Vector2f(200.f, 100.f));
	playerMoney.setFillColor(Color::Black);
	playerMoney.setPosition(window.getSize().x / 5, window.getSize().y * 3 / 4 - 30.f);
	Font font;
	font.loadFromFile("Font/NanumGothic.ttf");
	Text text;
	text.setFont(font);
	text.setString("Left\nMoney : ");
	text.setPosition(window.getSize().x / 5 + text.getCharacterSize(), window.getSize().y * 3 / 4 - 20.f);

	// Card class for manage card
	Card playDeck;

	Player player;
	Enemy enemy(emotions, emotionsIndex);


	Texture t1;
	t1.loadFromFile("Texture/Surprised-Baby.jpg");

	Texture board;
	board.loadFromFile("Texture/boardTexture.jpg");

	float lightSize = videoSizeY / 5;
	CircleShape tableLite(lightSize);
	tableLite.setFillColor(Color(255,255,255,20));
	tableLite.setPosition(Vector2f((videoSizeX - lightSize*2)/2,(videoSizeY - lightSize*2)/2));

	

	// window loop
	while (window.isOpen()) {

		Vector2i pos = Mouse::getPosition(window);

		

		if (gameStart) {
			TurnStart = true;
			gameStart = false;
		}

		if (TurnStart) {
			// draw card only when start game.
			TurnStart = false;

			//default betting
			player.loseMoney(1); // �ǵ�
			enemy.loseMoney(1); // �ǵ�
			bettedMoney = 2; // betted money �ʱ�ȭ
			lastBettedMoney = 1; // lastbettedmoney �ʱ�ȭ

			//get the card for player
			int card = playDeck.getCard();
			player.setCardNumber(card);


			//get the card for enemy
			card = playDeck.getCard();
			enemy.setCardNumber(card);

			if (playerTurn)
				emotionAndBettingMoney.setButtonString("Player\nTurn", 0);
			enemy.updateWhanTurnStart();
		
			enemyPanel.setButtonString(enemyMoneyAndEmotions[1] + enemy.getEmotion(), 1);
		}

		// update panel
		text.setString("Left\nMoney: " + std::to_string(player.getLeftMoney()));
		enemyPanel.setButtonString(enemyMoneyAndEmotions[0] + std::to_string(enemy.getLeftMoney()), 0);
		

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					//game start
					if (!gameStart&&emotionAndBettingMoney.getClickedButton(pos) == 0) {
						gameStart = true;
					}
					
					// player betting
					if (TurnProceed && playerTurn && !emotionTime && !gameStart) {
						playerTurn = false;

						switch (bettingMenu.getClickedButton(pos))
						{
						case 0:
							lastBettedMoney = 0;
							TurnOver = true;
							TurnProceed = false;
							break;
						case 1:
							TurnOver = true;
							TurnProceed = false;
							break;
						case 2:
							lastBettedMoney *= 2;
						case 3:
							lastBettedMoney += 3;
						default:
							break;
						}
						lastBettedMoney = player.betting(lastBettedMoney);
						bettedMoney += lastBettedMoney;
						emotionAndBettingMoney.setButtonString("Enemy\nTurn", 0);
					}

					// player emotion
					if (menu.getClickedButton(pos) != -1 && emotionTime && playerTurn && !gameStart) {
						enemy.setEmotion(menu.getClickedButton(pos));
						emotionTime = false;
						TurnProceed = true;
					}
				}

			}
		}

		if (enemyTurn) {
			enemyTurn = false;
			lastBettedMoney = enemy.betting(lastBettedMoney);
			std::cout << lastBettedMoney << std::endl;
			emotionAndBettingMoney.setButtonString("Player\nTurn", 0);
			bettedMoney += lastBettedMoney;

			if (lastBettedMoney == 0)
				TurnOver = true;

			sleep(Time(seconds(1)));
			playerTurn = true;
		}

		if (!playerTurn) {
			enemyTurn = true;
		}
	
		emotionAndBettingMoney.setButtonString(game[1] + " : " + std::to_string(bettedMoney), 1);

	
		if (TurnOver) { // turn end
			TurnStart = true;
			emotionTime = true;
			enemy.updateWhenTurnEnd(playerTurn, player.getCardNumber());
			emotionAndBettingMoney.setButtonString("Turn\nEnded", 0);

			if (playerTurn) { //player win
				player.earnMoney(bettedMoney);
			}
			else
				enemy.earnMoney(bettedMoney);

			// ī�� �ٽ����� �ٽ� ��ο�
			if (playDeck.checkUseAll()) {
				enemy.resetCard();
			}

			if (enemy.isAllin() || enemy.isAllin()) {
				std::string winner;
				if (playerTurn)
					winner = "player";
				else
					winner = "enemy";
				emotionAndBettingMoney.setButtonString(winner + " win! ", 0);


				gameOver = true;
			}
		}
		
		// update panel
		text.setString("Left\nMoney: "+std::to_string(player.getLeftMoney()));
		enemyPanel.setButtonString(enemyMoneyAndEmotions[0] + std::to_string(enemy.getLeftMoney()), 0);

		window.clear(Color(150, 75, 0));
		window.draw(enemyCard);
		window.draw(tableLite);

		
		if (gameStart)
			emotionAndBettingMoney.highLight(pos);
		else {
			menu.highLight(pos);
			bettingMenu.highLight(pos);
			emotionAndBettingMoney.setOnBlack(0, true);
		}


		emotionAndBettingMoney.draw(window);
		enemyPanel.draw(window);


		window.draw(playerMoney);
		window.draw(text);
		window.draw(playerCard);


		if (emotionTime) {
			menu.draw(window);
		}
		else {
			bettingMenu.draw(window); 
		}


		window.display();

		if (TurnOver) {
			TurnOver = false;
			sleep(Time(seconds(1)));
		}
		if (gameOver) {
			sleep(Time(seconds(1)));
			playerTurn = true; // false�� enemyTurn�޴� ģ���� true�� ����� ������.
			enemyTurn = false;
			TurnProceed = false;
			emotionTime = true; // false�� playerTurn�� ���۵Ǿ� ������.
			gameStart = false; // ����� ��ư �Է��� �ޱ������Դϴ�.
			gameOver = false;
			TurnStart = false;

			emotionAndBettingMoney.setButtonString("RESTART", 0);
		}
	}
}