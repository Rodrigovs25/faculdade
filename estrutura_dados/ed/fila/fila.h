#ifndef FILA_H
#define FILA_H

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

class Fila
{
    public:
        Fila() {tamanho = 0;};
        int GetTamanho() {return tamanho;};
        bool Vazia() {return tamanho == 0;};
        virtual void Enfileira(TipoItem item) = 0;
        virtual TipoItem Desenfileira() = 0;
        virtual void Limpa() = 0;
    protected:
        int tamanho;
};

class FilaArranjo : public Fila
{
    public:
        FilaArranjo();
        void Enfileira(TipoItem item);
        TipoItem Desenfileira();
        void Limpa();
    private:
        int frente;
        int tras;
        static const int MAXTAM = 8;
        TipoItem itens[MAXTAM];
};


#endif