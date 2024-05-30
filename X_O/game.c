#include <stdio.h>

void displayBoard(char board[3][3]) {
  printf("\n#############");
  printf("\n# %c | %c | %c #",board[0][0],board[0][1],board[0][2]);
  printf("\n#===========#");
  printf("\n# %c | %c | %c #",board[1][0],board[1][1],board[1][2]);
  printf("\n#===========#");
  printf("\n# %c | %c | %c #",board[2][0],board[2][1],board[2][2]);
  printf("\n#############\n");
    
}


// Function to check if someone has won
int checkWinner(char board[3][3], char symbol) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return 1;
        }
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) {
            return 1;
        }
    }

    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
        return 1;
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
        return 1;
    }

    return 0; // No winner yet
}

// Main function for the game
void Game() {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    char player1 = 'X';
    char player2 = 'O';
    int currentPlayer = 1;

    printf("Welcome to Tic Tac Toe!\n");

    for (int turn = 0; turn < 9; ++turn) {
        displayBoard(board);

        int row, col;
        printf("Player %d, enter coordinates (row column): ", currentPlayer);
        scanf("%d %d", &row, &col);
        while(row < 4 && row > 0 && col < 4 col row > 0 ){
          printf("Wrong, you should enter the rows and columns between 1 and 3\nInput: ");
          scanf("%d %d", &row, &col);
        }

        if (board[row][col] == ' ') {
            if (currentPlayer == 1) {
                board[row][col] = player1;
            } else {
                board[row][col] = player2;
            }
        } else {
            printf("Cell already occupied! Choose another cell.\n");
            --turn; // Repeat the turn for the same player
        }

        if (checkWinner(board, player1)) {
            displayBoard(board);
            printf("Player 1 (X) wins! Congratulations!\n");
            break;
        } else if (checkWinner(board, player2)) {
            displayBoard(board);
            printf("Player 2 (O) wins! Congratulations!\n");
            break;
        }

        currentPlayer = 3 - currentPlayer; // Switch players
    }

    if (!checkWinner(board, player1) && !checkWinner(board, player2)) {
        displayBoard(board);
        printf("It's a draw! The game is over.\n");
    }
}
