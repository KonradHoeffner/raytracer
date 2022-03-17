module;

#include <string>

export module Lichtquelle;

import Vector3d;
import Farbe;

export class Lichtquelle {
								public:
								Vector3d position;
  Farbe farbe;

Lichtquelle() {
  position.set(0, 10, 0);
  farbe.set(1, 1, 1);
}

Lichtquelle(Vector3d position, Farbe farbe) {
  this->position = position;
  this->farbe = farbe;
}

//std::string toString() { return "Lichtquelle - Position: " + position.toString() + " Farbe: " + farbe.toString(); }

};
