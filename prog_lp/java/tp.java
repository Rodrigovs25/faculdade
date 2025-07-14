import java.util.HashSet;
import java.util.Set;

public class Conjunto {

    private Set<Integer> elementos;

    public Conjunto() {
        this.elementos = new HashSet<>();
    }

    public boolean ehVazio() {
        return elementos.isEmpty();
    }

    public Conjunto uniaoConj(Conjunto conjuntoB) {
        Conjunto conjuntoResultado = new Conjunto();
        conjuntoResultado.elementos.addAll(this.elementos);
        conjuntoResultado.elementos.addAll(conjuntoB.elementos);
        return conjuntoResultado;
    }

    public Conjunto intersConj(Conjunto conjuntoB) {
        Conjunto conjuntoResultado = new Conjunto();
        conjuntoResultado.elementos.addAll(this.elementos);
        conjuntoResultado.elementos.retainAll(conjuntoB.elementos);
        return conjuntoResultado;
    }

    public Conjunto diffConj(Conjunto conjuntoB) {
        Conjunto conjuntoResultado = new Conjunto();
        conjuntoResultado.elementos.addAll(this.elementos);
        conjuntoResultado.elementos.removeAll(conjuntoB.elementos);
        return conjuntoResultado;
    }

    public Conjunto diffSimConj(Conjunto conjuntoB) {
        Conjunto conjuntoResultado = new Conjunto();
        Conjunto diffA = this.diffConj(conjuntoB);
        Conjunto diffB = conjuntoB.diffConj(this);
        conjuntoResultado = diffA.uniaoConj(diffB);
        return conjuntoResultado;
    }

    public void addConj(int elemento) {
        elementos.add(elemento);
    }

    public void remConj(int elemento) {
        elementos.remove(elemento);
    }

    public int tamConj() {
        return elementos.size();
    }

    public boolean ehElemConj(int elemento) {
        return elementos.contains(elemento);
    }

    public static void main(String[] args) {
        Conjunto conjuntoA = new Conjunto();
        Conjunto conjuntoB = new Conjunto();

        conjuntoA.addConj(1);
        conjuntoA.addConj(2);
        conjuntoA.addConj(3);

        conjuntoB.addConj(2);
        conjuntoB.addConj(3);
        conjuntoB.addConj(4);

        System.out.println("Conjunto A: " + conjuntoA.elementos);
        System.out.println("Conjunto B: " + conjuntoB.elementos);

        System.out.println("É vazio? " + conjuntoA.ehVazio());
        System.out.println("União: " + conjuntoA.uniaoConj(conjuntoB).elementos);
        System.out.println("Interseção: " + conjuntoA.intersConj(conjuntoB).elementos);
        System.out.println("Diferença: " + conjuntoA.diffConj(conjuntoB).elementos);
        System.out.println("Diferença Simétrica: " + conjuntoA.diffSimConj(conjuntoB).elementos);
        System.out.println("Tamanho: " + conjuntoA.tamConj());
        System.out.println("Contém o elemento 2? " + conjuntoA.ehElemConj(2));
    }
}
