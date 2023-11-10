#ifndef PILA_CLASS
#define PILA_CLASS

#include "./EP.cpp"
#include "includes.h"
#include <cmath>

class PilaLR {
    public:
        vector<EP> entrada;
        PilaLR() {
            this->entrada.push_back(EP("$"));
            this->entrada.push_back(EP("0"));
        }

        Token getTokenType(const string& token);
        void expansion(string);
        void reduccion();
        string imprimir() const;
};

struct Rule {
    string generate;
    Token token;
    int elements;
};
Rule rrules[10] = {
    {"0", Token::T_Unkwown, 0},
    {"0", Token::T_Unkwown, 0},
    {"0", Token::T_Unkwown, 0},
    {"0", Token::T_Unkwown, 0},
    {"0", Token::T_Unkwown, 0},
    {"0", Token::T_Unkwown, 0},
    {"0", Token::T_Unkwown, 0},
    {"ListVar", Token::T_ListaVar, 0},
    {"0", Token::T_Unkwown, 0},
    {"0", Token::T_Unkwown, 0}
};
struct Regla {
    static void Simple(PilaLR* pila, int& token_eval) {
        pila->entrada.push_back(EP(std::to_string(token_eval)));
    }  
    static void Compleja(PilaLR* pila, int& token_eval) {
        pila->entrada.pop_back();

        token_eval = std::abs(token_eval);
        int top = (int)(pila->entrada[pila->entrada.size() - 1].valor.c_str()[0] - '0');

        struct Rule resultado = rrules[token_eval];
        int eval = reglasProduccion[top][resultado.token];

        if (!resultado.elements) {
            pila->entrada.push_back(EP(resultado.generate));
            pila->entrada.push_back(EP(std::to_string(eval)));
        }
    }
};

Token PilaLR::getTokenType(const string& word) {
    // operadores o caracteres especiales
    if (word.length() == 1) {
        switch (*(word.c_str())) {
            case '+': return T_opSuma;
            case '*': return T_opMul;
            case '<':
            case '>': return T_opRelac;
            case '!': return T_opNot;
            case ';': return T_puntoYComa;
            case ',': return T_coma;
            case '(': return T_ParentesisDerecho;
            case ')': return T_ParentesisIzquierdo;
            case '{': return T_llaveDerecha;
            case '}': return T_llaveIzquierda;
            case '=': return T_asignacion;
            case '$': return T_dollar;
        }
    }
    else if (word.length() > 1) {
        if (word == "int" || word == "float" || word == "string" || word == "void") return T_TIPO;
        if (word == "||")       return T_opOr;
        if (word == "&&")       return T_opAnd;
        if (word == "==")       return T_opIgualdad;
        if (word == "while")    return T_while;
        if (word == "else")     return T_else;
        if (word == "return")   return T_return;
        else {
            static regex ID_regex("^[a-zA-Z_][a-zA-Z0-9_]{0,30}$");
            string ID = std::regex_replace(word, ID_regex, "ID");
            if (ID == "ID") return T_ID;
        }
    }
    return T_Unkwown;
}

void PilaLR::expansion(string datos) {
    stringstream ss(datos);
    vector<string> tokens_vector;
    Token t_token;
    string t;

    /* Sistema de expansión */
    while (ss >> t) tokens_vector.push_back(t);

    // Proceso de expansión
    for (int i = 0; i<tokens_vector.size(); i++) {
        string token = tokens_vector[i];
        // proceso de analizador lexico
        t_token = this->getTokenType(token);        
        int top = (int)(this->entrada[this->entrada.size() - 1].valor.c_str()[0] - '0'); // almacenar anterior

        this->entrada.push_back(EP(token, t_token)); // crear elemento con valor y tipo
        int eval = reglasProduccion[top][t_token];
        cout << "\nEval\t" << eval << endl;
        if (eval > 0)
            Regla::Simple(this, eval);
        else if (eval < 0) {
            Regla::Compleja(this, eval);
            i--;
        }
    }
    this->entrada.push_back(EP("$", T_dollar)); 
}

void PilaLR::reduccion() {
    int top, remove;

    this->entrada.pop_back();
    
    while (true) {
        top = (int)(this->entrada.back().valor.c_str()[0] - '0');
        remove = reglasReduccion[top][T_dollar];

        // approved state
        if (!remove) break;

        for (int i = 0; i<remove; i++)
            this->entrada.pop_back();

        top = (int)(this->entrada.back().valor.c_str()[0] - '0');
        this->entrada.push_back(EP("E"));
        this->entrada.push_back(EP(std::to_string('0' + reglasProduccion[top][T_E])));
    }
}

string PilaLR::imprimir() const {
    string output;
    for (auto ep: this->entrada)
        output += ep.valor;
    return output;
}
#endif


/*
    Estado inicial
    ->  int hola;

Pila                    Entrada $                       salida
$0                      inthola;$                       d5
$0int5                  hola;$                          d8
$0int5hola8             ;$                              r7 ListVaR
$0int5hola8LiatVar      ;$                              9
$0int5hola8LiatVar9     ;$                              d12
$0int5hola8LiatVar9;12   $                              r6 DefVar nos dice = tipo identificador <ListaVar> ; tienes 4, quita el doble


// comportamiento de Regla Compleja
        resultado = valor de la regla
        eval = comparacion resultado <> top
        push resultado, eval

// comportamiento de producciones o solitarios
// 1. comparar la entrada con el tope -> pushear la entrada y después el resultado


// comportamiento de las reglas de reduccion
// 1. aplicas sus eliminaciones respectivas
// 2. comparar lo que genera la regla con el tope -> pushear la regla y después el resultado
// 3. Tope con dollar
// 4. Hasta programa o aceptacion


// ALgoritmo basico
// quitas todo y metes DefVar
//comparacion de anterior de tope con tope
//inserta lo de la regla
//tope con dolar
//quita todo e inserta la regla "palabra"


// reduccion
$0Defvar4                $                              r4 <Definicion> ::= <DefVar>
$0Definicon3             $                              r2  <<Definiciones> ::= \e > ::= \e 
$0Definiciones2          $                              R1 <programa> ::= <Definiciones> 
*/

// Estado inicial $0
// Entrada : a+b+c+d+e+f$          

/*
R2
tope con dolar 
retirar 2
insertar E
anterior de tope con tope = push de 4

R1
tope con dolar
retirar 6
insertar E
anterior de tope con tope = push de 4

$0a2+3b2+3c2+3d2+3e2+3f 2	$	r2 E -> id   
$0a2+3b2+3c2+3d2+3e2+3E4	$	r1  E -> id + E
$0a2+3b2+3c2+3d2+3E4	    $	r1 E -> id + E
$0a2+3b2+3c2+3E4	        $	r1 E -> id + E
$0a2+3b2+3E4	            $	r1 E -> id + E
$0a2+3E4	                $	r1 E -> id + E
$0E1	                    $	r0 acept
*/
