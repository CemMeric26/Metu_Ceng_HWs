#include "Piece.h"


/****************************************************/
/****               *** PIECE ***                ****/

/* Contsructor : initializes <edges> of the object to the those given in the
   argument. The edges given in the argument array should be cloned first,
   and its clones should be reserved, not the edges themselves.
   Note that the ordering of the given edges will always be as follows:
   edges[0]: Left side edge, 
   edges[1]: Bottom side edge, 
   edges[2]: Right side edge, 
   edges[3]: Top side edge.
*/
Piece::Piece(Edge* edge_list[4]) {
    // TODO
    edges[0]= edge_list[0]->clone();
    edges[1]= edge_list[1]->clone();
    edges[2]= edge_list[2]->clone();
    edges[3]= edge_list[3]->clone();


}

/* Destructor  : It should destruct its edges too.
*/
Piece::~Piece() {
    // TODO
    for(unsigned int i=0;i<4;i++)
    {
        delete edges[i];
        edges[i]=NULL;
    }
}

/* Copy constructor : Apply deep copy.
*/
Piece::Piece(const Piece& piece) {
    // TODO
    for(unsigned int i=0;i<4;i++)
    {
        *(this->edges[i])= *(piece.edges[i]);
    }
    
}

// This is already implemented for you, do NOT change it!
ostream& operator<< (ostream& os, const Piece& piece) {

	for (int i = 0; i < 4; i++)
		os << piece.edges[i]->getId() << "  \n";
	return os;
}
