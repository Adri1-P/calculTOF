#include "action.hh"

//******************************************************************************
//******************************************************************************
MyActionInitialization::MyActionInitialization(): G4VUserActionInitialization(){}
MyActionInitialization::~MyActionInitialization(){}
//******************************************************************************

void MyActionInitialization::Build() const
{
	//je ne sais pas exactement à quoi elle sert
	//mais cette méthode fait partie de celles de base
	MyPrimaryGenerator *generator = new MyPrimaryGenerator();
	SetUserAction(generator);

	MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);

	MyEventAction *eventAction = new MyEventAction(runAction);
	SetUserAction(eventAction);

	MySteppingAction *steppingAction = new MySteppingAction(eventAction);
	SetUserAction(steppingAction);
}

//******************************************************************************

void MyActionInitialization::BuildForMaster() const
{
	//méthode utilisée pour le multithreading
	MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);
}
//******************************************************************************
//******************************************************************************
