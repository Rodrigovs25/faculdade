#ifndef ARVORE_H
#define ARVORE_H

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

class TipoNo
{
    public:
        TipoNo();
    private:
        TipoItem item;
        TipoNo *esq;
        TipoNo *dir;
        friend class ArvoreBinaria;
};

class ArvoreBinaria
{
    public:
        ArvoreBinaria();
        ~ArvoreBinaria();
        void Insere(TipoItem item);
        void Caminha(int tipo);
        void Limpa();
    private:
        void InsereRecursivo(TipoNo* &p, TipoItem item);
        void ApagaRecursivo(TipoNo* p);
        void PorNivel();
        void PreOrdem(TipoNo* p);
        void InOrdem(TipoNo* p);
        void PosOrdem(TipoNo* p);
    
        TipoNo *raiz;
};


#endif