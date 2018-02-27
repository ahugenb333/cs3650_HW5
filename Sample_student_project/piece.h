// Brock Ferrell
// CS2401
// November 23, 2015
// Project7
/**
	@file piece.h
	@brief This file includes the class to make game pieces
	@author Jarred Utt (documentation)
**/
#ifndef PIECE_H
#define PIECE_H
enum color {black, white, blank};

class piece {
public:
	piece() {theColor = blank;}

	void flip()
	{
		if (theColor == white) {
			theColor = black;
		}
		else if (theColor == black) {
			theColor = white;
		}
	}

	bool is_blank()const {return theColor == blank;}
	bool is_black()const {return theColor == black;}
	bool is_white()const {return theColor == white;}
	void set_white() {theColor = white;}
	void set_black() {theColor = black;}

private:
	color theColor;

};

#endif

