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

// ������ �������� Ȯ���մϴ�.
bool isGameEnd(int playerLeftMoney, int enemyLeftMoney, bool draw) {
	if ((playerLeftMoney == 0 || enemyLeftMoney == 0) && !draw)
		return true;

	return false;
}

int main(void) {
	// �÷��̾� ������ Ȯ�� 
	bool playerTurn = true;
	bool enemyTurn = false;
	
	//�̱�� Ȯ��
	bool playerWin;

	// ���� ���� �ð�
	bool emotionTime = true;

	// ���� ����
	bool gameStart = false;
	bool gameOver = false;
	bool drew = false;

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

	// ���� ���۽� �޴�
	Font font;
	font.loadFromFile("Font/NanumGothic.ttf");
	Text gameStartInfo; // ���� ���� ������
	gameStartInfo.setFont(font);
	gameStartInfo.setString("1 vs 1\nIndian Poker");
	gameStartInfo.setCharacterSize(100);
	gameStartInfo.setPosition(300, 200 );
	Text whoWin;
	whoWin.setFont(font);
	whoWin.setString("Result: NoBody win");
	whoWin.setCharacterSize(50);
	whoWin.setPosition(400,450);
	std::string gameMenu[2] = { "Game\nStart", "Exit" };
	Menu gameStartMenu(window.getSize().x, window.getSize().y, 2, gameMenu);//���� ���� �Ǵ� ���� ���� ����
	gameStartMenu.setAlign(false);
	gameStartMenu.move(gameStartMenu.getRightMostLine() - 2, 0);

	//���� �޴���
	std::string game[2] = { "Game\nStart", "Betted\nMoney" };
	Menu emotionAndBettingMoney(window.getSize().x, window.getSize().y, 2, game);
	emotionAndBettingMoney.setAlign(true);
	emotionAndBettingMoney.move(0, emotionAndBettingMoney.getBottonline() / 2);

	// �÷��̾� ������
	const int emotionsIndex = 4;
	const int bettingIndex = 5;
	std::string emotions[emotionsIndex] = { "Well...", "Good!", "OMG","idiot" };
	std::string betting[bettingIndex] = { "Die", "Call","Double", "Triple", "All IN" };
	Menu menu(window.getSize().x, window.getSize().y, emotionsIndex, emotions);
	menu.setAlign(true); // true -> ��������
	menu.move(0, menu.getBottonline());
	Menu bettingMenu(window.getSize().x, window.getSize().y, bettingIndex, betting);
	bettingMenu.setAlign(true);
	bettingMenu.move(0, menu.getBottonline());

	//ī�� �����ֱ� ���� ����
	Vector2f cardSize(150, 200);
	RectangleShape playerCard(cardSize);
	playerCard.setPosition((window.getSize().x - cardSize.x)/2, window.getSize().y * 3 / 5);
	RectangleShape enemyCard(cardSize);
	enemyCard.setPosition(window.getSize().x / 2 - cardSize.x/2, 50.f);

	//���� �÷��̾� ������
	std::string enemyMoneyAndEmotions[2] = { "Left\nMoney: ", "Emotion:\n" };
	Menu enemyPanel(window.getSize().x, window.getSize().y, 2, enemyMoneyAndEmotions);
	enemyPanel.setAlign(true);
	//����� ���� ���� �˷��ִ� ����.
	RectangleShape enemyChoose(Vector2f(200, 100));
	enemyChoose.setFillColor(Color::Black);
	enemyChoose.setPosition(window.getSize().x - 210, 10 );
	Text enemyChooseOne;
	enemyChooseOne.setFont(font);
	enemyChooseOne.setString("Bet Call:\nnothing");
	enemyChooseOne.setPosition(window.getSize().x - 200, 20 );

	//�÷��̾� ������ - ���� �� ǥ��
	RectangleShape playerMoney(Vector2f(200.f, 100.f));
	playerMoney.setFillColor(Color::Black);
	playerMoney.setPosition(window.getSize().x / 5, window.getSize().y * 3 / 4 - 30.f);
	Text text;
	text.setFont(font);// ���� ���� �޴����� ������.
	text.setString("Left\nMoney : ");
	text.setPosition(window.getSize().x / 5 + text.getCharacterSize(), window.getSize().y * 3 / 4 - 20.f);

	// Card class for manage card
	Card playDeck;

	// �÷��̾�� enemy ����
	Player player;
	Enemy enemy(emotions, emotionsIndex);

	// ���̺� ����
	float lightSize = videoSizeY / 5;
	CircleShape tableLite(lightSize);
	tableLite.setFillColor(Color(255,255,255,20));
	tableLite.setPosition(Vector2f((videoSizeX - lightSize*2)/2,(videoSizeY - lightSize*2)/2));
		



	// window loop
	while (window.isOpen()) {

		Vector2i pos = Mouse::getPosition(window);// ���콺 ��ġ�� �� �ݺ�Ƚ������ Ȯ���� �ؾ��մϴ�.


		if (TurnStart) { //�� �����Ҷ� �� �ʱ�ȭ
			// draw card only when start game.
			TurnStart = false;

			//default betting
			if (!drew) { // ��������� �ʱ�ȭ���� �ʽ��ϴ�.
				player.loseMoney(1); // �ǵ�
				enemy.loseMoney(1); // �ǵ�
				bettedMoney = 2; // betted money �ʱ�ȭ
				lastBettedMoney = 1; // lastbettedmoney �ʱ�ȭ
			}
			else
				drew = false;

			//get the card for player
			int card = playDeck.getCard();
			player.setCardNumber(card);

			//get the card for enemy
			card = playDeck.getCard();
			enemy.setCardNumber(card);

			if (playerTurn)
				emotionAndBettingMoney.setButtonString("Player\nTurn", 0);
			enemy.updateWhanTurnStart();

			// enemy���� �г� �ʱ�ȭ
			enemyPanel.setButtonString(enemyMoneyAndEmotions[1] + enemy.getEmotion(), 1);
		}

		// update panel
		text.setString("Left\nMoney: " + std::to_string(player.getLeftMoney()));
		enemyPanel.setButtonString(enemyMoneyAndEmotions[0] + std::to_string(enemy.getLeftMoney()), 0);

		Event event;

		if (player.isAllin()) { // �����̸� �Է� �ȹ޽��ϴ�.
			TurnOver = true;
		}
		else {
			while (window.pollEvent(event) && !player.isAllin()) { // playerinput �� �����մϴ�. player�� ���������� �Է� �ȹ޽��ϴ�.
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.mouseButton.button == Mouse::Left) {
						//game start
						if (!gameStart&&gameStartMenu.getClickedButton(pos) != -1) { // ���� ���� �Ǵ� ������
							if (gameStartMenu.getClickedButton(pos) == 0) {
								TurnStart = true;
								gameStart = true;
							}
							else if (gameStartMenu.getClickedButton(pos) == 1)
								return 0;
						}
						if (gameStart) { // ������ ���۵Ǿ����� �÷��̾��� �Է��� ��ٸ��ϴ�.
							// player betting
							if (TurnProceed && playerTurn && !emotionTime) {
								playerTurn = false; // �ϱ�ü

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
									break;
								case 3:
									lastBettedMoney *= 3;
									break;
								case 4:
									lastBettedMoney = player.getLeftMoney();
									break;
								default:
									break;
								}
								lastBettedMoney = player.betting(lastBettedMoney);
								bettedMoney += lastBettedMoney;
								emotionAndBettingMoney.setButtonString("Enemy\nTurn", 0);
							}

							// player emotion
							if (menu.getClickedButton(pos) != -1 && emotionTime && playerTurn) {
								enemy.setEmotion(menu.getClickedButton(pos));
								emotionTime = false;
								TurnProceed = true;
							}
						}
					}
				}
			}
		}


		if (enemyTurn) { // ������Դϴ�.
			enemyTurn = false;
			if (!enemy.isAllin()) {
				lastBettedMoney = enemy.betting(lastBettedMoney);
				emotionAndBettingMoney.setButtonString("Player\nTurn", 0);
				enemyChooseOne.setString("Bet Call:\n"+ enemy.getChoosesString());
				bettedMoney += lastBettedMoney;
				if (enemy.getChooses() == 0 || enemy.getChooses() == 1)
					TurnOver = true;
				sleep(Time(seconds(1))); // ����� ������ �������̶�� ���� �˷��ֱ� ���� ��� �����带 ����ϴ�.
				playerTurn = true;
			}
			else {
				TurnOver = true;
				lastBettedMoney = -1;
			}
		}

		if (!playerTurn)//�ϱ�ü, �ڽ��� ������ ȭ���� ����ֱ� ���� �ʿ��մϴ�.
			enemyTurn = true;
	
		// panel update
		emotionAndBettingMoney.setButtonString(game[1] + " : " + std::to_string(bettedMoney), 1);
		text.setString("Left\nMoney: " + std::to_string(player.getLeftMoney()));
		enemyPanel.setButtonString(enemyMoneyAndEmotions[0] + std::to_string(enemy.getLeftMoney()), 0);
		

		if (TurnOver) { // ���� ������ �������� �غ��մϴ�.
			TurnOver = false;
			TurnStart = true;
			emotionTime = true;
			playerWin = false;
			
			if (playDeck.checkUseAllAndThenReset())
				enemy.resetCard();

			if (player.getCardNumber()%10+1 == enemy.getCardNumber()%10+1) 
				drew = true;
			else if(player.getCardNumber()%10+1 > enemy.getCardNumber()%10+1)
				playerWin = false;// ��ȣ ��.(player�� ���� �ִ� ī�尡 ����� ī���̹Ƿ�.
			else
				playerWin = true;

			// die �����ϸ� ������ ���� ���̰� �׷��� lastbettedMoney�� 0�̴�.
			if (lastBettedMoney == 0) {
				playerWin = playerTurn;// �÷��̾� ���� �ƴϸ� �÷��̾ �̱�̴ϴ�.

				// 10�λ��¿��� die�ϸ� �� ����� �̱������� 10���� �߰��� �־�� �Ѵ�.
				if (player.getCardNumber() % 10 + 1 == 10 && playerWin) { // �÷��̾ ���� �ִ� ī�尡 ��� ī���̹Ƿ�.
					enemy.loseMoney(10);
					bettedMoney += 10;
				}
				else if (enemy.getCardNumber() % 10 + 1 == 10 && !playerWin) {
					player.loseMoney(10);
					bettedMoney += 10;
				}
			}

			if(!drew)
				enemy.updateWhenTurnEnd(!playerWin, player.getCardNumber());// ���п� ������ ī���� ���� �Ѱ� ����. �÷��̾� �� = ��� �̱�.
			emotionAndBettingMoney.setButtonString("Turn\nEnded", 0);

			if(drew) // ���� �� ����.
				emotionAndBettingMoney.setButtonString("Drew", 0);
			else if (playerWin)// �̱� ������� ����.
				player.earnMoney(bettedMoney);
			else
				enemy.earnMoney(bettedMoney);

			playDeck.showCard(playerCard, window, enemy.getCardNumber());
			window.draw(enemyChoose);
			window.draw(enemyChooseOne);

			window.display(); // ���� ī�� Ȯ�� �����ٶ�� �߽��ϴ�.
			sleep(Time(seconds(2)));

			if (isGameEnd(player.getLeftMoney(), enemy.getLeftMoney(), drew)) {// ������ �������� ���� �̰������ �Բ� �ٽ� ������ ������ Ȯ���ϱ� ���� ȭ���� ���ϴ�.
				if (playerWin)
					whoWin.setString("Result: Player Win");
				else
					whoWin.setString("Result: Enemy Win");
				player.reset();
				enemy.reset();
				emotionTime = true;
				playerTurn = true;
				enemyTurn = false;
				gameStart = false;
				gameOver = false;
				drew = false;
				TurnOver = false;
				TurnStart = false;
				TurnProceed = false;

				enemyChooseOne.setString("Bet Call:\nnothing");
			}
		}

		if (!gameStart) { // ���۽� ȭ���� ���ϴ�.
			window.clear(Color::Black);
			window.draw(gameStartInfo);
			window.draw(whoWin);
			gameStartMenu.draw(window);
			gameStartMenu.highLight(pos);
		}
		else {
			//�� ���
			window.clear(Color(150, 75, 0));
			window.draw(tableLite);

			//�÷��̾� �޴� ��
			if(emotionTime) // ���� ���� ǥ���� �����´�.
				menu.draw(window);
			else
				bettingMenu.draw(window);
			menu.highLight(pos);
			bettingMenu.highLight(pos);

			//���� ��Ȳ �� ��� �޴���
			emotionAndBettingMoney.draw(window);
			enemyPanel.draw(window);
			window.draw(enemyChoose);
			window.draw(enemyChooseOne);

			//�÷��̾� ���� ��
			window.draw(playerMoney);
			window.draw(text);
			if(!TurnOver) // ��ǥ������ �����ݴϴ�.
				playDeck.showCard(playerCard, window, -1); // -1�϶��� ��ǥ�� ������.
			
			playDeck.showCard(enemyCard, window, player.getCardNumber());
		}

		//������ ȭ�鿡 ���ϴ�.
		window.display();
	}
}