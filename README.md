# C++ language side project
## 1. Purpose
1) Mastery of Object-Oriented Programming
2) Mastery of the C++ Language
   <br>
## 2. Duration
24.06.25 ~ 24.08.30

## 3. Project
### 1) Combat Simulation Utilizing Object-Oriented Programming

(1) Two players take turns playing the game. <br>
(2) Before the game starts, the health, mana, attack power, and defense of the player objects can be determined. <br>
(3) Players can choose one of four actions: move, attack, special attack, or heal. <br>
(4) Movement allows the player to move one square in the X or Y direction on a 2D grid. <br>
(5) Attack allows the player to attack an opponent within one square. <br>
(6) Special attack consumes mana to attack an opponent within one square. <br>
(7) Heal consumes mana to restore health. <br>
(8) Players take turns performing these actions, and the player who reduces the opponent's health to zero wins the game. <br>
### 2) Chess Game Using Object-Oriented Programming

#### 1. Overview
The chess game is implemented using object-oriented programming principles. Two players take turns playing the game on an 8x8 board, moving their pieces according to the rules of chess. The game supports the movement of all standard chess pieces: King, Queen, Rook, Bishop, Knight, and Pawn.

#### 2. Players
1. **Two Players**: One player controls the white pieces, and the other controls the black pieces. 
2. **Turn-Based Play**: Players alternate turns to move their pieces.

#### 3. Game Setup
1. **Initial Board Setup**: 
   - Each player starts with their pieces arranged in the standard chess layout.
   - Pawns are placed on the second and seventh ranks.
   - Rooks, Knights, Bishops, Queen, and King are placed on the first and eighth ranks respectively.

#### 4. Pieces and Movement
1. **King**:
   - Moves one square in any direction.
   - Symbol: 'K' for White, 'k' for Black.
2. **Queen**:
   - Moves any number of squares along a rank, file, or diagonal.
   - Symbol: 'Q' for White, 'q' for Black.
3. **Rook**:
   - Moves any number of squares along a rank or file.
   - Symbol: 'R' for White, 'r' for Black.
4. **Bishop**:
   - Moves any number of squares diagonally.
   - Symbol: 'B' for White, 'b' for Black.
5. **Knight**:
   - Moves in an L-shape: two squares in one direction and then one square perpendicular.
   - Symbol: 'N' for White, 'n' for Black.
6. **Pawn**:
   - Moves forward one square, with the option to move two squares forward from its initial position.
   - Captures diagonally.
   - Symbol: 'P' for White, 'p' for Black.

#### 5. Valid Moves
- Each piece type has a specific rule for valid movements, which is implemented in their respective `isValidMove` method.
- Pieces cannot move through other pieces, except for the Knight.
- Pawns have special rules for capturing and initial double-square movement.

#### 6. Game Actions
1. **Move Piece**: Players input the starting and ending coordinates for the piece they wish to move.
   - The game checks if the move is valid according to the piece's movement rules.
   - If valid, the piece is moved to the new location.
   - The turn is then switched to the other player.
   - If the move is invalid, the player is prompted to try again.

#### 7. Display
- The board is displayed in the console, showing the current positions of all pieces.
- Empty squares are represented by a dot ('.').

#### 8. Game Loop
- The game runs in a loop, displaying the board and prompting the current player for their move.
- The loop continues until a player wins by checkmating the opponent's king.

#### 9. Example Usage
```cpp
int main() {
    Game game;
    game.start();
    return 0;
}
```
- This code initializes the game and starts the main game loop.

This implementation uses object-oriented principles to model the chess pieces, their behaviors, and the overall game mechanics, providing a structured and extendable codebase for the chess game.
