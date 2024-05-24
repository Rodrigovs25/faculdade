#ifndef PILHA_H
#define PILHA_H

class Pilha
{
    public:
        Pilha(){tamanho = 0;};
        int GetTamanho() {return tamanho;};
        bool pilhavazia() {return tamanho == 0;};
        virtual void empilha(TipoItem item) = 0;
        virtual TipoItem desempilha() = 0;
        virtual void destroipilha() = 0;
    protected:
        int tamanho;
};

class PilhaArranjo : public Pilha
{
    public:
        PilhaArranjo();
        void criapilha();
        void empilha(TipoItem item);
        TipoItem desempilha();
        void destroipilha();
    private:
        FilaArranjo fila1;
        FilaArranjo fila2;
        static const int MAXTAM = 10;
};


#endif