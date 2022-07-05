:- module(main, [salad_type/2, person_can_eat/3, possible_order_options/3, count_per_type/2]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

salad_type_helper2([],Type):- Type=vegetarian;Type=omnivorous.
salad_type_helper2([H|ItemList], Type):- not_vegetarian(H),!,Type=omnivorous.
salad_type_helper2([H|ItemList], Type):- salad_type_helper2(ItemList,Type).


salad_type_helper([],Type):- Type=vegan;Type=vegetarian;Type=omnivorous.
salad_type_helper([H|ItemList], Type) :- not_vegetarian(H),!,Type=omnivorous.
salad_type_helper([H|ItemList], Type):- not_vegan(H), !,salad_type_helper2(ItemList,Type).
salad_type_helper([H|ItemList], Type):- salad_type_helper(ItemList,Type).


salad_type( ItemList , Type ):- salad_type_helper(ItemList,Type).



omni_eats([],Salad,Salad).
omni_eats([H|SaladList],Salad,X):- omni_eats(SaladList,[H|Salad],X).

vegi_eats([],Salad,Salad).
vegi_eats([H|SaladList],Salad,X):- salad_type(H,vegetarian),!,vegi_eats(SaladList,[H|Salad],X).
vegi_eats([H|SaladList],Salad,X):- vegi_eats(SaladList,Salad,X).

vegan_eats([],Salad,Salad).
vegan_eats([H|SaladList],Salad,X):- salad_type(H,vegan),!,vegan_eats(SaladList,[H|Salad],X).
vegan_eats([H|SaladList],Salad,X):- vegan_eats(SaladList,Salad,X).


person_can_eat_helper(Person,SaladList,X):- omnivorous(Person),!,omni_eats(SaladList,[],X).
person_can_eat_helper(Person,SaladList,X):- vegetarian(Person),!,vegi_eats(SaladList,[],X).
person_can_eat_helper(Person,SaladList,X):- vegan(Person),vegan_eats(SaladList,[],X).

reverse([],Z,Z).
reverse([H|T],Z,Acc) :- reverse(T,Z,[H|Acc]).

person_can_eat( Person , SaladList , Salad) :- person_can_eat_helper(Person,SaladList,X),reverse(X,Y,[]),member(Salad,Y).






possible_order_options( Person , OrderString , ItemList ):-false .






count_helper([],CO,CVI,CV,CO,CVI,CV).
count_helper([S|SaladList],CO,CVI,CV,A,B,C):- salad_type(S,vegan),!,Z is CV+1, count_helper(SaladList,CO,CVI,Z,A,B,C).
count_helper([S|SaladList],CO,CVI,CV,A,B,C):- salad_type(S,vegetarian),!,Z is CVI+1, count_helper(SaladList,CO,Z,CV,A,B,C).
count_helper([S|SaladList],CO,CVI,CV,A,B,C):- salad_type(S,omnivorous),!,Z is CO+1, count_helper(SaladList,Z,CVI,CV,A,B,C).




count_per_type( SaladList , TypeList ):- count_helper(SaladList,0,0,0,A,B,C),A=0,B=0,C=0,!,TypeList=[] .
count_per_type( SaladList , TypeList ):- count_helper(SaladList,0,0,0,A,B,C),A>0,B>0,C>0,!,TypeList=[[omnivorous,A],[vegetarian,B],[vegan,C]] .
count_per_type( SaladList , TypeList ):- count_helper(SaladList,0,0,0,A,B,C),A>0,B>0,C=0,!,TypeList=[[omnivorous,A],[vegetarian,B]] .
count_per_type( SaladList , TypeList ):- count_helper(SaladList,0,0,0,A,B,C),A>0,B=0,C>0,!,TypeList=[[omnivorous,A],[vegan,C]] .
count_per_type( SaladList , TypeList ):- count_helper(SaladList,0,0,0,A,B,C),A=0,B>0,C>0,!,TypeList=[[vegetarian,B],[vegan,C]] .
count_per_type( SaladList , TypeList ):- count_helper(SaladList,0,0,0,A,B,C),A>0,B=0,C=0,!,TypeList=[[omnivorous,A]] .
count_per_type( SaladList , TypeList ):- count_helper(SaladList,0,0,0,A,B,C),A=0,B>0,C=0,!,TypeList=[[vegetarian,B]] .
count_per_type( SaladList , TypeList ):- count_helper(SaladList,0,0,0,A,B,C),A=0,B=0,C>0,!,TypeList=[[vegan,C]] .



