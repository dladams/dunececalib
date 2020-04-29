AdcCalibGraphs* doCalib(string dstName, string crName,
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
  cg.makeMultiChannelPads("Height", 4, 4, 1400, 1000);
  cg.makeMultiChannelPads("fresArea", 4, 4, 1400, 1000);
  cg.makeMultiChannelPads("fresHeight", 4, 4, 1400, 1000);
  cg.makeMultiChannelPads("Shaping", 4, 4, 1400, 1000);
  cg.printMultiChannelPads();
  if ( doShaping ) {
    string fclfile = "shapingTime_" + crName + ".fcl";
    cout << "Writing shaping calibration " << fclfile << endl;
    cg.writeFcl("Shaping", fclfile.c_str());
  }
  if ( doAreaGain ) {
    string fclfile = "areaGain_" + crName + ".fcl";
    cout << "Writing area gain calibration " << fclfile << endl;
    cg.writeFcl("AreaGain", fclfile.c_str());
  }
  if ( doHeightGain ) {
    string fclfile = "heightGain_" + crName + ".fcl";
    cout << "Writing height gain calibration " << fclfile << endl;
    cg.writeFcl("HeightGain", fclfile.c_str());
  }
  string chsumName;
  chsumName = "chsum_area_slope_" + crName + ".{png,tpad}";
  cg.drawChannelSummaryPad("Area", "Slope", "", 0, 1200)->print(chsumName);
  chsumName = "chsum_area_csdof_" + crName + ".{png,tpad}";
  cg.drawChannelSummaryPad("Area", "csdof", "", 0, 1500)->print(chsumName);
  chsumName = "chsum_height_slope_" + crName + ".{png,tpad}";
  cg.drawChannelSummaryPad("Height", "Slope", "", 0, 215)->print(chsumName);
  chsumName = "chsum_shaping_mean_" + crName + ".{png,tpad}";
  cg.drawChannelSummaryPad("Shaping", "Pedestal", "shapingFitPlus", 4.0, 4.8)->print(chsumName);
  return pcg;
}

