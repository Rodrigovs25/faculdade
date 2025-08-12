import java.util.ArrayList;
import java.util.List;

public class Conjunto {
    private List<Integer> lista;

    public Conjunto() {
        this.lista = new ArrayList<>();
    }

    public boolean ehVazio() {
        return lista.isEmpty();
    }

    public Conjunto uniaoConj(Conjunto outroConj) {
        Conjunto resultado = new Conjunto();
        resultado.lista.addAll(this.lista);
        for (Integer elemento : outroConj.lista) {
            if (!resultado.lista.contains(elemento)) {
                resultado.lista.add(elemento);
            }
        }
        return resultado;
    }

    public Conjunto intersConj(Conjunto outroConj) {
        Conjunto resultado = new Conjunto();
        for (Integer elemento : this.lista) {
            if (outroConj.lista.contains(elemento)) {
                resultado.lista.add(elemento);
            }
        }
        return resultado;
    }

    public Conjunto diffConj(Conjunto outroConj) {
        Conjunto resultado = new Conjunto();
        for (Integer elemento : this.lista) {
            if (!outroConj.lista.contains(elemento)) {
                resultado.lista.add(elemento);
            }
        }
        return resultado;
    }

    public Conjunto diffSimConj(Conjunto outroConj) {
        Conjunto uniao = this.uniaoConj(outroConj);
        Conjunto intersecao = this.intersConj(outroConj);
        return uniao.diffConj(intersecao);
    }

    public void addConj(Integer x) {
        if (!this.lista.contains(x)) {
            this.lista.add(x);
        }
    }

    public void remConj(Integer x) {
        this.lista.remove(x);
    }

    public int tamConj() {
        return this.lista.size();
    }

    public boolean ehElemConj(Integer x) {
        return this.lista.contains(x);
    }

    // Exemplo de uso
    public static void main(String[] args) {
        Conjunto conjuntoA = new Conjunto();
        Conjunto conjuntoB = new Conjunto();

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
        return lista;
    }
}
