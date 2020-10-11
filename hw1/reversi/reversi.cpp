#include <vector>
#include <stdexcept>

#include "reversi.h"

using namespace std;




void Square::flip()
{
    switch (value_)
    {
    case WHITE:
        value_ = BLACK;
        break;
    case BLACK:
        value_ = WHITE;
        break;
    default:
        break;
    }
}

Square::SquareValue opposite_color(Square::SquareValue value)
{
    switch (value)
    {
    case Square::WHITE:
        return Square::BLACK;
    case Square::BLACK:
        return Square::WHITE;
    default:
        throw invalid_argument("Illegal square value");
    }
}







Square& Board::operator()(char row, size_t column)
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

Square const& Board::operator()(char row, size_t column) const
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

bool Board::is_legal_and_opposite_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] != Square::FREE && squares_[row_index][column - 1] != turn;
    }
    return false;
}

bool Board::is_legal_and_same_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] == turn;
    }
    return false;
}

bool Board::is_valid_location(char row, size_t column) const
{
    size_t row_index = row_to_index(row);
    return row_index < dimension_ && column - 1 < dimension_;
}

Checkpoint::Checkpoint(const Board& b, Square::SquareValue turn) :
    board_(b),
    turn_(turn)
{

}

ostream& Board::print(ostream& out) const
{
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        if (i < 10)
        {
            out << " ";
        }
        else
        {
            out << (i / 10);
        }
    }
    out << endl;
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        out << (i % 10);
    }
    out << endl;
    for (size_t i = 0; i < dimension_; i++)
    {
        out << (char)('a' + i) << ':';
        for (size_t k = 0; k < dimension_; k++)
        {
            out << squares_[i][k];
        }
        out << endl;
    }
    return out;
}



void Reversi::prompt() const
{
    cout << board_ << endl;
    cout << (turn_ == Square::BLACK ? "B" : "W");
    cout << " - Enter 'p r/c', 'q', 'c', 'u':" << endl;
}

void Reversi::win_loss_tie_message(size_t white_count, size_t black_count)
{
    cout << board_ << endl;
    if (white_count > black_count)
    {
        cout << "W wins" << endl;
    }
    else if (white_count < black_count)
    {
        cout << "B wins" << endl;
    }
    else
    {
        cout << "Tie" << endl;
    }
    cout << "W=" << white_count << "/B=" << black_count << endl;
}

bool Reversi::is_legal_choice(char row, size_t column, Square::SquareValue turn) const
{
    // Vectors for each cardinal direction
    const size_t direction_count = 8;
    const int direction_row[] =    {-1, -1,  0, +1, +1, +1,  0, -1};
    const int direction_column[] = { 0, -1, -1, -1,  0, +1, +1, +1};

    // Make sure location is free
    if (board_(row, column) != Square::FREE)
    {
        return false;
    }

    // Now check in each directions
    for (size_t d = 0; d < direction_count; d++)
    {
        // Where we're checking
        char cursor_row = row + direction_row[d];
        size_t cursor_column = column + direction_column[d];

        // Move towards the direction while we're on the opposite color
        bool found_opposite = false;
        while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_))
        {
            found_opposite = true;
            cursor_row += direction_row[d];
            cursor_column += direction_column[d];
        }

        // Check if the next thing after is our color
        bool found_same = board_.is_legal_and_same_color(cursor_row, cursor_column, turn_);

        // If this direction is valid, the move is valid, so short circuit and return
        if (found_opposite && found_same) {
            return true;
        }
    }
    return false;
}

bool Reversi::is_game_over() const
{
    for (unsigned char row = 'a'; row < 'a' + board_.dimension(); row++)
    {
        for (size_t column = 1; column <= board_.dimension(); column++)
        {
            if (is_legal_choice(row, column, turn_))
            {
                return false;
            }
        }
    }
    return true;
}


/*------------------- STUDENT TO WRITE -----------------*/
/**
 * Assigns the internal SquareValue enumeration
 * to the provided input argument.
 * Note: The input is a SquareValue not a full Square
 */
Square& Square::operator=(SquareValue value) {
    //Square temp;
    this->value_ = value;
    return *this;
}


bool Square::operator==(SquareValue value) const {
    return (value_ == value);
}

bool Square::operator!=(SquareValue value) const {
    return !(value_ == value);
}

/**
*  ostream operator for a Square object that outputs
*    '-' for FREE, 'B' for BLACK, and 'W' for WHITE.
*  Note: Since data members in the Square struct are public
*    we do not need to make this a friend function.
*/
std::ostream& operator<<(std::ostream& out, const Square& square) {
    if(square.value_ == 1) {
        out << 'W';
    } else if(square.value_ == 2) {
        out << 'B';
    } else {
        out << '-';
    }
    return out;
}





//BOARD
/**
* Initializing constructor
*/
Board::Board(size_t s) {

    dimension_ = s;
    squares_ = new Square*[s];
    for(size_t i = 0; i < s; i++) {
        squares_[i] = new Square[s];
    }
}

//copy constructor
Board::Board(const Board& rhs) {
    dimension_ = rhs.dimension_;
    squares_ = new Square*[rhs.dimension_];
    for(size_t i = 0; i < dimension_; i++) {
        squares_[i] = new Square[dimension_];
    }

    for(size_t i = 0; i < dimension_; i++) {
        for(size_t j = 0; j < dimension_; j++) {
            squares_[i][j] = rhs.squares_[i][j];
        }
    }
}

//board destructor
Board::~Board() {

    for(size_t i = 0; i < dimension_; i++) {
        delete [] squares_[i];
    }
    delete [] squares_;
}

/**
*  Outputs the board
*  Should be a simple wrapper for Board::print().
*/
std::ostream& operator<<(std::ostream& out, const Board& board) {
    board.print(out);
    return out;
}


/**
* Constructs the board of a given side length (dimension)
* Should set the middle 2x2 elements of the board to:
*    BW
*    WB
*/
Reversi::Reversi(size_t size) : board_(size), turn_(Square::BLACK) { //, history_(Checkpoint c(board_, Square::BLACK)) {
    size_t mid = size / 2;

    board_('a' -1+ mid, mid) = Square::BLACK;
    board_('a'-1 + mid, mid + 1) = Square::WHITE;
    board_('a' + mid, mid) = Square::WHITE;
    board_('a'+ mid, mid + 1) = Square::BLACK;

}

void Reversi::play() {

    bool gameOver = false;
    
    while(!is_game_over()) {
        prompt();

        cin >> action;
        if(action == 'p') {
            cin >> row >> clmn;
        }
        //size_t clmn = column - '0';
        //if(column2 >= 0 && column2 <= )
        if(action == 'p') {
            
            if (is_legal_choice(row,clmn, turn_)) {
                 
                board_(row, clmn) = turn_;
                 // Vectors for each cardinal direction
                const size_t direction_count = 8;
                const int direction_row[] = {-1, -1,  0, +1, +1, +1,  0, -1};
                const int direction_column[] = { 0, -1, -1, -1,  0, +1, +1, +1};


                // Now check in each directions
                for (size_t d = 0; d < direction_count; d++)
                {
                    // Where we're checking
                    char cursor_row = row + direction_row[d];
                    size_t cursor_column = clmn + direction_column[d];

                    // Move towards the direction while we're on the opposite color
                    bool found_opposite = false;
                    while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_))
                    {
                        found_opposite = true;
                        cursor_row += direction_row[d];
                        cursor_column += direction_column[d];
                    }
                    bool found_same = board_.is_legal_and_same_color(cursor_row, cursor_column, turn_);

                    // Where we're checking
                    cursor_row = row + direction_row[d];
                    cursor_column = clmn + direction_column[d];

                    // Move towards the direction while we're on the opposite color
                    
                    while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_))
                    {
                        if (found_opposite && found_same) {
                            if((size_t)(cursor_row-'a') < board_.dimension() && clmn - 1 < board_.dimension()){
                                
                                board_(cursor_row, cursor_column).flip();
                                
                            }
                        }
                        cursor_row += direction_row[d];
                        cursor_column += direction_column[d];
                    }

                }

                if(turn_ == Square::WHITE) {
                    turn_ = Square::BLACK;
                } else {
                    turn_ = Square::WHITE;
                }
            } else {
                continue;
            }
        } else if(action == 'c') {
            
            save_checkpoint();
            continue;
        } else if(action == 'u') {
            undo();
            //prompt();
            continue;
        } else {
            gameOver = true;
            for (unsigned char row = 'a'; row < 'a' + board_.dimension(); row++) {
                for (size_t column = 1; column <= board_.dimension(); column++) {
                    if(board_(row,column) == Square::WHITE) {
                        white_count++;
                    } else if(board_(row,column) == Square::BLACK) {
                        black_count++;
                    }
                }
            }
            win_loss_tie_message(white_count, black_count);
            break;
        }     

     if(is_game_over() || gameOver){
        if(!gameOver) {
            for (unsigned char row = 'a'; row < 'a' + board_.dimension(); row++) {
                for (size_t column = 1; column <= board_.dimension(); column++) {
                    if(board_(row,column) == Square::WHITE) {
                        white_count++;
                    } else if(board_(row,column) == Square::BLACK) {
                        black_count++;
                    }
                }
            }
        }
        win_loss_tie_message(white_count, black_count);
        break;
     } 
    }
    cout << board_ << endl;
}



/**
* Makes a checkpoint of the current board and player turn
* and saves it in the history vector
*/
void Reversi::save_checkpoint() {
    Checkpoint c(board_, turn_);
    history_.push_back(c);
}

/**
* Overwrites the current board and player turn with the
*  latest saved checkpoint. If no checkpoint is available
*  simply return.
*/
void Reversi::undo() {
    this->board_ = history_.back().board_;
    this->turn_ = history_.back().turn_;
    history_.pop_back();
}

Board& Board::operator=(const Board& rhs) {
    this->dimension_ = rhs.dimension_;  // Dimension
    this->squares_ = rhs.squares_;
    return *this;
}