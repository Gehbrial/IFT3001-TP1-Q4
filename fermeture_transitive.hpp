#ifndef FERMETURETRANSITIVE
#define FERMETURETRANSITIVE

#include "matrice.hpp"

void fermetureTransitive(Matrice& a, Matrice (*multiplication)(const Matrice&, const Matrice&));

Matrice StrassenPourMatricesTriangulaires(const Matrice& A, const Matrice& B);

#endif
