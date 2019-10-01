#include <amp_graphics.h>
#include "GameCore.h"

using namespace GameCore;

const short DECK_LENGTH{ 4 };

enum CARD_TYPE {
	CLUB,
	DIAMOND,
	SPADE,
	HEART
};

int main()
{
	

	Deck deck[DECK_LENGTH];
	Hand player, house;

	int moneyBet{ 0 };
	size_t deckSize{ 0 };
	bool gameLoop{ true }, endTurn{ false };

	srand(static_cast<unsigned int>(time(NULL)));

	for (int i{ 0 }; i < DECK_LENGTH; i++)
	{
		deck[i].Shuffle(&deckSize);
	}

	while (gameLoop)
	{
		player.CleanHand();
		house.CleanHand();
		moneyBet = 0;

		deckSize = deck[0].cards.size();

		do {
			system("cls");

			player.ReadHand();

			std::cout << "Betting money: " << moneyBet << "$\n\n";

			std::cout << "Pick a card	[ a ]\nBet a Sum	[ s ]\nEnd Your Turn	[ d ]\n";

			int _moduel = rand() % 4;

			switch (_getch())
			{
			case 'a':
				// add and remove cards
				player.AddCardToHand(&deck[_moduel].cards[0]);
				deck[_moduel].RemoveCard(1);
				break;
			case 's':
				// bet a sum
				std::cout << "Bet a sum of money: ";
				std::cin >> moneyBet;
				break;
			case 'd':
				// end your turn
				endTurn = true;
				break;
			default:
				break;
			}
		} while (!endTurn);

		endTurn = false;

		system("cls");

		if (player.points > MAX_WIN_SCORE)
		{
			std::cout << "____________________________________________________\n\n"
				"\\   /   ---   |   |       |       ---    ---    ----\n"
				" \\ /   |   |  |   |       |      |   |  |      |\n"
				"  |    |   |  |   |       |      |   |   ---   |--\n"
				"  |    |   |  |   |       |      |   |      |  |\n"
				"  |     ---    ---         ----   ---    ---    ----\n"
				"____________________________________________________\n\n";
		}
		else {
			player.ReadHand();

			std::cout << "The House is picking . . .\n\n";

			while (house.points < player.points)
			{
				size_t _randomGeneration = rand() % (deck[0].cards.size() - 1) + 1;

				//std::cout << deck[0].cards.size() << " | " << _randomGeneration << '\n';

				house.AddCardToHand(&deck[0].cards[_randomGeneration], false);
				deck[0].RemoveCard(_randomGeneration);
			}

			if (house.points > MAX_WIN_SCORE || house.points < player.points) {
				// player wins
				std::cout << "Player Wins\n";
				player.money += moneyBet;
			}
			else if (house.points == player.points)
			{
				// tied game
				std::cout << "It is a tie\n";
			}
			else
			{
				// House wins
				std::cout << "House Wins\n";
				house.money += moneyBet;
				player.money -= moneyBet;
			}

			std::cout << house.points << '\n';
		}

		char answer{ 'y' };

		std::cout << "       Do you want to play again? [ y / n ] (10$) ";
		std::cin >> answer;

		switch (answer)
		{
		case 'Y':
		case 'y':
			if (player.money < 10) {
				system("cls");
				std::cout << "You do not have enough money to enter, ";
				system("pause");
				return 0;
			}

			player.money -= 10;

			break;
		case 'N':
		case 'n':
			gameLoop = false;
			break;
		default:
			break;
		}
	}

	return 0;
}

/*#include <iostream>
#include <conio.h>
#include <vector>

enum CARD {
	//EMPTY,
	ACE = 1,
	TWO = 2,
	THREE = 3,
	FOUR = 4,
	FIVE = 5,
	SIX = 6,
	SEVEN = 7,
	EIGHT = 8,
	NINE = 9,
	TEN = 10,
	KNIGHT = 11,
	QUEEN = 12,
	KING = 13
};

enum CARD_VARIANT {
	SPADE,
	DIAMOND,
	HEART,
	CLUB
};

class Deck {
public:
	CARD cardTypes;

	void RemoveCard() {
	
	}

private:
	
};

class Hand {
public:
	void PickCard() {
	
	}
	void ReadHand() const {
		
	}

private:
	std::vector<int> m_cards;
};

int main() {
	Deck deck;
	Hand player, house;

	do {
		std::cout << "Pick a card	[ a ]\nBet a Sum	[ s ]\nEnd Your Turn	[ d ]\n";

		switch (_getch())
		{
		case 'a':
			// pick a card
		case 's':
			// bet a sum
		case 'd':
			// end your turn
		default:
			break;
		}

		system("cls");
	} while (true);

	return 0;
}

#include <iostream>
#include <string>
#include <conio.h>
#include <vector>

enum KEY_TYPES {
	W = 119,
	S = 115,
	SPACE = 32,
	ESCAPE = 27
};

class Menu {
	struct Button {
		std::string name{ "" };
		short idTrigger{ 0 };
	};

	struct MenuItem {
		std::string name{ "" };
		std::vector<std::string> subName;
	};

public:
	short currentMenuEntry{ 0 }, subMenuEntry{ 0 };
	std::vector<MenuItem> items;
	std::vector<Button> buttons;

	void AssignMenuEntry(std::string mainName, std::vector<std::string> subNames) {
		MenuItem _newItem = { mainName, subNames };

		items.push_back(_newItem);
	}

	void AssignButton(std::string buttonName, int returnType = 0) {
		Button _newButton = { buttonName, returnType };

		buttons.push_back(_newButton);
	}

	// When the player goes below 0 in the menu start from the bottom (vise versa)
	void LimitSelection() {
		if (subMenuEntry < 0) {
			subMenuEntry = 0;
		}
		else if (subMenuEntry >= static_cast<short>(items.size())) {
			subMenuEntry = static_cast<short>(items.size() - 1);
		}

		if (currentMenuEntry < 0) {
			currentMenuEntry = static_cast<short>(items[subMenuEntry].subName.size() - 1);
		}
		else if (currentMenuEntry >= static_cast<short>(items[subMenuEntry].subName.size())) {
			currentMenuEntry = 0;
		}
	}

	void ChangeToSubMenu() {
		for (unsigned short i{ 0 }; i < items[subMenuEntry].subName.size(); i++)
		{
			if (items[subMenuEntry].subName[currentMenuEntry] == items[i].name)
			{
				subMenuEntry = i;
				break;
			}
		}
	}

	int DetectButton() {
		for (unsigned short i{ 0 }; i < items[subMenuEntry].subName.size(); i++)
		{
			if (buttons[i].name == items[subMenuEntry].subName[currentMenuEntry])
			{
				return buttons[i].idTrigger;
			}
		}

		return 0;
	}

	void DrawMenu() const {
		std::cout << "--------| " << items[subMenuEntry].name << " |--------\n\n";
		
		for (unsigned short i{ 0 }; i < items[subMenuEntry].subName.size(); i++)
		{
			std::cout << (char)9 << (i == currentMenuEntry ? "->" : "  ") << items[subMenuEntry].subName[i] << '\n';
		}
	}

private:
	
};

int main() {
	bool quitGame{ false };
	Menu* mainMenu = new Menu;

	// Create buttons and their submenus
	mainMenu->AssignMenuEntry("Main Menu", { "Singelplayer", "Multiplayer", "Options", "Credits", "Quit" });
	mainMenu->AssignMenuEntry("Singelplayer", { "Story Mode", "Normal Mode", "Return" });
	mainMenu->AssignMenuEntry("Multiplayer", { "Return" });

	// Create buttons and their asigned values
	mainMenu->AssignButton("Story Mode", 1);
	mainMenu->AssignButton("Normal Mode", 2);
	//mainMenu->AssignButton("Options", 3);
	//mainMenu->AssignButton("Options", 4);
	mainMenu->AssignButton("Credits", 5);

	mainMenu->AssignButton("Return", -1);
	mainMenu->AssignButton("Quit", -2);
	
	do {
		mainMenu->LimitSelection();
		mainMenu->DrawMenu();

		switch (_getch())
		{
		case KEY_TYPES::W:
			mainMenu->currentMenuEntry--;
			break;
		case KEY_TYPES::S:
			mainMenu->currentMenuEntry++;
			break;
		case KEY_TYPES::ESCAPE:
			mainMenu->subMenuEntry = mainMenu->currentMenuEntry = 0;
			break;
		case KEY_TYPES::SPACE:
			mainMenu->ChangeToSubMenu();

			std::cout << mainMenu->DetectButton();

			system("pause");

			switch (mainMenu->DetectButton())
			{
			case 0:
				break;
			case -2:
				quitGame = true;
				break;
			case -1:
				mainMenu->subMenuEntry = 0;
				break;
			case 1:
				// Start StoryMode Game
				break;
			default:
				break;
			}

			mainMenu->currentMenuEntry = 0;
			break;
		default:
			//quitGame = true;
			break;
		}

		system("cls");

	} while (!quitGame);

	delete mainMenu;

	return 0;
}*/
