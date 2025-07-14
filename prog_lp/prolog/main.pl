% main.pl

% Inclui o arquivo com as implementações do conjunto
:- consult('conjunto.pl').

% Exemplos de uso
exemplo1 :-
    write('Exemplo 1:\n'),
    Conj1 = [1, 2, 3],
    Conj2 = [3, 4, 5],
    write('Conjunto 1: '), write(Conj1), nl,
    write('Conjunto 2: '), write(Conj2), nl,
    ehVazio(Conj1, Vazio1), write('Conjunto 1 vazio? '), write(Vazio1), nl,
    uniaoConj(Conj1, Conj2, Uniao), write('União: '), write(Uniao), nl.

exemplo2 :-
    write('Exemplo 2:\n'),
    Conj = [1, 2, 3, 4, 5],
    Elem = 3,
    write('Conjunto: '), write(Conj), nl,
    write('Elemento a ser removido: '), write(Elem), nl,
    remConj(Conj, Elem, NovoConj), write('Novo Conjunto: '), write(NovoConj), nl.

% Adicione mais exemplos conforme necessário

% Para executar os exemplos
:- exemplo1.
:- exemplo2.