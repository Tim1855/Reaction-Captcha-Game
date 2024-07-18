#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <iostream>

class BoundingBox {
public:
    // Konstruktor, der die Koordinaten der Bounding Box initialisiert
    BoundingBox(int x1, int y1, int x2, int y2); 

    // Getter-Methode für die X-Koordinate der linken oberen Ecke
    int getX1() const;

    // Getter-Methode für die Y-Koordinate der linken oberen Ecke
    int getY1() const;

    // Getter-Methode für die X-Koordinate der rechten unteren Ecke
    int getX2() const;

    // Getter-Methode für die Y-Koordinate der rechten unteren Ecke
    int getY2() const;

private:
    // Private Variablen zur Speicherung der Koordinaten der Bounding Box
    int m_x1, m_y1, m_x2, m_y2;
};

#endif // BOUNDINGBOX_HPP
