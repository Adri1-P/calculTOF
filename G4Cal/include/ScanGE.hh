#ifndef SCAN_GE_HH
#define SCAN_GE_HH

#include "MetaDetector.hh"

class ScanGE : public MetaDetector //classe de base pour éviter de modifier directement construction.cc à chaque fois.
//On peut mimer les messengers avec des Get/set d'attributs et en créeant une classe qui hérite de celle-ci.
{
public :
	ScanGE();
	~ScanGE();

	virtual void Construct(G4LogicalVolume*logicWorld,G4Material* LYSO_GE, G4Material* worldMat);

private :
G4LogicalVolume *MD_scoringVolume;

};

#endif
