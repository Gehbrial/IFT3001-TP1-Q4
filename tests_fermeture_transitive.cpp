#include <assert.h>
#include <iostream>
#include <sstream>
#include <string>

#include "fermeture_transitive.hpp"
#include "entier.hpp"

void imprimeMatrice(const std::string& nom, const Matrice& a) {
  const std::string identification = nom + " = ";
  const std::string espace(identification.length(), ' ');
  for (unsigned int i = 0; i < a.nbLignes(); i++) {
    if (i == (a.nbLignes() - 1) / 2) {
      std::cout << identification;
    } else {
      std::cout << espace;
    }
    std::cout << " [ ";
    for (unsigned int j = 0; j < a.nbColonnes(); j++) {
      std::cout << a.at(i, j) << " ";
    }
    std::cout << "]" << std::endl;
  }
}

bool test(const std::string& nom_du_test, const Matrice& graphe, const Matrice& fermeture_transitive) {
  const unsigned int nb_resets = Entier::nombreResets();

  Entier::resetCompteur();
  Matrice resultat_Strassen(graphe);
  fermetureTransitive(resultat_Strassen, &Strassen);
  const unsigned int nb_multiplications_Strassen = Entier::nombreMultiplications();

  Entier::resetCompteur();
  Matrice resultat_classique(graphe);
  fermetureTransitive(resultat_classique, &multiplicationClassique);
  const unsigned int nb_multiplications_classique = Entier::nombreMultiplications();

  Entier::resetCompteur();
  Matrice resultat_strassen_triangulaire(graphe);
  fermetureTransitive(resultat_strassen_triangulaire, &StrassenPourMatricesTriangulaires);
  const unsigned int nb_multiplications_Strassen_triangulaire = Entier::nombreMultiplications();
  
  if (Entier::nombreResets() - nb_resets != 3) {
    std::cout << "0 point: La fonction reset a ete appelee en dehors du test" << std::endl;
    return false;
  }

  const bool resultat = (resultat_Strassen == fermeture_transitive) &&
    (resultat_classique == fermeture_transitive);

  if (resultat) {
    std::cout << "+1 point: Le test " << nom_du_test << " a passe." << std::endl;
  } else {
    std::cout << "+0 point: Le test " << nom_du_test << " a echoue." << std::endl;
    imprimeMatrice("graphe", graphe);
    std::cout << std::endl;
    imprimeMatrice("solution classique", resultat_Strassen);
    std::cout << std::endl;
    imprimeMatrice("solution Strassen", resultat_Strassen);
    std::cout << std::endl;
    imprimeMatrice("solution Strassen triangulaire", resultat_strassen_triangulaire);
    std::cout << std::endl;
    imprimeMatrice("solution attendue ", fermeture_transitive);
  }

  std::cout << "Nombre de multiplications (algorithme classique):   " << nb_multiplications_classique << std::endl
	    << "Nombre de multiplications (Strassen): " << nb_multiplications_Strassen << std::endl
	    << "Nombre de multiplications (Strassen triangulaire): " << nb_multiplications_Strassen_triangulaire << std::endl << std::endl;
  
  return resultat;
}

bool testSimple() {
  int graphe[4] = {1, 1,
		   0, 1};
  return test("simple", Matrice(graphe, 2, 2), Matrice(graphe, 2, 2));
}

bool testQuatreParQuatre() {
  int graphe[16] = {1, 1, 1, 0,
		    0, 1, 0, 0,
		    0, 0, 1, 1,
		    0, 0, 0, 1};
  int fermeture[16] = {1, 1, 1, 1,
		       0, 1, 0, 0,
		       0, 0, 1, 1,
		       0, 0, 0, 1};
  return test("quatre par quatre", Matrice(graphe, 4, 4), Matrice(fermeture, 4, 4));
}

bool testEnonce() {
  int graphe[8*8] = {1, 0, 1, 0, 0, 0, 0, 0,
		     0, 1, 0, 1, 0, 0, 0, 0,
		     0, 0, 1, 0, 1, 1, 0, 0,
		     0, 0, 0, 1, 1, 0, 0, 0,
		     0, 0, 0, 0, 1, 0, 1, 0,
		     0, 0, 0, 0, 0, 1, 1, 0,
		     0, 0, 0, 0, 0, 0, 1, 1,
		     0, 0, 0, 0, 0, 0, 0, 1};
  int fermeture[8*8] = {1, 0, 1, 0, 1, 1, 1, 1,
			0, 1, 0, 1, 1, 0, 1, 1,
			0, 0, 1, 0, 1, 1, 1, 1,
			0, 0, 0, 1, 1, 0, 1, 1,
			0, 0, 0, 0, 1, 0, 1, 1,
			0, 0, 0, 0, 0, 1, 1, 1,
			0, 0, 0, 0, 0, 0, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 1};
  return test("enonce", Matrice(graphe, 8, 8), Matrice(fermeture, 8, 8));
}

bool testNParNFermetureComplete(unsigned int n) {
  assert(estUnePuissanceDeDeux(n));
  Matrice graphe(n, n);
  graphe.at(0, 0) = 1;
  for (unsigned int i = 1; i < n; i++) {
    graphe.at(i, i) = 1;
    graphe.at(i - 1, i) = 1;
  }

  Matrice fermeture(n, n);
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = i; j < n; j++) {
      fermeture.at(i, j) = 1;
    }
  }

  std::ostringstream string_stream;
  string_stream << "Test fermeture complete " << n << " x " << n << std::endl;
  return test(string_stream.str(), graphe, fermeture);
}

bool testNParN(unsigned int n) {
  assert(n >= 2);
  assert(estUnePuissanceDeDeux(n));
  Matrice graphe(n, n);
  graphe.at(0, 0) = 1;
  graphe.at(1, 1) = 1;
  for (unsigned int i = 2; i < n; i++) {
    graphe.at(i, i) = 1;
    graphe.at(i - 2, i) = 1;
  }

  Matrice fermeture(n, n);
  for (unsigned int i = 0; i < n; i++) {
    fermeture.at(i, i) = 1;
    for (unsigned int j = i + 1; j < n; j++) {
      fermeture.at(i, j) = (1 ^ (i + j)) & 1; // 8-)
    }
  }
  
  std::ostringstream string_stream;
  string_stream << "Test " << n << " x " << n << std::endl;
  return test(string_stream.str(), graphe, fermeture);
}

int main() {
  // Les tests suivant pourront etre modifies lors de la correction et d'autres tests pourront s'ajouter.
  testSimple();
  testQuatreParQuatre();
  testEnonce();
  testNParNFermetureComplete(1 << 4);
  testNParN(1 << 4);
}
