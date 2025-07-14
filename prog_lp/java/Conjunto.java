import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * A classe Conjunto representa um conjunto finito de elementos inteiros.
 * Esta implementação utiliza uma lista (ArrayList) para armazenar os elementos.
 */
public class Conjunto<V> {
    /** Lista que armazena os elementos do conjunto. */
    private List<V> lista;

    /**
     * Construtor padrão que inicializa a lista de elementos.
     */
    public Conjunto() {
        this.lista = new ArrayList<>();
    }

    /**
     * Verifica se o conjunto está vazio.
     *
     * @return true se o conjunto estiver vazio, false caso contrário.
     */
    public boolean ehVazio() {
        return lista.isEmpty();
    }

    /**
     * Realiza a união deste conjunto com outro conjunto.
     *
     * @param novo_conjunto O conjunto a ser unido.
     * @return Um novo conjunto representando a união dos conjuntos.
     */
    public Conjunto<V> uniaoConj(Conjunto<V> novo_conjunto) {
        Conjunto<V> resultado = new Conjunto<V>();

        for (V i : this.lista){
            resultado.addConj(i);
        }
        
        for (V i : novo_conjunto.lista) {
            if (!resultado.lista.contains(i)) {
                resultado.addConj(i);
            }
        }

        resultado.lista.sort(null);

        return resultado;
    }

    /**
     * Realiza a interseção deste conjunto com outro conjunto.
     *
     * @param novo_conjunto O conjunto a ser intersectado.
     * @return Um novo conjunto representando a interseção dos conjuntos.
     */
    public Conjunto<V> intersConj(Conjunto<V> novo_conjunto) {
        Conjunto<V> resultado = new Conjunto<V>();
        
        for (V i : this.lista) {
            if (novo_conjunto.lista.contains(i)) {
                resultado.addConj(i);
            }
        }

        resultado.lista.sort(null);

        return resultado;
    }

    /**
     * Realiza a diferença deste conjunto com outro conjunto.
     *
     * @param novo_conjunto O conjunto a ser subtraído.
     * @return Um novo conjunto representando a diferença dos conjuntos.
     */
    public Conjunto<V> diffConj(Conjunto<V> novo_conjunto) {
        Conjunto<V> resultado = new Conjunto<V>();
        
        for (V i : this.lista) {
            if (!novo_conjunto.lista.contains(i)) {
                resultado.addConj(i);
            }
        }

        resultado.lista.sort(null);

        return resultado;
    }

    /**
     * Realiza a diferença simétrica deste conjunto com outro conjunto.
     *
     * @param novo_conjunto O conjunto para a diferença simétrica.
     * @return Um novo conjunto representando a diferença simétrica dos conjuntos.
     */
    public Conjunto<V> diffSimConj(Conjunto<V> novo_conjunto) {
        Conjunto<V> uniao = this.uniaoConj(novo_conjunto);
        Conjunto<V> intersecao = this.intersConj(novo_conjunto);
        Conjunto<V> resultado = uniao.diffConj(intersecao);
        
        resultado.lista.sort(null);

        return resultado;
    }

    /**
     * Adiciona um elemento ao conjunto, se não estiver presente.
     *
     * @param x O elemento a ser adicionado ao conjunto.
     */
    public void addConj(V x) {
        if (x != null && !this.lista.contains(x)) {
            this.lista.add(x);
        }
    }

    /**
     * Remove um elemento do conjunto, se presente.
     *
     * @param x O elemento a ser removido do conjunto.
     */
    public void remConj(Integer x) {
        if (x != null && this.lista.contains(x)) {
            this.lista.remove(x);
        }
    }

    /**
     * Obtém o tamanho (número de elementos) do conjunto.
     *
     * @return O tamanho do conjunto.
     */
    public int tamConj() {
        return this.lista.size();
    }

    /**
     * Verifica se um elemento está presente no conjunto.
     *
     * @param x O elemento a ser verificado.
     * @return true se o elemento estiver no conjunto, false caso contrário.
     */
    public boolean ehElemConj(Integer x) {
        return (x != null && this.lista.contains(x));
    }

    // Método auxiliar para obter os elementos do conjunto
    public List<V> getElementos() {
        return lista;
    }

}
