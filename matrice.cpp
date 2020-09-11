////////////////////////////////////////////////////////////////////////////////
// NE PAS MODIFIER CE FICHIER
////////////////////////////////////////////////////////////////////////////////
#include "matrice.hpp"

#include <assert.h>
#include <cmath>

Matrice::Matrice(unsigned int nb_lignes, unsigned int nb_colonnes)
  : m_elements(nb_lignes * nb_colonnes, 0),
    m_nb_colonnes(nb_colonnes)
{
  assert(nb_lignes > 0 && nb_colonnes > 0);
}

Matrice::Matrice(const Matrice& une_matrice)
  : m_elements(une_matrice.m_elements),
    m_nb_colonnes(une_matrice.nbColonnes())
{
}

Matrice::Matrice(const Matrice& source,
		 unsigned int premiere_ligne,
		 unsigned int derniere_ligne,
		 unsigned int premiere_colonne,
		 unsigned int derniere_colonne)
  : m_elements((derniere_ligne - premiere_ligne) * (derniere_colonne - premiere_colonne)),
    m_nb_colonnes(derniere_colonne - premiere_colonne)
{
  assert(premiere_ligne < derniere_ligne && derniere_ligne <= source.nbLignes());
  assert(premiere_colonne < derniere_colonne && derniere_colonne <= source.nbColonnes());
  
  for (unsigned int i = premiere_ligne; i < derniere_ligne; i++) {
    for (unsigned int j = premiere_colonne; j < derniere_colonne; j++) {
      at(i - premiere_ligne, j - premiere_colonne) = source.at(i, j);
    }
  }
}

Matrice::Matrice(int const* donnees, unsigned int nb_lignes, unsigned int nb_colonnes)
  : m_elements(donnees, donnees + nb_lignes * nb_colonnes),
    m_nb_colonnes(nb_colonnes)
{
  assert(nb_lignes > 0 && nb_colonnes > 0);
}

unsigned int Matrice::nbLignes() const {
  return m_elements.size() / m_nb_colonnes;
}

unsigned int Matrice::nbColonnes() const {
  return m_nb_colonnes;
}

bool Matrice::estCarree() const {
  return nbLignes() == nbColonnes();
}

bool Matrice::estTriangulaireInferieure() const {
  if (!estCarree())
    return false;
  const unsigned int n = nbLignes();
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = i + 1; j < n; j++) {
      if (at(i, j) != 0)
	return false;
    }
  }
  return true;
}

bool Matrice::estTriangulaireSuperieure() const {
  if (!estCarree())
    return false;
  const unsigned int n = nbLignes();
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < i; j++) {
      if (at(i, j) != 0)
	return false;
    }
  }
  return true;
}

Entier Matrice::at(unsigned int i, unsigned int j) const {
  assert(i < nbLignes() && j < nbColonnes());
  return m_elements[i * m_nb_colonnes + j];
}

Entier& Matrice::at(unsigned int i, unsigned int j) {
  assert(i < nbLignes() && j < nbColonnes());
  return m_elements[i * m_nb_colonnes + j];
}

Matrice Matrice::operator+(const Matrice& operande) const {
  assert(nbLignes() == operande.nbLignes());
  assert(nbColonnes() == operande.nbColonnes());
  Matrice resultat(*this);
  for (int i = 0; i < nbLignes(); i++) {
    for (int j = 0; j < nbColonnes(); j++) {
      resultat.at(i, j) += operande.at(i, j);
    }
  }
  return resultat;
}

// Retourne la difference entre la matrice A et la matrice B
Matrice Matrice::operator-(const Matrice& operande) const {
  assert(nbLignes() == operande.nbLignes());
  assert(nbColonnes() == operande.nbColonnes());
  Matrice resultat(*this);
  for (int i = 0; i < nbLignes(); i++) {
    for (int j = 0; j < nbColonnes(); j++) {
      resultat.at(i, j) -= operande.at(i, j);
    }
  }
  return resultat;
}

Matrice Matrice::operator-() const {
  Matrice resultat(nbLignes(), nbColonnes());
  for (int i = 0; i < nbLignes(); i++) {
    for (int j = 0; j < nbColonnes(); j++) {
      resultat.at(i, j) = -at(i, j);
    }
  }
  return resultat;
}

bool Matrice::operator==(const Matrice& operande) const {
  if (operande.nbLignes() != nbLignes() || operande.nbColonnes() != nbColonnes())
    return false;
  for (unsigned int i = 0; i < nbLignes(); i++) {
    for (unsigned int j = 0; j < nbColonnes(); j++) {
      if (at(i, j) != operande.at(i, j))
	return false;
    }
  }
  return true;
}

bool estUnePuissanceDeDeux(unsigned int x) {
  return x > 0 && (x & (x - 1)) == 0;	// 8-)
}

// Retourne le produit de la matrice A avec la matrice B
Matrice Strassen(const Matrice& A, const Matrice& B) {
  assert(A.estCarree() && B.estCarree());
  assert(A.nbLignes() == B.nbLignes());
  assert(estUnePuissanceDeDeux(A.nbLignes()));

  // Multiplication de deux matrices de dimensions 1 x 1
  if (A.nbLignes() == 1) {
    Matrice resultat(1, 1);
    resultat.at(0, 0) = A.at(0, 0) * B.at(0, 0);
    return resultat;
  }

  const unsigned int deux_n = A.nbLignes();
  const unsigned int n =  deux_n / 2;
  Matrice a00(A, 0, n, 0, n);
  Matrice a01(A, 0, n, n, deux_n);
  Matrice a10(A, n, deux_n, 0, n);
  Matrice a11(A, n, deux_n, n, deux_n);
  Matrice b00(B, 0, n, 0, n);
  Matrice b01(B, 0, n, n, deux_n);
  Matrice b10(B, n, deux_n, 0, n);
  Matrice b11(B, n, deux_n, n, deux_n);

  Matrice m1 = Strassen(a00 + a11, b00 + b11);
  Matrice m2 = Strassen(a10 + a11, b00);
  Matrice m3 = Strassen(a00, b01 - b11);
  Matrice m4 = Strassen(a11, b10 - b00);
  Matrice m5 = Strassen(a00 + a01, b11);
  Matrice m6 = Strassen(a10 - a00, b00 + b01);
  Matrice m7 = Strassen(a01 - a11, b10 + b11);

  Matrice resultat(deux_n, deux_n);
  // Coin superieur gauche
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      resultat.at(i, j) = m1.at(i, j) + m4.at(i, j) - m5.at(i, j) + m7.at(i, j);
    }
  }
  // Coin superieur droit
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      resultat.at(i, n + j) = m3.at(i, j) + m5.at(i, j);
    }
  }
  // Coin inferieur gauche
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      resultat.at(n + i, j) = m2.at(i, j) + m4.at(i, j);
    }
  }
  // Coin inferieur droit
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      resultat.at(n + i, n + j) = m1.at(i, j) + m3.at(i, j) - m2.at(i, j) + m6.at(i, j);
    }
  }
  return resultat;
}

Matrice multiplicationClassique(const Matrice& A, const Matrice& B) {
  assert(A.nbColonnes() == B.nbLignes());
  
  Matrice resultat(A.nbLignes(), B.nbColonnes());
  for (unsigned int i = 0; i < resultat.nbLignes(); i++) {
    for (unsigned int j = 0; j < resultat.nbColonnes(); j++) {
      for (unsigned int k = 0; k < A.nbColonnes(); k++) {
	resultat.at(i, j) += A.at(i, k) * B.at(k, j);
      }
    }
  }
  return resultat;
}
