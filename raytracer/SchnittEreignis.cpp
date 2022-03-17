export module SchnittEreignis;

import Vector3d;
import Dreieck;

export class SchnittEreignis
{
public:
  Vector3d schnittPunkt;
  Vector3d normale;
  double distanz;
  Dreieck *pDreieck;

  SchnittEreignis() {}

  SchnittEreignis(Vector3d schnittPunkt, Vector3d normale, double distanz, Dreieck *pDreieck) {
    this->schnittPunkt = schnittPunkt;
    this->normale = normale;
    this->distanz = distanz;
    this->pDreieck = pDreieck;
  }
};
