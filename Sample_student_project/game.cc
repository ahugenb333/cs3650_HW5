/** @file game.cc
	@brief Member function implementations for the file game.h

	This file contains the member function implementations for the
	the class game.h. This is the core driver of the Othello game
	package. It includes basic game mechanics and a MIN/MAX AI bot.

	@author Jarred Utt (documentation only)
	@author Brock Ferrell (all code)
	@bug Might be unknown bugs (Seg fault?)
*/
#include <cassert>    // Provides assert
#include <climits>    // Provides INT_MAX and INT_MIN
#include <iostream>   // Provides cin, cout
#include <queue>      // Provides queue<string>
#include <string>     // Provides string
#include "game.h"     // Provides definition of game class
using namespace std;

namespace main_savitch_14
{
//*************************************************************************
// STATIC MEMBER CONSTANTS
// const int game::SEARCH_LEVELS;

//*************************************************************************
// PUBLIC MEMBER FUNCTIONS

/**
	@brief Controls the game mechanics using member functions
	This function determines when the game ends, displays the board
	status after each move, and determines the winner of the game.
	@return game::who, the winner

*/
game::who game::play( )
// The play function should not be overridden. It plays one round of the
// game, with the human player moving first and the computer second.
// The return value is the winner of the game (or NEUTRAL for a tie).
{
	restart( );

	while (!is_game_over( ))
	{
		display_status( );
		whosTurn();
		if (last_mover( ) == COMPUTER) {
			countingPieces();
			make_human_move( );
		}
		else {
			make_computer_move( );
		}
	}
	display_status( );
	return HUMAN;
}



/*
 @brief OPTIONAL VIRTUAL FUNCTIONS (overriding these functions is optional)
*/
/**
	@brief This function is used to display messages to the console
		This function uses cout from <iostream> and std namespace to
		pass a string message to the console.
	@param message, a const string passed by reference
	@return void
*/
void game::display_message(const string& message) const
{
	cout << message;
}
/**
	@brief This function retrieves the game move from the user
		This funtion uses the getline function to retrieve a
		game move from the terminal user
	@return answer, a string
*/
string game::get_user_move( ) const
{
	string answer;

	display_message("If you cannot move, please press 'S'\n");
	display_message("Your move, please: ");
	getline(cin, answer);
	return answer;
}
/**
	@brief This function outputs the current winner
		This function returns an enumerated value game::who
		which is either computer or human. It determines the 
		winner by chip count
	@return game::who, the winner
*/
game::who game::winning()const {

	int value = evaluate();

	if (value > 0) {
		return last_mover();
	} else if (value < 0) {
		return next_mover();
	} else {
		return NEUTRAL;
	}

}


/**
	PRIVATE FUNCTIONS (these are the same for every game)
*/
/**
	@brief This function evaluates the best possible next move
		This function uses binary trees to create a new game for
		every possbile next move. It then evaluates the chip count
		and decides what the best move to make is.
	@param look_ahead- an integer, beat_this- an integer
	@return evaluate- an integer
*/
int game::eval_with_lookahead(int look_ahead, int beat_this)
// Evaluate a board position with lookahead.
// --int look_aheads:  How deep the lookahead should go to evaluate the move.
// --int beat_this: Value of another move that we're considering. If the
// current board position can't beat this, then cut it short.
// The return value is large if the position is good for the player who just
// moved.
{
	queue<string> moves;   // All possible opponent moves
	int value;             // Value of a board position after opponent moves
	int best_value;        // Evaluation of best opponent move
	game* future;          // Pointer to a future version of this game

	// Base case:
	if (look_ahead == 0 || is_game_over( ))
	{
		if (last_mover( ) == COMPUTER)
			return evaluate( );
		else
			return -evaluate( );
	}

	// Recursive case:
	// The level is above 0, so try all possible opponent moves. Keep the
	// value of the best of these moves from the opponent's perspective.
	compute_moves(moves);
	// assert(!moves.empty( ));
	best_value = INT_MIN;
	while (!moves.empty( ))
	{
		future = clone( );
		future->make_move(moves.front( ));
		value = future->eval_with_lookahead(look_ahead - 1, best_value);
		delete future;
		if (value > best_value)
		{
			if (-value <= beat_this)
				return INT_MIN + 1; // Alpha-beta pruning
			best_value = value;
		}
		moves.pop( );
	}

	// The value was calculated from the opponent's perspective.
	// The answer we return should be from player's perspective, so multiply times -1:
	return -best_value;
}

/**
	@brief This function makes the computer's move
		This function uses the eval_with_lookahead function to determine
		the best move for the compputer to make, then makes this move
	@return void
*/
void game::make_computer_move( )
{
	queue<string> moves;
	int value;
	int best_value;
	string best_move;
	game* future;

	// Compute all legal moves that the computer could make.
	compute_moves(moves);
	//assert(!moves.empty( ));

	// Evaluate each possible legal move, saving the index of the best
	// in best_index and saving its value in best_value.
	best_value = INT_MIN;
	while (!moves.empty( ))
	{
		future = clone( );
		future->make_move(moves.front( ));
		value = future->eval_with_lookahead(SEARCH_LEVELS, best_value);
		delete future;
		if (value >= best_value)
		{
			best_value = value;
			best_move = moves.front( );
		}
		moves.pop( );
	}

	// Make the best move.
	make_move(best_move);
}

/**
	@brief This function makes the human move
		This function takes a string input from the terminal
		that corresponds to a move on the board. It then checks
		the legality of that move and if it is legal: makes the move,
		and if it is not legal: prompts for another move.
	@return void
*/
void game::make_human_move( ) {
	string move;

	move = get_user_move( );
	while (!is_legal(move))
	{
		display_message("Illegal move.\n");
		move = get_user_move( );
	}
	make_move(move);
}

}



