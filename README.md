# Chess_c
This is an implementation of chess in c where an emphasis is put on using as little memory as possible. Representing a board efficiently enables possibilities to examine more positions. Hopefully i will get around to implementing a simple "chess computer" using classic approaches like game-trees etc.   

## Representing pieces
Each peace is represented by 4 bit. This means one byte represents 2 pieces. 

The first bit represents the color - `0` for white, `1` for black

The pieces are represented like this:
```c
EMPTY = 0  // 0000
KING = 2   // 0100
BISHOP = 8 // 0010
ROOK = 6   // 0110
KNIGHT = 4 // 0001
PAWN = 10  // 0101
QUEEN = 14 // 0111
```
The pieces are assigned the numbers to make attributes easy to get with a single mask. 
1. **can move straight mask** : `0100` == `0100`
2. **can move straight only one piece** : `0110` == `0100`
3. **can move diagonal** : `0001` == `0001`
<!-- 4. **can move in an L shape** :  -->