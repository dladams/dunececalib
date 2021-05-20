// icebergCalib.C
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

int icebergCalib(string dst, string dstver, string crn) {
  string myname = "myCalib: ";
  if ( dstver == "v1" ) {
    doCalib(dst, dstver, crn,  1, 7, 3.5,  0.0,  0.0, 0.0);
  } else if ( dstver == "v2" ) {
    doCalib(dst, dstver, crn,  2, 7, 3.5,  0.0,  0.0, 0.0);
  } else if ( dstver == "v3" ) {
    doCalib(dst, dstver, crn,  3, 7, 3.5,  0.0,  0.0, 0.0);
  } else if ( dstver == "v4" ) {
    doCalib(dst, dstver, crn,  4, 7, 3.5,  0.0,  0.0, 0.0);
  } else if ( dstver == "v5" ) {
    doCalib(dst, dstver, crn,  1, 7, 3.5, 50.0,  0.0, 0.0);
  } else if ( dstver == "v6" ) {
    doCalib(dst, dstver, crn,  1, 7, 3.5,  0.0, 50.0, 0.0);
  } else if ( dstver == "v7" ) {
    doCalib(dst, dstver, crn, -4, 7, 3.5,  0.0, 50.0, 0.0);
  } else if ( dstver == "v8" ) {
    doCalib(dst, dstver, crn, -4, 7, 3.5,  1.0, 50.0, 0.0);
  } else if ( dstver == "v9" ) {
    doCalib(dst, dstver, crn, -4, 7, 3.5,  1.0, 50.0, 1.0);
  } else if ( dstver == "v10" ) {
    doCalib(dst, dstver, crn,  -7, 7, 0.0,  0.0,  0.0, 0.0);
  } else {
    cout << myname << "Invalid dataset version " << dstver << endl;
    return 1;
  }
  return 0;
}
