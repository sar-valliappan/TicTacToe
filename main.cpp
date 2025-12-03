#include <iostream>
#include <random>

void print_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << " " << board[i][j] << " ";
            if (j < 2) std::cout << "|";
        }
        std::cout << "\n";
        if (i < 2) std::cout << "---+---+---\n";
    }
}

bool check_win(char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    return false;
}

bool is_tied(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

int minimax(char board[3][3], bool isMaximizing) {
    if (check_win(board, 'X')) return -10;
    if (check_win(board, 'O')) return 10;
    if (is_tied(board)) return 0;

    if (isMaximizing) {
        int best = std::numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = std::max(best, minimax(board, false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = std::numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = std::min(best, minimax(board, true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

void computer_move(char board[3][3]) {
    int bestVal = std::numeric_limits<int>::min();
    int bestRow = -1;
    int bestCol = -1;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(board, false);
                board[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }

    board[bestRow][bestCol] = 'O';
}

void game(char board[3][3], char choice) {
    char player = 'X';
    int row, col;
    while (true) {
        std::cout << "Player " << player << ", enter a row and column (1-3) to place your mark. Separated by a space: ";
        std::cin >> row >> col;
        if (std::cin.fail()) {
            std::cout << "Not an integer! Try again.\n";
            std::cin.clear();            
            std::cin.ignore(1000, '\n'); 
            continue;
        }
        row--;
        col--;

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            std::cout << "Invalid move! Try again.";
            continue;
        }

        if (board[row][col] != ' ') {
            std::cout << "That space is already taken! Try again.";
            continue;
        }

        board[row][col] = player;
        print_board(board);
        if (check_win(board, player)) {
            std::cout << "Player " << player << " wins!\n";
            break;
        }
        if (is_tied(board)) {
            std::cout << "It's a tie!\n";
            break;
        }
        if (choice == 'n') {
            switch (player) {
            case 'X':
                player = 'O';
                break;
            case 'O':
                player = 'X';
                break;
            }
        }
        if (choice == 'y') {
            computer_move(board);
            std::cout << "Computer's move:\n";
            print_board(board);
            if (check_win(board, 'O')) {
                std::cout << "The computer wins!\n";
                break;
            }
            if (is_tied(board)) {
                std::cout << "It's a tie!\n";
                break;
            }
        }
    }
}

int main() {
    char board[3][3];
    int row, col;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }

    std::cout << "Welcome to Tic Tac Toe!\n";
    std::cout << "Would you like to play against the computer? (y/n): ";
    char choice;
    std::cin >> choice;
    if (choice != 'y' && choice != 'n') {
        std::cout << "Invalid choice! Defaulting to human vs. human.\n";
        choice = 'n';
    }
    game(board, choice);
}