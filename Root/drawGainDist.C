// drawPdperfGainDist.C
//
// David Adams
// November 2019
//
// Fig. 3 in pdperf52
//
// scal - calib name: tool areaGain_scal is used
// ssel - Blank shows both good in green and bad in red
// ymax - 0 is autoscale
// ng, gmin, gmax - Defaults in calplots if ng is zero
// slab - Plot label: "" for no label, pdsp for PDSP standard
void drawGainDist(string scal, string ssel ="", double ymax =0.0,
                  string slab = "",
                  unsigned int ng =0, double gmin =0.0, double gmax =0.0) {
  if ( scal.size() == 0 ) {
    cout << "Usage: root> drawGainDist(CAL)" << endl;
    cout << "  e.g. CAL = \"calib20191203\"" << endl;
    return;
  }
  string sttl = "areaGain_" + scal;
  TPadManipulator* pp = calplots(sttl, true, false, "", ssel, ng, gmin, gmax);
  if ( pp == nullptr ) return;
  //pp->print("tmp.png");
  // Decorate
  if ( slab.size() ) {
    if ( slab == "pdsp" ) slab = "#bf{ProtoDUNE-SP}";
    TLatex* ptxt = new TLatex(0.16, 0.84, slab.c_str());
    ptxt->SetNDC();
    ptxt->SetTextFont(42);
    ptxt->SetTextSize(0.04);
    pp->add(ptxt);
  }
  pp->hist()->GetXaxis()->CenterTitle();
  pp->centerAxisTitles();
  pp->setCanvasSize(1400, 1000);
  if ( ymax > 0.0 ) pp->setRangeY(0, ymax);
  // Print
  //string ofnam = "gaindist.{pdf,png,tpad}";
  string ofnam = "gaindist_" + scal;
  if ( ssel.size() ) ofnam += "-" + ssel;
  ofnam += ".{png,tpad}";
  cout << "Printing " << ofnam << endl;
  //pp->setCanvasSize(1400, 1000);
  pp->print(ofnam);
}
