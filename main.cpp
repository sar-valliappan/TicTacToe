#include <iostream>

void print_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool check_win(char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            std::cout << "Player " << player << " wins!";
            return true;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            std::cout << "Player " << player << " wins!";
            return true;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        std::cout << "Player " << player << " wins!";
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        std::cout << "Player " << player << " wins!";
        return true;
    }
    return false;
}

int main() {
    char board[3][3];
    char player = 'X';
    int row, col;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }

    while (true) {
        print_board(board);
        std::cout << "Player " << player << ", enter a row and column (0-2) to place your mark. Separated by a space: ";
        std::cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            std::cout << "Invalid move! Try again.";
            continue;
        }

        if (board[row][col] != ' ') {
            std::cout << "That space is already taken! Try again.";
            continue;
        }
        board[row][col] = player;
        check_win(board, player);

        switch (player) {
            case 'X':
                player = 'O';
                break;
            case 'O':
                player = 'X';
                break;
        }
    }
}