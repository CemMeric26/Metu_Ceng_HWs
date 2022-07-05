#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    
    this->passengers.insert(Passenger(firstname,lastname));
    
    
    
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO*/ 
    Passenger *ps;ps=NULL;
    Passenger p=Passenger(firstname,lastname);
    
    
    
    if(this->passengers.search(p)!=NULL)
    {
        ps=&((this->passengers.search(p))->data);
    }
    
    
    return ps;
    
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    /* TODO */
    
    this->flights.insert(Flight(flightCode,departureTime,arrivalTime,departureCity,arrivalCity,economyCapacity,businessCapacity));
    
}



void AirlineReservationSystem::searchFlight(BSTNode<Flight> *r,std::vector<Flight *> &result,const std::string &departureCity, const std::string &arrivalCity)
{   
    if(r == NULL)
    {
        return ;
    }
   
    if((r->data).getDepartureCity()==departureCity && (r->data).getArrivalCity()==arrivalCity)
    {
        Flight *f= &(r->data);
        result.push_back(f);
    }
    
    
    searchFlight(r->left,result,departureCity,arrivalCity);
    searchFlight(r->right,result,departureCity,arrivalCity);
    
    
}

    


std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    /* TODO */
    std::vector<Flight *> result;
    
    searchFlight(flights.getRoot(),result,departureCity,arrivalCity);
    

    return result;
}


void AirlineReservationSystem::flight_pointer(BSTNode<Flight> *r,const std::string &flightCode, BSTNode<Flight> *&n)
{
    
    if(r==NULL)
    {
        return ;
    }
    
    else if((r->data).getFlightCode()==flightCode)
    {
         n = r;
    }
   
    
    flight_pointer(r->left,flightCode,n);
    flight_pointer(r->right,flightCode,n);
    
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Passenger p= Passenger(firstname,lastname);
    BSTNode<Flight> *n=NULL;Flight *f=NULL;
    flight_pointer(flights.getRoot(),flightCode,n);
    if(n!=NULL)
    {
       f = &(n->data); 
    }
    
    
    if(this->passengers.search(p)==NULL)
    {
        return ;
    }
    
    else if(f==NULL)//there is no flight with this code
    {
        ;
    }
    
    else
    {
        Passenger *ps=searchPassenger(firstname,lastname);
        Ticket t=Ticket(ps,f,ticketType);
        (n->data).addTicket(t);
    }
    
    
    
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    
    Passenger p= Passenger(firstname,lastname);
    BSTNode<Flight> *n=NULL;Flight *f=NULL;
    flight_pointer(flights.getRoot(),flightCode,n);
    if(n!=NULL)
    {
       f = &(n->data); 
    }
    
    
    if(this->passengers.search(p)==NULL)
    {
        return ;
    }
    
    else if(f==NULL)  //there is no flight with this code
    {
        return ;
    }
    
    else
    {
        Passenger *ps=searchPassenger(firstname,lastname);
        Ticket t=Ticket(ps,f,ticketType);
        freeTicketRequests.enqueue(t);
    }
    
    
    
    
    
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    /* TODO */
    BSTNode<Flight> *n=NULL;Flight *f=NULL;
    flight_pointer(flights.getRoot(),flightCode,n);
    if(n!=NULL)
    {
       f = &(n->data); 
    }
    
    Queue<Ticket> temp; 
    
    while(!freeTicketRequests.isEmpty())
    {
        Ticket t=freeTicketRequests.dequeue();
        if((t.getFlight())->getFlightCode()==flightCode)
        {
            if(!(f->addTicket(t)))
            {
                temp.enqueue(t);
            }
            
        }
        else
        {
            temp.enqueue(t);
        }
        
    }
    
    while(!temp.isEmpty())
    {
        Ticket a=temp.dequeue();
        freeTicketRequests.enqueue(a);
    }
    
    f->setCompleted(true);
    
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}
