////////////////////////////////////////////////////////////////////////////////
// NE PAS MODIFIER CE FICHIER
//
// Note: Les classes d'efficacite sont donnees en fonction de matrices de taille
//       n x n.
////////////////////////////////////////////////////////////////////////////////

#ifndef MATRICE
#define MATRICE

#include <vector>

#include "entier.hpp"

class Matrice {
private:
  std::vector<Entier> m_elements;
  unsigned int m_nb_colonnes;
public:
  Matrice(unsigned int nb_lignes, unsigned int nb_colonnes); // Construit la matrice nulle de dimensions nb_lignes x nb_colonnes. Efficacite: Theta(n^2)
  Matrice(const Matrice& une_matrice);			     // Constructeur de copie. Efficacite: Theta(n^2)
  // Construit une sous-matrice de la matrice source constituee des
  // lignes entre premiere_ligne et derniere_ligne (exclusivement) et
  // des colonnes premiere_colonne et derniere_colonne (exclusivement)
  Matrice(const Matrice& source, unsigned int premiere_ligne, unsigned int derniere_ligne, unsigned int premiere_colonne, unsigned int derniere_colonne); // Efficacite: Theta(n^2)
  // Construit une matrice a partir d'un vecteur listant les elements de la matrice ligne par ligne. Efficacite: Theta(n^2)
  Matrice(int const* donnees, unsigned int nb_lignes, unsigned int nb_colonnes);

  unsigned int nbLignes() const;   // Nombre de lignes. Efficacite: Theta(1)
  unsigned int nbColonnes() const; // Nombre de colonnes. Efficacite: Theta(1)
  bool estCarree() const;	   // Retourne vrai si la matrice est carree. Efficacite: Theta(1)
  bool estTriangulaireInferieure() const; // Retourne vrai si la matrice est triangulaire inferieure. Efficacite: O(n^2)
  bool estTriangulaireSuperieure() const; // Retourne vrai si la matrice est triangulaire inferieure. Efficacite: O(n^2)

  Entier at(unsigned int i, unsigned int j) const;  // Retourne le nombre a la ligne i et la colonne j. Efficacite: Theta(1)
  Entier& at(unsigned int i, unsigned int j);	    // Retourne une reference sur le nombre a la ligne i et la colonne j. Efficacite: Theta(1)

  Matrice operator+(const Matrice& operande) const; // Additionne deux matrices. Efficacite: Theta(n^2)
  Matrice operator-(const Matrice& operande) const; // Soustrait deux matrices. Efficacite: Theta(n^2)
  Matrice operator-() const;			    // Negation d'une matrice. Efficacite: Theta(n^2)
  bool operator==(const Matrice& operande) const;   // Teste l'egalite entre deux matrices. Efficacite: O(n^2)
};

// Retourne vrai si x est une puissance de 2. Efficacite: Theta(1)
bool estUnePuissanceDeDeux(unsigned int x);

// Retourne le produit de la matrice A avec la matrice B. Fonctionne
// seulement pour les matrices carrees n x n ou n est une puissance de
// deux. Efficacite: Theta(n^lg(7))
Matrice Strassen(const Matrice& A, const Matrice& B);

// Algorithme de multiplication matricielle classique. Efficacite: Theta(n^3)
Matrice multiplicationClassique(const Matrice& A, const Matrice& B);

#endif
