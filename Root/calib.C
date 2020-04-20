// calib.C

#include "ExtraDataset.h"
#ifdef HAVE_EXTRA_DATASETS
#include "extraDatasets.h"
#endif

#include "dune/DuneCommon/cePulserToAdc.h"

//   varyOffset: 0 ==> fix at 0.0, otherwise use as starting value
//   varyPedestal: 0 ==> fix at 0.0, otherwise use as starting value
AdcCalibGraphs*
calib(string dstName ="", string crName ="", bool usePulser =false,
      double xfminIn =-101, double xfmaxIn =0.0,
      bool showExtraDsts =false,
      float varyOffset =0.0, float varyPedestal =0.0, float varyPedOff =0.0,
      int icha1In =-1, int nchaIn =-1) {
  using Name = std::string;
  using Index = unsigned int;
  const Name myname = "calib: ";
  vector<ExtraDataset> extraDsts;
#ifdef HAVE_EXTRA_DATASETS
  if ( showExtraDsts ) {
    for ( const ExtraDataset& eds : extraDatasets(dstName) ) {
      if ( eds.name != dstName ) extraDsts.push_back(eds);
    }
  }
  cout << "Extra dataset count: " << extraDsts.size() << endl;
#endif
  const AdcCalibData* pcad = makeAdcCalibData(dstName, crName, true);
  if ( pcad == nullptr ) return nullptr;
  for ( ExtraDataset eds : extraDsts ) {
    const AdcCalibData* pcadext = makeAdcCalibData(eds.name, crName, true);
    if ( pcadext == nullptr ) {
      cout << "Unable to build extra dataset " << eds.name << endl;
      return nullptr;
    }
  }
  static AdcCalibGraphs* pcg = nullptr;
  delete pcg;
  pcg = new AdcCalibGraphs(dstName, crName);
  AdcCalibGraphs& cg = *pcg;
  double xfmin = xfminIn;
  double xfmax = xfmaxIn;
  if ( xfmin >= xfmax ) {
    xfmin = -4;
    xfmax = 7;
  }
  const IndexRangeTool* pcrt = DuneToolManager::instance()->getShared<IndexRangeTool>("channelRanges");
  IndexRange crRange = pcrt->get(crName);
  if ( ! crRange.isValid() ) {
    cout << myname << "Invalid channel range: " << crName << endl;
    return pcg;
  }
  Index icha1 = icha1In >= 0 ? icha1In : crRange.first();
  Index ncha  = nchaIn > 0   ? nchaIn  : crRange.size();
  string varName = "Height";
  varName = "Area";
  //varName = "Shaping";
  //varName = "ChiSquare";
  //varName = "CSNormDof";
  //TF1* pfit = offsetLinePedTF1(0, 900, 0, -6, 15);
  cout << myname << "Graphing" << endl;
  cg.setAllowMissingRuns(false);
  cg.setErrorScaling(2);
  cg.setChargeUnit("ke");
  if ( usePulser ) {
    double tol = 0.001;
    TF1* pFitPulser = cePulserToAdcTF1("adcpulser", tol);
    vector<string> fixpars;
    //fixpars.push_back("AdcScale");
    fixpars.push_back("Pedestal");
    if ( xfmin > -2 ) fixpars.push_back("NegScale");
    if ( xfmax < 32 ) fixpars.push_back("R5");
    if ( xfmax < 16 ) fixpars.push_back("R4");
    if ( xfmax <  8 ) fixpars.push_back("R3");
    if ( 1 ) {
      fixpars.push_back("R6");
      fixpars.push_back("R5");
      fixpars.push_back("R4");
      fixpars.push_back("R3");
      fixpars.push_back("R2");
      fixpars.push_back("R1");
      fixpars.push_back("R0");
    }
    fixpars.push_back("QVscale");
    vector<string> varpars;
    varpars.push_back("R0");
    varpars.push_back("R1");
    for ( string spar : fixpars ) {
      if ( find(varpars.begin(), varpars.end(), spar) != varpars.end() ) continue;
      int ipar = pFitPulser->GetParNumber(spar.c_str());
      if ( ipar < 0 ) continue;
      double val = pFitPulser->GetParameter(ipar);
      //if ( spar == "R3") val *=1.02;
      pFitPulser->FixParameter(ipar, val);
    }
    for ( string spar : varpars ) {
      int ipar = pFitPulser->GetParNumber(spar.c_str());
      if ( ipar < 0 ) continue;
      double val = pFitPulser->GetParameter(ipar);
      pFitPulser->SetParLimits(ipar, 0.9*val, 1.1*val);
    }
    cg.setFitFunction("Height", pFitPulser);
    cg.setFitFunction("Area", pFitPulser);
  } else {
    if ( varyPedestal == 0.0 ) {
      cg.fixHeightPedestal(0.0);
      cg.fixAreaPedestal(0.0);
    } else {
      cg.getFitFunction("Area", 0)->SetParameter(2, varyPedestal);
      cg.getFitFunction("Height", 0)->SetParameter(2, varyPedestal);
    }
    if ( varyPedOff == 0.0 ) {
      cg.fixHeightPedestalOffset(0.0);
      cg.fixAreaPedestalOffset(0.0);
    } else {
      cg.getFitFunction("Area", 0)->SetParameter(4, varyPedOff);
      cg.getFitFunction("Height", 0)->SetParameter(4, varyPedOff);
    }
    cg.fixHeightNegScale(1.0);
    if ( varyOffset == 0.0 ) {
      cg.fixHeightOffset(0.0);
      cg.fixAreaOffset(0.0);
      float omin = xfmin < 0.0 ? xfmin - 1.0 : 0.0;
      float omax = xfmax - 2.0;
      for ( Name vname : {"Area", "Height"} ) {
        TF1* pf = cg.getFitFunction(vname, 0);
        if ( pf == nullptr ) continue;
        int ipar = pf->GetParNumber(vname.c_str());
        if ( ipar >= 0 ) {
          pf->SetParLimits(ipar, omin, omax);
        }
      }
    } else {
      cg.getFitFunction("Area", 0)->SetParameter(0, varyOffset);
      cg.getFitFunction("Height", 0)->SetParameter(0, varyOffset);
    }
    //cg.fixAreaOffset(-0.02);
    cg.fixAreaNegScale(1.0);
    //cg.fixAreaNegScale(1.025);
  }
  int rstat = cg.makeGraphs(icha1, ncha);
  Index icol = 0;
  for ( ExtraDataset eds : extraDsts ) {
    cg.makeExtraGraphs(eds.name, icha1, ncha, eds.color, eds.marker);
  }
  bool doFit = true;
  bool doPads = false;
  bool doGainResiduals = false;  // False means only fuill residuals
  cg.doGainResiduals(doGainResiduals);
  if ( rstat ) {
    cout << myname << "ERROR: cg.makeGraphs returned " << rstat << endl;
  } else {
    if ( doFit ) {
      cout << myname << "Fitting" << endl;
      cg.fitGraphs(icha1, ncha, xfmin, xfmax);
      cg.resGraphs(icha1, ncha);
      if ( doPads ) {
        cout << myname << "Padding" << endl;
        cg.makeMultiChannelPads(varName, 4, 4);
        cg.makeMultiChannelPads("fres" + varName, 4, 4);
        if ( doGainResiduals ) {
          cg.makeMultiChannelPads("gres" + varName, 4, 4);
          cg.makeMultiChannelPads("calres" + varName, 4, 4);
        }
        pcg->drawChannelSummaryPad("Area", "csdof", "", 0, 1000);
      }
    }
#if 0
    cout << myname << "Printing" << endl;
    cg.printMultiChannelPads();
    string fclfile = crName + ".fcl";
    cout << myname << "Writing calibration " << fclfile << endl;
    cg.writeFcl(fclfile.c_str());
#endif
  }
  return pcg;
}
