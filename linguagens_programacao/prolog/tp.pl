% União de conjuntos
uniaoConj([], Conjunto, Conjunto).
uniaoConj([X | Resto], ConjuntoB, Resultado) :-
    member(X, ConjuntoB),
    uniaoConj(Resto, ConjuntoB, Resultado).
uniaoConj([X | Resto], ConjuntoB, [X | Resultado]) :-
    \+ member(X, ConjuntoB),
    uniaoConj(Resto, ConjuntoB, Resultado).

% Interseção de conjuntos
intersConj([], _, []).
intersConj([X | Resto], ConjuntoB, [X | Resultado]) :-
    member(X, ConjuntoB),
    intersConj(Resto, ConjuntoB, Resultado).
intersConj([X | Resto], ConjuntoB, Resultado) :-
    \+ member(X, ConjuntoB),
    intersConj(Resto, ConjuntoB, Resultado).

% Diferença de conjuntos
diffConj([], _, []).
diffConj([X | Resto], ConjuntoB, [X | Resultado]) :-
    \+ member(X, ConjuntoB),
    diffConj(Resto, ConjuntoB, Resultado).
diffConj([X | Resto], ConjuntoB, Resultado) :-
    member(X, ConjuntoB),
    diffConj(Resto, ConjuntoB, Resultado).

% Diferença Simétrica de conjuntos
diffSimConj(ConjuntoA, ConjuntoB, Resultado) :-
    diffConj(ConjuntoA, ConjuntoB, DiffAB),
    diffConj(ConjuntoB, ConjuntoA, DiffBA),
    append(DiffAB, DiffBA, Resultado).

% Adição de elemento ao conjunto
addConj(Elemento, Conjunto, Resultado) :-
    \+ member(Elemento, Conjunto),
    append([Elemento], Conjunto, Resultado).

% Remoção de elemento do conjunto
remConj(Elemento, Conjunto, Resultado) :-
    delete(Conjunto, Elemento, Resultado).

% Tamanho do conjunto
tamConj(Conjunto, Tamanho) :-
    length(Conjunto, Tamanho).

% Verifica se elemento está no conjunto
ehElemConj(Elemento, Conjunto) :-
    member(Elemento, Conjunto).
