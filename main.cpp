#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

using namespace std;

enum class PieceType {
  PAWN,
  KING,
  QUEEN,
  ROOK,
  BISHOP,
  KNIGHT
};

// Base class for all chess pieces
class Piece {
protected:
  string id;
  PieceType type;
  bool player; // true for white, false for black
  int x, y;
  bool alive;

public:
  Piece(const string& id, PieceType type, bool player, int x, int y)
    : id(id), type(type), player(player), x(x), y(y), alive(true) {}

  virtual vector<vector<int>> getValidMoves(const vector<vector<string>>& board, const unordered_map<string, unique_ptr<Piece>>& pMap) = 0;

  bool getPlayer() {
    return player;
  }

  vector<int> getPosition(){
    return vector<int>({x, y});
  }



  virtual ~Piece() = default;
};

// Derived class for Pawn
class Pawn : public Piece {
public:
  Pawn(const string& id, PieceType type, bool player, int x, int y)
    : Piece(id, type, player, x, y) {}

  vector<vector<int>> getValidMoves(const vector<vector<string>>& board, const unordered_map<string, unique_ptr<Piece>>& pMap) override {
    vector<vector<int>> validMoves;
    int direction = player ? 1 : -1;  // White pawns move up (+1), black pawns move down (-1)

    // Single square move forward
    int nx = x + direction;
    if (nx >= 0 && nx <= 7) {
      if (board[nx][y] == "") {
        validMoves.push_back({nx, y});

        // Initial two-square move forward
        if ((player && x == 1) || (!player && x == 6)) {
          int nnx = x + 2 * direction;
          if (board[nnx][y] == "") {
            validMoves.push_back({nnx, y});
          }
        }
      }
    }

    // Diagonal captures
    vector<int> dy = {-1, 1};  // Left (-1) and right (1)
    for (int d : dy) {
      int ny = y + d;
      if (ny >= 0 && ny <= 7 && board[nx][ny] != "" && pMap.at(board[nx][ny])->getPlayer() != player) {
        validMoves.push_back({nx, ny});
      }
    }
    return validMoves;
  }
};

// Derived class for Rook (Placeholder for brevity)
class Rook : public Piece {
public:
    Rook(const string& id, PieceType type, bool player, int x, int y)
        : Piece(id, type, player, x, y) {}

    vector<vector<int>> getValidMoves(const vector<vector<string>>& board, const unordered_map<string, unique_ptr<Piece>>& pMap) override {
        vector<vector<int>> validMoves;

        // Directions for a rook (right, left, up, down)
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        for (const auto& dir : directions) {
            int dx = dir.first;
            int dy = dir.second;
            int nx = x;
            int ny = y;

            // Move in the current direction until out of bounds or blocked
            while (true) {
                nx += dx;
                ny += dy;

                // Check if the new position is within the board bounds
                if (nx < 0 || nx > 7 || ny < 0 || ny > 7) {
                    break;
                }

                // Check if the position is empty or has an opponent's piece
                if (board[nx][ny] == "") {
                    validMoves.push_back({nx, ny});
                } else {
                    if (pMap.at(board[nx][ny])->getPlayer() != player) {
                        validMoves.push_back({nx, ny});
                    }
                    break; // Rook can't move past this piece
                }
            }
        }

        return validMoves;
    }
};


// Derived class for Knight (Placeholder for brevity)
class Knight : public Piece {
public:
  Knight(const string& id, PieceType type, bool player, int x, int y)
    : Piece(id, type, player, x, y) {}

  vector<vector<int>> getValidMoves(const vector<vector<string>>& board, const unordered_map<string, unique_ptr<Piece>>& pMap) override {
        vector<vector<int>> validMoves;

        // Directions for a rook (right, left, up, down)
        vector<pair<int, int>> directions = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

        for (const auto& dir : directions) {
            int dx = dir.first;
            int dy = dir.second;
            int nx = x;
            int ny = y;

            // Move in the current direction until out of bounds or blocked

            nx += dx;
            ny += dy;

            // Check if the new position is within the board bounds
            if (nx < 0 || nx > 7 || ny < 0 || ny > 7) {
              continue;
            }

            // Check if the position is empty or has an opponent's piece
            if (board[nx][ny] == "") {
              validMoves.push_back({nx, ny});
            } else {
              if (pMap.at(board[nx][ny])->getPlayer() != player) {
                validMoves.push_back({nx, ny});
              }
            }
        }

        return validMoves;
    }
};

// Derived class for Bishop (Placeholder for brevity)
class Bishop : public Piece {
public:
  Bishop(const string& id, PieceType type, bool player, int x, int y)
    : Piece(id, type, player, x, y) {}

  vector<vector<int>> getValidMoves(const vector<vector<string>>& board, const unordered_map<string, unique_ptr<Piece>>& pMap) override {
        vector<vector<int>> validMoves;

        // Directions for a rook (right, left, up, down)
        vector<pair<int, int>> directions = {{1, 1}, {-1, -1}, {-1, 1}, {1, -1}};

        for (const auto& dir : directions) {
            int dx = dir.first;
            int dy = dir.second;
            int nx = x;
            int ny = y;

            // Move in the current direction until out of bounds or blocked
            while (true) {
                nx += dx;
                ny += dy;

                // Check if the new position is within the board bounds
                if (nx < 0 || nx > 7 || ny < 0 || ny > 7) {
                    break;
                }

                // Check if the position is empty or has an opponent's piece
                if (board[nx][ny] == "") {
                    validMoves.push_back({nx, ny});
                } else {
                    if (pMap.at(board[nx][ny])->getPlayer() != player) {
                        validMoves.push_back({nx, ny});
                    }
                    break;
                }
            }
        }

        return validMoves;
    }
};

// Derived class for Queen (Placeholder for brevity)
class Queen : public Piece {
public:
  Queen(const string& id, PieceType type, bool player, int x, int y)
    : Piece(id, type, player, x, y) {}

  vector<vector<int>> getValidMoves(const vector<vector<string>>& board, const unordered_map<string, unique_ptr<Piece>>& pMap) override {
        vector<vector<int>> validMoves;

        // Directions for a rook (right, left, up, down)
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};

        for (const auto& dir : directions) {
            int dx = dir.first;
            int dy = dir.second;
            int nx = x;
            int ny = y;

            // Move in the current direction until out of bounds or blocked
            while (true) {
                nx += dx;
                ny += dy;

                // Check if the new position is within the board bounds
                if (nx < 0 || nx > 7 || ny < 0 || ny > 7) {
                    break;
                }

                // Check if the position is empty or has an opponent's piece
                if (board[nx][ny] == "") {
                    validMoves.push_back({nx, ny});
                } else {
                    if (pMap.at(board[nx][ny])->getPlayer() != player) {
                        validMoves.push_back({nx, ny});
                    }
                    break; // Rook can't move past this piece
                }
            }
        }

        return validMoves;
    }
};

// Derived class for King (Placeholder for brevity)
class King : public Piece {
public:
  King(const string& id, PieceType type, bool player, int x, int y)
    : Piece(id, type, player, x, y) {}

  vector<vector<int>> getValidMoves(const vector<vector<string>>& board, const unordered_map<string, unique_ptr<Piece>>& pMap) override {
    vector<vector<int>> validMoves;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    string opKingId = (player) ? "BK" : "WK";
    vector<int> opKingPosition = pMap.at(opKingId)->getPosition();

    for (const auto& dir: directions){
      int dx = dir.first;
      int dy = dir.second;
      int nx = x + dx;
      int ny = y + dy;

      if (nx < 0 || nx > 7 ||ny < 0 || ny > 7){
        continue;
      }

      if (board[nx][ny] == "" || (board[nx][ny] != "" && pMap.at(board[nx][ny])->getPlayer() != player)){
        if(abs(opKingPosition[0] - nx) > 1 || abs(opKingPosition[1] - ny) > 1){
          validMoves.push_back({nx, ny});
        }
      }
    }

    return validMoves;
  }
};

// Chess class to manage the game
class Chess {
public:
  Chess() : turn(true), board(8, vector<string>(8, "")) {
    initializeBoard();
  }

  int move (){
    // Check if in check
    bool check = is_in_check(board, pMap);


    if (check){
      auto possible_moves = is_mate(board, pMap);
      if (possible_moves.size() == 0)
        return (player) ? 1:0;
      else {
        
      }
    }



    

  }

private:
  vector<vector<string>> board;  // Board state with piece identifiers
  unordered_map<string, unique_ptr<Piece>> pMap;  // Map of piece identifiers to pieces
  bool turn;  // Current turn: true for white, false for black

  string turnToStr() {
    return (turn) ? "W" : "B";
  }

  void initializeBoard() {
    // Initialize pawns
    for (int i = 0; i < 8; i++) {
      // White pawns
      pMap["WP" + to_string(i + 1)] = make_unique<Pawn>("WP" + to_string(i + 1), PieceType::PAWN, true, 1, i);
      board[1][i] = "WP" + to_string(i + 1);

      // Black pawns
      pMap["BP" + to_string(i + 1)] = make_unique<Pawn>("BP" + to_string(i + 1), PieceType::PAWN, false, 6, i);
      board[6][i] = "BP" + to_string(i + 1);
    }

    // Initialize rooks
    pMap["WR1"] = make_unique<Rook>("WR1", PieceType::ROOK, true, 0, 0);
    board[0][0] = "WR1";
    pMap["WR2"] = make_unique<Rook>("WR2", PieceType::ROOK, true, 0, 7);
    board[0][7] = "WR2";

    pMapp["BR1"] = make_unique<Rook>("BR1", PieceType::ROOK, false, 7, 0);
    board[7][0] = "BR1";
    pMap["BR2"] = make_unique<Rook>("BR2", PieceType::ROOK, false, 7, 7);
    board[7][7] = "BR2";

    // Initialize knights
    pMap["WN1"] = make_unique<Knight>("WN1", PieceType::KNIGHT, true, 0, 1);
    board[0][1] = "WN1";
    pMap["WN2"] = make_unique<Knight>("WN2", PieceType::KNIGHT, true, 0, 6);
    board[0][6] = "WN2";

    pMap["BN1"] = make_unique<Knight>("BN1", PieceType::KNIGHT, false, 7, 1);
    board[7][1] = "BN1";
    pMap["BN2"] = make_unique<Knight>("BN2", PieceType::KNIGHT, false, 7, 6);
    board[7][6] = "BN2";

    // Initialize bishops
    pMap["WB1"] = make_unique<Bishop>("WB1", PieceType::BISHOP, true, 0, 2);
    board[0][2] = "WB1";
    pMap["WB2"] = make_unique<Bishop>("WB2", PieceType::BISHOP, true, 0, 5);
    board[0][5] = "WB2";

    pMap["BB1"] = make_unique<Bishop>("BB1", PieceType::BISHOP, false, 7, 2);
    board[7][2] = "BB1";
    pMap["BB2"] = make_unique<Bishop>("BB2", PieceType::BISHOP, false, 7, 5);
    board[7][5] = "BB2";

    // Initialize queens
    pMap["WQ"] = make_unique<Queen>("WQ", PieceType::QUEEN, true, 0, 3);
    board[0][3] = "WQ";
    pMap["BQ"] = make_unique<Queen>("BQ", PieceType::QUEEN, false, 7, 3);
    board[7][3] = "BQ";

    // Initialize kings
    pMap["WK"] = make_unique<King>("WK", PieceType::KING, true, 0, 4);
    board[0][4] = "WK";
    pMap["BK"] = make_unique<King>("BK", PieceType::KING, false, 7, 4);
    board[7][4] = "BK";
  }

  bool is_in_check(const vector<vector<string>>& board, const unordered_map<string, unique_ptr<Piece>>& pMap) {
    // Check detection logic
    // Placeholder: Implement logic to check if the current player's king is in check
    return false;
  }

  unordered_map<string, vector<vector<int>>> is_mate(const vector<vector<string>>& board, const unordered_map<string, unique_ptr<Piece>>& pMap) {
    // Checkmate detection logic
    // Placeholder: Implement logic to check if the current player is in checkmate
    return false;
  }

  id take_user_input(){
    string id = cin >> "What piece would you like to move? " << endl;
    if (pMap.find(id) == pMap.end() || pMap.at(id)->alive == false){
      cout << "Invalid move" << endl;
    } else {
      // NEED TO GET THE valid moves and get the user input 
      return id;
    }
  }
};

int main() {
  Chess game;
  // Additional game logic can be added here to play the game
  return 0;
}

