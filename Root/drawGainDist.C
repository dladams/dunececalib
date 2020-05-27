// drawPdperfGainDist.C
//
// David Adams
// November 2019
//
// Fig. 3 in pdperf52

void drawGainDist(string scal ="") {
  if ( scal.size() == 0 ) {
    cout << "Usage: root> drawGainDist(CAL)" << endl;
    cout << "  e.g. CAL = \"calib201912_nov19extv4\"" << endl;
    return;
  }
  string slab = "areaGain_" + scal;
  TPadManipulator* pp = calplots(slab, true, false, "");
  if ( pp == nullptr ) return;
  //pp->print("tmp.png");
  // Decorate
  TLatex* ptxt = new TLatex(0.16, 0.84, "#bf{ProtoDUNE-SP}");
  ptxt->SetNDC();
  ptxt->SetTextFont(42);
  ptxt->SetTextSize(0.04);
  pp->hist()->GetXaxis()->CenterTitle();
  pp->add(ptxt);
  pp->centerAxisTitles();
  // Print
  //string ofnam = "gaindist.{pdf,png,tpad}";
  string ofnam = "gaindist_" + scal + ".{png,tpad}";
  cout << "Printing " << ofnam << endl;
  //pp->setCanvasSize(1400, 1000);
  pp->print(ofnam);
}
