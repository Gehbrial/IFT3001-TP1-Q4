#include "entier.hpp"

unsigned int Entier::m_nombre_multiplications = 0;
unsigned int Entier::m_nombre_resets = 0;

Entier::Entier()
  : m_valeur(0)
{
}

Entier::Entier(int valeur)
  : m_valeur(valeur)
{
}

Entier::Entier(const Entier& entier)
  : m_valeur(entier.m_valeur)
{
}

Entier Entier::operator*(const Entier& operande) const {
  Entier::m_nombre_multiplications++;
  return Entier(m_valeur * operande.m_valeur);
}

Entier Entier::operator+(const Entier& operande) const {
  return Entier(m_valeur + operande.m_valeur);
}

Entier Entier::operator-(const Entier& operande) const {
  return Entier(m_valeur - operande.m_valeur);
}

Entier Entier::operator-() const {
  return Entier(-m_valeur);
}

Entier Entier::operator/(const Entier& operande) const {
  return Entier(m_valeur / operande.m_valeur);
}

bool Entier::operator==(const Entier& operande) const {
  return m_valeur == operande.m_valeur;
}

bool Entier::operator!=(const Entier& operande) const {
  return m_valeur != operande.m_valeur;
}

Entier& Entier::operator+=(const Entier& operande) {
  m_valeur += operande.m_valeur;
  return *this;
}

Entier& Entier::operator-=(const Entier& operande) {
  m_valeur -= operande.m_valeur;
  return *this;
}

Entier& Entier::operator*=(const Entier& operande) {
  Entier::m_nombre_multiplications++;
  m_valeur *= operande.m_valeur;
  return *this;
}

Entier& Entier::operator/=(const Entier& operande) {
  m_valeur /= operande.m_valeur;
  return *this;
}

void Entier::resetCompteur() {
  m_nombre_multiplications = 0;
  m_nombre_resets++;
}

unsigned int Entier::nombreMultiplications() {
  return m_nombre_multiplications;
}

unsigned int Entier::nombreResets() {
  return m_nombre_resets;
}

std::ostream& operator<<(std::ostream& os, const Entier& entier) {
  return os << entier.m_valeur;
}
