// doCalib.C
//
// David Adams
// May 2020
//
// Script to carry out calibrations with AdcCalibGraphs and write results
// and plots to ./calibrations/dstName-fitname/crName

AdcCalibGraphs* doCalib(string dstName, string fitName, string crName,
             int dacmin =1, int dacmax =7,
             float varyOffset =0.0, float varyPedestal =0.0,
             float varyShift =0.0, float varyNegScale =0.0,
             bool doShaping =true, bool doAreaGain =true, bool doHeightGain =true) {
  string myname = "doCalib: ";
  bool usePulser = false;
  bool showExtraDst = true;
  float xfmin = dacmin - 0.5;
  float xfmax = dacmax + 0.5;
  AdcCalibGraphs* pcg = calib(dstName, crName, usePulser, xfmin, xfmax, showExtraDst,
                              varyOffset, varyPedestal, varyShift, varyNegScale);
  if ( pcg == nullptr ) return pcg;
  AdcCalibGraphs& cg = *pcg;
  cout << myname << "Printing" << endl;
  cg.makeMultiChannelPads("Area", 4, 4, 1400, 1000);
  cg.makeMultiChannelPads("fresArea", 4, 4, 1400, 1000);
  cg.makeMultiChannelPads("Height", 4, 4, 1400, 1000);
  cg.makeMultiChannelPads("fresHeight", 4, 4, 1400, 1000);
  cg.makeMultiChannelPads("Shaping", 4, 4, 1400, 1000);
  //cg.printMultiChannelPads();
  string outdir = "calibrations/" + dstName;
  if ( fitName.size() ) outdir += "-" + fitName;
  string fcldir = outdir + "/fcl/";
  string crdir = outdir + "/" + crName + "/";
  if ( doShaping ) {
    string com = "mkdir -p " + fcldir;
    if ( gSystem->Exec(com.c_str()) ) {
      cout << myname << "Unable to create directory." << endl;
    } else {
      string fclfile = fcldir + "shapingTime_" + crName + ".fcl";
      cout << myname << "Writing shaping calibration " << fclfile << endl;
      cg.writeFcl("Shaping", fclfile.c_str());
    }
  }
  if ( doAreaGain ) {
    string com = "mkdir -p " + fcldir;
    if ( gSystem->Exec(com.c_str()) ) {
      cout << myname << "Unable to create directory." << endl;
    } else {
      string fclfile = fcldir + "areaGain_" + crName + ".fcl";
      cout << myname << "Writing area gain calibration " << fclfile << endl;
      cg.writeFcl("AreaGain", fclfile.c_str());
    }
  }
  if ( doHeightGain ) {
    string com = "mkdir -p " + fcldir;
    if ( gSystem->Exec(com.c_str()) ) {
      cout << myname << "Unable to create directory." << endl;
    } else {
      string fclfile = fcldir + "heightGain_" + crName + ".fcl";
      cout << myname << "Writing height gain calibration " << fclfile << endl;
      cg.writeFcl("HeightGain", fclfile.c_str());
    }
  }
  for ( string prefix : {"Area", "fresArea", "Height", "fresHeight", "Shaping"} ) {
    string dir = crdir + "/" + prefix + "/";
    string com = "mkdir -p " + dir;
    if ( gSystem->Exec(com.c_str()) ) {
      cout << myname << "Unable to create directory." << endl;
    } else {
      cg.printMultiChannelPads(prefix, dir);
      cout << myname << "Writing " + prefix + " plots" << endl;
    }
  }
  string chsumName;
  string sumdir = outdir + "/chsum/";
  string com = "mkdir -p " + sumdir;
  string dir;
  if ( gSystem->Exec(com.c_str()) ) {
    cout << myname << "Unable to create directory." << endl;
  } else {
    cout << myname << "Writing summary plots." << endl;
    dir = sumdir + "area_slope/";
    com = "mkdir -p " + dir;
    if ( gSystem->Exec(com.c_str()) ) {
      cout << myname << "Unable to create directory." << endl;
    } else {
      chsumName = dir + "chsum_area_slope_" + crName + ".{png,tpad}";
      cg.drawChannelSummaryPadBare("Area", "Slope", "", 0, 1200)->print(chsumName);
    }
    dir = sumdir + "area_csdof/";
    com = "mkdir -p " + dir;
    if ( gSystem->Exec(com.c_str()) ) {
      cout << myname << "Unable to create directory." << endl;
    } else {
      chsumName = dir + "chsum_area_csdof_" + crName + ".{png,tpad}";
      cg.drawChannelSummaryPadBare("Area", "csdof", "", 0, 1500)->print(chsumName);
    }
    dir = sumdir + "height_slope/";
    com = "mkdir -p " + dir;
    if ( gSystem->Exec(com.c_str()) ) {
      cout << myname << "Unable to create directory." << endl;
    } else {
      chsumName = dir + "chsum_height_slope_" + crName + ".{png,tpad}";
      cg.drawChannelSummaryPadBare("Height", "Slope", "", 0, 215)->print(chsumName);
    }
    dir = sumdir + "shaping_mean/";
    com = "mkdir -p " + dir;
    if ( gSystem->Exec(com.c_str()) ) {
      cout << myname << "Unable to create directory." << endl;
    } else {
      chsumName = dir + "chsum_shaping_mean_" + crName + ".{png,tpad}";
      cg.drawChannelSummaryPadBare("Shaping", "Pedestal", "shapingFitPlus", 4.0, 4.8)->print(chsumName);
    }
  }
  return pcg;
}

