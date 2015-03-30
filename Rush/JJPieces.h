#pragma once

//! Teams enum
/*
The two teams are listed (white/black).
*/
enum JJTeams{
	white=1, neutral=0, black=-1
};

//! Armies enum
/*!
The types of armies are listed.
*/
enum JJArmies{
	classic,
	battleship
};

//! Piece type enum
/*!
The types of pieces are listed. Each army type  is stored on a different row.
*/

enum JJPieces{
	empty,												// to signify no piece is there, when necessary
	pawn, rook, knight, bish, king, queen,				// classic
	torp, dest, hitDest, salv, battle, aircc,			// battleship
	conflict											// temporary placeholder when conflicts have happened on a square.
};

enum JJaTypes{
	placement, movement
};

int respawn(JJPieces type){
	switch (type){
	// Classic
	case pawn:
		return 2;
	case knight:
		return 4;
	case rook:
		return 4;
	case bish:
		return 3;
	case king:
		return 5;
	case queen:
		return 6;
	// Battleship
	case torp:
		return 4;
	case dest:
		return 6;
	case salv:
		return 5;
	case aircc:
		return 3;
	}
	return 0;
}

int speedGet(JJPieces type){
	switch (type){
	case pawn:
		return 0;
	case torp:
		return 0;
	case salv:
		return 2;
	case rook:
		return 10;
	case battle:
		return 8;
	default:
		return 5;
	}
}