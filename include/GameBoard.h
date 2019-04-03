/**
 * \file GameBoard.h
 * \author Shivam Taneja
 * \brief API and state variables of Board game ie the actual UI for user
 */
#ifndef A3_GAME_BOARD_H_
#define A3_GAME_BOARD_H_

#include <iostream>
#include <functional>
#include <vector>

#include "CardTypes.h"
#include "CardStack.h"
using std::vector;

/**
 *  \brief Class representing the GameBoard
 *  \details Includes four main components Tableau, Foundation, Deck, and Waste
 */
class BoardT{
private:

	vector<CardT> myvector{};

/**
 *  \brief Creates a vector of cardstack named T for Foundation
 */
	vector<CardStackT> T;

/**
 *  \brief Creates a vector of cardstack named F for Foundation
 */
	vector<CardStackT> F;

/**
 *  \brief Creates a vector of cardstack named D for Deck
 */	
	CardStackT D ;

/**
 *  \brief Creates a vector of cardstack named W for Deck
 */	
	CardStackT W ;

/**
 *  \brief checks if there are 104ccards in the T, F, D, W
 *  \param T The cards in the Tableau
 *  \param F The cards in the Foundation
 *  \param D The cards in the Deck
 *  \param W The cards in the Waste
 *  \return  true -> if there are 104 cards in the T, F, D, W
 */
     bool two_decks(vector<CardStackT> T, vector<CardStackT> F, CardStackT D, CardStackT W);

/**
 *  \brief checks if the card can be moved from one index of the tableau to another index of the tableau
 *  \param n0 The index to move the card from
 *  \param n1 The index to move the card to
 *  \return  true -> if the card can be moved,  else ->false 
 */
     bool valid_tab_tab(unsigned int n0, unsigned int n1);

/**
 *  \brief checks if the card can be moved from one index of the tableau to the foundation
 *  \param n0 The index to move the card from for the tableau
 *  \param n1 The index to move the card to for the foundation
 *  \return  true -> if the card can be moved,  else ->false 
 */
     bool valid_tab_foundation(unsigned int n0, unsigned int n1);

/**
 *  \brief checks if the card can be moved from the waste to the tableau
 *  \param n The index to move the card to for the tableau from the waste
 *  \return true->if the card can be moved,  else ->false 
 */
     bool valid_waste_tab(unsigned int n);

/**
 *  \brief checks if the card can be moved from the waste to the foundation
 *  \param n The index to move the card to for the foundation from the waste
 *  \return  true  -> if the card can be moved,  else ->false 
 */
     bool valid_waste_foundation(unsigned int n);

/**
 *  \brief checks if the card can be placed for the tableau
 *  \param c The card that will be moved from the tableau
 *  \param d The card that will have a card placed on it
 *  \return  true -> if the card can be moved,  else ->false 
 */
     bool tab_placeable(CardT c, CardT d);

/**
 *  \brief checks if the card can be placed for the foundation
 *  \param c The card that will be moved from the foundation
 *  \param d The card that will have a card placed on it
 *  \return  true ->  if the card can be moved,  else -> false 
 */
     bool foundation_placeable(CardT c, CardT d);

/**
 *  \brief checks if the card at the category is in a valid position
 *  \param c The category from CategoryT
 *  \param n Unsigned Integer corresponding to the location of the cards
 *  \return  true-> if its a valid position,  else -> false
 */
     bool is_valid_pos(CategoryT c, unsigned int n);

/**
 *  \brief counts of cards in T that matches the condition f
 *  \param T The cards in the Tableau or Foundation
 *  \param f lambda expression that should filter the counting 
 *  \return number of cards in the T
 */
     unsigned int cnt_cards_seq(std::vector<CardStackT> T, std::function<bool(CardT)> f);

/**
 *  \brief counts of cards in T that matches the condition f
 *  \param T The cards in the Waste or Deck
 *  \param f lambda expression that should filter the counting 
 *  \return number of cards in the T
 */
     unsigned int cnt_cards_stack(CardStackT T, std::function<bool(CardT)> f);

/**
 *  \brief counts of cards in T, F, D, W  that matches the condition f
 *  \param T The cards in the Tableau
 *  \param F The cards in the Foundation
 *  \param D The cards in the Deck
 *  \param W The cards in the Waste
 *  \param f lambda expression that should filter the counting 
 *  \return number of cards (Natural number)
 */
     unsigned int cnt_cards(vector<CardStackT> T, std::vector<CardStackT> F, CardStackT D, CardStackT W, std::function<bool(CardT)> f);

/**
 *  \brief Creates an initial sequence of the number of cards as specified by the user
 *  \param n Integer for the number of cards
 *  \return  vector of CardStackT, corresponding to the number of cards in the current sequence
 */
     vector<CardStackT> init_seq(unsigned int n);

/**
 *  \brief Creates an initial sequence of the number of cards as specified by the user
 *  \param deck Integer for the number of cards
 *  \return Returns a vector of CardStackT, corresponding to the number of cards in the current sequence
 */
     vector<CardStackT> tab_deck(vector<CardT> deck);

/**
 *  \brief checks if the card can be placed from the tableau
 *  \return Returns true if the card can be moved, false otherwise
*/        
     bool valid_tab_mv();

/**
 *  \brief checks if the card can be moved from the waste
 *  \return Returns true if the card can be moved, false otherwise
 */
     bool valid_waste_mv();

public:

/**
*  \brief Constructs a new BoardT
*  \param in The vector of CardT (aka the whole two card deck)
*/
     BoardT(vector<CardT> in);

/**
*  \brief Checks if moving the element from one Tableau to another component is valid or not
*  \param a The (Component) where the top of tableau want to go
*  \param x Index of Tableau (from)
*  \param y Index of another (Component) (to)
*  \return if valid -> true else -> false
*/
     bool is_valid_tab_mv(CategoryT a, unsigned int x, unsigned int y);

/**
*  \brief Checks if moving the element from Waste to another component is valid or not
*  \param a The (Component) where the top of waste want to go
*  \param x Index of another (Component) (to)
*  \return if valid -> true else -> false
*/
     bool is_valid_waste_mv(CategoryT a, unsigned int x);

/**
*  \brief Checks if moving the element from deck to another component is valid or not
*  \return if valid -> true else -> false
*/
     bool is_valid_deck_mv();

/**
*  \brief moves the element from deck to another component 
*  \param a The (Component) where the top of tableau want to go
*  \param x Index of which Tableau (Component) (from)
*  \param y Index of another (Component) (to)
*/
     void tab_mv(CategoryT a, unsigned int x, unsigned int y);

/**
 *  \brief Moves a card from the waste
 *  \param a The category for the cards
 *  \param x The card that will have a card placed on it
 */
     void waste_mv(CategoryT a, unsigned int x);

/**
 *  \brief Moves a card from the deck
 */
     void deck_mv();

/**
 *  \brief Returns a cardstack for cards at the tableau at the specific index
 *  \param a An integer corresponding to the stack for the tableau
 *  \return cardstack for cards at the tableau at the specific index
 */
     CardStackT get_tab(unsigned int a);

/**
 *  \brief Returns a cardstack for cards at the foundation at the specific index
 *  \param a An integer corresponding to the stack for the foundation
 *  \return cardstack for cards at the foundation at the specific index
 */
     CardStackT get_foundation(unsigned int a);

/**
 *  \brief Returns the deck
 *  \return the deck
 */
     CardStackT get_deck();

/**
 *  \brief Returns the waste
 *  \return  the waste
 */
     CardStackT get_waste();

/**
 *  \brief checks if a valid move exists
 *  \return  true if a valid move exists, false otherwise
 */
     bool valid_mv_exists();

/**
 *  \brief checks if the BoardT is currently in win state
 *  \return true if the game has been won, false otherwise
 */
     bool is_win_state();
};

#endif
