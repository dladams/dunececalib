// drawPdperfGainDist.C
//
// David Adams
// November 2019
//
// Fig. 3 in pdperf52

void drawGainDist(string scal, string ssel ="", double ymax =0.0) {
  if ( scal.size() == 0 ) {
    cout << "Usage: root> drawGainDist(CAL)" << endl;
    cout << "  e.g. CAL = \"calib20191203\"" << endl;
    return;
  }
  string slab = "areaGain_" + scal;
  TPadManipulator* pp = calplots(slab, true, false, "", ssel);
  if ( pp == nullptr ) return;
  //pp->print("tmp.png");
  // Decorate
  if ( scal.substr(0, 2) != "ib" ) {
    TLatex* ptxt = new TLatex(0.16, 0.84, "#bf{ProtoDUNE-SP}");
    ptxt->SetNDC();
    ptxt->SetTextFont(42);
    ptxt->SetTextSize(0.04);
    pp->add(ptxt);
  }
  pp->hist()->GetXaxis()->CenterTitle();
  pp->centerAxisTitles();
  pp->setCanvasSize(1400, 1000);
  if ( ymax > 0.0 ) pp->SetRangeY(0, ymax);
  // Print
  //string ofnam = "gaindist.{pdf,png,tpad}";
  string ofnam = "gaindist_" + scal;
  if ( ssel.size() ) ofnam += "-" + ssel;
  ofnam += ".{png,tpad}";
  cout << "Printing " << ofnam << endl;
  //pp->setCanvasSize(1400, 1000);
  pp->print(ofnam);
}
