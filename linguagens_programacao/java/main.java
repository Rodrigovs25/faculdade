public class main {

    public static void main(String[] args) {

        //Criação de Conjuntos:
        Conjunto<Integer> conjuntoA = new Conjunto<Integer>();
        Conjunto<Integer> conjuntoB = new Conjunto<Integer>();

        //Adição de Elementos:
        conjuntoA.addConj(1);
        conjuntoA.addConj(3);
        conjuntoA.addConj(2);
        conjuntoA.addConj(5);
        conjuntoB.addConj(2);
        conjuntoB.addConj(3);
        conjuntoB.addConj(4);
        conjuntoB.addConj(6);

        //Impressão:
        System.out.println("Conjunto A: " + conjuntoA.getElementos());
        System.out.println("Conjunto B: " + conjuntoB.getElementos());
    
        //Operações entre Conjuntos:    
        Conjunto<Integer> uniao = conjuntoA.uniaoConj(conjuntoB);
        System.out.println("Uniao: " + uniao.getElementos());  
        Conjunto<Integer> intersecao = conjuntoA.intersConj(conjuntoB);
        System.out.println("Intersecao: " + intersecao.getElementos());  
        Conjunto<Integer> diferenca = conjuntoA.diffConj(conjuntoB);
        System.out.println("Diferenca entre A e B: " + diferenca.getElementos());  
        Conjunto<Integer> dif_sim = conjuntoA.diffSimConj(conjuntoB);
        System.out.println("Diferenca Simetrica entre A e B: " + dif_sim.getElementos());  

        //Verificação e Manipulação:
        System.out.println("Eh vazio? " + conjuntoA.ehVazio());  
        System.out.println("Tamanho: " + conjuntoA.tamConj());  
        System.out.println("Contem o elemento 2? " + conjuntoA.ehElemConj(1));  

        conjuntoA.remConj(2);
        System.out.println("Conjunto A: " + conjuntoA.getElementos());

    }
    
}
