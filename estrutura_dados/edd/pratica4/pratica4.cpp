#include <iostream>
#include <grp.h>

using namespace std;

void box(int x, int y, int r){
    cout << "Quadrado: " << endl;
    cout << "Top left: (" << x-r << "," << y+r << "). ";
    cout << "Top right: (" << x+r << "," << y+r << "). ";
    cout << "Bottom left: (" << x-r << "," << y-r << "). ";
    cout << "Bottom right: (" << x+r << "," << y-r << ")." << endl;
}

void estrela(int x, int y, int r){
    if (r > 0) {
        estrela(x-r, y+r, r / 2);
        estrela(x+r, y+r, r / 2);
        estrela(x-r, y-r, r / 2);
        estrela(x+r, y-r, r / 2);
        box(x, y, r); //-> substituir por rectangle da graphics.h
        //rectangle(int left, int top, int right, int bottom);
        //ou imprimir na tela as coordenadas do quadrado
    }
}
int main(){

    estrela(0, 0, 2);

    return 0;
}