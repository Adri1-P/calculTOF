#ifndef CM_DETECTOR_HH
#define CM_DETECTOR_HH

#include "MetaDetector.hh"

class CMdetector: public MetaDetector //classe de base pour éviter de modifier directement construction.cc à chaque fois.
//On peut mimer les messengers avec des Get/set d'attributs et en créeant une classe qui hérite de celle-ci.
{
public :
	CMdetector();
	~CMdetector();

	virtual void Construct(G4LogicalVolume*logicWorld, G4Material* PbW04_Black,G4Material* PbW04_Y,G4Material* Bialkali_Bleu);

	G4LogicalVolume ** getTheScoringVolumes() {return allScoringVolumes;}




private :
G4LogicalVolume *MD_scoringVolume;
G4LogicalVolume *allScoringVolumes[3];


};

#endif
