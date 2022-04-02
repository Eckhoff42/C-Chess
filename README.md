# Chess_c
This is an implementation of chess in c where an emphasis is put on using as little memory as possible. Representing a board efficiently enables possibilities to examine more positions. Hopefully i will get around to implementing a simple "chess computer" using classic approaches like game-trees etc.

## How to run the program:
**How to run the main program:**
1. Clone the directory
2. Navigate into the project folder
3. run  
  - ```bash
    make run
    ```

**How to run the test**
1. Clone the directory
2. Navigate into the project folder
3. run  
  - ```bash
    make runtest
    ```

## Demo
Demo is coming later

## Implementation details

### Representing pieces
Each peace is represented by 4 bit. This means one byte represents 2 pieces. 

The first bit represents the color - `0` for white, `1` for black

The pieces are represented like this:
```c
EMPTY = 0  // 0000
PAWN = 2   // 0100
ROOK = 6   // 0110
QUEEN = 14 // 0111
KING = 10  // 0101
BISHOP = 8 // 0001
KNIGHT = 4 // 0010
```

The pieces are assigned the numbers to make attributes easy to get with a single mask. 
1. **can move straight mask** : `0100` == `0100`
2. **can move straight only one piece** : `0110` == `0100`
3. **can move diagonal** : `0001` == `0001`
<!-- 4. **can move in an L shape** :  -->

### Representing a board
A typical chess board is 8x8 with 32 pieces. This is represented as a 8*4 char-array. One game position uses 32 byte without any compression.

```
     0   1   2   3    <-- x values
   ----------------|
 1 |   |   |   |   |
   ----------------|
 2 |   |   |   |   |
   ----------------|
 3 |   |   |   |   |
   ----------------|
 4 |   |   |   |   |
   ----------------|
 5 |   |   |   |   |
   ----------------|
 6 |   |   |   |   |
   ----------------|
 7 |   |   |   |   |
   ----------------|
 ^--- y values
```