## Charge calibration for protoDUNE-SP

David Adams   
July 2020

### Introduction

This documents summarizes the charge calibration procedure for protoDUNE run 1
(July 2018 - July 2020).
The general goals and procedures for calibration are [here](procedure.md).
The protoDUNE datasets and some calibration results are posted on the
[ProtoDUNE calibration page](https://internal.dunescience.org/people/dladams/protodune/calibrations).

### Datasets

A calibration dataset is a list of run numbers along with the DAC setting for each run.
The [Iceberg dataset definition script](../Root/Iceberg/makeIcebergCalibData.C)
provides this information and the location of the channel summary histogram files for a few named datasets
In particular, dec18extv4 is the dataset used for the calibration used in production reconstruction.

The dataset definition script may be run directly to displays the locations of the
channel summary histogram files for a specified dataset and channel range, e.g.
<pre>
root [0] makeAdcCalibData("dec18extv4", "apa1z", false)
AdcCalibData dec18extv4 apa1z
     1    6068  data/dec18extv4/apa1z/roicha006068pos.root
    -1    6068  data/dec18extv4/apa1z/roicha006068neg.root
     2    6046  data/dec18extv4/apa1z/roicha006046pos.root
    -2    6046  data/dec18extv4/apa1z/roicha006046neg.root
     3    6045  data/dec18extv4/apa1z/roicha006045pos.root
    -3    6045  data/dec18extv4/apa1z/roicha006045neg.root
     4    6043  data/dec18extv4/apa1z/roicha006043pos.root
    -4    6043  data/dec18extv4/apa1z/roicha006043neg.root
     5    6042  data/dec18extv4/apa1z/roicha006042pos.root
    -5    6042  data/dec18extv4/apa1z/roicha006042neg.root
     6    6041  data/dec18extv4/apa1z/roicha006041pos.root
    -6    6041  data/dec18extv4/apa1z/roicha006041neg.root
     7    6040  data/dec18extv4/apa1z/roicha006040pos.root
    -7    6040  data/dec18extv4/apa1z/roicha006040neg.root
     8    6039  data/dec18extv4/apa1z/roicha006039pos.root
    -8    6039  data/dec18extv4/apa1z/roicha006039neg.root
    10    6038  data/dec18extv4/apa1z/roicha006038pos.root
   -10    6038  data/dec18extv4/apa1z/roicha006038neg.root
    12    6037  data/dec18extv4/apa1z/roicha006037pos.root
   -12    6037  data/dec18extv4/apa1z/roicha006037neg.root
    15    6036  data/dec18extv4/apa1z/roicha006036pos.root
   -15    6036  data/dec18extv4/apa1z/roicha006036neg.root
    18    6035  data/dec18extv4/apa1z/roicha006035pos.root
   -18    6035  data/dec18extv4/apa1z/roicha006035neg.root
(const AdcCalibData *) 0xb4fb350
</pre>
If the last argument is true, the script checks for the existence of each file and excludes
those that are missing.

### Evaluation of channel summary data

The first step in calibration is evaluation of the channel summary data, i.e. the mean value
of pulse area, height and shaping time for each run and charge sign.
Histograms with these means as function of channel number can be created with this command
<pre>
duneproc pdspRunCalib/dpcr_${CRN}/roi${SGN}${STHR} np04_run${SRUN}_evts000000-000100
</pre>
where SRUN is the six digit run number, e.g. 004871, SGN (pos or neg) is the charge sign,
CRN is the channel range, e.g. apau, apv, apaz1 or apaz2, and
STHR is the threshold in ADC counts, 40 for default calibration.
Here events 1-99 are used in the calibration.
The channel summary histograms are recorded in the file roicha.root in the run directory.

I use the script [makeRunjobs](doc/pdcalib-202007/makeRunjobs) to create the duneoproc commands
for the full dataset.

These histogram files are then copied to the location specified in the dataset definition,
i.e. to data/${SAM}/${CRN}/roicha${RUN}${SGN}.root where SAM is the dataset name (e.g. dec18extv4).
The sample name is typically the dataset name but it may instead can be in the format ${DST}-XXX where DST is the dataset
name and XXX allows for differnt processing options, e.g. different ROI thresholds or
window sizes.
I use the script [moveData](doc/pdcalib-202007/moveData) to do the copying.

### Calibration

The calibrations, i.e. area gain, height gain and shaping time for each channel are evaluated
from the channel summary data using
the rather complicated utility class [AdcCalibGraphs](../Utility/AdcCalibGraphs.h).
The Root script [doCalib.C](../Root/doCalib.C) provides a wrapper to use this utility to generate
the fcl calibration files and many associated plots.
The protoDUNE-specific script doCalibPdsp can be used to call that Root script, e.g.
<pre>
doCalibPdsp $SAM $CRN
</pre>
where DST is the dataset name, e.g. dec18extv4 and CRN is the channel range, e.g. apa1z.
The output is written to ./calibrations/$SAM and includes many plots and fcl files with
area gains, height gains and shaping times.
Those files define tool configurations of type FclFloatArray.

The calibration for the full detector is specified in a configuration for tool type FclFileFloatArray
which lists the relative paths for the channel range calibration files.
This configuration may be created in ./fcl with the command
<pre>
makeCalibPdsp $DST
</pre>
The channel range configurations are also copied to the appropriate location in that directory.

### Using the calibration

To use the calibration, it must be installed on the fcl path ($FHICL_FILE_PATH), e.g. by copying the
files in ./fcl to ./job.
Note that the subdirectory structure in ./fcl for the channel range files must be preserved.

The calibration will be available if detector configuration file is included in the job confguration.
E.g., to plot the distribution of (area) gains for (locally installed) dataset jul20extv4, use 
<pre>
root [0] drawGainDist("jul20extv07")
.
.
.
calplots:   # bad: 156
calplots:   # good: 15204
Printing gaindist_jul20extv07.{png,tpad}
</pre>
Use the dataset name calib20191213_dec18ext to obtain the distribution for current default calibration.
