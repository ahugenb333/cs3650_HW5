// File: game.h (part of the namespace main_savitch_14)

/**
    @brief Game header file
	@file game.h
	@details function declarations for game.cc. Original file by Brock Ferrell.
	@author Braden Baker
	@date 20
 */

#ifndef MAIN_SAVITCH_GAME
#define MAIN_SAVITCH_GAME
#include <queue>   // Provides queue<string>
#include <string>  // Provides string

namespace main_savitch_14
{
class game
{
public:
	// ENUM TYPE
	/**
	@brief Determines the winner of the game.
	@return Computer if the computer won.
	@return Human if human player won.
	@return Neutral if it's a draw.
	*/
	enum who { HUMAN, NEUTRAL, COMPUTER }; // Possible game outcomes

    
	// CONSTRUCTOR and DESTRUCTOR
	game( ) { move_number = 0; }
	virtual ~game( ) { }

	// PUBLIC MEMBER FUNCTIONS
	// The play function should not be overridden. It plays one game,
	// with the human player moving first and the computer second.
	// The computer uses an alpha-beta look ahead algorithm to select its
	// moves. The return value is the winner of the game (or NEUTRAL for
	// a tie).
	who play( );

protected:
	// *******************************************************************
	// OPTIONAL VIRTUAL FUNCTIONS (overriding these is optional)
	// *******************************************************************
	/**
	@brief Virtual void function to display a message.
	*/
	virtual void display_message(const std::string& message) const;
	/**
	@brief Virtual string function to get the human player's move.
	*/
	virtual std::string get_user_move( ) const;
	/**
	@param at least one move has already been taken.
	@brief Virtual who function to calculate whether the human or computer went last.
	*/
	virtual who last_mover( ) const
	{ return (move_number % 2 == 1 ? HUMAN : COMPUTER); }
	/**
	@return Returns the number of moves completed.
	*/
	virtual int moves_completed( ) const { return move_number; }
	/**
	@brief Virtual who function to calculate who makes the next move.
	*/
	virtual who next_mover( ) const
	{ return (move_number % 2 == 0 ? HUMAN : COMPUTER); }
	/**
	@brief Virtual who function to figure out the opposite player.
	*/
	virtual who opposite(who player) const
	{ return (player == HUMAN) ? COMPUTER : HUMAN; }
	/**
	@brief Virtual void function to count pieces on board.
	*/
	virtual void countingPieces() = 0;
	/**
	@brief Virtual void function to figure out who's turn it is.
	*/
	virtual void whosTurn() = 0;
	/**
	@brief Virtual who function to calculate who's winning by counting pieces left on the board.
	*/
	virtual who winning( ) const;
    

	// *******************************************************************
	// VIRTUAL FUNCTIONS THAT MUST BE OVERRIDDEND:
	// The overriding function should call the original when it finishes.
	// *******************************************************************
	// Have the next player make a specified move:
	/**
	@brief Virtual void function to apply player's move.
	*/
	virtual void make_move(const std::string& move) { ++move_number; }
	/**
	@brief Virtual void function to restart the game.
	*/
	// Restart the game from the beginning:
	virtual void restart( ) { move_number = 0; }
    
    
    // *******************************************************************
    // PURE VIRTUAL FUNCTIONS
    // *******************************************************************
    // (these must be provided for each derived class)
    // Return a pointer to a copy of myself:
	/**
	@brief Virtual game* function to return a pointer to a copy of itself.
     */
    virtual game* clone( ) const = 0;
    /**
     @brief Virtual void function to compute all possible moves for the next player.
     */
    // Compute all the moves that the next player can make:
    virtual void compute_moves(std::queue<std::string>& moves) const = 0;
    /**
     @brief Virtual void function to display the status of the current game.
     */
    // Display the status of the current game:
    virtual void display_status( ) const = 0;
    /**
     @brief Virtual int function to evaluate the board position.
     */
    // Evaluate a board position:
    // NOTE: positive values are good for the computer.
    virtual int evaluate( ) const = 0;
    /**
     @brief Virtual bool function to see if the game is over.
     */
    // Return true if the current game is finished:
    virtual bool is_game_over( ) const = 0;
    /**
     @brief Virtual bool function to figure out if the move entered is legal.
     */
    // Return true if the given move is legal for the next player:
    virtual bool is_legal(const std::string& move) const = 0;
    
    
    int move_number;                     // Number of moves made so far
    
    
private:
    
    // STATIC MEMBER CONSTANT
    static const int SEARCH_LEVELS = 4;  // Levels for look-ahead evaluation
    
    // PRIVATE FUNCTIONS (these are the same for every game)
    int eval_with_lookahead(int look_ahead, int beat_this);
    void make_computer_move( );
    void make_human_move( );
};
}

#endif


