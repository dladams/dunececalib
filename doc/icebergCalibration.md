## Charge calibration for Iceberg

David Adams   
May 2020

### Introduction

This documents summarizes the charge calibration procedure for Iceberg run 3.
The general goals and procedures for calibration are [here](procedure.md).
The Iceberg datasets and some calibration results are posted on the
[Iceberg calibration page](https://internal.dunescience.org/people/dladams/protodune/iceberg/calibrations).

### Datasets

A calibration dataset is a list of run numbers along with the DAC setting for each run.
The [Iceberg dataset definition script](../Root/Iceberg/makeIcebergCalibData.C)
provides this information and the location of the channel summary histogram files for a few named datasets
In particular ib3_b900 is the dataset
used to calibrate the bulk of the data, i.e. that taken with standard configuration.

The dataset definition script may be run directly to displays the locations of the
channel summary histogram files for a specified dataset and channel range, e.g.
<pre>
root [0] makeAdcCalibData("ib3_b900", "apaz1", true)
AdcCalibData ib3_b900 apaz1
     1    4484  data/ib3_b900/apaz1/roicha004484pos.root
    -1    4484  data/ib3_b900/apaz1/roicha004484neg.root
     1    4679  data/ib3_b900/apaz1/roicha004679pos.root
    -1    4679  data/ib3_b900/apaz1/roicha004679neg.root
.
.
.
    12    4690  data/ib3_b900/apaz1/roicha004690pos.root
   -12    4690  data/ib3_b900/apaz1/roicha004690neg.root
</pre>
If the last argument is true, the script checks for the existence of each file and excludes
those that are missing.

### Evaluation of channel summary data

The first step in calibration is evaluation of the channel summary data, i.e. the mean value
of pulse area, height and shaping time for each run and charge sign.
Histograms with these means as function of channel number can be created with this command
<pre>
duneproc ibRunCalib/roi${SGN}${STHR}/dpcr_${CRN} iceberg${SRUN}
</pre>
where SRUN is the six digit run number, e.g. 004871, SGN (pos or neg) is the charge sign,
CRN is the channel range, e.g. apau, apv, apaz1 or apaz2, and
STHR is the threshold in ADC counts, 40 for default calibration.
The histograms are recorded in the file roicha.root in the run directory.

These histogram files are then copied to the location specified in the dataset definition,
i.e. to data/${SAM}/${CRN}/roicha${RUN}${SGN}.root where SAM is the dataset name (e.g. ib3_b900).
The sample name can be the dataset name or can be in the format ${DST}-XXX where DST is the dataset
name and XXX allows for differnt processing options, e.g. different ROI thresholds or
window sizes.

### Calibration

The calibrations, i.e. area gain, height gain and shaping time for each channel are evaluated
from the channel summary data using
the rather complicated utility class [AdcCalibGraphs](../Utility/AdcCalibGraphs.h).
The Root script [doCalib.C](../Root/doCalib.C) provides a wrapper to use this utility to generate
the fcl calibration files and many associated plots.
The Iceberg-specific Root script [icebergCalib.C](../Root/Iceberg/icebergCalib.C)
assigns names to standard fitting options and passes
those to doCalib to carry out calibrations.

The calibration plots and fcl files may be constructed with the command doCalibIceberg which takes
the dataset name, fit version (see [icebergCalib.C](../Root/Iceberg/icebergCalib.C)) and 
channel range (apau, apav, apaz1, apaz2) as arguments, e.g.
<pre>
doCalibIceberg ib4 v10 apaz1
</pre>
Substituting top for the channel range produces the top-level fcl.
All fcl files are placed in calibrations/DST-VER/fcl where DST is the dataset name and VER is the fit version.

The script I use to copy the calibration to my
[web area](https://internal.dunescience.org/people/dladams/protodune/iceberg/calibrations)
is [wcopy](wcopy).
