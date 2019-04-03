#include "catch.h"
#include "Stack.h"
#include "CardTypes.h"
#include "CardStack.h"

#include <vector>
#include <typeinfo>
#include <iostream>

	using std::out_of_range;
using std::invalid_argument;


//helper functions
vector<CardT> deck(){
	std::vector<CardT> d;
	for (RankT rank = ACE; rank <= KING; rank++)
	{
		for (unsigned int suit = 0; suit < 4; suit++)
		{
			CardT n = {static_cast<SuitT>(suit), rank};
			d.push_back(n);
		}
	}

	return d;
}

bool checkCard(CardT a, CardT d){
	return (a.r == d.r && a.s == d.s);
}





//test cases
TEST_CASE("tests for CardStack", "[CardStack]")
{
	CardStackT p = deck();

	SECTION("general test for size non-seq Stack")
	{
		REQUIRE(p.size() == 52);
	}
	SECTION("general test for top non-seq Stack")
	{
		
			CardT c = p.top();

		// p = p.pop();

			REQUIRE((c.s == 3 && c.r == KING) == true);
	}
	SECTION("general test for pop non-seq Stack")
	{
		for (int i = 0; i < 10; i++)
		{
			p = p.pop();
		}
		REQUIRE(p.size() == 42);
	}

	SECTION("general test for push non-seq Stack ")
	{
		CardT n = {static_cast<SuitT>(2), KING};
		p = p.push(n);
		REQUIRE(p.size() == 53);
	}

	SECTION("general test error for pop non-seq Stack")
	{
		for (int i = 0; i < 52; i++)
		{
			p = p.pop();
		}
		REQUIRE_THROWS_AS(p = p.pop(), out_of_range);
	}

	SECTION("general test error for top non-seq Stack")
	{
		for (int i = 0; i < 52; i++)
		{
			p = p.pop();
		}
		REQUIRE_THROWS_AS(p.top(), out_of_range);
	}
	SECTION("Test toSeq")
	{
		vector<CardT> seq = p.toSeq();
		REQUIRE(seq.size() == 52);
	}
}
