(* main.sml *)

use "list.sml";

fun main() =
    let
        val conjuntoA = criarConjunto()
        val conjuntoB = criarConjunto()

        val conjuntoA = addConj(addConj(addConj(addConj(conjuntoA, 1), 2), 3), 5)
        val conjuntoB = addConj(addConj(addConj(conjuntoB, 2), 3), 4)

        val uniao = uniaoConj(conjuntoA, conjuntoB)
        val intersecao = intersConj(conjuntoA, conjuntoB)
        val diferenca = diffConj(conjuntoA, conjuntoB)
        val difSimetrica = diffSimConj(conjuntoA, conjuntoB)

        val vazioA = ehVazio(conjuntoA)
        val tamanhoA = tamConj(conjuntoA)
        val contemDois = ehElemConj(conjuntoA, 2)

        val conjuntoA = remConj(conjuntoA, 2)

        (* Impressões *)
        val _ = print("Conjunto A: " ^ Int.toStringList (#1 conjuntoA) ^ "\n")
        val _ = print("Conjunto B: " ^ Int.toStringList (#1 conjuntoB) ^ "\n")
        val _ = print("União: " ^ Int.toStringList (#1 uniao) ^ "\n")
        val _ = print("Interseção: " ^ Int.toStringList (#1 intersecao) ^ "\n")
        val _ = print("Diferença: " ^ Int.toStringList (#1 diferenca) ^ "\n")
        val _ = print("Diferença Simétrica: " ^ Int.toStringList (#1 difSimetrica) ^ "\n")
        val _ = print("É vazio? " ^ Bool.toString vazioA ^ "\n")
        val _ = print("Tamanho: " ^ Int.toString tamanhoA ^ "\n")
        val _ = print("Contém o elemento 2? " ^ Bool.toString contemDois ^ "\n")
    in
        ()
    end

(* Chamada da Função Principal *)
val _ = main()
