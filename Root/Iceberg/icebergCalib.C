// icbergCalib.C
//
// David Adams
// May 2020
//
// Root script to generate calibration fcl files and
// related plots for Iceberg.
//
// Arguments:
//      dst - Dataset name.
//   fitopt - fitting option
//      crn - Channel range, e.g. apau, apav, apaz1 or apaz2
//
// Input channel summary files are taken from data/dst/crn
// Output is written to calibrations/dst-fitopt

int icebergCalib(string dst, string fitopt, string crn) {
  string myname = "icebergCalib: ";
  if ( fitopt == "v1" ) {
    doCalib(dst, fitopt, crn,  1, 7, 3.5,  0.0,  0.0, 0.0);
  } else if ( fitopt == "v2" ) {
    doCalib(dst, fitopt, crn,  2, 7, 3.5,  0.0,  0.0, 0.0);
  } else if ( fitopt == "v3" ) {
    doCalib(dst, fitopt, crn,  3, 7, 3.5,  0.0,  0.0, 0.0);
  } else if ( fitopt == "v4" ) {
    doCalib(dst, fitopt, crn,  4, 7, 3.5,  0.0,  0.0, 0.0);
  } else if ( fitopt == "v5" ) {
    doCalib(dst, fitopt, crn,  1, 7, 3.5, 50.0,  0.0, 0.0);
  } else if ( fitopt == "v6" ) {
    doCalib(dst, fitopt, crn,  1, 7, 3.5,  0.0, 50.0, 0.0);
  } else if ( fitopt == "v7" ) {
    doCalib(dst, fitopt, crn, -4, 7, 3.5,  0.0, 50.0, 0.0);
  } else if ( fitopt == "v8" ) {
    doCalib(dst, fitopt, crn, -4, 7, 3.5,  1.0, 50.0, 0.0);
  } else if ( fitopt == "v9" ) {
    doCalib(dst, fitopt, crn, -4, 7, 3.5,  1.0, 50.0, 1.0);
  } else {
    cout << myname << "Invalid fitting option " << fitopt << endl;
    return 1;
  }
  return 0;
}
