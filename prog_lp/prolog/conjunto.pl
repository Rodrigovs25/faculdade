% Verifica se o conjunto é vazio
ehVazio([], true).
ehVazio(_, false).

% União de conjuntos
uniaoConj(A, B, Uniao) :-
    append(A, B, Uniao).

% Interseção de conjuntos
intersConj([], _, []).
intersConj([X|RestoA], B, Intersecao) :-
    (   member(X, B)
    ->  Intersecao = [X|RestoIntersecao]
    ;   Intersecao = RestoIntersecao
    ),
    intersConj(RestoA, B, RestoIntersecao).

% Diferença de conjuntos
diffConj([], _, []).
diffConj([X|RestoA], B, Diferenca) :-
    (   member(X, B)
    ->  Diferenca = RestoDiferenca
    ;   Diferenca = [X|RestoDiferenca]
    ),
    diffConj(RestoA, B, RestoDiferenca).

% Diferença simétrica de conjuntos
diffSimConj(A, B, DiferencaSimetrica) :-
    diffConj(A, B, DiferencaAB),
    diffConj(B, A, DiferencaBA),
    append(DiferencaAB, DiferencaBA, DiferencaSimetrica).

% Adiciona elemento ao conjunto
addConj(Conj, X, NovoConj) :-
    (   member(X, Conj)
    ->  NovoConj = Conj
    ;   NovoConj = [X|Conj]
    ).

% Remove elemento do conjunto
remConj([], _, []).
remConj([X|Resto], Y, NovoConj) :-
    (   X = Y
    ->  NovoConj = Resto
    ;   NovoConj = [X|RestoNovoConj]
    ),
    remConj(Resto, Y, RestoNovoConj).

% Retorna o tamanho do conjunto
tamConj(Conj, Tamanho) :-
    length(Conj, Tamanho).

% Verifica se um elemento pertence ao conjunto
ehElemConj(Conj, X) :-
    member(X, Conj).
