// AdcCalibGraphs.h

#ifndef AdcCalibGraphs_H
#define AdcCalibGraphs_H

#include <string>
#include <map>
#include <memory>
#include "dunecore/DuneInterface/Tool/IndexMapTool.h"
#include "dunecore/DuneCommon/Utility/TPadManipulator.h"

#include "TGraphErrors.h"

class TF1;
namespace lariov {
  class ChannelStatusProvider;
}

class AdcCalibGraphs {

public:

  using Index = unsigned int;
  using Name = std::string;
  using NameVector = std::vector<Name>;
  using NameMap = std::map<Name, Name>;
  using Graph = TGraphErrors;
  using GraphPtr = std::shared_ptr<Graph>;
  using Pad = TPadManipulator;
  using PadPtr = std::shared_ptr<Pad>;
  using GraphMap = std::map<Index, GraphPtr>;
  using GraphNameMap = std::map<Name, GraphPtr>;
  using GraphMapMap = std::map<Name, GraphMap>;
  using GraphMapMapMap = std::map<Name, GraphMapMap>;
  using PadMap = std::map<Index, PadPtr>;
  using PadMapMap = std::map<Name, PadMap>;
  using PadNameMap = std::map<Name, PadPtr>;
  using FunVector = std::vector<TF1*>;
  using FunVectorMap = std::map<Name, FunVector>;

  // Ctor.
  //   a_dstName: Name of the input dataset in AdcCalibData
  //   a_crName: Name of the channel range to process
  AdcCalibGraphs(Name dstName, Name a_crName);

  // Dtor.
  ~AdcCalibGraphs();

  // Allow misssing runs. Default is not.
  void setAllowMissingRuns(bool val =true) { m_allowMissingRuns = val; }
  bool getAllowMissingRuns() { return m_allowMissingRuns; }

  // Set error scaling.
  //   0: Errors set to zero
  //   1: Error bars are sigma/RMS.
  //   2: Error bars are scaled by 1/sqrt(count)
  void setErrorScaling(int val =true) { m_errorScaling = val; }
  int getErrorScaling() { return m_errorScaling; }

  // Include gain and cal residuals when calculating full residuals.
  void doGainResiduals(bool opt =true) { m_doGainResiduals = opt; }

  // Fix fit parameters for Height and Area.
  void fixHeightSlope(double slopHeight);
  void fixHeightOffset(double offsHeight =0.0);
  void fixHeightPedestal(double pedeHeight =0.0);
  void fixHeightShift(double pedeHeight =0.0);
  void fixHeightNegScale(double nscaHeight =1.0);
  void fixAreaSlope(double slopArea);
  void fixAreaOffset(double offsArea =0.0);
  void fixAreaPedestal(double pedeArea =0.0);
  void fixAreaShift(double pedeArea =0.0);
  void fixAreaNegScale(double nscaArea =1.0);
  
  // Retrieve the ifun'th fit function for variable varName. Null for no fit.
  // Caller can change the starting value, etc.
  TF1* getFitFunction(Name varName, Index ifun =0);

  // Set the ifun'th fit function for variable varName. Null for no fit.
  int setFitFunction(Name varName, TF1* pfit, Index ifun =0);

  // Get/set the charge unit: Q_{step} (default), fC, e, ke
  Name chargeUnit() const { return m_chargeUnit; }
  void setChargeUnit(Name val) { m_chargeUnit = val; }

  // Create primary dataset graphs for ncha channels starting at icha1
  // for channels that do not already have graphs.
  // Returns 0 for success.
  Index makeGraphs(Index icha1, Index ncha =1);

  // Create extra dataset graphs for dataset dstName ncha channels starting at icha1
  // for channels that do not already have graphs.
  // Returns 0 for success.
  Index makeExtraGraphs(Name dstName, Index icha1, Index ncha, int icol =2, int imrk =0);

  // Create graphs for dataset dstName in grasOut for ncha channels starting at icha1.
  Index makeGraphsInternal(Name dstName, Index icha1, Index ncha,
                           GraphMapMap& grasOut, int icol, int imrk);

  // Return the pre-inclusive range of created graphs.
  Index graphChannelBegin() const { return m_graphChannelBegin; }
  Index graphChannelEnd() const { return m_graphChannelEnd; }
  Index graphChannelSize() const { return graphChannelEnd() - graphChannelBegin(); }
  
  // Fit the graphs for ncha channels starting at icha1.
  // Returns 0 for success.
  Index fitGraphs(Index icha1, Index ncha, double xmin, double xmax, Name fopt ="QS");

  // Create the residual graphs.
  Index resGraphs(Index icha1, Index ncha);

  // Return the drawing pad for a graph.
  // Pad size is ny x nx pixels.
  PadPtr pad(Name gnam, Index icha, Index nx=700, Index ny=500);

  // Return and draw the pad for a graph.
  PadPtr draw(Name gnam, Index icha);

  // Return the drawing pad for multiple graphs.
  // Pad size is ny x nx pixels.
  PadPtr multiChannelPad(Name gnam, Index icha, Index ncha, Index npadx, Index npady,
                         Index nx=1400, Index ny=1000);

  // Make multi-channel pads for all graphed channels.
  void makeMultiChannelPads(Name gnam, Index npadx, Index npady, Index nx=1400, Index ny=1000);

  // Return the existing graph for a channel.
  // If dstName is blank, then graph for the primary dataset is returned.
  // Otherwise the graph for extra dataset dstName.
  GraphPtr graph(Name gnam, Index icha, Name dstName ="");

  // Print all the multichannel pads whose names begin with prefix, e.g. "Area".
  // prepending outpre to the output file names.
  int printMultiChannelPads(Name prefix ="", Name outpre ="") const;

  // Create a channel summary plot.
  // E.g. slope vs. channel.
  //   varName: Pulser fit variable: Height, Area, Shaping, ...
  //   parName: Name of the parameter from the fit of the variable.
  //   fitName: Name of the fit function. For blank "Fit" is appended to the variable name.
  //   If pgraName is not null, the graph name is returned.
  GraphPtr channelSummaryGraph(Name varName, Name parName, Name fitName ="", Name* pgraName =nullptr);
  PadPtr channelSummaryPad(Name varName, Name parName, Name fitName ="",
                           double ymin =0.0, double ymax=0.0, Index wx=1400, Index wy=500);
  PadPtr drawChannelSummaryPad(Name varName, Name parName, Name fitName ="",
                               double ymin =0.0, double ymax=0.0, Index wx=1400, Index wy=500);
  // Add alternate interface because of incomplete support for intepreted shared_ptr in Root 6.18/04.
  Pad* drawChannelSummaryPadBare(Name varName, Name parName, Name fitName ="",
                               double ymin =0.0, double ymax=0.0, Index wx=1400, Index wy=500) {
    return drawChannelSummaryPad(varName, parName, fitName, ymin, ymax, wx, wy).get();
  }

  // Return graph with ratio of summary values.
  //   ratName: AHS - Area/Height/Shaping
  // These can also be fetched with the channelSummary methods using varName="Ratio" and parName=ratName.
  GraphPtr channelRatioGraph(Name ratName);

  // Return the variable name for plot variable name, e.g. gresHeight --> Height.
  Name variableName(Name graName) const;

  // Return the label for a variable name for this object.
  Name label(Name varName) const;

  // Write the gains and shaping times in fcl format.
  // calName = AreaGain, HeightGain or Shaping
  // If the file name is blank, it is constructed from the label.
  // Use setChargeUnit to set the charge unit for gain calibrations.
  int writeFcl(Name calName, Name filName= "");

  // Return the graph map.
  const GraphMapMap& graphMaps() const { return m_gras; }

private:

  Name m_dstName;
  Name m_fileTemplatePos;
  Name m_fileTemplateNeg;
  Name m_crName;
  NameVector m_varNames;
  NameVector m_fitNames;
  NameVector m_resNames;
  int m_markerType = 5;
  GraphMapMap m_gras;
  NameVector m_extraDsts;
  GraphMapMapMap m_extraGras;
  PadMapMap m_pads;
  PadNameMap m_multiPads;
  FunVectorMap m_fits;
  GraphNameMap m_chsgras;
  GraphNameMap m_chsgrasBad;
  GraphNameMap m_chsgrasNoisy;
  GraphNameMap m_chsgrasBpu;
  PadNameMap m_chspads;
  bool m_allowMissingRuns;
  int m_errorScaling;
  bool m_doGainResiduals;
  NameMap m_labels;
  float m_xgmin;
  float m_xgmax;
  Name m_chargeUnit;
  Index m_graphChannelBegin;
  Index m_graphChannelEnd;
  const lariov::ChannelStatusProvider* m_pChannelStatusProvider;
  const IndexMapTool* m_pchanstat;

};

#endif
