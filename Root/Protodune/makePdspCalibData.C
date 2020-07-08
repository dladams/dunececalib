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
  if ( dstName == "dec18int" ) {
    runMap[ 2] = {6025};
    runMap[ 3] = {6024};
    runMap[ 4] = {6023};
    runMap[ 5] = {6022};
    runMap[ 6] = {6020};
    runMap[ 7] = {6006};
    runMap[ 8] = {6005};
    runMap[10] = {6004};
    runMap[12] = {6003};
    runMap[15] = {6002};
    runMap[18] = {6001};
    runMap[21] = {6000};
    runMap[25] = {5999};
    runMap[30] = {5998};
    runMap[35] = {5997};
    runMap[40] = {5996};
    runMap[50] = {5995};
  } else if ( dstName == "dec18ext"   ||
              dstName == "dec18extv2" ||
              dstName == "dec18extv3" ||
              dstName == "dec18extv4" ||
              dstName == "dec18extv5" )  {
    if ( dstName == "dec18ext" ) {
      basedir = "/nashome/d/dladams/dev/dudev01/calib/data";
    } else {
      skipMissingFiles = true;
    }
    runMap[ 1] = {6068};
    runMap[ 2] = {6046};
    runMap[ 3] = {6045};
    runMap[ 4] = {6043};
    runMap[ 5] = {6042};
    runMap[ 6] = {6041};
    runMap[ 7] = {6040};
    runMap[ 8] = {6039};
    runMap[10] = {6038};
    runMap[12] = {6037};
    runMap[15] = {6036};
    runMap[18] = {6035};
    //runMap[21] = {6034};
    //runMap[25] = {6033};
    //runMap[30] = {6032};
  } else if ( dstName == "jan19extLed" ) {
    dirName = "jan19ext";
    runMap[ 3] = {6592};
    runMap[ 9] = {6591};
    runMap[10] = {6590};
    runMap[11] = {6589};
    runMap[13] = {6588};
    runMap[14] = {6587};
    runMap[16] = {6586};
    runMap[17] = {6585};
  } else if ( dstName == "jan19extNoLed" ) {
    dirName = "jan19ext";
    runMap[ 3] = {6593};
  } else if ( dstName == "jan19extNew" ) {
    dirName = "jan19ext";
    runMap[ 1] = {6604};
    runMap[ 2] = {6599, 6600};
    runMap[ 3] = {6601};
    runMap[ 4] = {6602};
    runMap[ 5] = {6603};
  } else if ( dstName == "jan19ext" ) {
    runMap[ 1] = {6604};
    runMap[ 2] = {6599, 6600};
    runMap[ 3] = {6592, 6593, 6601};
    runMap[ 4] = {6602};
    runMap[ 5] = {6603};
    runMap[ 9] = {6591};
    runMap[10] = {6590};
    runMap[11] = {6589};
    runMap[13] = {6588};
    runMap[14] = {6587};
    runMap[16] = {6586};
    runMap[17] = {6585};
  } else if ( dstName == "jan19g78int" ) {
    //runMap[ 1] = 6373;
    runMap[ 2] = {6349};
    runMap[ 3] = {6346};
    runMap[ 4] = {6344};
    runMap[ 5] = {6343};
    runMap[ 6] = {6342};
    runMap[ 7] = {6341};
    runMap[ 8] = {6340};
    runMap[10] = {6338};
    runMap[12] = {6337};
    runMap[15] = {6336};
    runMap[18] = {6335};
    runMap[21] = {6333};
    runMap[25] = {6319};
    runMap[30] = {6318};
    runMap[35] = {6317};
    runMap[40] = {6316};
    runMap[50] = {6315};
  } else if ( dstName == "feb19ext" ) {
    runMap[ 1] = {6676};
    runMap[ 2] = {6677};
    runMap[ 3] = {6678};
    runMap[ 4] = {6679};
    runMap[ 5] = {6680};
    runMap[ 6] = {6681};
    runMap[ 7] = {6682};
    runMap[ 8] = {6683};
    runMap[ 9] = {6684};
    runMap[10] = {6685};
    runMap[11] = {6686};
    runMap[12] = {6687};
    runMap[13] = {6689};
    runMap[14] = {6690};
    runMap[15] = {6691};
    runMap[ 3] = {6692};
  } else if ( dstName == "hv" ) {
    runMap[22] = {6696};
    runMap[31] = {6713};
    runMap[40] = {6740};
  } else if ( dstName == "apr19extv4" ) {
    skipMissingFiles = true;
    runMap[ 1] = {7604};
    runMap[ 2] = {7605};
    runMap[ 3] = {7606};
    runMap[ 4] = {7607};
    runMap[ 5] = {7608};
    runMap[ 6] = {7609};
    runMap[ 7] = {7610};
    runMap[ 8] = {7611};
    runMap[ 9] = {7612};
    runMap[10] = {7613};
    runMap[11] = {7614};
    runMap[12] = {7615};
    runMap[13] = {7616};
    runMap[14] = {7617};
    runMap[15] = {7618};
    runMap[16] = {7619};
    runMap[17] = {7620};
    runMap[18] = {7624};
    runMap[21] = {7625};
    runMap[25] = {7626};
  } else if ( dstName == "nov19ext"   ||
              dstName == "nov19extv4" ) {
    crNameDefault = "apa7z";
    runMap[ 1] = {10489};
    runMap[ 2] = {10491};
    runMap[ 3] = {10492};
    runMap[ 4] = {10493};
    runMap[ 5] = {10495};
    runMap[ 6] = {10496};
    runMap[ 7] = {10497};
    runMap[ 8] = {10498};
    runMap[ 9] = {10499};
    runMap[10] = {10500};
    runMap[11] = {10501};
    runMap[12] = {10502};
    runMap[13] = {10503};
    runMap[14] = {10504};
    runMap[15] = {10505};
    runMap[16] = {10506};
    runMap[17] = {10507};
    runMap[18] = {10508};
    runMap[21] = {10509};
    //runMap[25] = {10510};
    //runMap[30] = {10511};
  } else if ( dstName.substr(0,8) == "jul20ext" ) {
    skipMissingFiles = true;
    runMap[ 1] = {11526};
    runMap[ 2] = {11527};
    runMap[ 3] = {11528};
    runMap[ 4] = {11529};
    runMap[ 5] = {11530};
    runMap[ 6] = {11531};
    runMap[ 7] = {11532};
    runMap[ 8] = {11533};
    runMap[ 9] = {11534};
    runMap[10] = {11535};
    runMap[11] = {11536};
    runMap[12] = {11537};
    runMap[13] = {11538};
    runMap[14] = {11539};
    runMap[15] = {11540};
    runMap[16] = {11541};
    runMap[17] = {11542};
    runMap[18] = {11543};
    runMap[21] = {11544};
    runMap[25] = {11545};
    runMap[30] = {11546};
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
