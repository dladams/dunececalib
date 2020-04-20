// makeIcebergCalibData.C
//
// David Adams
// April 2020
//
// Define the default function that defines Iceberg datasets.

const AdcCalibData* makeAdcCalibData(string dstName, string crNameIn, bool checkFile) {
  using Name = std::string;
  using Index = unsigned int;
  using IndexVector = vector<Index>;
  Name myname = "makeAdcCalibData: ";
  Name crName = crNameIn;
  const AdcCalibData* pcad = AdcCalibData::get(dstName, crNameIn);
  if ( pcad != nullptr ) return pcad;
  using RunMap = std::map<int, IndexVector>;   // Runs indexed by pulser gain
  RunMap runMap;
  Name dirName = dstName;
  string basedir = "data";
  bool skipMissingFiles = false;
  Name crNameDefault = "apa1z";
  if ( dstName.substr(0,10) == "ib20200303" ) {
    runMap[ 1] = {4481, 4484};
    runMap[ 2] = {4485};
    runMap[ 3] = {4486};
    runMap[ 4] = {4487};
    runMap[ 5] = {4488};
    runMap[ 6] = {4489};
    runMap[ 7] = {4490};
    runMap[ 8] = {4491};
    runMap[ 9] = {4492};
    runMap[10] = {4493};
    runMap[11] = {4494};
    runMap[12] = {4495};
  } else {
    cout << myname << "Dataset not found: " << dstName << endl;
    return pcad;
  }
  if ( crName == "" || crName == "." ) crName = crNameDefault;
  AdcCalibData* pcadMut = AdcCalibData::create(dstName, crName);
  pcad = pcadMut;
  if ( pcad == nullptr ) {
    cout << myname << "Unable to create calib data: " << dstName << " " << crName << endl;
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
