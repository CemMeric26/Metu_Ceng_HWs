:- module(main, [is_movie_directed_by/2, total_awards_nominated/2, all_movies_directed_by/2, total_movies_released_in/3, all_movies_released_between/4]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE
is_movie_directed_by(Title, Director) :- movie(Title,Director,_,_,_,_) .

movie_help(Title,Director,Year,OscarNoms,EmmyNoms,GoldenGlobeNoms,Acc):-movie(Title,Director,Year,OscarNoms,EmmyNoms,GoldenGlobeNoms), Acc is (OscarNoms+EmmyNoms+GoldenGlobeNoms) .
total_awards_nominated(Title ,Nominations) :- movie_help(Title,_,_,_,_,_,X), Nominations is X .


all_movies_directed_by(Director, Movies):- findall(Title,movie(Title, Director,_,_,_,_), Movies ).

total_movies_released_in_help([],Year,Acc,Acc).
total_movies_released_in_help([Movie|Movies],Year,Count,Acc):- 
    movie(Movie,_,Year,_,_,_),
    Z is Acc+1,
    total_movies_released_in_help(Movies,Year,Count,Z).
    
total_movies_released_in_help([Movie|Movies],Year,Count,Acc):- 
    movie(Movie,_,AnotherYear,_,_,_),
    Year \= AnotherYear,
    total_movies_released_in_help(Movies,Year,Count,Acc).    


total_movies_released_in(Movies,Year,Count):- total_movies_released_in_help(Movies,Year,Count,0). 


acc_reverse([], Acc, Acc).
acc_reverse([H|T], Acc, Res) :- acc_reverse(T, [H|Acc], Res).

reverse(X, Y) :- acc_reverse(X, [], Y).


all_movies_released_between_help([],_,_,Acc,Acc).
all_movies_released_between_help([Movie|Movies],MinYear,MaxYear,Acc,Res):-
    movie(Movie,_,Year,_,_,_),
    Year =< MaxYear,
    Year >= MinYear,
    all_movies_released_between_help(Movies,MinYear,MaxYear,[Movie|Acc],Res).
    
all_movies_released_between_help([Movie|Movies],MinYear,MaxYear,Acc,Res):-
    movie(Movie,_,Year,_,_,_),
    (Year > MaxYear; Year < MinYear),
    all_movies_released_between_help(Movies,MinYear,MaxYear,Acc,Res).


%all_movies_released_between_help([Movie|Movies],MinYear,MaxYear,Acc,Res):-
 %   movie(Movie,_,Year,_,_,_),
  %  Year < MinYear,
   % all_movies_released_between_help(Movies,MinYear,MaxYear,Acc,Res).  
    

all_movies_released_between(Movies,MinYear,MaxYear,MoviesBetweenGivenYears):-all_movies_released_between_help(Movies,MinYear,MaxYear,[],Z), reverse(Z,MoviesBetweenGivenYears)  .

