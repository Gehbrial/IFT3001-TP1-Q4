// Nom: Gabriel Méthot
// IDUL: GAMET8
// NI: 111183847

#include "fermeture_transitive.hpp"
#include <assert.h>

void fermetureTransitive(Matrice& a,                                                   // Une matrice
			 Matrice (*multiplication)(const Matrice&, const Matrice&)) {  // Un pointeur sur une fonction calculant le produit matricielle
  assert(a.estCarree());
  assert(a.estTriangulaireSuperieure());
  assert(estUnePuissanceDeDeux(a.nbLignes()));

  Matrice b = Matrice(a.nbLignes(), a.nbColonnes());

  unsigned int length = a.nbLignes();
  unsigned int half_length = a.nbLignes() / 2;

  // Séparation de la matrice A en quatre parties
  Matrice upper_left = Matrice(a, 0, half_length, 0, half_length);
  Matrice upper_right = Matrice(a, 0, half_length, half_length, length);
  Matrice lower_left = Matrice(half_length, half_length);
  Matrice lower_right = Matrice(a, half_length, length, half_length, length);

  // On traite A00 et A11
  if (half_length > 1) {
    fermetureTransitive(upper_left, multiplication);
    fermetureTransitive(lower_right, multiplication);
  }

  // Construction de la matrice B
  for (unsigned int i = 0; i < a.nbLignes() / 2; i++) {
    for (unsigned int j = 0; j < a.nbColonnes() / 2; j++) {
      b.at(i, j) = upper_left.at(i, j);
      b.at(i, j + a.nbColonnes() / 2) = upper_right.at(i, j);
      b.at(i + a.nbLignes() / 2, j) = lower_left.at(i, j);
      b.at(i + a.nbLignes() / 2, j + a.nbColonnes() / 2) = lower_right.at(i, j);
    }
  }

  // On élève la matrice B à la puissance 3
  b = (*multiplication)((*multiplication)(b, b), b);

  // On remplace les valeurs non nulles de la matrice B par 1
  for (unsigned int i = 0; i < b.nbLignes(); i++) {
    for (unsigned int j = 0; j < b.nbColonnes(); j++) {
      if (b.at(i, j) != 0) {
        a.at(i, j) = 1;
      }
    }
  }
}

// Retourne le produit de la matrice A avec la matrice B
Matrice StrassenPourMatricesTriangulaires(const Matrice& A, const Matrice& B) {
  assert(A.estCarree() && B.estCarree());
  assert(A.nbLignes() == B.nbLignes());
  assert(estUnePuissanceDeDeux(A.nbLignes()));
  assert(A.estTriangulaireSuperieure() && B.estTriangulaireSuperieure());

  if (A.nbLignes() == 1) {
    Matrice resultat(1, 1);
    resultat.at(0, 0) = A.at(0, 0) * B.at(0, 0);
    return resultat;
  }

  const unsigned int length = A.nbLignes();
  const unsigned int half_length =  length / 2;

  Matrice a00(A, 0, half_length, 0, half_length);
  Matrice a01(A, 0, half_length, half_length, length);
  Matrice a10(A, half_length, length, 0, half_length);
  Matrice a11(A, half_length, length, half_length, length);
  Matrice b00(B, 0, half_length, 0, half_length);
  Matrice b01(B, 0, half_length, half_length, length);
  Matrice b10(B, half_length, length, 0, half_length);
  Matrice b11(B, half_length, length, half_length, length);

  Matrice m1 = Strassen(a00 + a11, b00 + b11);
  Matrice m2 = Strassen(a10 + a11, b00);
  Matrice m3 = Strassen(a00, b01 - b11);

  Matrice m4 = Matrice(m2.nbLignes(), m2.nbColonnes());

  for (unsigned int i = 0; i < m2.nbLignes(); i++) {
    for (unsigned int j= 0; j < m2.nbColonnes(); j++) {
      m4.at(i, j) = Entier(-1) * m2.at(i, j);
    }
  }

  Matrice m5 = Strassen(a00 + a01, b11);
  Matrice m6 = Strassen(a10 - a00, b00 + b01);
  Matrice m7 = Strassen(a01 - a11, b10 + b11);

  Matrice resultat(length, length);

  // Coin superieur gauche
  for (unsigned int i = 0; i < half_length; i++) {
    for (unsigned int j = 0; j < half_length; j++) {
      resultat.at(i, j) = m1.at(i, j) + m4.at(i, j) - m5.at(i, j) + m7.at(i, j);
    }
  }
  // Coin superieur droit
  for (unsigned int i = 0; i < half_length; i++) {
    for (unsigned int j = 0; j < half_length; j++) {
      resultat.at(i, half_length + j) = m3.at(i, j) + m5.at(i, j);
    }
  }
  // Coin inferieur gauche
  for (unsigned int i = 0; i < half_length; i++) {
    for (unsigned int j = 0; j < half_length; j++) {
      resultat.at(half_length + i, j) = 0;
    }
  }
  // Coin inferieur droit
  for (unsigned int i = 0; i < half_length; i++) {
    for (unsigned int j = 0; j < half_length; j++) {
      resultat.at(half_length + i, half_length + j) = m1.at(i, j) + m3.at(i, j) - m2.at(i, j) + m6.at(i, j);
    }
  }
  return resultat;
}
