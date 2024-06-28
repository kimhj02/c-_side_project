#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

enum Color { WHITE, BLACK };
enum PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

class Board;

class Piece {
protected:
    Color color;
    PieceType type;
public:
    Piece(Color color, PieceType type) : color(color), type(type) {}
    virtual ~Piece() {}
    Color getColor() const { return color; }
    PieceType getType() const { return type; }
    virtual bool isValidMove(int startX, int startY, int endX, int endY, Board* board) = 0;
    virtual char getSymbol() = 0;
};

class King : public Piece {
public:
    King(Color color) : Piece(color, KING) {}
    bool isValidMove(int startX, int startY, int endX, int endY, Board* board) override;
    char getSymbol() override { return (color == WHITE) ? 'K' : 'k'; }
};

class Queen : public Piece {
public:
    Queen(Color color) : Piece(color, QUEEN) {}
    bool isValidMove(int startX, int startY, int endX, int endY, Board* board) override;
    char getSymbol() override { return (color == WHITE) ? 'Q' : 'q'; }
};

class Rook : public Piece {
public:
    Rook(Color color) : Piece(color, ROOK) {}
    bool isValidMove(int startX, int startY, int endX, int endY, Board* board) override;
    char getSymbol() override { return (color == WHITE) ? 'R' : 'r'; }
};

class Bishop : public Piece {
public:
    Bishop(Color color) : Piece(color, BISHOP) {}
    bool isValidMove(int startX, int startY, int endX, int endY, Board* board) override;
    char getSymbol() override { return (color == WHITE) ? 'B' : 'b'; }
};

class Knight : public Piece {
public:
    Knight(Color color) : Piece(color, KNIGHT) {}
    bool isValidMove(int startX, int startY, int endX, int endY, Board* board) override;
    char getSymbol() override { return (color == WHITE) ? 'N' : 'n'; }
};

class Pawn : public Piece {
public:
    Pawn(Color color) : Piece(color, PAWN) {}
    bool isValidMove(int startX, int startY, int endX, int endY, Board* board) override;
    char getSymbol() override { return (color == WHITE) ? 'P' : 'p'; }
};

class Board {
private:
    vector<vector<Piece*>> board;
public:
    Board() {
        board.resize(8, vector<Piece*>(8, nullptr));
    }
    ~Board() {
        for (auto& row : board) {
            for (auto& piece : row) {
                delete piece;
            }
        }
    }

    Piece* getPiece(int x, int y) const {
        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            return board[x][y];
        }
        return nullptr;
    }

    void setPiece(int x, int y, Piece* piece) {
        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            board[x][y] = piece;
        }
    }

    void display() const {
        for (int y = 7; y >= 0; y--) {
            for (int x = 0; x < 8; x++) {
                Piece* piece = board[x][y];
                if (piece) {
                    cout << piece->getSymbol() << ' ';
                }
                else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
};
bool King::isValidMove(int startX, int startY, int endX, int endY, Board* board) {
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    return (dx <= 1 && dy <= 1);
}

bool Queen::isValidMove(int startX, int startY, int endX, int endY, Board* board) {
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    return (dx == dy || startX == endX || startY == endY);
}

bool Rook::isValidMove(int startX, int startY, int endX, int endY, Board* board) {
    return (startX == endX || startY == endY);
}

bool Bishop::isValidMove(int startX, int startY, int endX, int endY, Board* board) {
    return (abs(endX - startX) == abs(endY - startY));
}

bool Knight::isValidMove(int startX, int startY, int endX, int endY, Board* board) {
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    return (dx * dy == 2);
}

bool Pawn::isValidMove(int startX, int startY, int endX, int endY, Board* board) {
    int direction = (color == WHITE) ? 1 : -1;
    if (startX == endX) {
        if ((endY - startY) == direction) {
            return true;
        }
        if ((color == WHITE && startY == 1 && endY == 3) || (color == BLACK && startY == 6 && endY == 4)) {
            return true;
        }
    }
    if (abs(startX - endX) == 1 && (endY - startY) == direction) {
        Piece* target = board->getPiece(endX, endY);
        return target != nullptr && target->getColor() != color;
    }
    return false;
}

class Player {
private:
    Color color;
    vector<Piece*> pieces;
public:
    Player(Color color) : color(color) {}
    Color getColor() const { return color; }
    bool movePiece(int startX, int startY, int endX, int endY, Board& board) {
        Piece* piece = board.getPiece(startX, startY);
        if (piece && piece->getColor() == color && piece->isValidMove(startX, startY, endX, endY, &board)) {
            board.setPiece(endX, endY, piece);
            board.setPiece(startX, startY, nullptr);
            return true;
        }
        return false;
    }
};

class Game {
private:
    Board board;
    Player whitePlayer;
    Player blackPlayer;
    Player* currentPlayer;
public:
    Game() : whitePlayer(WHITE), blackPlayer(BLACK), currentPlayer(&whitePlayer) 
    {
        setupBoard();
    }

    void setupBoard() 
    {
        for (int i = 0; i < 8; ++i) {
            board.setPiece(i, 1, new Pawn(WHITE));
            board.setPiece(i, 6, new Pawn(BLACK));
        }
        board.setPiece(0, 0, new Rook(WHITE));
        board.setPiece(7, 0, new Rook(WHITE));
        board.setPiece(0, 7, new Rook(BLACK));
        board.setPiece(7, 7, new Rook(BLACK));
        board.setPiece(1, 0, new Knight(WHITE));
        board.setPiece(6, 0, new Knight(WHITE));
        board.setPiece(1, 7, new Knight(BLACK));
        board.setPiece(6, 7, new Knight(BLACK));
        board.setPiece(2, 0, new Bishop(WHITE));
        board.setPiece(5, 0, new Bishop(WHITE));
        board.setPiece(2, 7, new Bishop(BLACK));
        board.setPiece(5, 7, new Bishop(BLACK));
        board.setPiece(3, 0, new Queen(WHITE));
        board.setPiece(3, 7, new Queen(BLACK));
        board.setPiece(4, 0, new King(WHITE));
        board.setPiece(4, 7, new King(BLACK));
    }

    void switchTurn() {
        if (currentPlayer == &whitePlayer) {
            currentPlayer = &blackPlayer;
        }
        else {
            currentPlayer = &whitePlayer;
        }
    }

    void start() {
        while (true) {
            board.display();
            cout << "현재 플레이어: " << (currentPlayer->getColor() == WHITE ? "백" : "흑") << endl;
            int startX, startY, endX, endY;
            cout << "이동할 기물의 위치 (x y): ";
            cin >> startX >> startY;
            cout << "이동할 위치 (x y): ";
            cin >> endX >> endY;

            if (currentPlayer->movePiece(startX, startY, endX, endY, board)) {
                switchTurn();
            }
            else {
                cout << "잘못된 이동입니다. 다시 시도하십시오." << endl;
            }
        }
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}
