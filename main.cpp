#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <unordered_map>
#include <exception>

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

  void setPosition(vector<int> new_pos){
    x = new_pos[0];
    y = new_pos[1];
  }

  bool isAlive(){
    return alive;
  }

  string getId(){
    return id; 
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
    // Check if in check with each state of the board
    bool check = is_in_check(board, pMap);
    if (check){
      cout << "You are in check!!!" << endl;
    }
    if (check){
      unordered_map<string, vector<vector<int>>> possible_moves = is_mate(board, pMap);
      if (check && possible_moves.size() == 0){
        return (turn) ? -1 : 1;
      }
    }
    pair<string, vector<int>> user_move = get_user_input();
    string piece_id = user_move.first;
    int nx = user_move.second[0];
    int ny = user_move.second[1];
    do_move(piece_id, nx, ny);

    turn = !turn;
    return 0;
  }

private:
  vector<vector<string>> board;  // Board state with piece identifiers
  unordered_map<string, unique_ptr<Piece>> pMap;  // Map of piece identifiers to pieces
  stack<pair<string, vector<int>>> moveHistory;
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

    pMap["BR1"] = make_unique<Rook>("BR1", PieceType::ROOK, false, 7, 0);
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

  bool is_in_check(const vector<vector<string>>& curr_board, const unordered_map<string, unique_ptr<Piece>>& curr_pMap) {
    string curr_king_id = (turn) ? "WK" : "BK";
    vector<int> curr_king_position = curr_pMap.at(curr_king_id)->getPosition();
    // get all the opposite player's moves
    //TODO: This can't call get_all_moves instead there should be a get raw moves function
    unordered_map<string, vector<vector<int>>> all_op_moves = get_all_possible_moves(!turn, curr_board, curr_pMap);

    for (const auto& pMoves: all_op_moves){
      for (const auto& move: pMoves.second){
        if (move[0] == curr_king_position[0] && move[1] == curr_king_position[1]){
          return true;
        }
      }
    }
    return false;
  }

  unordered_map<string, vector<vector<int>>> is_mate(const vector<vector<string>>& board, const unordered_map<string, unique_ptr<Piece>>& pMap) {
    // Checkmate detection logic
    // Placeholder: Implement logic to check if the current player is in checkmate
    unordered_map<string, vector<vector<int>>> possible_moves;
    return possible_moves;
  }

  pair<string, vector<int>> get_user_input(){
    pair<string, vector<int>> user_move;
    unordered_map<string, vector<vector<int>>> possible_moves = get_all_filtered_moves();
    string id;
    string move_idx;
    int move_idx_int;
    while(true){
      cout << "What piece ID would you like to move? " << endl;
      cin >> id;
      if (possible_moves.find(id) == possible_moves.end()){
        cout << "ID is not valid" << endl;
        continue;
      }

      cout << "Here are the available moves for this piece: " << endl;
      for (int i = 0; i < possible_moves.at(id).size(); i++){
        cout << i+1 << ":< " << possible_moves.at(id)[i][0] << ", " << possible_moves.at(id)[i][1] << "> " << endl; 
      }

      cin >> move_idx;
      try {
        move_idx_int = std::stoi(move_idx);
        if (move_idx_int >= possible_moves.at(id).size()){
          cout << "Invalid move index" << endl;
          continue;
        }
      } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        continue;
      } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
        continue;
      }
      user_move = {id, possible_moves.at(id)[move_idx_int]};
      break;

    }

    return user_move;
  }


  unordered_map<string, vector<vector<int>>> get_all_possible_moves(bool player,  const vector<vector<string>>& curr_board, const unordered_map<string, unique_ptr<Piece>>& curr_pMap){
    unordered_map<string, vector<vector<int>>> all_moves;
    for (const auto& pPiece: curr_pMap){
      const unique_ptr<Piece>& curr_piece = pPiece.second;
      if(curr_piece->getPlayer() != player || !curr_piece->isAlive()){
        continue;
      }
      vector<vector<int>> curr_piece_moves = curr_piece->getValidMoves(curr_board, curr_pMap);

      if (curr_piece_moves.size() != 0){

        all_moves[curr_piece->getId()] = curr_piece_moves;
      }
    }
    return all_moves;
  }

  // TODO: Need to add functionality for the case when the piece is moved
  unordered_map<string, vector<vector<int>>> get_all_filtered_moves(){
    auto possible_moves = get_all_possible_moves(turn, board, pMap);
    unordered_map<string, vector<vector<int>>> all_valid_moves;
    for (const auto& pMove: possible_moves){
      string curr_piece_id = pMove.first;
      for (const auto& move: pMove.second){
        do_move(curr_piece_id, move[0], move[1]);
        if (!is_in_check(board, pMap)){
          all_valid_moves[curr_piece_id].push_back(move);
        }
        undo_move();
      }
    }

    return all_valid_moves;
  }


  // Do a move and repeat the coordinates of the old position
  void do_move(const string& id, int nx, int ny){
    vector<int> curr_position = pMap[id]->getPosition();
    pMap[id]->setPosition({nx, ny});
    board[curr_position[0]][curr_position[1]] = "";
    board[nx][ny] = id;
    moveHistory.push({id, {curr_position[0], curr_position[1]}});
  }

  void undo_move(){
    pair<string, vector<int>> last_move = moveHistory.top();
    moveHistory.pop();
    vector<int> curr_position = pMap[last_move.first]->getPosition();
    pMap[last_move.first]->setPosition({last_move.second[0], last_move.second[1]});
    board[curr_position[0]][curr_position[1]] = "";
    board[last_move.second[0]][last_move.second[1]] = last_move.first;
  }

};





int main() {
  Chess game;
  // Additional game logic can be added here to play the game
  return 0;
}

