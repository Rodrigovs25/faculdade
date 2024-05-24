(* conjunto.sml *)

(* Definição do Tipo de Dados Abstrato Conjunto *)
datatype 'a Conjunto = Vazio | Elemento of 'a * 'a Conjunto

(* Definição do Tipo de Dados Abstrato Conjunto usando Lista *)
datatype 'a Conjunto = Conjunto of 'a list

(* Operação: Verificar se o Conjunto está vazio *)
fun ehVazio(Conjunto []) = true
  | ehVazio _ = false

(* Operação: União de Conjuntos *)
fun uniaoConj(Conjunto A, Conjunto B) = Conjunto (A @ B)

(* Operação: Interseção de Conjuntos *)
fun intersConj(Conjunto A, Conjunto B) = Conjunto (List.filter (fn x => List.exists (fn y => x = y) B) A)

(* Operação: Diferença de Conjuntos *)
fun diffConj(Conjunto A, Conjunto B) = Conjunto (List.filter (fn x => not (List.exists (fn y => x = y) B)) A)

(* Operação: Diferença Simétrica de Conjuntos *)
fun diffSimConj(A, B) = uniaoConj(diffConj(A, B), diffConj(B, A))

(* Operação: Adicionar Elemento ao Conjunto *)
fun addConj(Conjunto A, x) = Conjunto (x :: A)

(* Operação: Remover Elemento do Conjunto *)
fun remConj(Conjunto A, x) = Conjunto (List.filter (fn y => x <> y) A)

(* Operação: Tamanho do Conjunto *)
fun tamConj(Conjunto A) = length A

(* Operação: Verificar se Elemento pertence ao Conjunto *)
fun ehElemConj(Conjunto A, x) = List.exists (fn y => x = y) A
