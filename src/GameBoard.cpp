/**
 * \file GameBoard.cpp
 * \author Shivam Taneja
 * \brief Implementation of BoardT.h and local fucntions
 */
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

#include <stdexcept>

#include "GameBoard.h"

using namespace std;

BoardT::BoardT(vector<CardT> deck) : T({}), F({}), D(CardStackT({})), W(CardStackT({}))
{
	for (RankT rank = ACE; rank <= KING; rank++){
		for (unsigned int suit = 0; suit < 4; suit++){
			int c = 0;
			for (unsigned int i = 0; i < deck.size();i++){
				if(deck[i].r == rank && deck[i].s == suit){
					c++;
				}
			}
			if(c != 2){
				throw invalid_argument("Deck argument invalid");
			}
		}
	}
	//initialize F:
	this->F = {};
	for (int i = 0; i < 8; i++)
	{
		vector<CardT> vec;
		CardStackT temp(vec);
		F.push_back(temp);
	}
	//initialize D:
	vector<CardT> vec;
	for (int i = 40; i <= 103; i++)
		vec.push_back(deck[i]);
	this->D = CardStackT(vec);

	//initialize W:
	vector<CardT> vec1;
	this->W = CardStackT(vec1);

	this->T = {};
	for (int i = 0; i < 10; i++)
	{
		vector<CardT> vec;
		for (int j = 4 * i; j <= (4 * (i + 1) - 3); j++)
		{
			vec.push_back(deck[j]);
		}
		CardStackT temp(vec);
		T.push_back(temp);
	}




}

bool BoardT::is_valid_tab_mv(CategoryT c, unsigned int n0, unsigned int n1 )
{

	if (c == Tableau ){

		bool cond1 = this->is_valid_pos(Tableau, n0);
		bool cond2 = this->is_valid_pos(Tableau, n1);
		if (cond1 && cond2){
			return this->valid_tab_tab(n0, n1);
		}
		else {
			throw out_of_range("Illegal move-gb51");
		}
	}

	else if (c == Foundation)
	{
		bool cond1 = this->is_valid_pos(Foundation, n0);
		bool cond2 = this->is_valid_pos(Foundation, n1);
		if (cond1 && cond2)
		{
			return this->valid_tab_foundation(n0, n1);
		}
		else
		{
			throw out_of_range("Illegal move-gb65");
		}
	}

	return false;	
}

bool BoardT::is_valid_waste_mv(CategoryT c, unsigned int n)
{
	if (this->W.size() == 0)
	{
		throw invalid_argument("Empty Waste-gm84");
	}
	else {
		if (c == Tableau)
		{
			bool cond1 = this->is_valid_pos(Tableau, n);
			if (!cond1)
			{
				throw out_of_range("Illegal move-gm92");
			} else {
				return this->valid_waste_tab(n);
			}
		}

		else if (c == Foundation)
		{
			bool cond1 = this->is_valid_pos(Foundation, n);
			if (!cond1)
			{
				throw out_of_range("Illegal move-gm103");
			}
			else
			{
				return this->valid_waste_foundation(n);
			}
		}

	}
	return false;
}

bool BoardT::is_valid_deck_mv(){
	return this->D.size() > 0;
}

void BoardT::tab_mv(CategoryT c, unsigned int n0, unsigned int n1){
	if (!(this->is_valid_tab_mv(c, n0, n1)))
	{
		throw invalid_argument("Illegal move-gm130");
	} else {
		if (c == Tableau){
			this->T[n1]= this->T[n1].push(this->T[n0].top());
			this->T[n0] = this->T[n0].pop();
		}
		else if (c == Foundation){
			this->F[n1] = this->F[n1].push(this->T[n0].top());
			this->T[n0] = this->T[n0].pop();
		}

	}
}

void BoardT::waste_mv(CategoryT c, unsigned int n){

	if (!(this->is_valid_waste_mv(c, n)))
	{
		throw invalid_argument("Illegal move-gm149");
	} 
	else {
		if (c == Tableau){
			this->T[n] =this->T[n].push(this->W.top());

			this->W = this->W.pop();
		}
		if (c == Foundation){
			this->F[n] = this->F[n].push(this->W.top());
			this->W = this->W.pop();
		}
	}
}

void BoardT::deck_mv(){
	if (!(this->is_valid_deck_mv()))
	{
		throw invalid_argument("Illegal move-gm165");
	} 
	else {
		this->W = this->W.push(this->D.top());
		this->D = this->D.pop();
	}
}

CardStackT BoardT::get_tab(unsigned int i){
	if (!this->is_valid_pos(Tableau, i))
	{
		throw out_of_range("Wrong-gm175");
	} else {
		return this->T[i];
	}
}

CardStackT BoardT::get_foundation(unsigned int i)
{
	if (!(this->is_valid_pos(Foundation, i)))
	{
		throw out_of_range("Wrong-gm185");
	}
	else
	{
		return this->F[i];
	}
}

CardStackT BoardT::get_deck()
{
	return this->D;
}

CardStackT BoardT::get_waste()
{
	return this->W;
}

bool BoardT::valid_mv_exists(){
	return valid_tab_mv() || valid_waste_mv() || is_valid_deck_mv();
}

bool BoardT::is_win_state(){

	for (int i = 0; i < 8; i++)
	{
		if ((this->F[i].size() == 0)){
			return false;
		}
		if ( (this->F[i].top().r != KING)){
			return false;
		}
	}
	return true;
}


// Local functions

bool BoardT::two_decks(vector<CardStackT> T, vector<CardStackT> F, CardStackT D, CardStackT W)
{
	SuitT st;
	RankT rk;
	for (st = Heart; st <= Spade; st = static_cast<SuitT>(st + 1))
	{
		for (rk = ACE; rk <= KING; rk++)
		{
			if (!(cnt_cards(T, F, D, W, [&](CardT cc) {return (cc.s == st && cc.r == rk); }) == 2))
			{
				return false;
				}
		}
	}
	return true;
}

unsigned int BoardT::cnt_cards_seq(vector<CardStackT> S, std::function<bool(CardT)> f)
{

	unsigned int i = 0;
	CardStackT s = S[i];
	unsigned int c = 0;
	while(i < S.size()){
	
		c = c + cnt_cards_stack(s,f );
		i++;
	}
	return c;
}

unsigned int BoardT::cnt_cards_stack(CardStackT s, std::function<bool(CardT)> f)
{
	unsigned int res = 0;
	unsigned int i = 0;
	CardT c;
	while( i < s.size()){
		if (f(c)){
			for (unsigned int j = 0; j < s.size(); j++)
			{
				if (s.toSeq()[i].s == c.s && s.toSeq()[i].r == c.r)
				{
					res++;
				}
			}
		}
		i++;
	}
	return res;
}
unsigned int BoardT::cnt_cards(vector<CardStackT> T, vector<CardStackT> F, CardStackT D, CardStackT W, std::function<bool(CardT)> f)
{
	unsigned int res = cnt_cards_seq(T, f) + cnt_cards_seq(F, f) + cnt_cards_stack(D, f) + cnt_cards_stack(W, f);
	return res;
}

vector<CardStackT> BoardT::init_seq(unsigned int n)
{
	vector<CardT> i;
	unsigned int ii = 0;
	vector<CardStackT> s;
	// if (s.size() == n){
		while(ii < n){
		// for (i; i < n ; ){
			s.push_back(CardStackT(i));
			ii++;
		}
		// }
		return s;
}

vector<CardStackT> BoardT::tab_deck(vector<CardT> deck)
{
	// vector<CardStackT> T;
	for (unsigned int i = 0; i < 10; i++)
	{
		vector<CardT> vec;
		unsigned int beginP = 4 * i;
		unsigned int endP = 4 * (i + 1) - 1;
		// T[i].toSeq() = deck;

		copy(deck.begin() + beginP, deck.begin() + endP + 1, vec.begin());
		T[i].toSeq() = vec;
	}
	return T;
}



bool BoardT::is_valid_pos(CategoryT c, unsigned int n)
{
	if (c == Tableau)
	{
		if ( 0<= n && n <=9 ){
			return true;
		}
	} else if (c == Foundation){
		if (0 <= n && n <= 7)
		{
			return true;
		}
	}
	return false;
}

bool BoardT::valid_tab_tab(unsigned int n0, unsigned int n1)
{
	if (this->T[n0].size() > 0){
		if (this->T[n1].size() > 0){
			return tab_placeable(this->T[n0].top(), this->T[n1].top());
		} 	
	}
	else if (this->T[n1].size() == 0)
	{
		return true;
	}
	return false;
}

bool BoardT::valid_tab_foundation(unsigned int n0, unsigned int n1)
{
	if (this->T[n0].size() > 0)
	{
		if (this->F[n1].size() > 0)
		{
			return foundation_placeable(this->T[n0].top(), this->F[n1].top());
		}
		else {
			return (this->T[n0].top().r == ACE);
		}
	}

	return false;
}

bool BoardT::valid_waste_tab(unsigned int n)
{
	if (this->T[n].size() > 0)
	{
		return tab_placeable(this->W.top(), this->T[n].top());
	}
	else if (this->T[n].size() == 0)
	{
		return true;
	}
	return false;
}

bool BoardT::valid_waste_foundation(unsigned int n)
{
	if (this->F[n].size() > 0)
	{
		return foundation_placeable(this->W.top(), this->F[n].top());
	}
	else if (this->F[n].size() == 0)
	{
		if (this->W.top().r == ACE)
		{
			return true;
		}
	}
	return false;
}

bool BoardT::tab_placeable(CardT c, CardT d){
	if (c.s == d.s && c.r == d.r - 1){
		return true;
	}
	return false;
}

bool BoardT::foundation_placeable(CardT c, CardT d)
{
	if (c.s == d.s && c.r == (d.r + 1))
	{
		return true;
	}
	return false;
}

bool BoardT::valid_tab_mv(){

	for (int i = 0; i <= 9;i++){
		for (int j = i; j <= 9; j++){
			if (is_valid_tab_mv(Tableau, i, j)){
				return true;
			}
		}
		for (int k = 0; k <= 7; k++)
		{
			if (is_valid_tab_mv(Foundation, i, k))
				return true;
		}
	}

	return false;
}

bool BoardT::valid_waste_mv()
{
	if (this->W.size() == 0)
		return false;

	//waste to tab:
	for (int i = 0; i <= 9; i++)
	{
		if (is_valid_waste_mv(Tableau, i))
			return true;
	}

	//waste to foundation:
	for (int i = 0; i <= 7; i++)
	{
		if (is_valid_waste_mv(Foundation, i))
			return true;
	}
	return false;
}



//Colaborated for Constructor with Ali Imitiaz
//Rest of the functions and routine was done by me