#ifndef ENTIER
#define ENTIER

#include <ostream>

class Entier {
private:
  int m_valeur;

  static unsigned int m_nombre_multiplications;
  static unsigned int m_nombre_resets;

  friend std::ostream& operator<<(std::ostream& os, const Entier& entier);
public:
  Entier();			// Initialise un entier nul
  Entier(int valeur);
  Entier(const Entier& entier);

  Entier operator*(const Entier& operande) const;
  Entier operator+(const Entier& operande) const;
  Entier operator-(const Entier& operande) const;
  Entier operator-() const;
  Entier operator/(const Entier& operande) const;
  bool operator==(const Entier& operande) const;
  bool operator!=(const Entier& operande) const;
  Entier& operator+=(const Entier& operande);
  Entier& operator-=(const Entier& operande);
  Entier& operator*=(const Entier& operande);
  Entier& operator/=(const Entier& operande);

  static void resetCompteur();
  static unsigned int nombreMultiplications();
  static unsigned int nombreResets();
};

std::ostream& operator<<(std::ostream& os, const Entier& entier);

#endif
