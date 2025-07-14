#ifndef PILHA_H
#define PILHA_H

typedef int TipoChave; // TipoChave é um inteiro
class TipoItem
{
    public:
        TipoItem();
        TipoItem(TipoChave c);
        void SetChave(TipoChave c);
        TipoChave GetChave();
        void Imprime();
    private:
        TipoChave chave;
        // outros membros
};

class Pilha
{
    public:
        Pilha(){tamanho = 0;};
        int GetTamanho() {return tamanho;};
        bool Vazia() {return tamanho == 0;};
        virtual void Empilha(TipoItem item) = 0;
        virtual TipoItem Desempilha() = 0;
        virtual void Limpa() = 0;
    protected:
        int tamanho;
};

class PilhaArranjo : public Pilha
{
    public:
        PilhaArranjo();
        void Empilha(TipoItem item);
        TipoItem Desempilha();
        void Limpa();
    private:
        int topo;
        static const int MAXTAM = 100;
        TipoItem itens[MAXTAM];
};

#endif