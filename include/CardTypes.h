/**
 * \file CardTypes.h
 * \author Shivam Taneja
 * \brief All the types of cards and constants required
 */
#ifndef A3_CARD_TYPES_H_
#define A3_CARD_TYPES_H_

using namespace std;
#include <utility>

/**
 * \brief Describes the rank of a card.
 */
typedef unsigned short int RankT;


/**
 * \brief RankT for an Ace.
 */
#define ACE    1

/**
 * \brief RankT for an Jack.
 */
#define JACK   11

/**
 * \brief RankT for a Queen.
 */
#define QUEEN  12

/**
 * \brief RankT for a King.
 */
#define KING   13

/**
 * \brief total number of cards
 */
const int TOTAL_CARDS = 104;

/**
 * \brief  Describes the Category of where the card is. 
 */
enum CategoryT
{
	Tableau,
	Foundation,
	Deck,
	Waste
};

/**
 * \brief  Describes the suit of the card. 
 */
enum SuitT
{
	Heart = 0,
	Diamond,
	Club,
	Spade
};

/**
 * \brief Describes the number of the card. 
 */
struct CardT
{
/**
 * \brief first component of playing card (Suit or color)
 */
	SuitT s;

	/**
 * \brief second component of playing card (Number 1-13)
 */
	RankT r;
} ;

#endif
