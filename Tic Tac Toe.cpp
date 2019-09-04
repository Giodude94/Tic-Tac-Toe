// 08/20/2019  Giovanni Vega
// This is tic tac toe game that uses simple text graphics and a basic A.I.
// I coded this by using the book Beginning C++ Through Game Programming as a reference.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <locale>

using namespace std;

//Function prototypes 
void instructions();
void displayBoard(const vector<char> &board);
void makeMove(vector<char> &board, int choice, char marker);
bool validMove(int choice, const vector<char> &board);
char winCheck(const vector<char> &baord);
char setPiece(char &human);
char opponent(char peice);
int computerMove(vector<char> board, char computer);
int humanMove(vector<char> &board, char human);
void announceWinner(char winner, char computer, char human);


int main (){
	int choice = 0;
	char turn = ' ';
	char human = ' ';
	char computer = ' ';
	
	char X = 'X';
	char O = 'O';
	
	vector <char> board(9, ' ');
	
	instructions();
	
	setPiece(human);
	computer = opponent(human);
	turn = 'X';//X's always go first.
	
	while(winCheck(board) == 'N'){//Game loop that checks to see if there is a winner after every move is made.
		if(turn == human){
			
			choice = humanMove(board,human);
			board[choice] = human;	
		}
		
		else{
		choice = computerMove(board,computer);
		board[choice] = computer;
		}
		
		displayBoard(board);
		turn = opponent(turn);
	}
	
	announceWinner(winCheck(board), computer, human);
	
	
	
	return 0;
}

//Functions

void instructions(){
	cout << "This program let's you play Tic-Tac-Toe against an AI." << endl
	     << "Here is the board: "<< endl
	     << "\n\n\t 0 | 1 | 2" << endl
		 << "\t"<<"-----------" <<endl
		 << "\t 3 | 4 | 5"<< endl
		 << "\t"<<"-----------" <<endl
		 << "\t 6 | 7 | 8 "<< endl;
}
void displayBoard(const vector<char> &board){ //Passing by reference is efficient compared to by value. Since passing by value makes a copy. Constant reference means the values are safe from being changed in this func.
	
	cout << "\n\n\t"<<board[0] << " | " << board[1] << " | " << board[2]<< endl
		 << "\t"<<"---------" <<endl
		 << "\t"<<board[3] << " | " << board[4] << " | " << board[5]<< endl
		 << "\t"<<"---------" <<endl
		 << "\t"<<board[6] << " | " << board[7] << " | " << board[8]<< endl
		 << "\n\n-------------------------------------------------"<<endl;
		 
}
bool validMove(int choice, const vector<char> &board){
	if(choice < 0 || choice > 8){
		return false;
	}
	else if(board.at(choice) != ' ' ){
		return false;
	} 
	
	return true;
}
char winCheck(const vector<char> &board){ //By returning a char instead of a bool we can return the piece if they are all the same. Which we can use in our AI move function to check for the next move.
	const int winningRows[8][3] = {
		{0,1,2},
		{0,4,8},
		{0,3,6},
		{1,4,7},
		{6,4,2},
		{2,5,8},
		{3,4,5},
		{6,7,8} };
	const int TOTAL_ROWS = 8; //There are 8 total rows that can win the game. 	
		
	for(int rows = 0; rows < TOTAL_ROWS; rows++){ //Checking the chars in each spot to see if they are the same 3 char in the winning spots. If so there is a winner.
		if(board[winningRows[rows][0]] != ' ' &&
		board[winningRows[rows][0]] == board[winningRows[rows][1]] &&
		board[winningRows[rows][1]] == board[winningRows[rows][2]])
		 	return board[winningRows[rows][0]]; //If there is a winner then return the winning character.
	}
	
	
	
	if(count(board.begin(), board.end(), ' ') == 0){//There are no more empty spaces. Therefore if we don't find a winning row and there are no more spaces then game is a tie.
		return 'T' ;//T is used if there is a tie.
	}
	
	return 'N'; //N is used for if the game is not over yet
	
}
char setPiece(char &human){
	char choice = ' ';
	
	cout << "Would you like to go first? (Y/N) \n";
	cin >> choice;
	if(choice == 'Y' || choice == 'y'){
		return human = 'X';
			
	}
	else{
		cout <<"I'll go first then. \n";
		return human = 'O';
	}

}
char opponent(char piece){//Setting the opponents piece.
	if(piece == 'X')
		return 'O';
	else
		return 'X';
}


int computerMove(vector<char> board, char computer){
	//First priority would be to make the winning move.
	bool found = false;
	int move = 0;
	
	
	while(!found && move < board.size()){//
		
		if(validMove(move,board)){//Check to see if the space selection is empty.
			
			board[move] = computer;
		
			found = winCheck(board) == computer;
			
		
			board[move] = ' '; 
		}
		if(!found){
			move++;
		}
		
	}
	
	//Second priority is to block the opponent from winning.
	if(!found){
		
		move = 0;
		char human = opponent(computer); //returns the piece that the opponent is using.
	
		while(!found && move < board.size()){
			
			if (validMove(move,board)){
			
				board[move] = human;
			
			
				found = winCheck(board) == human;
			
				board[move] = ' ';
			}
			if(!found){
				move++;
			}
		}
	}	
	
	//Third and last priority is to make a strategic move from a list of space priorities.
	if(!found){
	
		move = 0;
		const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7}; //Order of moves for the computer to take.
		
		while(!found && move < board.size()){
			if(validMove(BEST_MOVES[move],board)){
				move = BEST_MOVES[move];
				found = true;
			}
			else {
				move++;
			}
			
		}
	}	
	
	
	cout<< "I will make my move onto space " << move << "." << endl;
	return move;
	
	
}	
int humanMove(vector<char> &board, char human){
	int choice = NULL;
	bool correctInput = false;

	cout << "Where would you like to make your move? (0-8)" << endl;
	//Clearing the buffer in case the user inputs something invalid in the previous question.
	cin.clear();
	cin.ignore(256,'\n');
	
	while(!correctInput){
		if(!(cin >> choice)){
			cout << "Please enter a number." <<endl;
			cin.clear();
			cin.ignore(256,'\n');
		}
		else if(!validMove(choice,board)){
			cout << "Please choose a valid spot. (0-8)" << endl;
		}
		else{
			correctInput = true;
		}
	}
	
	return choice;
}

void announceWinner(char winner, char computer, char human){
	if(winner == computer){
		cout << "I have won. Better luck next time human."<<endl;
	}
	
	else if (winner == human){
		cout << "You have beat me. I will be victorious next time." <<endl;
	}
	
	else{
		cout <<"There is no winner." <<endl;
	}
}




	
