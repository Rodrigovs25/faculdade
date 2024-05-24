#include <iostream>
#include <string>

using namespace std;

typedef string TipoChave;


class TipoNo {
    public:
        TipoNo();
        void SetChave(TipoChave c);
        TipoChave GetChave();
        void Imprime();

    private:
        TipoChave chave;
        TipoNo *esq;
        TipoNo *dir;
        int qts;
        bool vivo;
    
    friend class ArvoreBinaria;
};

TipoNo::TipoNo() {
    chave = "-1"; // indica um item vazio
    qts = 1;
    esq = NULL;
    dir = NULL;
    vivo = true;
}

void TipoNo::SetChave(TipoChave c){
    chave = c;
}

TipoChave TipoNo::GetChave(){
    return chave;
}

void TipoNo::Imprime(){
    cout << chave << " ";
}

class ArvoreBinaria
{
    public:
        ArvoreBinaria(){
            raiz = NULL;
        };


        void Insere(TipoChave chave, int tipo);
        void Caminha();
        void Remove(TipoChave chave);

    private:
        void InsereRecursivo(TipoNo* &p, TipoChave chave, int tipo);
        void ApagaRecursivo(TipoNo* p);
        void RemoveRecursivo(TipoNo* &p, TipoChave chave);
        void Antecessor(TipoNo* q, TipoNo* &r);
        void InOrdem(TipoNo* p);
        TipoNo *raiz;
};

void ArvoreBinaria::Insere(TipoChave chave, int tipo){
    InsereRecursivo(raiz, chave, tipo);
}
void ArvoreBinaria::InsereRecursivo(TipoNo* &p, TipoChave chave, int tipo){
    if(p == NULL){
        p = new TipoNo();
        p->SetChave(chave);
        p->vivo = !tipo;
    }
    else{
        if(chave < p->GetChave())
            InsereRecursivo(p->esq, chave, tipo);
        else if (chave > p->GetChave())
            InsereRecursivo(p->dir, chave, tipo);
        else if (chave == p->GetChave()) {
            if(tipo == 0)
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
        return;
    }
    if (chave < no->GetChave())
        return RemoveRecursivo(no->esq, chave);
    else if (chave>no->GetChave())
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

    q = r;
    r = r->esq;
    free(q);
}

void ArvoreBinaria::Caminha(){
    InOrdem(raiz);
}

void ArvoreBinaria::InOrdem(TipoNo *p){
    if(p!=NULL){
        InOrdem(p->esq);

        if(p->vivo){
            p->Imprime();
            cout << p->qts << endl;
        }

        InOrdem(p->dir);
    }
}


int main(){
    
    string assassino, vitima;
    ArvoreBinaria Ass;

    while(cin >> assassino >> vitima){

        Ass.Insere(assassino, 0);

        Ass.Insere(vitima, 1);
    }
    
    cout << "HALL OF MURDERERS" << endl;

    Ass.Caminha();
    
    return 0;

}

//./a.out < in.txt