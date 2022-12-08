using namespace URANIE::DataServer;
using namespace URANIE::Launcher;
void tests(){

// cout << endl << "====================================" << endl;
// cout << "Example 1: load myData.dat." << endl;
// TDataServer *tds1 = new TDataServer("myTDS","my title");
// tds1->fileDataRead( "myData.dat" );
// cout << "Number of elements = " << tds1->getNPatterns() << endl;
// cout << "Number of attributes = " << tds1->getNAttributes() << endl;
//
// cout << "Display contents:" << endl;
// tds1->scan("*");
// cout << "Display the list of attributes:" << endl;
// tds1->getListOfAttributes()->ls();
// cout << "Draw y versus x." << endl;
//
// TCanvas *c_2D = new TCanvas("2DCanvas","2D",1);
// tds1->draw("x1:x2");
// c_2D->Draw();
TDataServer * tds = new TDataServer();

// TCode *G4Code = new TCode(tds, "/biomaps/physique/apaillet/calculTOF/G4Cal/build/sim -n 1");


// TLauncher *G4Launcher = new TLauncher(tds,G4Code);
// // G4Launcher->setWorkingDirectory("/biomaps/physique/apaillet/calculTOF_outputs/G4Outputs/UranieTests")
// G4Launcher->run();

const char* path = "../../calculTOF_outputs/G4Outputs/test.root";

tds->ntupleDataRead(path,"Hits");
// tds->scan("*");
tds->getListOfAttributes()->ls();

// TCanvas *c1D = new TCanvas("1D","at
}
