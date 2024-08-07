#include <iostream>
#include <vector>

class TicTacToe {
public:
    TicTacToe();
    void playGame();

private:
    void printBoard();
    bool makeMove(int player);
    bool checkWin(int player);
    bool isBoardFull();
    char getSymbol(int player);

    std::vector<std::vector<char>> board;
};

TicTacToe::TicTacToe() {
    board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
}

void TicTacToe::printBoard() {
    std::cout << "  0 1 2\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < 3; ++j) {
            std::cout << board[i][j];
            if (j < 2) std::cout << "|";
        }
        std::cout << "\n";
        if (i < 2) std::cout << "  -+-+-\n";
    }
}

bool TicTacToe::makeMove(int player) {
    int row, col;
    std::cout << "Player " << player << " (" << getSymbol(player) << "), enter row and column: ";
    std::cin >> row >> col;

    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = getSymbol(player);
        return true;
    } else {
        std::cout << "Invalid move. Try again.\n";
        return false;
    }
}

bool TicTacToe::checkWin(int player) {
    char symbol = getSymbol(player);

    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||
            (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
        (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)) {
        return true;
    }

    return false;
}

bool TicTacToe::isBoardFull() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == ' ')
                return false;
    return true;
}

char TicTacToe::getSymbol(int player) {
    return player == 1 ? 'X' : 'O';
}

void TicTacToe::playGame() {
    int player = 1;
    while (true) {
        printBoard();
        if (makeMove(player)) {
            if (checkWin(player)) {
                printBoard();
                std::cout << "Player " << player << " (" << getSymbol(player) << ") wins!\n";
                break;
            }
            if (isBoardFull()) {
                printBoard();
                std::cout << "It's a draw!\n";
                break;
            }
            player = 3 - player; // Switch player
        }
    }
}

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}
