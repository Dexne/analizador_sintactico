#include "./Pila.cpp"
#include "./Manejador.cpp"

int main() {
    PilaLR p;
    Manejador m("compilador.csv");

    p.expansion("int hola ;");
    cout << p.imprimir() << std::endl;
    // p.reduccion();
    // cout << p.imprimir() << std::endl;

    return 0;
}
