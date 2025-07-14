class Conjunto:
    def __init__(A):
        A.lista = []

    def ehVazio(A):
        return not A.lista
    
    def uniaoConj(A, B):
        C = Conjunto()
        for i in A.lista:
            C.addConj(i)
        for j in B.lista:
            if j not in C.lista:
                C.addConj(j)
        C.lista.sort()
        return C
    
    def intersConj(A, B):
        C = Conjunto()
        for i in A.lista:
            if i in B.lista:
                C.addConj(i)
        C.lista.sort()
        return C

    def diffConj(A, B):
        C = Conjunto()
        for i in A.lista:
            if i not in B.lista: 
                C.addConj(i)
        C.lista.sort()
        return C
    
    def diffSimConj(A, B):
        uniao = A.uniaoConj(B)
        intersecao = A.intersConj(B)
        C = uniao.diffConj(intersecao)
        C.lista.sort()
        return C

    def addConj(A, x):
        if x not in A.lista:
            A.lista.append(x)

    def remConj(A, x):
        if x in A.lista:
            A.lista.remove(x)

    def tamConj(A):
        return len(A.lista)

    def ehElemConj(A, x):
        return x in A.lista