/*!
 ___________________________________________________________________
/																	\
|	|||||||||||||	||||    ||||	  |||||||||		||||	||||	|
|	||||     ||||	||||	||||	||||			||||	||||	|
|	||||	 ||||	||||	||||	||||			||||	||||	|
|	|||||||||||||	||||	||||	  ||||||		||||||||||||	|
|	||||  ||||		||||	||||		 ||||||		||||||||||||	|
|	||||   ||||		||||	||||		    ||||	||||	||||	|
|	||||    ||||	||||	||||			||||	||||	||||	|
|	||||	 ||||	  ||||||||		 |||||||||		||||	||||	|
|																	|
|	Original board game library written by Jonathan Janosi.			|
|	Game concept developed with Jonathan Janosi, Sasha Sorraine		|
|	and Brenden Sims. For use in 4GP6 capstone project.				|
|																	|
|	These files contain the code to run the game but contain no		|
|	code for user interfaces. It simply maintains board state and	|
|	updates it with inputs and outputs.								|
|																	|
|	The board game itself is a two-player abstract-styled game,		|
|	where two opponents submit theirs turns simulataneously, and	|
|	then each turn plays out according to a set of rules.			|
|																	|	
|	All classes and functions use naming convention JJ<name> to		|
|	avoid potential conflicts integrating the code into the C4		|
|	engine later.													|
|																	|
|	Other design documents contain the rules for the game in		|
|	greater details, this code contains only implementation			|
|	With some basic commenting.										|
|																	|
\__________________________________________________________________*/

// (Rush is the working name for this game, still subject to change)


#pragma once
#include <list>			// Used to store and manage certain game elements
#include "JJPieces.h"	// Definitions and enumerations of different piece, team and army types.
using namespace std;

//! JJAction is a simple data storage class. It holds onto the relevant information for an action until is it resolved by JJRush.
class JJAction{
public:
	int x1, x2, y1, y2;		// y1, x1 are initial position. If they are valued at {-1,-1} they are currently of the board and it is a placement action
	// Otherwise, it is a move action.
	JJPieces type;
	JJTeams colour;
	JJAction();
	JJAction(int xin, int xout, int yin, int yout, JJPieces piece, JJTeams col);
};
 // Needs to exist. Should never actually happen.
JJAction::JJAction(){
	x1 = 12;
	x2 = 12;
	y1 = 12;
	y2 = 12;
	type = pawn;
	colour = white;
}

//! Constructor for the JJaction class.
JJAction::JJAction(int xin, int xout, int yin, int yout, JJPieces piece, JJTeams col){
	x1 = xin;
	x2 = xout;
	y1 = yin;
	y2 = yout;
	type = piece;
	colour = col;
}

//! Used to correct for odd situations where pieces would move through the corners of square simulatenously from different directions, which should result in collision.
class JJConflict{
public:
	bool ne, nw, se, sw;
	bool king;
	bool setStatus(int i,int j, bool k);
	void clear();
};


// Clears conflicts on in square.
void JJConflict::clear(){
	ne = false;
	nw = false;
	se = false;
	sw = false;
	king = false;
}

bool JJConflict::setStatus(int i, int j, bool k){
	if (!ne && !nw && !se && !sw){
		switch (i){
		case 0:
			if (j = 0){ ne = true; }
			else{ se = true; }
			break;
		case -1:
			if (j = 0){ nw = true; }
			else { sw = true; }
			break;
		}
		if (k){
			king = true;
		}
		return true;
	}
	else
		return false;
}

//! Class containing the elements of an individual boardsquare.
class JJBoardSquare{
public:
	JJPieces type	=	empty;			// Type of piece - default neutral
	JJTeams	team	=	neutral;		// Team of piece - default neutral
	int goalX = 10, goalY = 10;
	bool active;		// Whether the piece on that square is currently active.
	void deactivate(){
		active = false;
	}
	void activate(){
		active = true;
	}
	void makeEmpty();
};

//! Makes the board square empty.
void JJBoardSquare::makeEmpty(){
	type = empty	;
	team = neutral	;
}

//! JJStockPiece represent units not on the field. It stores both a type or piece and its respawn timer.
class JJStockPiece{
public:
	int respawn;
	JJPieces type;
	JJStockPiece(JJPieces x);
	JJStockPiece(JJPieces x, int y);
};

//! Constructor for JJStockPiece. 
JJStockPiece::JJStockPiece(JJPieces x){
	respawn = 0;
	type = x;
}

//! Constructor for JJStockPiece including respawn timer
JJStockPiece::JJStockPiece(JJPieces x, int y){
	respawn = y;
	type = x;
}


//! The army manager for pieces of the board. Contains the current stock and respawn timers of all pieces off the board.
/*
JJStock manages all aspect of the board game pertaining to pieces off the board.
*/

class JJStock{
public:
	list <JJStockPiece> units;
	JJTeams colour;
	JJStock();
	JJStock(JJArmies army);		// Takes army type as input, creates stock of pieces
	void clearStock(){			// Clears the current team of any members.
		units.clear();
	};
	bool removeFromStock(JJPieces check);
	void addToStock(int respawn, JJPieces type);
};


//! Remove from stock checks stock for a pieces matching type with repspawn timer 0.
bool JJStock::removeFromStock(JJPieces check){
	for (list<JJStockPiece>::iterator itr = units.begin(); itr != units.end(); ++itr)
	{
		JJStockPiece copy = *itr;
		if (copy.type == check && copy.respawn==0){
			itr = units.erase(itr);
			return true;
		}
	}

	return false;
}

//! Adds new piece to stack with a given respawn timer.
void JJStock::addToStock(int respawn, JJPieces type){
	units.push_back(JJStockPiece(type, respawn));
};

JJStock::JJStock(){
	units.push_back(JJStockPiece(pawn));
	units.push_back(JJStockPiece(pawn));
	units.push_back(JJStockPiece(pawn));
	units.push_back(JJStockPiece(pawn));
	units.push_back(JJStockPiece(pawn));
	units.push_back(JJStockPiece(knight));
	units.push_back(JJStockPiece(knight));
	units.push_back(JJStockPiece(rook));
	units.push_back(JJStockPiece(rook));
	units.push_back(JJStockPiece(bish));
	units.push_back(JJStockPiece(bish));
	units.push_back(JJStockPiece(king));
	units.push_back(JJStockPiece(queen));
}

//! JJStock constructor populates the stock with the units of the desired team.
JJStock::JJStock(JJArmies army){
	switch (army){
	case classic:
		// Total: 5 pawns, 2 knights, 2 rooks, 2 bishops, 1 king, 1 queen, 13 pieces
		units.push_back(JJStockPiece(pawn));
		units.push_back(JJStockPiece(pawn));
		units.push_back(JJStockPiece(pawn));
		units.push_back(JJStockPiece(pawn));
		units.push_back(JJStockPiece(pawn));
		units.push_back(JJStockPiece(knight));
		units.push_back(JJStockPiece(knight));
		units.push_back(JJStockPiece(rook));
		units.push_back(JJStockPiece(rook));
		units.push_back(JJStockPiece(bish));
		units.push_back(JJStockPiece(bish));
		units.push_back(JJStockPiece(king));
		units.push_back(JJStockPiece(queen));
		break;
	case battleship:
		//Total: 6 Torpedos, 1 destroyer, 2 salvage, 1 battleship, 2 aircaft carriers
		units.push_back(JJStockPiece(torp));
		units.push_back(JJStockPiece(torp));
		units.push_back(JJStockPiece(torp));
		units.push_back(JJStockPiece(torp));
		units.push_back(JJStockPiece(torp));
		units.push_back(JJStockPiece(torp));
		units.push_back(JJStockPiece(dest));
		units.push_back(JJStockPiece(salv));
		units.push_back(JJStockPiece(salv));
		units.push_back(JJStockPiece(battle));
		units.push_back(JJStockPiece(aircc));
		units.push_back(JJStockPiece(aircc));
		break;
	}
}

//! JJRush contains the entire board game and calls all other functions.
class JJRush{
public:
	bool gameOver;				// Flag is set when someone hits a score greater than three. Resolves current actions phase then ends game.
	JJBoardSquare board[9][11];	// 9x9 game board, made up of boardsquares
	JJConflict conflicts[8][10]; // represents the corners of the boardsquares where 4 squares meet
	JJStock teams[2];			// Both teams stocks
	int score[2];				// Both teams scores
	list<JJAction> actionList;	// Full set of actions
	list<JJAction> speedQueue;	// Actions currently being executed/to be executed next
	list<JJAction> placements;  // List of placements actions for the end of the next turn.
	list<JJAction> knightMoves; // List of knight moves. Needed because they dodge conflict except on the landing square.
	

	//Function descriptions and constructor descriptions accompany their definitions below.

	void ResolveAll();
	void ResolveSpeed(int speed);
	bool pieceFromStock(JJPieces type, JJTeams team);
	void pieceToStock(JJPieces type, JJTeams team, int mod);
	bool isThere(JJPieces type, JJTeams team, int x, int y);
	void moveToGoal();
	void passiveMove(int origX, int origY, int targX, int targY);
	void attack(int origX, int origY, int targX, int targY);
	void destroy(JJPieces destroyer, JJTeams destTeam, int x, int y);
	void deactivateAll();
	void deactivateConf();
	JJRush();
	JJRush(JJArmies w, JJArmies b);
	void submitAction(JJaTypes aType, JJTeams team,JJPieces type, int x1, int y1, int x2, int y2);
	void resolveConflict(int i, int j);
	void placeKnights();
	void getscore(JJTeams scorer);
	void destConf(int i, int j, bool k);
};

void JJRush::destConf(int i, int j, bool k){
	if (conflicts[i][j].ne == true){
		pieceToStock(board[i + 1][j + 1].type, board[i + 1][j + 1].team, 0);
		board[i + 1][j + 1].type = empty;
		board[i + 1][j + 1].team = neutral;
		board[i + 1][j + 1].goalX = i + 1;
		board[i + 1][j + 1].goalY = j + 1;
	}
	if (conflicts[i][j].se == true){
		pieceToStock(board[i + 1][j].type, board[i + 1][j].team, 0);
		board[i + 1][j].type = empty;
		board[i + 1][j].team = neutral;
		board[i + 1][j].goalX = i + 1;
		board[i + 1][j].goalY = j;
	}
	if (conflicts[i][j].nw == true){
		pieceToStock(board[i][j + 1].type, board[i][j + 1].team, 0);
		board[i][j + 1].type = empty;
		board[i][j + 1].team = neutral;
		board[i][j + 1].goalX = i;
		board[i][j + 1].goalY = j + 1;
	}
	if (conflicts[i][j].sw == true){
		pieceToStock(board[i][j].type, board[i][j].team, 0);
		board[i][j].type = empty;
		board[i][j].team = neutral;
		board[i][j].goalX = i;
		board[i][j].goalY = j;
	}
}

//! Places knights at the end of speed 5.
void JJRush::placeKnights(){
	for (list<JJAction>::const_iterator itr = placements.begin(), end = placements.end(); itr != end; ++itr) {
		JJAction temp = *itr;
		if (temp.y2 == 11 || temp.y2 == 0){
			getscore(temp.colour);
		}
		else if (board[temp.x2][temp.y2].active){
			pieceToStock(knight, temp.colour, 0);
			if (board[temp.x2][temp.y2].type != king){
				pieceToStock(board[temp.x2][temp.y2].type, board[temp.x2][temp.y2].team, 0);
				board[temp.x2][temp.y2].type = conflict;
				board[temp.x2][temp.y2].activate();
			}
		}
		else {
			if (board[temp.x2][temp.y2].type != empty){
				pieceToStock(board[temp.x2][temp.y2].type, board[temp.x2][temp.y2].team, 0);
			}
			board[temp.x2][temp.y2].type = knight;
			board[temp.x2][temp.y2].team = temp.colour;
			board[temp.x2][temp.y2].activate();
		}
	}
	knightMoves.empty();
}

//! Use this function to submit actions to the game.
void JJRush::submitAction(JJaTypes aType,JJTeams team, JJPieces type, int x1, int y1, int x2, int y2){
	JJAction temp = JJAction(x1, x2, y1, y2, type, team);
	if (aType == movement)
		actionList.push_back(temp);
	else
		placements.push_back(temp);
};

//! Deactivate all squares at the end of the turn.
void JJRush::deactivateAll(){
	for (int i = 0; i < 9; i++){
		for (int j = 1; j < 10; j++){
			// Conflicts exist to prevent oddities on the rare situation where three entities try to enter the same square at once.
			if (board[i][j].type == conflict){
				board[i][j].makeEmpty();
				board[i][j].deactivate();
			}
			// Torpedos should always be considered active.
			else if (board[i][j].type!=torp) {
				board[i][j].deactivate();
			}
			// All other pieces should be rendered inactive at this point.
			else {
				board[i][j].deactivate();
			}
		}
	}
	deactivateConf();
}

//! Deactivate all conflicts between individual steps.
void JJRush::deactivateConf(){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 10; j++){
			conflicts[i][j].clear();
		}
	}
}

//! Default constructor builds the game with two classic armies.
JJRush::JJRush(){
	teams[0] = JJStock(classic);
	teams[1] = JJStock(classic);
	score[0] = 0;
	score[1] = 0;
	for (int i = 0; i < 9; i++){
		for (int j = 1; j < 10; j++){
			board[i][j].goalX = i;
			board[i][j].goalY = j;
		}
	}
}

//! Constructor for rush with teams selected.
JJRush::JJRush(JJArmies w, JJArmies b){
	teams[0] = JJStock(w); 
	teams[1] = JJStock(b);
	score[0] = 0;
	score[1] = 0;
	for (int i = 0; i < 9; i++){
		for (int j = 1; j < 10; j++){
			board[i][j].goalX = i;
			board[i][j].goalY = j;
		}
	}
}


//! Removes a piece from the board.
void JJRush::destroy(JJPieces destroyer, JJTeams destTeam, int x, int y){
	// Handle special exceptions to respawn timers first.
	if (board[x][y].type == torp && destroyer==salv && board[x][y].team==destTeam){
		pieceToStock(torp, destTeam, -2);
	}
	// Specific exceptions: torpedoes should not destroy salvage boats on their team OR either player's battleships.
	else if (!((board[x][y].type == salv && destroyer == torp && board[x][y].team == destTeam) || (board[x][y].type == battle && destroyer == torp))){
		pieceToStock(board[x][y].type, board[x][y].team, 0);
		board[x][y].type = conflict;
		board[x][y].goalX = x;
		board[x][y].goalY = y;
	}
}

//! isThere() is a function to check if a certain piece type/team is in a square.
bool JJRush::isThere(JJPieces type, JJTeams team, int x, int y){
	if (board[x][y].type && board[x][y].team == team){ return true; }
	else { return false; }
}

//! PieceFromStock removes a piece for the stcok of pieces and places it on the board.
bool JJRush::pieceFromStock(JJPieces type, JJTeams team){
	if (team == white){
		return teams[0].removeFromStock(type);
	}
	else if (team = black){
		return teams[1].removeFromStock(type);
	}
	return false;
}

//! Takes a piece from the board and readds it to the stock, with a given respawn timer.
void JJRush::pieceToStock(JJPieces type, JJTeams team, int mod){
	if (team == white){
		teams[0].addToStock(respawn(type)+mod, type);
	}
	else if (team = black){
		teams[0].addToStock(respawn(type)+mod, type);
	}
}

//! Increments the team whose score points by 1
void JJRush::getscore(JJTeams scorer){
	if (scorer == white){
		score[0] += 1;
		if (score[0] >= 3)
			gameOver = true;
	}
	else {
		score[1] += 1;
		if (score[1] >= 3)
			gameOver = true;
	}

}

//! ResolveAll goes through the actions queue, then calls functions which analyse the contents of actions and attempts to resolve them all.
void JJRush::ResolveAll(){
	for (int i = 0; i > 12; i++){
		// After speed 5, check if aircraft carriers are in last two rows, as they score there.
		if (i == 6){
			for (int x = 0; x < 9; x++){
				for (int y = 1; y>3; y++){
					if (board[x][y].type == aircc && board[x][y].team == black){
						getscore(black);
						board[x][y].makeEmpty;
					}
				}
				for (int y = 9; y > 11; y++){
					if (board[x][y].type == aircc && board[x][y].team == white){
						getscore(white);
						board[x][y].makeEmpty();
					}
				}
			}
		}

		for (list<JJAction>::const_iterator itr = actionList.begin(), end = actionList.end(); itr != end; ++itr) {
			if (!gameOver){
				JJAction temp = *itr;
				if (isThere(temp.type, temp.colour, temp.x1, temp.y1)){			//Check to make sure pieces is still alive before submitting action.
					switch (i){
					case 0:
						// If a pawn is attacking a piece, it gets bonus speed.
						if (temp.type == pawn) {
							if (board[temp.x2][temp.y2].type != empty){
								speedQueue.push_back(temp);
								itr = actionList.erase(itr);
							}
							else if (temp.type == torp && board[temp.x2][temp.y2].type == empty){
								speedQueue.push_back(temp);
								itr = actionList.erase(itr);
							}
						}
						break;
					case 2:
						if (temp.type == salv){
							speedQueue.push_back(temp);
						}
						break;
					case 5:
						if (temp.type != pawn && speedGet(temp.type) == 5)
							speedQueue.push_back(temp);
						break;
					case 8:
						if (temp.type = battle){
							speedQueue.push_back(temp);
						}
						break;

					case 10:
						if (temp.type = rook){
							speedQueue.push_back(temp);
						}
						break;
					}
				}
				ResolveSpeed(i);
			}
		}
	}
		actionList.empty();

	for (list<JJAction>::const_iterator itr = placements.begin(), end = placements.end(); itr != end; ++itr) {
		JJAction temp = *itr;
		if (board[temp.x2][temp.y2].type == empty){
			board[temp.x2][temp.y2].type = temp.type;
			board[temp.x2][temp.y2].team = temp.colour;
		}
	}
	placements.empty();
}

//! ResolveSpeed resolves all of the actions of the pieces with a given speed, taken as an argument.
void JJRush::ResolveSpeed(int speed){
	switch (speed){

	//Start of round actions have lots of exceptions
	case 0:
		for (list<JJAction>::const_iterator i = speedQueue.begin(), end = speedQueue.end(); i != end; ++i) {
			JJAction temp = *i;
			if (temp.type == torp && board[temp.x2][temp.y2].type == empty){
				if (pieceFromStock(torp, temp.colour)){
					board[temp.x2][temp.y2].team = temp.colour;
					board[temp.x2][temp.y2].type = torp;
					board[temp.x2][temp.y2].activate();
				}
			}
			else if (temp.type == pawn) {
				board[temp.x1][temp.y1].goalX = temp.x2;
				board[temp.x1][temp.y1].goalY = temp.y2;
				board[temp.x2][temp.y2].activate();
			}
		}
		speedQueue.empty();
		moveToGoal();
		break;
	//Battleship attack action.
	case 8:
		for (list<JJAction>::const_iterator i = speedQueue.begin(), end = speedQueue.end(); i != end; ++i) {
			JJAction temp = *i;
			// Check to make sure the battleship has survived the move.
			if (temp.type == battle && isThere(temp.type,temp.colour,temp.x1+temp.colour,temp.y1)){
				destroy(battle, temp.colour, temp.x2, temp.x1);
			}
		}
		speedQueue.empty();
	//case 5 sets goals for all battleships due to automove. then continues to default.
	case 5:
		for (int i = 0; i < 9; i++){
			for (int j = 1; j < 10; j++){
				if (board[i][j].type==battle){
					board[i][j].goalX += board[i][j].team;
					board[i][j].activate();
				}
			}
		}
		//DOES NOT BREAK HERE. CONTINUE TO DEFAULT.
	//Default resolves for both speed 5 and speed 10 movements.
	default:
		for (list<JJAction>::const_iterator i = speedQueue.begin(), end = speedQueue.end(); i != end; ++i) {
			JJAction temp = *i;
			if (speedGet(temp.type) == speed){
				if (temp.type != knight){
					board[temp.x1][temp.y1].goalX = temp.x2;
					board[temp.x1][temp.y1].goalY = temp.y2;
					board[temp.x2][temp.y2].activate();
				}
				// Knights get put into a special knight move function.
				else {
					board[temp.x1][temp.y1].makeEmpty();
					board[temp.x1][temp.y1].deactivate();
					knightMoves.push_back(temp);
				}
			}
		}
		speedQueue.empty();
		moveToGoal();
		break;
	}
}

//! Void move to goal spaces. Called after setting goals with resolve speed.
void JJRush::moveToGoal(){

	bool end = true;			// Will be switched off if there are potentially still actions left to resolve.
	int checkX, checkY;			// Integer set up to assist in checking.

	for (int i = 0; i < 9; i++){
		for (int j = 1; j < 10; j++){
			if (board[i][j].goalX != i && board[i][j].goalY != j){
				if (i>board[i][j].goalX){ checkX = i - 1; }
				if (i<board[i][j].goalX){ checkX = i + 1; }
				if (j>board[i][j].goalY){ checkY = j - 1; }
				if (j<board[i][j].goalY){ checkX = j + 1; }
				end = false;
				if ((checkY == 0 || checkY == 11)){
					
				}
				switch (board[i][j].type){
				case salv:
					passiveMove(i,j,checkX,checkY);
					break;
				default:
					attack(i, j, checkX, checkY);
					break;
				}
			}
		}
	}
	if (end == false){
		deactivateConf();
		moveToGoal();
	}
	else{
		placeKnights();
		deactivateAll();
	}
}


//! The attack option is called on to resolve moves for aggresive pieces (any piece capable of taking other pieces).
void JJRush::attack(int origX, int origY, int targX, int targY){

	int checkX, checkY;			// Integer set up to assist in checking.
	if (board[targX][targY].active){
		// Find the attacked target move.
		if (targX>board[targX][targY].goalX){ checkX = targX - 1; }
		if (targX<board[targX][targY].goalX){ checkX = targX + 1; }
		if (targY>board[targX][targY].goalY){ checkY = targY - 1; }
		if (targY<board[targX][targY].goalY){ checkY = targY + 1; }

		// If the piece would move off the board, it scores! Scoring pieces don't get put back into the stock.
		if (checkY == 11 || checkY == 0){
			getscore(board[origX][origY].team);
			board[origX][origY].deactivate();
			board[origX][origY].makeEmpty();
			board[origX][origY].goalX = origX;
			board[origX][origY].goalY = origY;
		}

		// If the next square of the targ is the origin square or the target square, the two units clash and destroy one of another
		// Otherwise, move the attacked piece first.
		if ((checkX == targX) && (checkY == targY) || (checkX == origX) && (checkY == origY)){
			// Kings win clashes. If two kings collide, the both die.
			if (board[targX][targY].type != king ){ destroy(board[origX][origY].type, board[origX][origY].team, targX, targY); }
			else if (board[origX][origY].type != king){ destroy(board[targX][targY].type, board[origX][origY].team, origX, origY); }
			else if (board[origX][origY].type == king && board[targX][targY].type == king) { destroy(board[targX][targY].type, board[origX][origY].team, origX, origY); destroy(board[origX][origY].type, board[origX][origY].team, targX, targY); }
		}
		else {
			attack(targX, targY, checkX, checkY);
		}
	} 

	// If moving througha corner, set corner flags so it is under conflict for a step.
	if (origX != targX && origY != targY){
		int i, j;
		if (origX > targX)
			i = -1;
		else
			i = 0;
		if (origX > targX)
			j = -1;
		else
			j = 0;

		bool test=conflicts[origX+i][origY+j].setStatus(i,j,board[origX][origY].type==king);
		if (!test){
			if (conflicts[origX + i][origY + j].king && board[origX][origY].type != king){
				pieceToStock(board[origX][origY].type, board[origX][origY].team, 0);
				board[origX][origY].makeEmpty();
				board[origX][origY].deactivate();
				board[origX][origY].goalX = origX;
				board[origX][origY].goalY = origY;
			}
			else if (conflicts[origX + i][origY + j].king && board[origX][origY].type == king){
				destConf(origX + i, origX + j, false);
				pieceToStock(king, board[origX][origY].team, 0);
				board[origX][origY].makeEmpty();
				board[origX][origY].deactivate();
				board[origX][origY].goalX = origX;
				board[origX][origY].goalY = origY;
			}
			else if (!conflicts[origX + i][origY + j].king && board[origX][origY].type == king){
				destConf(origX + i, origX + j, false);
				conflicts[origX + i][origY + j].king = true;
				board[targX][targY] = board[origX][origY];
				board[origX][origY].makeEmpty();
				board[origX][origY].deactivate();
				board[origX][origY].goalX = origX;
				board[origX][origY].goalY = origY;
			}
			else {
				destConf(origX + i, origX + j, false);
				board[origX][origY].makeEmpty();
				board[origX][origY].deactivate();
				board[origX][origY].goalX = origX;
				board[origX][origY].goalY = origY;
			}
		}
	}
	// Check to see if the piece is still alive (ie. was not destroyed above)
	// If it is, move it.
	if (!isThere(empty, neutral, origX, origY)){
		destroy(board[origX][origY].type, board[origX][origY].team, targX, targY);
		board[targX][targY] = board[origX][origY];

		board[origX][origY].deactivate()	;
		board[origX][origY].makeEmpty()		;
		board[origX][origY].goalX = origX	;
		board[origX][origY].goalY = origY	;
		// With the exception of destroyer, colliding with another pieces halts movement.
		if (board[targX][targY].type != dest){
			board[targX][targY].goalX = targX;
			board[targX][targY].goalY = targY;

		}
	}
}

//! The attack option is called on to resolve moves for passive pieces.
void JJRush::passiveMove(int origX, int origY, int targX, int targY){
	int checkX, checkY;			// Integer set up to assist in checking.
	if (targX > board[targX][targY].goalX){ checkX = targX - 1; }
	if (targX<board[targX][targY].goalX){ checkX = targX + 1; }
	if (targY>board[targX][targY].goalY){ checkY = targY - 1; }
	if (targY < board[targX][targY].goalY){ checkY = targY + 1; }

	// If the piece would move off the board, it scores and is removed. Scoring pieces don't get put back into the stock.
	if (checkY == 11 || checkY == 0){
		getscore(board[origX][origY].team);
		board[origX][origY].deactivate();
		board[origX][origY].makeEmpty();
		board[origX][origY].goalX = origX;
		board[origX][origY].goalY = origY;
	}

	// Check to see if any other ships are attempting to move to that square. If so, cancel moves.
	for (int i = 0; i < 9; i++){
		for (int j = 1; j < 10; j++){
			if (origX != i && origY != j && board[i][j].goalX == targX && board[i][j].goalY == targY){
				board[origX][origY].goalX = origX;
				board[origX][origY].goalY = origY;
				board[i][j].goalX = i;
				board[i][j].goalX = j;
				return;
			}
		}
	}

	if (board[origX][origY].type == salv && (board[targX][targY].type != empty && board[targX][targY].type != torp)) {
		board[origX][origY].goalX = origX;
		board[origX][origY].goalY = origY;
		return;
	}
	else if (board[origX][origY].type == salv && board[targX][targY].type == torp && board[origX][origY].team == board[targX][targY].team){
		destroy(board[origX][origY].type, board[origX][origY].team, targX, targY);
		board[targX][targY] = board[origX][origY];

		// Eliminate salv.
		board[origX][origY].deactivate();
		board[origX][origY].makeEmpty();
		board[origX][origY].goalX = origX;
		board[origX][origY].goalY = origY;

		// Reclaiming torpedoes stops movement.
		board[targX][targY].goalX = targX;
		board[targX][targY].goalY = targY;
	}
	// If a salcage boat runs into an enemy torpedo.
	else if (board[targX][targY].type == torp){
		//delete both salavge boat and torpedo, put into respawn
		pieceToStock(salv, board[origX][origY].team, 0);
		pieceToStock(torp, board[targX][targY].team, 0);
		board[origX][origY].deactivate();
		board[origX][origY].makeEmpty();
		board[origX][origY].goalX = origX;
		board[origX][origY].goalY = origY;
		board[targX][targY].type = conflict;
		board[targX][targY].team = neutral;
	}
}

//! A function to check the validity of moves.
/*---------------------------------------------------------------------------------------------------------------------------------
JJmoveCheck is a function that is used to hightlight squares and make sure moves are valid before submitting. Seperated into sections
by army.

	\param type the type of pieces being checked
	\param x1 the original x position on the board
	\param y1 the original t position on the board
	\param x2 the post-move x position on the board
	\param y2 the post-move y position on the board
	\param submits which way is forward for a piece (relevant to certain pieces), generally 1 or -1.
---------------------------------------------------------------------------------------------------------------------------------*/
bool JJmoveCheck(JJRush gameBoard, JJPieces type, JJTeams team, int x1, int y1, int x2, int y2){
	int yDiff = abs(y1 - y2);	// These two statements repeated so much in my initial if statements
	int xDiff = abs(x1 - x2);	// I figured I might as well abstract them.
	int forward = 1;			// Define forward as 1 if white or -1 if black. (white moves up ranks and black move down)
	if (team == black){
		forward = -1;
	}
	// Can't go to a place off the board
	if (x2<0 || x2>8 || y2<0 || y2>11){
		return false;
	}
	// Teams may not move back to their own scoring zone.
	if ((team == black && y2 == 11) || (team == white && y2 == 0)){
		return false;
	}
	// Reject move if the piece isn't actually there.
	if (!gameBoard.isThere(type, team, x1, y1)){
		return false;
	}

	switch (type){
	// Empty case, all positions will return false.
	case empty:
		return false;
		break;
	// Classic army
	/*
		This army is the simplest army, the pieces are all based on chess equivalent (though they may change thematically
		over development). It contains the pawn, rook, knight, bish, king, and queen JJPieces types.
	*/
	case pawn:
		if ((y2 == y1 + forward) && (xDiff <= 1)){ return true; }
		else { return false; }
	case rook:
		if ((x1 == x2) && ((y2 == y1 + 1) || (y2 == y1 - 1))){ return true; }
		else if ((y2 == y1) && (x1 != x2) && (xDiff <= 3)){ return true; }
		else { return false; }
	case knight:
		if ((((xDiff == 1) || (yDiff == 1)) && ((xDiff == 2) || (yDiff == 2))) && (xDiff != yDiff)){ return true; }
		else { return false; }
	case bish:
		if (((xDiff == 2) && (yDiff == 2))|| ((xDiff==yDiff) && (xDiff==1) && (x2==11 || x2==0))){ return true; }
		else { return false; }
	case queen:
		if ((xDiff <= 2) && (yDiff <= 2) && ((xDiff != 0) || (yDiff != 0))){ //filters out no move, moves greater than 2 spaces
			if ((xDiff == 0) || (yDiff == 0) || (xDiff == yDiff)){ return true; } //Checks to see if the move is horizontal or diagonal.
		}
		return false;
	case king:
		if ((xDiff <= 1) && (yDiff <= 1) && ((xDiff != 0) || (yDiff != 0))){ //filters out no move, moves greater than 1 space.
			if ((xDiff == 0) || (yDiff == 0) || (xDiff == yDiff)){ return true; } //Checks to see if the move is horizontal or diagonal.
		}
		return false;
	// Battleship army
	/*
		This army is based strongly on predicting your opponents moves. Successful predictions can lead to very strong results, poor prediction
		leave your pieces seeming very weak. Contains dest, salv, battle, aircc. Does not contain torp, handled by placement.
	*/
	case dest:
		if (((yDiff = 0) && (xDiff == 2)) || ((yDiff == 2) && (xDiff == 0))){ return true; }
		return false;
	case salv:
		if ((xDiff <= 2) && (yDiff <= 2) && ((xDiff != 0) || (yDiff != 0))){ //filters out no move, moves greater than 2 spaces
			if ((xDiff == 0) || (yDiff == 0) || (xDiff == yDiff)){ return true; } //Checks to see if the move is horizontal or diagonal.
		}
		return false;
	case battle:
		yDiff = abs(y1 + forward - y2);								//Fixes check for automove
		if ((xDiff <= 2) && (yDiff <= 2) && ((yDiff != 0) || (xDiff != 0))){ return true;}
		return false;
	case aircc:
		if ((y2 == y1 + forward) && (xDiff <= 1)){ return true; }
		return false;
	case torp:
		if (y2 > 2 && y2 < 9 && gameBoard.isThere(empty,neutral,x2,y2)) { return true; }		// Check to see if the torpedo is not is either of the back two rows, and that the space is empty.
		return false;
	}
// Should not make it here, but if it does somehow
	return false;
}
