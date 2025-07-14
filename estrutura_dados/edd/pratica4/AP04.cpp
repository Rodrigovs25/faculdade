#include <iostream>
#include <vector>
 
using namespace std;

template <typename S>
ostream& operator<<(ostream& os, const vector<S>& vector){
    for (auto element : vector) {
        os << element << " ";
    }

    return os;
}

int Elimina(vector<int>* v, int pos_a_eliminar, int salto){
    //cout << "pos_a_eliminar: "<< pos_a_eliminar << " em " << v->size()-1 << endl;
    //cout  << endl << "Estado antes de erase: "<< *v << endl;
    
    if(v->size()==1) {
        vector<int>::iterator it = v->begin();
        return *it;
    }

    else {
        v->erase(v->begin() + pos_a_eliminar);
        int prox = pos_a_eliminar + salto - 1;
        //cout << "prox inicial: " << prox << endl;
        if (prox > v->size() - 1 && v->size() - 1 > 0) {
            prox = prox % (v->size());
            //cout << prox % (v->size()) << endl;
        }
        //cout << "prox final: " << prox << endl;
    
        Elimina(v, prox, salto);
    }

}

int main() {

    
    int NC = 0, n = 0, k = 0, m = 0, resta = 0, prim_pos = 0;
 
    cin >> NC;

    ////cout << "NC: " << NC << endl;

    for (int i = 0; i < NC; i++){
        vector<int> circ;
        cin >> n >> k;
        //cout << "n: " << n << " " << "k: " << k << endl;
        for (int i = 0; i < n; i++) {
            circ.push_back(i+1);
        }

        prim_pos = k - 1;

        if (k > circ.size()) {
            prim_pos = k % circ.size() - 1;
        }
        
        resta = Elimina(&circ, prim_pos, k);

        cout << "Case " << i + 1 << ": " << resta << endl;
        
        ////cout << endl << "Estado Final do Vetor: " << circ << endl;
    
    }
    return 0;
}