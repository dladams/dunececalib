// calplots.C
//
// David Adams
// February 2019
//
// Plots gain calibration.

TPadManipulator* calplots(string calname,
                          bool doDist =true, bool doDraw =true,
                          string a_fnamout ="%CAL%.{tpad,png}") {
  string myname = "calplots: ";
  using Index = unsigned int;
  DuneToolManager* pdtm = DuneToolManager::instance();
  DuneToolManager* ptm = DuneToolManager::instance();
  const IndexMapTool* pchs = ptm->getShared<IndexMapTool>("channelStatus");
  if ( pchs == nullptr ) {
    cout << myname << "Calibration not found: " << calname << endl;
    return nullptr;
  }
  FloatArrayTool* pcal = pdtm->getShared<FloatArrayTool>(calname);
  if ( pcal == nullptr ) {
    cout << myname << "Calibration not found: " << calname << endl;
    return nullptr;
  }
  Index ncha = pcal->size();
  cout << "Calibration label: " << pcal->label() << endl;
  cout << "Calibration channel count: " << ncha << endl;
  if ( doDist ) {
    float gmin = 0.015;
    float gmax = 0.035;
    Index ng = 80;
    string sttl = "Gains for " + calname + "; Gain [ke/(ADC count)/tick]; # channels";
    TH1* phgAll = new TH1F("hgainsAll", sttl.c_str(), ng, gmin, gmax);
    TH1* phgGoo = new TH1F("hgainsGoo", sttl.c_str(), ng, gmin, gmax);
    TH1* phgBad = new TH1F("hgainsBad", sttl.c_str(), ng, gmin, gmax);
    vector<TH1*> hists = { phgAll, phgGoo, phgBad};
    for ( TH1* ph : hists ) {
      ph->SetLineWidth(2);
      ph->SetStats(0);
      ph->SetTitle(sttl.c_str());
    }
    phgBad->SetLineColor(2);
    phgBad->SetLineWidth(1);
    int nbad = 0;
    int ngoo = 0;
    for ( Index icha=0; icha<ncha; ++icha ) {
      int chs = pchs->get(icha);
      bool isBad = chs == 1 || chs == 3;
      float gain = pcal->value(icha);
      bool isLo = gain < gmin;
      bool isHi = gain > gmax;
      if ( isLo ) {
        if ( ! isBad ) cout << myname << "Lo gain: " << icha << ": " << gain << endl;
        gain = gmin + 0.00001;
      }
      if ( isHi ) {
        if ( ! isBad ) cout << myname << "Hi gain: " << icha << ": " << gain << endl;
        gain = gmax - 0.00001;
      }
      phgAll->Fill(gain);
      if ( isBad ) ++nbad;
      else ++ngoo;
      if ( isBad ) phgBad->Fill(gain);
      else phgGoo->Fill(gain);
    }
    cout << myname << "  # bad: " << nbad << endl;
    cout << myname << "  # good: " << ngoo << endl;
    // Create labels.
    vector<string> labs;
    ostringstream sslab;
    sslab.str("");
    sslab << "Good count: " << phgGoo->GetEntries();
    labs.push_back(sslab.str());
    sslab.str("");
    sslab << "Bad count: " << phgBad->GetEntries();
    labs.push_back(sslab.str());
    sslab.str("");
    sslab.setf(ios::fixed);
    sslab.precision(5);
    sslab << "Good mean: " << phgGoo->GetMean();
    labs.push_back(sslab.str());
    sslab.str("");
    sslab.precision(3);
    float rmsf = phgGoo->GetRMS()/phgGoo->GetMean();
    sslab << "Good RMS/mean: " << rmsf;
    labs.push_back(sslab.str());
    // Draw.
    TPadManipulator* pman = new TPadManipulator;
    pman->add(phgGoo);
    pman->add(phgBad, "same");
    pman->addAxis();
    float xlab = 0.70;
    float ylab = 0.85;
    float dylab = 0.045;
    for ( string lab : labs ) {
      TLatex* ptxt = new TLatex(xlab, ylab, lab.c_str());
      ptxt->SetNDC();
      ptxt->SetTextFont(42);
      ptxt->SetTextSize(0.80*dylab);
      pman->add(ptxt);
      ylab -= dylab;
    }
    if ( doDraw ) pman->draw();
    if ( a_fnamout.size() ) {
      string fnamout = a_fnamout;
      StringManipulator sman(fnamout, false);
      sman.replace("%CAL%", calname);
      pman->print(fnamout);
    }
    return pman;
  }
  return nullptr;
}   
