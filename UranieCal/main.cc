#include <cstdio>
#include <TFile.h>
#include "TDataServer.h"

using namespace URANIE::DataServer;

int main(int argc, char** argv)
{
  // TDataServer *tds1 = new TDataServer("myTDS","my title");
  printf("Hello world");
  TDataServer *tds1 = new TDataServer();

  return 0;
}
