import java.util.ArrayList;
import java.util.List;

/**
 * A classe Conjunto representa um conjunto finito de elementos inteiros.
 * Esta implementação utiliza uma lista (ArrayList) para armazenar os elementos.
 */
public class Conjunto<V> {

    public static char[] lista;
    /** Lista que armazena os elementos do conjunto. */
    private List<V> elementos;

    /**
     * Construtor padrão que inicializa a lista de elementos.
     */
    public Conjunto() {
        this.elementos = new ArrayList<>();
    }

    /**
     * Verifica se o conjunto está vazio.
     *
     * @return true se o conjunto estiver vazio, false caso contrário.
     */
    public boolean ehVazio() {
        return elementos.size() == 0;
    }

    /**
     * Realiza a união deste conjunto com outro conjunto.
     *
     * @param outroConj O conjunto a ser unido.
     * @return Um novo conjunto representando a união dos conjuntos.
     */
    public Conjunto<V> uniaoConj(Conjunto<V> outroConj) {
        Conjunto<V> resultado = new Conjunto<V>();
        resultado.elementos.addAll(this.elementos);
        for (V elemento : outroConj.elementos) {
            if (!resultado.elementos.contains(elemento)) {
                resultado.elementos.add(elemento);
            }
        }
        return resultado;
    }

    /**
     * Realiza a interseção deste conjunto com outro conjunto.
     *
     * @param outroConj O conjunto a ser intersectado.
     * @return Um novo conjunto representando a interseção dos conjuntos.
     */
    public Conjunto<V> intersConj(Conjunto<V> outroConj) {
        Conjunto<V> resultado = new Conjunto<V>();
        for (V elemento : this.elementos) {
            if (outroConj.elementos.contains(elemento)) {
                resultado.elementos.add(elemento);
            }
        }
        return resultado;
    }

    /**
     * Realiza a diferença deste conjunto com outro conjunto.
     *
     * @param outroConj O conjunto a ser subtraído.
     * @return Um novo conjunto representando a diferença dos conjuntos.
     */
    public Conjunto<V> diffConj(Conjunto<V> outroConj) {
        Conjunto<V> resultado = new Conjunto<V>();
        for (V elemento : this.elementos) {
            if (!outroConj.elementos.contains(elemento)) {
                resultado.elementos.add(elemento);
            }
        }
        return resultado;
    }

    /**
     * Realiza a diferença simétrica deste conjunto com outro conjunto.
     *
     * @param outroConj O conjunto para a diferença simétrica.
     * @return Um novo conjunto representando a diferença simétrica dos conjuntos.
     */
    public Conjunto<V> diffSimConj(Conjunto<V> outroConj) {
        Conjunto<V> uniao = this.uniaoConj(outroConj);
        Conjunto<V> intersecao = this.intersConj(outroConj);
        return uniao.diffConj(intersecao);
    }

    /**
     * Adiciona um elemento ao conjunto, se não estiver presente.
     *
     * @param x O elemento a ser adicionado ao conjunto.
     */
    public void addConj(V x) {
        if (!this.elementos.contains(x)) {
            this.elementos.add(x);
        }
    }

    /**
     * Remove um elemento do conjunto, se presente.
     *
     * @param x O elemento a ser removido do conjunto.
     */
    public void remConj(Integer x) {
        this.elementos.remove(x);
    }

    /**
     * Obtém o tamanho (número de elementos) do conjunto.
     *
     * @return O tamanho do conjunto.
     */
    public int tamConj() {
        return this.elementos.size();
    }

    /**
     * Verifica se um elemento está presente no conjunto.
     *
     * @param x O elemento a ser verificado.
     * @return true se o elemento estiver no conjunto, false caso contrário.
     */
    public boolean ehElemConj(Integer x) {
        return this.elementos.contains(x);
    }

    // Exemplo de uso
    public static void main(String[] args) {
        Conjunto<Integer> conjuntoA = new Conjunto<Integer>();
        Conjunto<Integer> conjuntoB = new Conjunto<Integer>();

        conjuntoA.addConj(1);
        conjuntoA.addConj(2);
        conjuntoB.addConj(2);
        conjuntoB.addConj(3);

        System.out.println(conjuntoA.ehVazio());  // false
        System.out.println(conjuntoA.uniaoConj(conjuntoB).getElementos());  // [1, 2, 3]
        System.out.println(conjuntoA.intersConj(conjuntoB).getElementos());  // [2]
        System.out.println(conjuntoA.diffConj(conjuntoB).getElementos());  // [1]
        System.out.println(conjuntoA.diffSimConj(conjuntoB).getElementos());  // [1, 3]
        System.out.println(conjuntoA.tamConj());  // 2
        System.out.println(conjuntoA.ehElemConj(1));  // true
    }

    // Método auxiliar para obter os elementos do conjunto
    public List<Integer> getElementos() {
        return elementos;
    }
}
