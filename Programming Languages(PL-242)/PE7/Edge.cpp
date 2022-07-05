#include "Edge.h"


/****************************************************/
/****                *** EDGE ***                ****/

/* Contsructor : initializes <id> of the object to the given integer
   and <password> of the object to the given Password object.   
*/
Edge::Edge(int id, Password password) {
    
    // TODO
    this->id=id;
    this->password=password;
    this->matchingEdge=NULL;
}

/* Destructor  : It is NOT responsible of the destruction of the matchingEdge!
*/
Edge::~Edge() {
    // TODO
    
}

/* Returns the <id> of the object
*/
int Edge::getId() const {
	// TODO
	
	return this->id;
}

/* Returns the pointer to the matching partner of the current edge.
   If the edge had not been matched before, it returns NULL.
*/
Edge* Edge::getMatchingEdge() const {
    // TODO
    if(matchingEdge)
        return this->matchingEdge;
    
    return NULL;
}

/* It tries to match the current Edge object with the one given in the argument.
   If the two edges are matchable then it does the matching by storing
   <matchingEdge> variables with each other, and returns true. Otherwise,
   it does not match and returns false.
   It applies the matching rules given in the pdf.
   Note that match operation is a mutual operation. Namely, if the current
   edge is matched, then its partner edge should be matched with the current 
   one too.
   HINT: It may need matchWithHelper(Password) method.
   
   Note: Of course, it would be nicer to overload this method for taking 
   different types of Edges as arguments, yet this design was preffered 
   specifically for you to discover mechanism of virtual. Helper method
   is given to the issue.
*/
bool Edge::matchWith(Edge& param_edge) {
    // TODO
    
    int satisfy=0;
    
    switch(this->password){
        
        case SEND_ME_STRAIGHT:
            if(this->matchWithHelper(param_edge.password))
            {
                this->breakMatch(); param_edge.breakMatch();
                this->matchingEdge = &param_edge;
                param_edge.matchingEdge= &(*this);
                satisfy=1;
            }
            
            break;
            
        case SEND_ME_OUTWARDS:
            if(this->matchWithHelper(param_edge.password))
            {
                this->breakMatch(); param_edge.breakMatch();
                this->matchingEdge = &param_edge;
                param_edge.matchingEdge= &(*this);
                satisfy=1;
            }
            
            break;
    
        case SEND_ME_INWARDS:
            if(this->matchWithHelper(param_edge.password))
            {
                this->breakMatch(); param_edge.breakMatch();
                this->matchingEdge = &param_edge;
                param_edge.matchingEdge= &(*this);
                satisfy=1;
            }
            break;
            
        case SEND_ME_COMPLETING_COMPOSITE:
            break;
        
        
    }
    
    if(satisfy==1)
        return true;
    
    
    return false;
}

/* If the current edge was matched with some edge before, then this method
   breaks the match, i.e. there is no match between those two edges anymore.
   Note that breaking match operation is a mutual operation. Namely, if the 
   matching of the current edge is broken, the matching recorded in its partner 
   edge should be broken too.
*/
void Edge::breakMatch() {
    // TODO
    if(this->matchingEdge)
    {
        (*matchingEdge).matchingEdge=NULL;
        this->matchingEdge = NULL;
    }
}

/****************************************************/
/****            *** STRAIGHT EDGE ***           ****/

/* Contsructor : initializes <id> of the object to the given integer
   and <password> of the object.
   Note that Password variable has a fixed value which is SEND_ME_STRAIGHT,
   therefore it is not given as an argument.
*/
StraightEdge::StraightEdge(int id):Edge(id,SEND_ME_STRAIGHT) {
	// TODO
	
	
	
}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
StraightEdge::~StraightEdge() {
    // TODO
}

/* This method clones the current object and returns the pointer to its clone.
   Cloning is actually a deep-copy operation, so you need to construct a new
   StraightEdge object.
   Note that if the current edge is matched with some other edge, then its
   matchingEdge should be cloned too and only the clones should be matched 
   with each other.
*/
Edge* StraightEdge::clone() const {
    // TODO
    
    Edge* new_st_edge = new StraightEdge(this->id);
    
    if(this->matchingEdge)
    {
        Edge* new_st_edge_clone= new StraightEdge(this->matchingEdge->getId());
        
        new_st_edge->matchWith(*new_st_edge_clone);
        
        
        //(*new_st_edge).matchingEdge = &(*new_st_edge_clone);
        //(*new_st_edge_clone).matchingEdge= &(*new_st_edge);
    }
    
    
    
    return new_st_edge;
    
    //return NULL;
    
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool StraightEdge::matchWithHelper(Password password) {
 
    // TODO
    if(password==SEND_ME_STRAIGHT)
        return true;
    
    
    
    return false;
}

/****************************************************/
/****            *** INWARDS EDGE ***            ****/

/* Contsructor : initializes <id> of the object to the given integer
   and <password> of the object.
   Note that Password variable has a fixed value which is SEND_ME_OUTWARDS,
   therefore it is not given as an argument.
*/
InwardsEdge::InwardsEdge(int id):Edge(id,SEND_ME_OUTWARDS) {
    // TODO
    
}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
InwardsEdge::~InwardsEdge() {
    // TODO
}

/* This method clones the current object and returns the pointer to its clone.
   Cloning is actually a deep-copy operation, so you need to construct a new
   InwardsEdge object.
   Note that if the current edge is matched with some other edge, then its
   matchingEdge should be cloned too and only the clones should be matched 
   with each other.
*/
Edge* InwardsEdge::clone() const {
    // TODO
    Edge* new_in_edge = new InwardsEdge(this->id);
    
    if(this->matchingEdge)
    {
        Edge* new_in_edge_clone= new InwardsEdge((this->matchingEdge)->getId());
        new_in_edge->matchWith(*new_in_edge_clone);
        
        //(new_in_edge)->getMatchingEdge()= new_in_edge_clone;
        //(new_in_edge_clone)->getMatchingEdge()= new_in_edge;
    }
    
    
    return new_in_edge;
    
    //return NULL;
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool InwardsEdge::matchWithHelper(Password password) {
    // TODO
    if(password==SEND_ME_INWARDS)
        return true;
    
    
    
    return false;
}

/****************************************************/
/****            *** OUTWARDS EDGE ***           ****/

/* Contsructor : initializes <id> of the object to the given integer
   and <password> of the object.
   Note that Password variable has a fixed value which is SEND_ME_INWARDS,
   therefore it is not given as an argument.
*/
OutwardsEdge::OutwardsEdge(int id):Edge(id,SEND_ME_INWARDS) {
    // TODO
    //this->password=SEND_ME_INWARDS;
}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
OutwardsEdge::~OutwardsEdge() {
    // TODO
}

/* This method clones the current object and returns the pointer to its clone.
   Cloning is actually a deep-copy operation, so you need to construct a new
   OutwardsEdge object.
   Note that if the current edge is matched with some other edge, then its
   matchingEdge should be cloned too and only the clones should be matched 
   with each other.
*/
Edge* OutwardsEdge::clone() const {
    // TODO
    
   Edge* new_out_edge = new OutwardsEdge(this->id);
    
    if(this->matchingEdge)
    {
        Edge* new_out_edge_clone= new OutwardsEdge((this->matchingEdge)->getId());
        new_out_edge->matchWith(*new_out_edge_clone);
        
        //(new_out_edge)->getMatchingEdge()= *(new_out_edge_clone);
        //(new_out_edge_clone)->getMatchingEdge()= &(new_out_edge);
    }
    
    
    return new_out_edge;
    
    //return NULL;
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool OutwardsEdge::matchWithHelper(Password password) {
	// TODO
	if(password==SEND_ME_OUTWARDS)
        return true;
    
    
    
    return false;
}

/****************************************************/
/*        THE BELOW PART WILL NOT BE GRADED.        */
/*      YOU CAN IMPLEMENT IF YOU WOULD LIKE TO.     */
/****************************************************/

/****************************************************/
/****            *** COMPOSITE EDGE ***          ****/

/* Contsructor : initializes <id> of the object to the given integer
   and <password> of the object.
   Note that Password variable has a fixed value which is SEND_ME_COMPLETING_COMPOSITE,
   therefore it is not given as an argument.
   Note that you may need to initialize matchIndex variable with some value
   so that you may benefit from that during any match operation.
*/
CompositeEdge::CompositeEdge(int id):Edge(id,SEND_ME_COMPLETING_COMPOSITE) {
	// TODO
	matchIndex=0;
	
	
	
}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
   However, it should delete its member edges too.
*/
CompositeEdge::~CompositeEdge() {
	// TODO
	for(unsigned int i=0;i<edges.size();i++)
	{
	    delete edges[i];
	}
	edges.clear();
}

/* This method clones the current object and returns the pointer to its clone.
   Cloning is actually a deep-copy operation, so you need to construct a new
   CompositeEdge object. During the construction, each member Edge object 
   should be cloned too, and the clone of the current CompositeEdge should
   include only the clones of the member edges.
   Note that if the current edge is matched with some other edge, then its
   matchingEdge should be cloned too and only the clones should be matched 
   with each other.
*/
Edge* CompositeEdge::clone() const {
    // TODO
    
    return NULL;
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool CompositeEdge::matchWithHelper(Password) {
	// TODO
	
	return true;
}

/* It tries to match the current CompositeEdge object with the one given in the 
   argument.
   If the two edges are matchable then it does the matching by storing
   <matchingEdge> variables with each other, and returns true. Otherwise,
   it does not match and returns false.
   It applies the matching rules given in the pdf.
   Note that match operation is a mutual operation. Namely, if the current
   edge is matched, then its partner edge should be matched with the current 
   one too.
   HINT: It may need matchWithHelper(Password) method.
   
   Note: Of course, it would be nicer to overload this method for taking 
   different types of Edges as arguments, yet this design was preffered 
   specifically for you to discover mechanism of virtual. Helper method
   is given to the issue.
*/
bool CompositeEdge::matchWith(Edge&) {
    // TODO
    
    return true;
}

/* If the current edge was matched with some edge before, then this method
   breaks the match, i.e. there is no match between those two edges anymore.
   Note that breaking match operation is a mutual operation. Namely, if the 
   matching of the current edge is broken, the matching recorded in its partner 
   edge should be broken too.
*/
void CompositeEdge::breakMatch() {
    // TODO
}

/* This method pushes back the given edge in the argument into the end of the 
   member edges vector.
*/
CompositeEdge* CompositeEdge::addEdge(Edge* edge) {
    // TODO
    
    
    return NULL;
}
