#ifndef EP_CLASS
#define EP_CLASS

#include "./includes.h"

class EP {
private:
    string valor;
    Token token;
public:
    EP(string valor) : valor(valor) {}
    EP(string valor, Token t_token) : valor(valor), token(t_token) {}
    friend class PilaLR;
};

class Terminal : public EP {
public:
    Terminal(string valor) : EP(valor) {}
};

class NoTerminal : public EP {
public:
    NoTerminal(string valor) : EP(valor) {}
};

class Estado : public EP {
public:
    Estado(string valor) : EP(valor) {}
};

#endif