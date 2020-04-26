min(X, N) :- X > N.
max(X, N) :- X < N.

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

op((X,Y), direita, (X1,Y), 1) :- X1 is X + 1, max(X1, 5).
op((X,Y), baixo, (X,Y1), 1) :- Y1 is Y + 1, max(Y1, 5).
op((X,Y), esquerda, (X1,Y), 1) :- X1 is X - 1, min(X1, 0).
op((X,Y), cima, (X,Y1), 1) :- Y1 is Y - 1, min(Y1, 0).

%no(estado_atual, pai, op, custo, custo_heuristica, profundidade).

pesquisa_aux([no(E,Pai,Op,C,CH,P)|_],no(E,Pai,Op,C,CH,P), _) :- 
	estado_final(E).
pesquisa_aux([no(E,Pai,_,_,_,_)|R], Sol, LE) :- 
	testa(E,Pai), pesquisa_aux(R, Sol, LE).
pesquisa_aux([no(E,Pai,Op,C,CH,P)|R],Sol, LE):- 
	\+ member(E, LE),
	expande(no(E,Pai,Op,C,CH,P),Lseg),
        insere_ordenado(Lseg,R,LFinal),
        pesquisa_aux(LFinal,Sol, [E|LE]).
pesquisa_aux([no(E,_,_,_,_,_)|R],Sol, LE):- 
	member(E, LE), pesquisa_aux(R,Sol, LE).

expande(no(E,Pai,Op,C,CH,P),L):- 
	findall(no(En,no(E,Pai,Op,C,CH,P), Opn, Cnn, CHn, P1), 
	(op(E,Opn,En,Cn), P1 is P+1, Cnn is Cn+C, heur(En,H), CHn is Cnn + H), L).

pesquisa :- estado_inicial(S0), pesquisa_aux([no(S0,[],[],0,0,0)], S, []), write(S), nl.

heur((X,Y),H) :- 
	estado_final((XF,YF)),
	X1 is XF - X,
	Y1 is YF - Y,
	H is abs(X1) + abs(Y1).

ins_ord(E, [], [E]).
ins_ord(no(E,Pai,Op,C,CH,P), [no(E1,Pai1,Op1,C1,CH1,P1)|T], [no(E,Pai,Op,C,CH,P),no(E1,Pai1,Op1,C1,CH1,P1)|T]) :- CH =< CH1.
ins_ord(no(E,Pai,Op,C,CH,P), [no(E1,Pai1,Op1,C1,CH1,P1)|T], [no(E1,Pai1,Op1,C1,CH1,P1)|T1]) :-
	ins_ord(no(E,Pai,Op,C,CH,P), T, T1).	

insere_ordenado([],L,L).
insere_ordenado([A|T], L, LF):- 
	ins_ord(A,L,L1),
	insere_ordenado(T, L1, LF).