// makeIcebergCalibData.C
//
// David Adams
// April 2020
//
// Define the default function that defines Iceberg datasets.

const AdcCalibData* makeAdcCalibData(string samName, string crNameIn, bool checkFile) {
  using Name = std::string;
  using Index = unsigned int;
  using IndexVector = vector<Index>;
  Name myname = "makeAdcCalibData: ";
  Name crName = crNameIn;
  const AdcCalibData* pcad = AdcCalibData::get(samName, crNameIn);
  if ( pcad != nullptr ) return pcad;
  using RunMap = std::map<int, IndexVector>;   // Runs indexed by pulser gain
  RunMap runMap;
  string basedir = "data";
  bool skipMissingFiles = false;
  Name crNameDefault = "apa1z";
  StringManipulator sman(samName, false);
  vector<string> fields = sman.split("-");
  if ( fields.size() > 2 ) {
    cout << "Invalid sample name: " << samName << endl;
    return nullptr;
  }
  string dstName = fields[0];
  Name dirName = dstName;
  vector<string> subdsts;
  if ( dstName == "ib3_b900" ) {
    subdsts.push_back("ib20200303");
    subdsts.push_back("ib20200306");
  | else if ( dstName == "ib4" ) {
    subdsts.push_back("ib20200721off");
  } else {
    subdsts.push_back(dstName);
  }
  for ( string subName : subdsts ) {
    // 14 mV/fC, 2.0 us, 900 mV, 500 pA
    if ( subName == "ib20200303" ) {
      runMap[ 1].push_back(4484);
      runMap[ 2].push_back(4485);
      runMap[ 3].push_back(4486);
      runMap[ 4].push_back(4487);
      runMap[ 5].push_back(4488);
      runMap[ 6].push_back(4489);
      runMap[ 7].push_back(4490);
      runMap[ 8].push_back(4491);
      runMap[ 9].push_back(4492);
      runMap[10].push_back(4493);
      runMap[11].push_back(4494);
      runMap[12].push_back(4495);
    }
    // 14 mV/fC, 2.0 us, 900 mV, 500 pA
    if ( subName == "ib20200306" ) {
      runMap[ 1].push_back(4679);
      runMap[ 2].push_back(4680);
      runMap[ 3].push_back(4681);
      runMap[ 4].push_back(4682);
      runMap[ 5].push_back(4683);
      runMap[ 6].push_back(4700);
      runMap[ 7].push_back(4685);
      runMap[ 8].push_back(4686);
      runMap[ 9].push_back(4701);
      runMap[10].push_back(4688);
      runMap[12].push_back(4690);
    }
    // 14 mV/fC, 2.0 us, 200 mV, 500 pA
    if ( subName == "ib20200312" ) {
      runMap[ 1].push_back(5245);
      runMap[ 2].push_back(5246);
      runMap[ 3].push_back(5247);
      runMap[ 4].push_back(5248);
      runMap[ 5].push_back(5249);
      runMap[ 6].push_back(5250);
      runMap[ 7].push_back(5251);
      runMap[ 8].push_back(5252);
      runMap[ 9].push_back(5253);
      runMap[10].push_back(5254);
      runMap[11].push_back(5255);
      runMap[12].push_back(5256);
    }
    if ( subName == "ib20200721off" ) {
      //runMap[ 0].push_back(5853);
      runMap[ 1].push_back(5874);
      runMap[ 2].push_back(5855);
      runMap[ 3].push_back(5856);
      runMap[ 4].push_back(5875);
      runMap[ 5].push_back(5858);
      runMap[ 6].push_back(5859);
      runMap[ 7].push_back(5860);
      runMap[ 8].push_back(5861);
      runMap[ 9].push_back(5876);
      runMap[10].push_back(5863);
      runMap[11].push_back(5864);
      runMap[12].push_back(5865);
      runMap[13].push_back(5866);
      runMap[14].push_back(5867);
      runMap[15].push_back(5877);
      runMap[16].push_back(5879);
      runMap[17].push_back(5870);
      runMap[18].push_back(5871);
      runMap[19].push_back(5872);
      runMap[20].push_back(5873);
    }
  }
  if ( runMap.size() == 0 ) {
    cout << myname << "Dataset not found: " << dstName << endl;
    return pcad;
  }
  if ( crName == "" || crName == "." ) crName = crNameDefault;
  AdcCalibData* pcadMut = AdcCalibData::create(dstName, crName);
  pcad = pcadMut;
  if ( pcad == nullptr ) {
    cout << myname << "Unable to create calib data: " << samName << " " << crName << endl;
    return pcad;
  }
  for ( RunMap::value_type arun : runMap ) {
    int ia = arun.first;
    for ( unsigned int run : arun.second ) {
      string srun = to_string(run);
      while ( srun.size() < 6 ) srun = "0" + srun;
      string fnamBase = basedir + "/" + dirName + "/" + crName + "/roicha" + srun;
      for ( string ssgn : {"pos", "neg"} ) {
        int isign = ssgn == "pos" ? 1 : -1;
        string fnam = fnamBase + ssgn + ".root";
        bool addFile = true;
        if ( checkFile ) {
          bool fileExists = ! gSystem->AccessPathName(fnam.c_str());
          addFile = fileExists;
        }
        if ( addFile ) pcadMut->add(isign*ia, run, fnam);
        else if ( skipMissingFiles ) cout << myname << "Skipping missing file: " << fnam <<endl;
        else {
          cout << myname << "Unable to find " << fnam << endl;
          return nullptr;
        }
      }
    }
  }
  pcad->print();
  return pcad;
}
