---------------------------------------------------------------------------------------------------------------
Instructions :
---------------------------------------------------------------------------------------------------------------

			***Modifier la géométrie : ***
Editer le fichier construction.cc de la manière suivante :
	dans la méthode Construct :
		MonScan *scanner = MonScan ScanGE(); -> instancier la classe voulue
		scanner->Construct(logicWorld,LYSO_GE,worldMat); -> mettre les bons arguments
		
---------------------------------------------------------------------------------------------------------------
		
			***Créer une nouvelle géométrie : ***
Utiliser la classe MetaDetector : hériter de cette classe et redéfinir les fonctions virtuelles
La méthode construct sera appelée dans construction.cc et pourra bénéficier de ses matériaux : ne pas définir les matériaux dans la classe du nouveau détecteur.
Pas de contraintes sur le constructeur.
Il faut impérativement utiliser SetScoringVolume sur le volume logique adéquat. Cela pour mettre à jour la variable héritée. Elle sera ensuite passée aux méthodes idoines.
Il faudra aussi ajouter la méthode d'Olga à un moment. (cf ScanGE.cc)

---------------------------------------------------------------------------------------------------------------

			***Modifier la source :***
Seules deux options dans generator.cc : mettre StraightToX à false ou à true.
à false, on a une source de backToBacks dans 4pi
à true, idem mais uniquement sur l'axe des x

---------------------------------------------------------------------------------------------------------------

			***Créer une nouvelle source : ***
Pas de métaSource, mais on peut s'inspirer de la classe backToBack, avec initialisation des attributs privés dans le constructeur,
une méthode Prepare qui se place dans le constructeur de MyPrimarygenerator
et une méthode Shoot dans la méthode generatePrimaries.
La classe peut-être instanciée dans le fichier header generator.hh

---------------------------------------------------------------------------------------------------------------

			***Ajouter un nouveau champ au NTuple "hits" :***
Deux manières :
+"propre" : 
	1. ajouter un attribut privé dans myHit.hh
	2. ajouter une méthode Get et une méthode Set pour cet attribut
	3. modifier fillHitInfo (dans le .cc) pour pouvoir mettre le hit à jour avec ce nouvel attribut
	4. modifier FillNTuple et ajouter une colonne pour cet attribut
	5. dans run.cc, ajouter une une colonne pour cet attribut
	6. dans detector.cc, assigner la valeur au hit et compléter fillHitInfo avec
	7. tester
+"rapide" :
	1. dans run.cc, ajouter une une colonne pour cet attribut
	2. dans detector.cc, assigner la valeur à une variable
	3. ajouter des paramètres dans la méthode FillNTuple
		+ un char* avec la liste des types des nouveaux attributs
		   d pour double, s pour string et i pour int
		+ l'ID du NTuple "hits"
		+ la liste des attributs dans l'ordre des types donnés
		* cf exemple dans myHit::FillNTuple
	4. tester

---------------------------------------------------------------------------------------------------------------

			***Reconstruire une image avec Castor : ***
1. Créer une LUT: 
	castor-G4PetScannerLut -alias GE_G4 -optf G4toCastorOptFile.txt
2. Convertir un fichier root dans le format de castor:
	castor-G4datafileConversion -il test0.root -o test -s GE_G4 -optf G4toCastorOptFile.txt
3. Reconstruire (castor standard):
	castor-recon -df test_df.Cdh -fout img_test -it 4:28 -dim 256,256,89 -fov 300,300,247.42 -opti MLEM 	
---------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------
