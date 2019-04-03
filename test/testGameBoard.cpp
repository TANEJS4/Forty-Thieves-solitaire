#include "catch.h"
#include "Stack.h"
#include "CardStack.h"
#include "CardTypes.h"
#include "GameBoard.h"

#include <vector>


vector<CardT> deck104()
{
	std::vector<CardT> d;
	for (RankT rank = ACE; rank <= KING; rank++)
	{
		for (unsigned int suit = 0; suit < 4; suit++)
		{
			CardT n = {static_cast<SuitT>(suit), rank};
			d.push_back(n);
			d.push_back(n);
		}
	}

	return d;
}

TEST_CASE("tests for GameBoard Constructor and getter", "[GameBoard]")
{
	vector<CardT> board104 = deck104();
	BoardT board14(board104);

	// SECTION("Test board with in correct number of cards"){

	// 	REQUIRE_THROWS_AS(BoardT board5(board52), invalid_argument);
	// }
	SECTION("Test Tableau exist  in correct form")
	{
		for (int i = 0; i < 10; i++)
		{
			REQUIRE(board14.get_tab(i).size() != 0);
		}
	}

	SECTION("Test Foundation exist  in correct form")
	{
		for (int i = 0; i < 8; i++)
		{
			REQUIRE(board14.get_foundation(i).size() == 0);
		}
	}

	SECTION("Test Deck exist  in correct form")
	{

		REQUIRE(board14.get_deck().size() != 0 );
		REQUIRE(board14.get_deck().size() == 64);
	}

	SECTION("Test Waste exist in correct form")
	{

		REQUIRE(board14.get_waste().size() == 0);
	}
	SECTION("Test error tableau")
	{
		REQUIRE_THROWS_AS(board14.get_tab(10), out_of_range);
	}

	SECTION("get foundation")
	{
		REQUIRE_THROWS_AS(board14.get_foundation(9), out_of_range);
	}
}

TEST_CASE("tests for GameBoard routines (with local)", "[GameBoard]")
{
	vector<CardT> board104 = deck104();
	BoardT board14(board104);
	SECTION("Test Tableau and Foundation move")
	{

		REQUIRE(!(board14.is_valid_tab_mv(Tableau, 0, 0)));
		REQUIRE((board14.is_valid_tab_mv(Foundation, 0, 0)));

		REQUIRE(!(board14.is_valid_tab_mv(Waste, 0, 0)));
		REQUIRE_FALSE(board14.is_valid_tab_mv(Tableau, 0, 0));
		REQUIRE_FALSE(board14.is_valid_tab_mv(Tableau, 0, 3));
		REQUIRE_FALSE((board14.is_valid_tab_mv(Tableau, 9, 9)));
		
	}

	SECTION("Test Waste move")
	{

		REQUIRE_THROWS_AS(board14.is_valid_waste_mv(Tableau, 0), invalid_argument);
		REQUIRE_THROWS_AS(board14.is_valid_waste_mv(Foundation, 0), invalid_argument);




	}

	SECTION("Test deck move")
	{
		REQUIRE(board14.is_valid_deck_mv());
	}

	SECTION("Test for any move that exists")
	{
		REQUIRE(board14.valid_mv_exists());
	}

	SECTION("Test for any move that exists")
	{
		REQUIRE(!(board14.is_win_state()));
	}

	SECTION("Test for moving card from tableau")
	{
		board14.tab_mv(Foundation, 0, 1);
		REQUIRE(board14.get_tab(0).size() == 1);
	}

	SECTION("Test error for moving card from waste")
	{
		REQUIRE_THROWS_AS(board14.waste_mv(Foundation, 0), invalid_argument);
		REQUIRE_THROWS_AS(board14.waste_mv(Tableau, 0) , invalid_argument);
	}

	SECTION("Test for moving card from deck")
	{
		board14.deck_mv();
		REQUIRE(board14.get_waste().size() > 0);
		REQUIRE(board14.get_deck().size() == 63);
	}
	SECTION("Test erros for moving card from tableau"){

	REQUIRE_THROWS_AS(board14.is_valid_tab_mv(Tableau, 10, 10), out_of_range);
	REQUIRE_THROWS_AS(board14.is_valid_tab_mv(Foundation, 10, 8), out_of_range);
	}
}