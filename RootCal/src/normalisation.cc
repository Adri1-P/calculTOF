// //D'après les codes d'Olga
// // $ Programme to make .lut and .hscan files
// #include <cstring>
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <strstream>
// #define MAXLINESIZE 512
// #include <cmath>
// #include <vector>
//
// #include "normalisation.hh"
//
// using namespace std;
//
//
//
// void binTotxt()
// {
//   char* filename = "/volatile3/castor_v3.1.1/config/scanner/GE_G4.lut";
//   FILE*  ptr_data_binary;
//   ptr_data_binary=fopen(filename,"r");
//   if (! ptr_data_binary)
//     {
//       printf("Unable to open file!");
//     }
//
//   float n=-1;
//
//   while (! feof(ptr_data_binary))
//     {
//
//       fread(&n, sizeof(float), 1,  ptr_data_binary);
//
// 	   cout<< n <<endl;
//
//     }
//
//
//      fclose(ptr_data_binary);
// }
//
//
//
//
//  getCastorCrystalID_CylindricalPET(scanner_radius,
// 													//nb scanner elements
// 													 nb_rsectors,
// 													 nb_trans_mod,
// 													 nb_axial_mod,
// 													 nb_trans_submod,
// 													 nb_axial_submod,
// 													 nb_trans_crystal,
// 													 nb_axial_crystal,
// 													// Gaps between scanner elements
// 													 gap_trans_mod,
// 													 gap_axial_mod,
// 													 gap_trans_submod,
// 													 gap_axial_submod,
// 													 gap_trans_crystal,
// 													 gap_axial_crystal,
// 													// crystal dimensions (mm)
// 													 crystal_size_depth,
// 													 crystal_size_trans,
// 													 crystal_size_axial);)
//
//
//
// {
//   uint32_t nb_cry_cur = 0;
//   int nb_mod = nb_axial_mod*nb_trans_mod;
//   int nb_submod = nb_axial_submod*nb_trans_submod;
//   int nb_crystal = nb_trans_crystal*nb_axial_crystal;
//
//   nb_cry_in_layer = nb_rsectors
//                   * nb_mod
//                   * nb_submod
//                   * nb_crystal;
//
//   nb_rings = nb_axial_mod
//            * nb_axial_submod
//            * nb_axial_crystal;
//
// int number_crystals_in_ring = nb_cry_in_layer/nb_rings;
//   //début code Castor de castor-G4PetScannerLUT.cc
//   for (int j=0 ; j<nb_mod ; j++)
//           for (int k=0 ; k<nb_submod ; k++)
//             for (int l=0 ; l<nb_crystal ; l++)
//             {
//               // crystal indexation
//               int cryID = int(j/nb_trans_mod)*nb_axial_submod*nb_axial_crystal*number_crystals_in_ring // = nb indexed crystals in the rings covered by the previous (axial) modules
//                         + int(k/nb_trans_submod)*nb_axial_crystal*number_crystals_in_ring // = nb indexed crystals in the rings covered by the previous (axial) submodules
//                         + int(l/nb_trans_crystal)*number_crystals_in_ring // = nb indexed crystals in the rings covered by the previous (axial) crystals
//                         + rs*nb_trans_mod*nb_trans_submod*nb_trans_crystal // = nb indexed crystals in the previous rsectors
//                         + j/nb_axial_mod*nb_trans_submod*nb_trans_crystal // = nb indexed crystals in the previous modules
//                         + k/nb_axial_submod*nb_trans_crystal // = nb indexed crystals in the previous submodules
//                         + l%nb_trans_crystal // previous crystals in the submodule
//                         + nb_cry_cur; // = number of crystals already indexed if lyr>0
//
//             }
//       }
//
//       // Update nb of crystal for systems with (required if nb_layers>1)
//       // nb_cry_cur += nb_crystals_lyr[lyr];
//
//   //fin code Castor de castor-G4PetScannerLUT.cc
// }
