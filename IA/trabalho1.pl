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

testa(X,no(E,_,_,_,_)) :- parede(X,E).

%op(estado_atual, op, estado_seguinte, custo).

op((X,Y), esquerda, (X1,Y), 1) :- X1 is X - 1, min(X1, 0).
op((X,Y), cima, (X,Y1), 1) :- Y1 is Y - 1, min(Y1, 0).
op((X,Y), direita, (X1,Y), 1) :- X1 is X + 1, max(X1, 5).
op((X,Y), baixo, (X,Y1), 1) :- Y1 is Y + 1, max(Y1, 5).

%no(estado_atual, pai, op, custo, profundidade).

pesquisa_largura([no(E,Pai,Op,C,P)|_],no(E,Pai,Op,C,P)) :- estado_final(E).
pesquisa_largura([no(E,Pai,_,_,_)|R], Sol) :- testa(E,Pai), pesquisa_largura(R, Sol).
pesquisa_largura([E|R],Sol):- expande(E,Lseg), insere_fim(Lseg,R,LFinal), pesquisa_largura(LFinal,Sol).

expande(no(E,Pai,Op,C,P),L):- findall(no(En,no(E,Pai,Op,C,P), Opn, Cnn, P1), (op(E,Opn,En,Cn), P1 is P+1, Cnn is Cn+C), L).

pesquisa :- estado_inicial(S0), pesquisa_largura([no(S0,[],[],0,0)], S), write(S), nl.

insere_fim([],L,L).
insere_fim(L,[],L).
insere_fim(R,[A|S],[A|L]):- insere_fim(R,S,L).