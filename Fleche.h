#ifndef FLECHE_H
#define FLECHE_H

#include "object.h"
#include "Couleur.h"


class Fleche: public Object
{
public:
	Fleche();
	Fleche(double x, double y, double z,double size);
	virtual ~Fleche();
	void Draw();
	void SetForceVent(int ForceVent) {
		this->ForceVent = ForceVent;
	}
	void SetOrientationVent(int OrientationVent) {
		this->OrientationVent = OrientationVent;
	}
	void Update();

private:
	double* Couleur;
	int OrientationVent;
	int ForceVent;
};

#endif // FLECHE_H
