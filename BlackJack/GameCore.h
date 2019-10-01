#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
//#include <algorithm>
//#include <random>

namespace GameCore {
	const short MAX_WIN_SCORE{ 21 };

	struct Card {
		std::string name{ "" };
		int points{ 0 };
	};

	class Deck
	{
	public:
		std::vector<Card> cards
		{
			{"ACE", 0},
			{"TWO", 2},
			{"THREE", 3},
			{"FOUR", 4},
			{"FIVE", 5},
			{"SIX", 6},
			{"SEVEN", 7},
			{"EIGHT", 8},
			{"NINE", 9},
			{"TEN", 10},
			{"KNIGHT", 10},
			{"QUEEN", 10},
			{"KING", 10}
		};

		//Deck();
		//~Deck();

		void Shuffle(const size_t* size);
		void RemoveCard(const size_t offset);
	};

	class Hand {
	public:
		unsigned int points{ 0 }, money{ 100 };

		//Hand();
		//~Hand();
		void CleanHand();
		void ReadHand() const;
		void AddCardToHand(Card* cardType, bool isPlayer = true);
	private:
		std::vector<std::string> m_cards;
	};
}

/*#include <vector>

enum CARD {
	//EMPTY,
	ACE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	KNIGHT,
	QUEEN,
	KING
};

enum CARD_VARIANT {
	SPADE,
	DIAMOND,
	HEART,
	CLUB
};

class Deck {
public:
	void RemoveCard();

private:
	CARD m_cardTypes[4];
};

class Hand {
public:
	void PickCard();
	void ReadHand() const;

private:
	std::vector<int> m_cards;
};*/
