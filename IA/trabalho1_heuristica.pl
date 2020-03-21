min(X, N) :- X > N.
max(X, N) :- X < N.

abs(X,X) :- X >= 0.
abs(X,Y) :- Y is -X.

estado_inicial((1,1)).
estado_final((4,4)).

parede((1,1),(1,2)).
parede((1,2),(1,1)).
parede((2,1),(2,2)).
parede((2,2),(2,1)).
parede((3,1),(4,1)).
parede((4,1),(3,1)).
parede((3,2),(3,3)).
parede((3,3),(3,2)).
parede((4,2),(4,3)).
parede((4,3),(4,2)).

testa(X,no(E,_,_,_,_,_)) :- parede(X,E).

%op(estado_atual, op, estado_seguinte, custo).

op((X,Y), esquerda, (X1,Y), 1) :- X1 is X - 1, min(X1, 0).
op((X,Y), cima, (X,Y1), 1) :- Y1 is Y - 1, min(Y1, 0).
op((X,Y), direita, (X1,Y), 1) :- X1 is X + 1, max(X1, 5).
op((X,Y), baixo, (X,Y1), 1) :- Y1 is Y + 1, max(Y1, 5).

%no(estado_atual, pai, op, custo, custo_heuristica, profundidade).

pesquisa_largura([no(E,Pai,Op,C,CH,P)|_],no(E,Pai,Op,C,CH,P)) :- 
	estado_final(E).
pesquisa_largura([no(E,Pai,_,_,_,_)|R], Sol) :- 
	testa(E,Pai), pesquisa_largura(R, Sol).
pesquisa_largura([E|R],Sol):- 
	expande(E,Lseg), insere_ordenado(Lseg,R,LFinal), pesquisa_largura(LFinal,Sol).

expande(no(E,Pai,Op,C,CH,P),L):- 
	findall(no(En,no(E,Pai,Op,C,CH,P), Opn, Cnn, CHn, P1), 
	(op(E,Opn,En,Cn), P1 is P+1, Cnn is Cn+C, heur(En,H), CHn is Cnn + H), L).

pesquisa :- estado_inicial(S0), pesquisa_largura([no(S0,[],[],0,0,0)], S), write(S), nl.

heur((X,Y),H) :- 
	estado_final((XF,YF)),
	X1 is XF - X, abs(X1,XA),
	Y1 is YF - Y, abs(Y1,YA),
	H is XA + YA.

insere_ordenado([],I,I).
insere_ordenado(I,[],I).
insere_ordenado(no(_,_,_,_,CHI,_),[no(_,_,_,_,CHA,_)|_],[no(_,_,_,_,CHI,_),no(_,_,_,_,CHA,_)|_]) :-
	CHI <= CHA, !.
insere_ordenado(I,[A|S],[A|L]):- insere_ordenado(I,S,L).