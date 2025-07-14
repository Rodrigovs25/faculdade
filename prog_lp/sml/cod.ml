(* Tipo de dado abstrato para Conjunto em SML *)
structure Conjunto =
struct
    (* Definindo o tipo 'conjunto' como uma lista de inteiros *)
    type conjunto = int list;

    (* Verifica se o conjunto é vazio *)
    fun ehVazio(A: conjunto) = null A;

    (* Realiza a união de dois conjuntos *)
    fun uniaoConj(A: conjunto, B: conjunto) =
        List.merge (op <) (A, B);

    (* Realiza a interseção de dois conjuntos *)
    fun intersConj(A: conjunto, B: conjunto) =
        List.filter (fn x => List.exists (fn y => x = y) B) A;

    (* Realiza a diferença de dois conjuntos (A - B) *)
    fun diffConj(A: conjunto, B: conjunto) =
        List.filter (fn x => not (List.exists (fn y => x = y) B)) A;

    (* Realiza a diferença simétrica de dois conjuntos (A Δ B) *)
    fun diffSimConj(A: conjunto, B: conjunto) =
        diffConj(A, B) @ diffConj(B, A);

    (* Adiciona um elemento ao conjunto *)
    fun addConj(x: int, A: conjunto) =
        if List.exists (fn y => x = y) A then A
        else x :: A;

    (* Remove um elemento do conjunto *)
    fun remConj(x: int, A: conjunto) =
        List.filter (fn y => not (x = y)) A;

    (* Retorna o tamanho do conjunto *)
    fun tamConj(A: conjunto) =
        length A;

    (* Verifica se um elemento está no conjunto *)
    fun ehElemConj(x: int, A: conjunto) =
        List.exists (fn y => x = y) A;

end;

(* Exemplo de uso *)
val conjuntoA = [1, 2, 3];
val conjuntoB = [2, 3, 4];

print ("Conjunto A: " ^ Int.toString (length conjuntoA) ^ "\n");
print ("Conjunto B: " ^ Int.toString (length conjuntoB) ^ "\n");

print ("É vazio? " ^ Bool.toString (Conjunto.ehVazio conjuntoA) ^ "\n");
print ("União: " ^ Int.toString (length (Conjunto.uniaoConj (conjuntoA, conjuntoB))) ^ "\n");
print ("Interseção: " ^ Int.toString (length (Conjunto.intersConj (conjuntoA, conjuntoB))) ^ "\n");
print ("Diferença: " ^ Int.toString (length (Conjunto.diffConj (conjuntoA, conjuntoB))) ^ "\n");
print ("Diferença Simétrica: " ^ Int.toString (length (Conjunto.diffSimConj (conjuntoA, conjuntoB))) ^ "\n");
print ("Tamanho: " ^ Int.toString (Conjunto.tamConj conjuntoA) ^ "\n");
print ("Contém o elemento 2? " ^ Bool.toString (Conjunto.ehElemConj (2, conjuntoA)) ^ "\n");
