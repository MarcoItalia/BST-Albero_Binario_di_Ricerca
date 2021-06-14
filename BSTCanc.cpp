#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class T> class Nodo{
public:
    T valore;
    Nodo* padre;
    Nodo* sx;
    Nodo* dx;

};

template <class T> class Albero{ 
Nodo<T>* radice;

public:
    Albero() { radice = nullptr; }

    Nodo<T>* getRadice() const {return radice;}

    void preorder(Nodo<T>* p) const {
        if(p){
            out << p->valore << " ";
            preorder(p->sx);
            preorder(p->dx);
        }
    }
    void inorder(Nodo<T>* p, int v) const {
        if(p){
            inorder(p->sx, v+1);
            out << v << " ";
            inorder(p->dx, v+1);
        }
    }
    void postorder(Nodo<T>* p) const {
        if(p){
            postorder(p->sx);
            postorder(p->dx);
            out << p->valore << " ";
        }
    }
    int altezza(Nodo<T>* p) const {
        if(!p)
            return 0;
        int sin, des;
        sin = altezza(p->sx);
        des = altezza(p->dx);
        return max(sin,des)+1;
    }

    Nodo<T>* Ricerca(T val, Nodo<T>* p){
        if(p->valore == val || p == nullptr)
            return p;
        else if(val < p->valore)
            return Ricerca(val, p->sx);
        else return Ricerca(val, p->dx);
    }
    void ArchiSuccess(T val){
        Nodo<T>* p = Ricerca(val, this->radice);
        int i = 0;
        if(p->dx != nullptr){
            p = p->dx;
            i++;
            while(p->sx != nullptr){
                    p = p->sx;
                    i++;
                }
            out << i << " ";
        }else{
            while(p->padre && p->padre->dx == p){
                p = p->padre;
                i++;
            }
            if(p->padre != nullptr)
                out << i+1 << " ";
            else out << "INF ";
        }
        
    }

    Nodo<T>* Minimo(Nodo<T>* p){
        if(p->sx == nullptr)
            return p;
        else return Minimo(p->sx);
    }

    void Trapianta(Nodo<T>* x, Nodo<T>* y){
        if( x->padre == nullptr)
            this->radice = y;
        else if(x == x->padre->sx)
            x->padre->sx = y;
        else x->padre->dx = y;

        if(y != nullptr)
            y->padre = x->padre;
    }

    void Cancellazione(T val){
        Nodo<T>* x = Ricerca(val, getRadice());
        if(x != nullptr){
            if(x->sx == nullptr)
                Trapianta(x, x->dx);
            else if(x->dx == nullptr)
                Trapianta(x, x->sx);
            else{
                Nodo<T>* y = Minimo(x->dx);
                if(y->padre != x){
                    Trapianta(y, y->dx);
                    y->dx = x->dx; 
                    y->dx->padre = y;
                }

                Trapianta(x, y);
                y->sx = x->sx;
                y->sx->padre = y;
            }
        }
        
        delete x;
    }

    void Inserisci(T val){
        Nodo<T>* nuovo = new Nodo<T>;
        nuovo->valore = val;
        nuovo->sx = nuovo->dx = nullptr;
        if(!this->radice){
            this->radice = nuovo;
            this->radice->padre = nullptr;
        }
        else{
            Nodo<T>* iter = radice;
            Nodo<T>* piter = nullptr;;
            while(iter){
                piter = iter;
                if(val <= iter->valore){
                    iter = iter->sx;
                }
                else {
                    iter = iter->dx;
                }

            }
            if(val <= piter->valore)
                piter->sx = nuovo;
            else piter->dx = nuovo;
            nuovo->padre = piter;
        }
    }

  /* 
    friend ostream& operator<<(ostream& out, const Albero<T>& al){
        Nodo<T>* iter = al.radice;
        

        return out;
    }*/
};

template <class T> void visit(Albero<T> tree, string visita){
    if(visita == "preorder")
        tree.preorder(tree.getRadice());
    else if (visita == "inorder")
        tree.inorder(tree.getRadice(), 0);
    else tree.postorder(tree.getRadice());

    out << endl;
}

int main(){

    int n, m, spaz1;
    string tipo, visita, v;
    Nodo<int>* nod = new Nodo<int>;

    for(int task = 0; task < 100; task++ ){
        in >> tipo;
        in >> n;
        in >> m;
        // int, double
        if(tipo == "int"){
            Albero<int> treei;
            for(int i = 0; i < n; i++){
                in >> v;
                if(v[0] == 'i'){
                    v = v.substr(4);
                    treei.Inserisci(stoi(v));
                }else {
                    v = v.substr(5);
                    treei.Cancellazione(stoi(v));
                }
            }
            for(int i = 0; i < m; i++){
                in >> v;
                treei.ArchiSuccess(stoi(v));
            }
            
            
        }
        else {
            Albero<double> treed;
            for(int i = 0; i < n; i++){
                in >> v;
                if(v[0] == 'i'){
                    v = v.substr(4);
                    treed.Inserisci(stod(v));
                }else {
                    v = v.substr(5);
                    treed.Cancellazione(stod(v));
                }
                
            }
            for(int i = 0; i < m; i++){
                in >> v;
                treed.ArchiSuccess(stod(v));
            }
        }
        

        out << endl;
    }
    

    return 0;
}
