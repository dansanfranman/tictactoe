#include <iostream>

int player;
int table[] = {0,0,0,0,0,0,0,0,0};
int choice;
char replay;
int winner;

bool Game();
void PrintTable();
bool ValidChoice();
bool WinCondition();
char ConvertChoice(int squareValue);

int main()
{
	while(Game());
	return 0;
}

//function to print board to screen each turn
void PrintTable()
{
	for(int i = 0; i < 9; i++)
	{
		std::cout << "[" << ConvertChoice(table[i]) << "]";
		if((i+1) % 3 == 0)
		{
			std::cout << std::endl;
		}
	}
}
//checks whether a move is possible, if yes: makes the move and switches player
bool ValidChoice()
{
	if(choice >= 0 && choice <9)
	{
		if(table[choice] == 0)
		{
			table[choice] = player + 1;
			player = !player;	
			return true;
		}
	}
	return false;

}

/*
A player wins by having completed a row, column or diagonal
If one of these conditions is met by player 1, the product of that row/column/diagonal will be 1
If the condition is instead met by player 2, the product will be 8
if neither player meets the condition, the product will be 0 - default value for each square
*/
bool WinCondition()
{
	int row, col, diag1, diag2;
	for(int i = 0; i < 3; i++)
	{
		row = table[3*i + 0] * table[3*i + 1] * table[3*i + 2];
		col = table[i + 0] * table[i + 3] *table[i + 6];
		if(row == 1 || col == 1)
		{
			break; 
		}
		if(row == 8 || col == 8)
		{
			break;
		}
	}
	diag1 = table[0] * table[4] * table[8];
	diag2 = table[2] * table[4] * table[6];

	if(row == 1 || col == 1 or diag1 == 1 || diag2 == 1)
	{
		winner = 1;
		return true;
	}
	if(row == 8 || col == 8 || diag1 == 8 || diag2 == 8)
	{
		winner = 2;
		return true;
	}
	//if no row or column has a product of 0, then there are no empty squares left in play
	//therefore the game is a draw
	for(int i = 0; i < 9; i++)
	{
		if(table[i] == 0)
		{
			return false;
		}
	}
	winner = 3;
	return true;
}

//Converts to human readable values
char ConvertChoice(int squareValue)
{
	if(squareValue == 0)
	{
		return '_';
	}
	else if(squareValue == 1)
	{
		return 'X';
	}
	return 'O';			
}

//Game logic 
bool Game()
{
	//reset game state
	player = 0;
	std::fill_n(table, 9, 0);
	PrintTable();
	do
	{
		std::cout << "It is: player " << player+1 << "'s turn." << std::endl;
		do
		{
			std::cout << "Enter your choice (1-9): ";
			std::cin >> choice;
			choice--;
		}
		while(!ValidChoice());
		PrintTable();
	}
	while(!WinCondition());
	if(winner != 3)
	{
		std::cout << "Congratulations! Player " << winner << " is the winner! Replay? y/n:  ";
	}
	else
	{
		std::cout << "Draw! Play again? y/n:  " << std::endl;
	}	
	std::cin >> replay;
	if(replay == 'y')
	{
		return true;
	}
	return false;
	
}
