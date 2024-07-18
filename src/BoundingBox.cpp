#include "BoundingBox.hpp" 

// Konstruktor der BoundingBox-Klasse, der Koordinaten für zwei Eckpunkte annimmt.
BoundingBox::BoundingBox(int x1, int y1, int x2, int y2)
    : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2) {}  // Initialisiert die Mitgliedsvariablen mit den übergebenen Werten.

// Getter-Methode für die X-Koordinate des ersten Punktes (linke obere Ecke).
int BoundingBox::getX1() const { return m_x1; }  // Gibt den Wert von m_x1 zurück.

// Getter-Methode für die Y-Koordinate des ersten Punktes (linke obere Ecke).
int BoundingBox::getY1() const { return m_y1; }  // Gibt den Wert von m_y1 zurück.

// Getter-Methode für die X-Koordinate des zweiten Punktes (rechte untere Ecke).
int BoundingBox::getX2() const { return m_x2; }  // Gibt den Wert von m_x2 zurück.

// Getter-Methode für die Y-Koordinate des zweiten Punktes (rechte untere Ecke).
int BoundingBox::getY2() const { return m_y2; }  // Gibt den Wert von m_y2 zurück.
