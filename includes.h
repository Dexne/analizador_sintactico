#ifndef INCLUDES_H
#define INCLUDES_H

#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>

using std::stringstream;
using std::reverse;
using std::fstream;
using std::string;
using std::vector;
using std::cout;
using std::getline;
using std::map;
using std::ios;
using std::regex;

class EP;
class PilaLR;

// static inline int reglasProduccion[5][4] = {
//      {2, 0, 0, 1},
//      {0, 0, 0, 0},
//      {0, 3, 0, 0},
//      {2, 0, 0, 4},
//      {0, 0, 0, 0}
// };
// static inline int reglasReduccion[5][4] = {
//      {0, 0, 0, 1},
//      {0, 0, 0, 0},
//      {0, 0, 2, 0},
//      {0, 0, 0, 4},
//      {0, 0, 6, 0},
// };

#define FILAS 95
#define COLUMNAS 48
static int reglasProduccion[95][48];
static int reglasReduccion[95][48];

typedef enum __token__ {
     T_ID = 0,
     T_ENTERO,
     T_REAL,
     T_CADENA,
     T_TIPO,
     T_opSuma,
     T_opMul,
     T_opRelac,	
     T_opOr,
     T_opAnd,
     T_opNot,	
     T_opIgualdad,	
     T_puntoYComa,	
     T_coma,
     T_ParentesisDerecho,
     T_ParentesisIzquierdo,
     T_llaveDerecha,
     T_llaveIzquierda,
     T_asignacion,
     T_if,
     T_while,
     T_return,
     T_else,
     T_dollar,
     T_programa,	
     T_Definiciones,
     T_Definicion,
     T_DefVar,
     T_ListaVar,
     T_DefFunc,
     T_Parametros,
     T_ListaParam,
     T_BloqFunc,
     T_DefLocales,	
     T_DefLocal,	
     T_Sentencias,	
     T_Sentencia,	
     T_Otro,	
     T_Bloque,	
     T_ValorRegresa,	
     T_Argumentos,	
     T_ListaArgumentos,	
     T_Termino,	
     T_LlamadaFunc,	
     T_SentenciaBloque,	
     T_Expresion,
     T_E,
     T_Unkwown
} Token;

#endif