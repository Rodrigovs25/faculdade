(* list.sml *)

datatype 'a Conjunto = Conjunto of 'a list

fun criarConjunto() = Conjunto([])

fun addConj(Conjunto A, x) = Conjunto(x :: #1 A)

fun remConj(Conjunto A, x) = Conjunto(List.filter (fn y => x <> y) (#1 A))

fun ehVazio(Conjunto A) = null (#1 A)

fun tamConj(Conjunto A) = length (#1 A)

fun ehElemConj(Conjunto A, x) = List.exists (fn y => x = y) (#1 A)

fun uniaoConj(Conjunto A, Conjunto B) = Conjunto(#1 A @ #1 B)

fun intersConj(Conjunto A, Conjunto B) =
    Conjunto(List.filter (fn x => List.exists (fn y => x = y) (#1 B)) (#1 A))

fun diffConj(Conjunto A, Conjunto B) =
    Conjunto(List.filter (fn x => not (List.exists (fn y => x = y) (#1 B))) (#1 A))

fun diffSimConj(A, B) = uniaoConj(diffConj(A, B), diffConj(B, A))
