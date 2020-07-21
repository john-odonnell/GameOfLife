/* Represents game board for Conway's Game of Life
 * 
 * The index (0, 0) on the board is the upper left corner
 * and indecies progress in row-major order
 * 
 * RULES:
 *  Any live cell with fewer than 2 live neighbors dies
 *  Any live cell with 2 or 3 live neighbors lives
 *  Any live cell with more than 3 live nieghbors dies
 *  Any dead cell with exactly 3 live neighbors becomes a live cell
 */

class GOLBoard {
    private:
        int height;
        int width;
        int gen;

        // private member board: bool pointer
        // points to first element of board array allocation
        // can be indexed?
        bool* board;

        // recursive update function
        void _update(int i, int j, int height, int width);
        int _neighbors(int i, int j);
    
    public:
        // constructors and destructors
        GOLBoard();
        GOLBoard(int height, int width, bool* board);
        ~GOLBoard();

        // functions to return private members
        int get_height();
        int get_width();
        int get_generation();
        bool* get_board();
        bool get_cell(int i, int j);

        // functions to set private members
        void set_height(int height);
        void set_width(int width);
        void set_generation(int gen);
        void set_board(bool board[]);
        void set_cell(int i, int j, bool cell);

        // board update function
        void update();
        void print_board();
};