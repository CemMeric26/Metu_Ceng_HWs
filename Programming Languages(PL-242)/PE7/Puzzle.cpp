#include "Puzzle.h"


/****************************************************/
/****              *** PUZZLE ***                ****/

/* Contsructor : It takes three integers in the following order:
    The first argument is size of the puzzle which is 2^N for some N >= 0.
    The second argument is the initial row id of the puzzle.
    The third argument is the initial column id of the puzzle.
    
    After initialization with the above arguments, the necessary 
    pointers should be initialized to NULL.
    Note that the final row id in this puzzle is equal to: 
       initial_row_id + size - 1.
    Note that the final column id in this puzzle is equal to: 
       initial_column_id + size - 1.
       
    ATTENTION: If a sub-puzzle member does not include any Piece, namely, 
    if its piece is NULL, then do NOT construct it. In other words, do 
    NOT construct subpuzzles unless they are required. 
*/
Puzzle::Puzzle(int size, int first_row, int first_column ) {
    // TODO
    
    this->size=size;
    this->first_row=first_row;
    this->first_column= first_column;   
    this->bottom_left=NULL;
    this->bottom_right=NULL;
    this->top_left=NULL;
    this->top_right=NULL;
    this->piece=NULL;

}

/* Destructor  : It should destruct its sub-puzzles, yet it is NOT responsible
   of the destruction of its Piece member.
*/
Puzzle::~Puzzle() {
    // TODO
   if(bottom_left)
        delete bottom_left;bottom_left=NULL;
    if(bottom_right)
        delete bottom_right; bottom_right=NULL;
    if(top_left)
        delete top_left; top_left=NULL;
    if(top_right)
        delete top_right; top_right=NULL;
  


}

/* Copy constructor : It totally applies deep copy except the Piece
   member part. Do not deep copy Piece objects of the puzzle, instead
   do shallow copy for Pieces.
*/
Puzzle::Puzzle(const Puzzle& puzzle) {
    // TODO
   this->size= puzzle.size;
    this->first_row=puzzle.first_row;
    this->first_column= puzzle.first_column;


  
    if(puzzle.size==1)
    {
        this->piece = puzzle.piece;
        this->bottom_left=NULL;
        this->bottom_right=NULL;
        this->top_left=NULL;
        this->top_right=NULL;
        
    }
    else
    {
        if(puzzle.bottom_left)
       { this->bottom_left= new Puzzle(*(puzzle.bottom_left)); this->bottom_left->piece= puzzle.bottom_left->piece;}
    else
       { this->bottom_left=NULL;  
       //this->bottom_left= new Puzzle(size/2,first_row+(size/2),first_column); this->bottom_left->piece= puzzle.bottom_left->piece;
       }

    if(puzzle.bottom_right)
    {        this->bottom_right= new Puzzle(*(puzzle.bottom_right));this->bottom_right->piece= puzzle.bottom_right->piece;}
    
    else
       { this->bottom_right=NULL; 
       //this->bottom_right= new Puzzle(size/2,first_row+(size/2),first_column+(size/2)); this->bottom_right->piece= puzzle.bottom_right->piece;
       }
    
    if(puzzle.top_left)
        {this->top_left= new Puzzle(*(puzzle.top_left)); this->top_left->piece= puzzle.top_left->piece;}
    else
        { this->top_left=NULL;
        //this->top_left= new Puzzle(size/2,first_row,first_column); this->top_left->piece= puzzle.top_left->piece;
        }

    if(puzzle.top_right)
        {this->top_right= new Puzzle(*(puzzle.top_right));this->top_right->piece= puzzle.top_right->piece;}
    else
    { this->top_right=NULL;
    //this->top_right= new Puzzle(size/2,first_row,first_column+(size/2)); this->top_right->piece= puzzle.top_right->piece;
    }
    }
    


}

/* Assignment operator : It totally applies shallow copy.
*/
Puzzle& Puzzle::operator=(const Puzzle& puzzle) {
    // TODO
    this->size=puzzle.size;
    this->first_row=puzzle.first_row;
    this->first_column= puzzle.first_column;
    this->bottom_left=puzzle.bottom_left;
    this->bottom_right=puzzle.bottom_right;
    this->top_left=puzzle.top_left;
    this->top_right=puzzle.top_right;
    this->piece=puzzle.piece;

    return *this;

}

/* This method directly assigns (without copying) the given Piece object to
   the corresponding sub-puzzle (cell) whose indices given in the second 
   argument in array form as follows <row_id, column_id>.
   
    ATTENTION: If a sub-puzzle member does not include any Piece, namely, 
    if its piece is NULL, then do NOT construct it. In other words, do 
    NOT construct subpuzzles unless they are required.
*/
//don't forget to  check edges later when you placing pieces
void Puzzle::placePiece(const Piece& piece, int location[2]) {
    // TODO
    if(size==1)
    {
        this->piece=&piece;
    }

    else if(location[0]< size/2 && location[1]<size/2)
    {
        if(top_left==NULL)
        {
            top_left = new Puzzle(size/2,first_row,first_column);
            top_left->placePiece(piece,location);
        }
            
        else
        {
            top_left->placePiece(piece,location);
        }
            
    }
    
    else if(location[0]>=size/2 && location[1]<size/2)
    {
        if(bottom_left==NULL)
        {
            bottom_left= new Puzzle(size/2, first_row+(size/2) ,first_column);
            int new_location[2];
            new_location[0]=location[0]-(size/2);
            new_location[1]=location[1];

            bottom_left->placePiece(piece,new_location);
                
        }
        else
        {
            int new_location[2];
            new_location[0]=location[0]-(size/2);
            new_location[1]=location[1];
            bottom_left->placePiece(piece,new_location);
        }
        
               

    }
    
    else if(location[0]<size/2 && location[1] >= size/2)
    {
        if(top_right==NULL)
        {
            top_right = new Puzzle(size/2,first_row,first_column+(size/2));
            int new_location[2];
            new_location[0]=location[0];
            new_location[1]=location[1]-(size/2);
            top_right->placePiece(piece,new_location);
        }
        else
        {
            int new_location[2];
            new_location[0]=location[0];
            new_location[1]=location[1]-(size/2);
            top_right->placePiece(piece,new_location);
        }

        
    }
    else if(location[0]>=size/2 && location[1] >= size/2)
    {
        if(bottom_right==NULL)
        {
            bottom_right = new Puzzle(size/2,first_row+(size/2),first_column+(size/2));
            int new_location[2];
            new_location[0]=location[0]-(size/2);
            new_location[1]=location[1]-(size/2);
            bottom_right->placePiece(piece,new_location);
        }
        else
        {
            int new_location[2];
            new_location[0]=location[0]-(size/2);
            new_location[1]=location[1]-(size/2);
            bottom_right->placePiece(piece,new_location);
        }
       
    }
    else
    {
        ;
    }


}

/* It returns directly the piece object located in the sub-puzzle (cell)
   whose row id and column id are given in the first and second elements of 
   2D array as argument, respectively. If there is no piece in the requested 
   indices, then this method throws an EmptyCellRequest exception defined in 
   Exception.h file.
*/
const Piece& Puzzle::getPiece(int location[2]) const {
    // TODO
    if(size==1)
    {
        if(piece==NULL)
        {
            throw EmptyCellRequest();
        }
        else
            return *piece;
    }

    else if(location[0]< first_row+(size/2) && location[1]<first_column + (size/2))
    {
        if(top_left)
            return top_left->getPiece(location);
        else
            throw EmptyCellRequest();
    }
    
    else if(location[0]>=first_row+(size/2) && location[1]<first_column + (size/2))
    {
        if(bottom_left)
            return bottom_left->getPiece(location);
        else
            throw EmptyCellRequest();
    }
    
    else if(location[0]<first_row+(size/2) && location[1] >= first_column + (size/2))
    {
        if(top_right)
            return top_right->getPiece(location);
        else
            throw EmptyCellRequest();
    }
      
    
    else if(location[0] >= first_row+(size/2) && location[1] >= first_column + (size/2))
    {
        if(bottom_right)
            return bottom_right->getPiece(location);
        else
            throw EmptyCellRequest();
    }

    else
    {
        throw EmptyCellRequest();
    }
    

    
    
  
}

/* This method returns the sub-puzzle whose initial and final row-column ids 
   are given in the first and second arguments, respectively. The indices
   given in the arguments will be given as an exact correspondence to one of
   the sub-puzzles of the current puzzle object.
   
   ATTENTION: The sub-puzzle to be cropped may correspond to a NULL part of the
   Puzzle object. In that case, it is enough to you to create a new Puzzle 
   object that satisfies the asked properties and return it. OF course, do NOT 
   forget to do this operation by escaping from memory leaks!!!
*/
Puzzle Puzzle::crop(int from[2], int to[2]) const {
    // TODO
     if(size-1== to[0]-from[0])
    {

        return Puzzle(*this) ;
    }

    else if(from[0]> first_row && from[1]> first_column)
    {
        if(bottom_right == NULL)
            return Puzzle(size/2,first_row,first_column).crop(from,to);

        else
            return bottom_right->crop(from,to);
    }
    else if(from[0]<= first_row && from[1]<= first_column )
    {
        if(top_left == NULL)
            return Puzzle(size/2,first_row,first_column).crop(from,to);

        else
            return top_left->crop(from,to);
    }
    else if(from[0]> first_row && from[1]<= first_column)
    {
        if(bottom_left == NULL)
            return Puzzle(size/2,first_row,first_column).crop(from,to);

        else
            return bottom_left->crop(from,to);
    }

    else if(from[0]<= first_row && from[1]> first_column)
    {
        if(top_right == NULL)
            return Puzzle(size/2,first_row,first_column).crop(from,to);

        else
            return top_right->crop(from,to);
    }

    else
    {
        return *this;
    }

}

/****************************************************/
/*        THE BELOW PART WILL NOT BE GRADED.        */
/*      YOU CAN IMPLEMENT IF YOU WOULD LIKE TO.     */
/****************************************************/
/*
    This method puts (patches) the given puzzle onto the corresponding part
    of the current puzzle object. To which part it will be patched on could
    be determined by just checking the initial row-column indices and the size
    of the puzzle given in the argument. 
    Unlike crop() method, the puzzle given in the argument may not be an exact 
    correspondence of some sub-puzzle. It is ensured that the given argument will
    be located on some sub-space of the current puzzle, yet it may *partially* 
    overlap with some or more sub-puzzles (See the figure in the pdf).
    The patch operation requires deep-copy of the corresponding sub-puzzles
    whereas it requires shallow copy of the corresponding Piece objects.
    
    HINT: You may get benefit from placePiece() method and you may start your
    operation by clearing the corresponding parts of the current puzzle.
*/
void Puzzle::patch(const Puzzle&) {
    // TODO
}

