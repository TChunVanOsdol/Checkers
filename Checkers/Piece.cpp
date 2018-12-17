#pragma once
#include "stdafx.h"
#include "Piece.h"

Piece::Piece() {}

Piece::Piece(checkertype col, int pos, Board &ref, Game &gref) {
	//Create a game piece with red or white team at a position index.
	color = col;
	position = pos;
	boardref = &ref;
	gameref = &gref;
	if (color == whiteteam) {
		checkerShape.setFillColor(sf::Color::White);
	}
	else {
		checkerShape.setFillColor(sf::Color::Red);
	}
	checkerShape.setOutlineColor(sf::Color::Green);
	checkerShape.setOutlineThickness(0.f);
	checkerShape.setRadius(boardref->tileW * 0.4); //Sets a radius to 40% of a tile's width
	checkerShape.setOrigin(-boardref->tileW * 0.1, -boardref->tileH * 0.1);
}

void Piece::drawPiece(sf::RenderWindow &window) {
	checkerShape.setPosition(boardref->getTilePos(position));
	window.draw(checkerShape);
}

void Piece::update(std::vector<Piece*> checkers) {
	//Update function can be created as a series of functions to help organize what should happen each game loop
	selectPiece();
	placePiece(checkers);
	if (gameref->newTurn == true) {
		filterPiece(checkers);
		if (jumpable == true) {
			searchTree(checkers);
		}
	}
}

void Piece::selectPiece() {
	//Select piece
	if (color == gameref->turnColor && boardref->pieceJumping == false && boardref->clickPos == position && selected == false && boardref->newClick == true && selectable == true) {
		selected = true;
		checkerShape.setOutlineThickness(8.f);
		std::cout << "Tiles to jump to: ";
		for (int pos : endPositions) {
			std::cout << pos << " ";
		}
		std::cout << std::endl;
	}
	//Deselect piece
	else if (boardref->clickPos == position && selected == true && boardref->newClick == true) {
		//Clicked on piece again
		checkerShape.setOutlineThickness(0.f);
		selected = false;
		if (boardref->pieceJumping == true) {
			//Player chose to end turn after jumping a piece
			gameref->changeTurn();
		}
		boardref->pieceJumping = false;
	}
}

void Piece::placePiece(std::vector<Piece*> checkers) {
	//Place a piece by checking if the next click is in a valid location
	if (selected == true && boardref->clickPos != position) {
		//Check all pieces to see if one of them is blocking the new click position
		bool pieceBlocked = false;
		for (Piece* checker : checkers) {
			if (boardref->clickPos == checker->position && checker->alive) {
				//Location is blocked by another piece
				pieceBlocked = true;
				break;
			}
		}
		//Piece is not blocked and the tile is black (black is the playable space)
		if (pieceBlocked == false && boardref->tileTypes[boardref->clickPos] == black) {
			if (color == redteam && kinged == false) {
				//Red moves down
				if (boardref->pieceJumping == false && (boardref->clickPos == position + boardref->tilesPerRow - 1 || boardref->clickPos == position + boardref->tilesPerRow + 1)) {
					//Valid position, no jump
					checkerShape.setOutlineThickness(0.f);
					position = boardref->clickPos;
					selected = false;
					//End of turn
					gameref->changeTurn();
				}
				//Red jumps down and left
				if (boardref->clickPos == position + (boardref->tilesPerRow - 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos - (boardref->tilesPerRow - 1) == checker->position && checker->color == whiteteam) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					//For jumping pieces, reusing the same pieceBlocked variable to check if there was actually an enemy piece to jump over
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//Red jumps down and right
				if (boardref->clickPos == position + (boardref->tilesPerRow + 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos - (boardref->tilesPerRow + 1) == checker->position && checker->color == whiteteam) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//King a piece if it reaches the other side 
				if (position >= boardref->tileCount - boardref->tilesPerRow) {
					kinged = true;
				}
			}
			else if (color == whiteteam && kinged == false) {
				//White moves up
				if (boardref->pieceJumping == false && (boardref->clickPos == position - boardref->tilesPerRow - 1 || boardref->clickPos == position - boardref->tilesPerRow + 1)) {
					//Valid position, no jump
					checkerShape.setOutlineThickness(0.f);
					position = boardref->clickPos;
					selected = false;
					//End of turn
					gameref->changeTurn();
				}
				//White jumps up and left
				if (boardref->clickPos == position - (boardref->tilesPerRow + 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos + (boardref->tilesPerRow + 1) == checker->position && checker->color == redteam) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//White jumps up and right
				if (boardref->clickPos == position - (boardref->tilesPerRow - 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos + (boardref->tilesPerRow - 1) == checker->position && checker->color == redteam) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//King a piece if it reaches the other side 
				if (position <= boardref->tilesPerRow) {
					kinged = true;
				}
			}
			else if (kinged == true) {
				//King moves
				if (boardref->pieceJumping == false && (boardref->clickPos == position - boardref->tilesPerRow - 1 || boardref->clickPos == position - boardref->tilesPerRow + 1
					|| boardref->clickPos == position + boardref->tilesPerRow - 1 || boardref->clickPos == position + boardref->tilesPerRow + 1)) {
					//Valid position, no jump
					checkerShape.setOutlineThickness(0.f);
					position = boardref->clickPos;
					selected = false;
					//End of turn
					gameref->changeTurn();
				}
				//King jumps up and left
				if (boardref->clickPos == position - (boardref->tilesPerRow + 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos + (boardref->tilesPerRow + 1) == checker->position && checker->color != color) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//King jumps up and right
				if (boardref->clickPos == position - (boardref->tilesPerRow - 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos + (boardref->tilesPerRow - 1) == checker->position && checker->color != color) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//King jumps down and left
				if (boardref->clickPos == position + (boardref->tilesPerRow - 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos - (boardref->tilesPerRow - 1) == checker->position && checker->color != color) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//King jumps down and right
				if (boardref->clickPos == position + (boardref->tilesPerRow + 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos - (boardref->tilesPerRow + 1) == checker->position && checker->color != color) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
			}
		}
		//Clicked location that is open, but cannot be moved to
		//Jumping pieces must jump again or end turn (by clicking on piece)
		else if (boardref->pieceJumping == false) {
			checkerShape.setOutlineThickness(0.f);
			selected = false;
		}
	}
}

void Piece::filterPiece(std::vector<Piece*> checkers) {
	//Check if piece can move at all. If possible, add the number of available moves to the owner's moveTotal
	std::vector<int> positionCheck;
	int closePositions;
	int moveCount;
	//Reset variables for search algorithm
	jumpable = false;
	endPositions.clear();

	if (kinged == true) {
		positionCheck.push_back(position + boardref->tilesPerRow + 1);
		positionCheck.push_back(position + boardref->tilesPerRow - 1);
		positionCheck.push_back(position - boardref->tilesPerRow + 1);
		positionCheck.push_back(position - boardref->tilesPerRow - 1);
		moveCount = 4;
	}
	else if (color == redteam) {
		positionCheck.push_back(position + boardref->tilesPerRow + 1);
		positionCheck.push_back(position + boardref->tilesPerRow - 1);
		moveCount = 2;
	}
	else if (color == whiteteam) {
		positionCheck.push_back(position - boardref->tilesPerRow + 1);
		positionCheck.push_back(position - boardref->tilesPerRow - 1);
		moveCount = 2;
	}

	closePositions = positionCheck.size();
	for (int i = 0; i < positionCheck.size(); i++) {
		//If the position is out of bounds, end this iteration
		if (positionCheck[i] >= boardref->tileCount || positionCheck[i] < 0) {
			moveCount--;
			continue;
		}
		//Is the position in question a white tile (unpathable)?
		if (boardref->tileTypes[positionCheck[i]] == white) {
			moveCount--;
			continue;
		}
		//Are any pieces blocking the position in question?
		for (Piece* checker : checkers) {
			//A piece is blocking the position
			if (checker->position == positionCheck[i]) {
				moveCount--;
				//Check if blocking piece is an enemy, but only if it's one space away
				if (checker->color != color && i < closePositions) {
					//Add a new position to check
					positionCheck.push_back(position + (positionCheck[i] - position) * 2);
					moveCount++;
					jumpable = true;
				}
				break;
			}
		}
	}
	//The piece cannot move, make it unselectable
	if (moveCount == 0) {
		selectable = false;
	}
	else {
		selectable = true;
	}
	gameref->moveTotal[color] += moveCount;
}

void Piece::searchTree(std::vector<Piece*> checkers) {
	//This function will find all possible ending points for a piece that can jump
	//Does not assume the piece becomes kinged during a chain of jumps

	//Positions for neighboring tiles
	int checkPos[4] = { boardref->tilesPerRow - 1, boardref->tilesPerRow + 1, -boardref->tilesPerRow - 1, -boardref->tilesPerRow + 1 };
	int checkCount = 4;
	int checkStart = 0;
	//Only check down if the piece is red and not kinged
	if (color == redteam && !kinged) {
		checkCount = 2;
	}
	//Only check up if the piece is white and not kinged
	if (color == whiteteam && !kinged) {
		checkStart = 2;
	}
	//Variables to track piece positions
	int currentNode = position;
	int enemyNode;
	int targetNode;
	//Groups of unexplored (open) and explored (closed) nodes
	std::vector<int> openSet = { position };
	std::vector<int> closedSet;

	while (!openSet.empty()) {
		//Choose the lowest position open node
		int lowestPos = boardref->tileCount;
		int lowestIndex = 0;
		for (int i = 0; i < openSet.size(); i++) {
			if (openSet[i] < lowestPos) {
				lowestPos = openSet[i];
				lowestIndex = i;
			}
		}
		currentNode = lowestPos;
		//Check the neighbor nodes
		for (int i = checkStart; i < checkCount; i++) {
			bool enemyChecked = false;
			bool spaceOpen = true;
			enemyNode = currentNode + checkPos[i];
			targetNode = currentNode + 2 * checkPos[i];
			//Check for out of bounds locations
			if (enemyNode < 0 || enemyNode >= boardref->tileCount || targetNode < 0 || targetNode >= boardref->tileCount) {
				continue;
			}
			//Check for unpathable (white) tiles
			if (boardref->tileTypes[enemyNode] == white || boardref->tileTypes[targetNode] == white) {
				continue;
			}
			//Check if node is already in the closed set
			bool endIter = false;
			for (int node : closedSet) {
				if (node == targetNode) {
					endIter = true;
					break;
				}
			}
			//End this iteration if the node is invalid
			if (endIter == true) {
				continue;
			}
			for (Piece* checker : checkers) {
				//Check if an enemy is in the correct position
				if (checker->position == enemyNode && checker->color != color) {
					enemyChecked = true;
				}
				//Check if target space is blocked 
				if (checker->position == targetNode) {
					spaceOpen = false;
					break;
				}
			}
			//If all the conditions are met, add the target node to the open set
			if (enemyChecked == true && spaceOpen == true) {
				openSet.push_back(targetNode);
			}
		}
		//Checking neighbors complete, move the current node into the closed set
		closedSet.push_back(currentNode);
		openSet.erase(openSet.begin() + lowestIndex);
	}
	//Save the closed set as the end positions
	endPositions = closedSet;
}