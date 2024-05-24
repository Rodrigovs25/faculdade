/*
#include <iostream>
#include <string>

using namespace std;

typedef string TipoChave;


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
};

TipoItem::TipoItem(){
    chave = -1; // indica um item vazio
}

TipoItem::TipoItem(TipoChave c){
    chave = c;
}

void TipoItem::SetChave(TipoChave c){
    chave = c;
}

TipoChave TipoItem::GetChave(){
    return chave;
}

void TipoItem::Imprime(){
    cout << chave << " ";
}

class TipoNo
{
    public:
        TipoNo();
        TipoItem item;
        TipoNo *esq;
        TipoNo *dir;
        int qts;
        bool vivo;
        int tipo;
        friend class ArvoreBinaria;
};

TipoNo::TipoNo()
{
    item.SetChave("");
    qts = 1;
    vivo = true;
    esq = NULL;
    dir = NULL;
}

class ArvoreBinaria
{
    public:
        ArvoreBinaria(){
            raiz = NULL;
        };


        void Insere(TipoItem item, int tipo);
        void Caminha(){
            InOrdem(raiz);
        };
        TipoItem Pesquisa(TipoChave chave);
        void Remove(TipoChave chave);

    private:
        void InsereRecursivo(TipoNo* &p, TipoItem item, int tipo);
        void ApagaRecursivo(TipoNo* p);
        TipoItem PesquisaRecursivo(TipoNo* p, TipoChave chave);
        void RemoveRecursivo(TipoNo* &p, TipoChave chave);
        void Antecessor(TipoNo* q, TipoNo* &r);
        void PorNivel();
        //void PreOrdem(TipoNo* p);
        void InOrdem(TipoNo* p);
        //void PosOrdem(TipoNo* p);
        TipoNo *raiz;
};


TipoItem ArvoreBinaria::Pesquisa(TipoChave chave) {
    return PesquisaRecursivo(raiz, chave);
}

TipoItem ArvoreBinaria::PesquisaRecursivo(TipoNo *no, TipoChave chave) {
    TipoItem aux;
    if (no == NULL) {
        aux.SetChave(""); // Flag para item não presente
        return aux;
    }
    if (chave < no->item.GetChave())
        return PesquisaRecursivo(no->esq, chave);
    else if (chave>no->item.GetChave())
        return PesquisaRecursivo(no->dir, chave);
    else
        return no->item;
}

void ArvoreBinaria::Insere(TipoItem item, int tipo){
    InsereRecursivo(raiz, item, tipo);
}
void ArvoreBinaria::InsereRecursivo(TipoNo* &p, TipoItem item, int tipo){
    if(p == NULL){
        p = new TipoNo();
        p->item = item;
        p->tipo = tipo;
    }
    else{
        if(item.GetChave() < p->item.GetChave())
            InsereRecursivo(p->esq, item, tipo);
        else if (item.GetChave() > p->item.GetChave())
            InsereRecursivo(p->dir, item, tipo);
        else if (item.GetChave() == p->item.GetChave()) {
            if (!tipo)
                p->qts++;
            else
                p->vivo = false;
        }
    }
}

void ArvoreBinaria::Remove(TipoChave chave) {
    return RemoveRecursivo(raiz, chave);
}

void ArvoreBinaria::RemoveRecursivo(TipoNo* &no, TipoChave chave){
    TipoNo *aux;
    if (no == NULL) {
        throw("Item nao está presente");
    }
    if (chave < no->item.GetChave())
        return RemoveRecursivo(no->esq, chave);
    else if (chave>no->item.GetChave())
        return RemoveRecursivo(no->dir, chave);
    else {
        if (no->dir == NULL) {
            aux = no;
            no = no->esq;
            free(aux);
        }
        else if(no->esq == NULL) {
            aux = no;
            no = no->dir;
            free(aux);
        }
        else
            Antecessor(no, no->esq);
    }
}

void ArvoreBinaria::Antecessor(TipoNo *q, TipoNo* &r){
    if(r->dir != NULL) {
        Antecessor(q, r->dir);
        return;
    }
    q->item = r->item;
    q = r;
    r = r->esq;
    free(q);
}

void ArvoreBinaria::InOrdem(TipoNo *p){
    if(p!=NULL){
        InOrdem(p->esq);
        if(p->vivo && !p->tipo) {
            p->item.Imprime();
            cout << p->qts << endl;           
        }
        InOrdem(p->dir);
    }
}


int main(){
    
    string ass, vitima;
    ArvoreBinaria Assa, Mortos;

    while(cin >> ass >> vitima){
        //cout << ass << " " << vitima << endl;
        TipoItem aux1, aux2;

        aux1.SetChave(ass);
        Assa.Insere(aux1, 0);

        aux2.SetChave(vitima);
        Assa.Insere(aux2, 1);
    }
    
    Assa.Caminha();
    
    return 0;
}


*/


#include <iostream>
#include <string>

using namespace std;

typedef string TipoChave;


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
};

TipoItem::TipoItem(){
    chave = -1; // indica um item vazio
}

TipoItem::TipoItem(TipoChave c){
    chave = c;
}

void TipoItem::SetChave(TipoChave c){
    chave = c;
}

TipoChave TipoItem::GetChave(){
    return chave;
}

void TipoItem::Imprime(){
    //cout << chave << " ";
    printf("%s ", chave);
}

class TipoNo
{
    public:
        TipoNo();
        TipoItem item;
        TipoNo *esq;
        TipoNo *dir;
        int qts;
        bool vivo;
        int tipo;
        friend class ArvoreBinaria;
};

TipoNo::TipoNo()
{
    item.SetChave("");
    qts = 1;
    vivo = true;
    esq = NULL;
    dir = NULL;
}

class ArvoreBinaria
{
    public:
        ArvoreBinaria(){
            raiz = NULL;
        };


        void Insere(TipoItem item, int tipo);
        void Caminha(){
            InOrdem(raiz);
        };
        TipoItem Pesquisa(TipoChave chave);
        void Remove(TipoChave chave);

    private:
        void InsereRecursivo(TipoNo* &p, TipoItem item, int tipo);
        void ApagaRecursivo(TipoNo* p);
        TipoItem PesquisaRecursivo(TipoNo* p, TipoChave chave);
        void RemoveRecursivo(TipoNo* &p, TipoChave chave);
        void Antecessor(TipoNo* q, TipoNo* &r);
        void PorNivel();
        //void PreOrdem(TipoNo* p);
        void InOrdem(TipoNo* p);
        //void PosOrdem(TipoNo* p);
        TipoNo *raiz;
};


TipoItem ArvoreBinaria::Pesquisa(TipoChave chave) {
    return PesquisaRecursivo(raiz, chave);
}

TipoItem ArvoreBinaria::PesquisaRecursivo(TipoNo *no, TipoChave chave) {
    TipoItem aux;
    if (no == NULL) {
        aux.SetChave(""); // Flag para item não presente
        return aux;
    }
    if (chave < no->item.GetChave())
        return PesquisaRecursivo(no->esq, chave);
    else if (chave>no->item.GetChave())
        return PesquisaRecursivo(no->dir, chave);
    else
        return no->item;
}

void ArvoreBinaria::Insere(TipoItem item, int tipo){
    InsereRecursivo(raiz, item, tipo);
}
void ArvoreBinaria::InsereRecursivo(TipoNo* &p, TipoItem item, int tipo){
    if(p == NULL){
        p = new TipoNo();
        p->item = item;
        p->tipo = tipo;
    }
    else{
        if(item.GetChave() < p->item.GetChave())
            InsereRecursivo(p->esq, item, tipo);
        else if (item.GetChave() > p->item.GetChave())
            InsereRecursivo(p->dir, item, tipo);
        else if (item.GetChave() == p->item.GetChave()) {
            if (!tipo)
                p->qts++;
            else
                p->vivo = false;
        }
    }
}

void ArvoreBinaria::Remove(TipoChave chave) {
    return RemoveRecursivo(raiz, chave);
}

void ArvoreBinaria::RemoveRecursivo(TipoNo* &no, TipoChave chave){
    TipoNo *aux;
    if (no == NULL) {
        throw("Item nao está presente");
    }
    if (chave < no->item.GetChave())
        return RemoveRecursivo(no->esq, chave);
    else if (chave>no->item.GetChave())
        return RemoveRecursivo(no->dir, chave);
    else {
        if (no->dir == NULL) {
            aux = no;
            no = no->esq;
            free(aux);
        }
        else if(no->esq == NULL) {
            aux = no;
            no = no->dir;
            free(aux);
        }
        else
            Antecessor(no, no->esq);
    }
}

void ArvoreBinaria::Antecessor(TipoNo *q, TipoNo* &r){
    if(r->dir != NULL) {
        Antecessor(q, r->dir);
        return;
    }
    q->item = r->item;
    q = r;
    r = r->esq;
    free(q);
}

void ArvoreBinaria::InOrdem(TipoNo *p){
    if(p!=NULL){
        InOrdem(p->esq);
        if(p->vivo && !p->tipo) {
            p->item.Imprime();
            //cout << p->qts << endl; 
            printf("%d\n", p->qts);
        }
        InOrdem(p->dir);
    }
}


int main(){
    
    string ass, vitima;
    ArvoreBinaria Assa, Mortos;

    while(scanf(" %s, %s", &ass, &vitima) != EOF){
        //cout << ass << " " << vitima << endl;
        TipoItem aux1, aux2;

        aux1.SetChave(ass);
        Assa.Insere(aux1, 0);

        aux2.SetChave(vitima);
        Assa.Insere(aux2, 1);
    }
    
    Assa.Caminha();
    
    return 0;
}
