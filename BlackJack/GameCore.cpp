#include "GameCore.h"

using namespace GameCore;

void Hand::CleanHand() {
	m_cards.clear();
	points = 0;
}

void Hand::AddCardToHand(Card* cardType, bool isPlayer) {
	short _chosenScore{ 0 };

	m_cards.push_back(cardType->name);

	if (cardType->name == "ACE") {
		if (isPlayer)
		{
			do {
				std::cout << "\nYou picked an ACE! Choose a score between 1-11: ";
				std::cin >> _chosenScore;

				cardType->points = _chosenScore;
			} while (_chosenScore > 11 || _chosenScore < 1);
		}
		else
		{
			_chosenScore = MAX_WIN_SCORE - points;
			_chosenScore = _chosenScore > 11 ? 11 : _chosenScore;
			cardType->points = _chosenScore;
		}
	}

	points += cardType->points;
}

void Hand::ReadHand() const {
	std::cout << "Money: " << money << "$\n";
	std::cout << "-----Your Hand-----\n\n";

	if (m_cards.size() == 0) {
		std::cout << "You hand is empty\n";
	}
	else {
		for (unsigned short i{ 0 }; i < m_cards.size(); i++) {
			std::cout << m_cards[i] << '\n';
		}
	}

	std::cout << "\nScore: " << points << "\n-------------------\n\n";
}

////////////////////////////////////////////////////////////////////////////////////////////

// made my own little, handy and simple shuffle function
void Deck::Shuffle(const size_t* size) {
	for (size_t i{ 0 }; i < *size; i++)
	{
		int _randomNumber = rand() % *size;
		Card _replaceCard = cards[i];

		cards[i] = cards[_randomNumber];
		cards[_randomNumber] = _replaceCard;
	}

	// Did not manage to make this work...
	//auto _randomGeneration = std::default_random_engine{};
	//std::random_shuffle(cards.begin(), cards.end(), _randomGeneration);
}

void Deck::RemoveCard(const size_t offset) {
	cards.erase(cards.begin() + offset - 1, cards.begin() + offset);
}