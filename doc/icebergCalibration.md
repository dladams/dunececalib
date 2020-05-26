## Charge calibration for Iceberg

David Adams   
May 2020

### Introduction

This documents summarizes the charge calibration procedure for Iceberg run 3.
The general goals and procedures for calibration are [procedure.md](here).
The Iceberg datasets and some calibration results are posted on the
[https://internal.dunescience.org/people/dladams/protodune/iceberg/calibrations/](Iceberg calibration page).

### Datasets

A calibration dataset is a list of run numbers along with the DAC setting for each run.
The [../Root/Iceberg/makeIcebergCalibData.C](Iceberg dataset definition script)
provides the information for a few named datasets, in particular ib3_b900 is the one
used to calibrate the bulk of the data, i.e. that taken with standard configuration.

### Evaluation of Response means
The first step in calibration is evaluation of the response means, i.e. the mean value
of pulse area, height and shaping time for each run and charge sign.
Histograms with these means as function of channel number can be created with this command
<pre>
duneproc ibRunCalib/roi${SGN}${STHR}/dpcr_${CRN} iceberg${SRUN}
</pre>
where SRUN is the six digit run number, e.g. 004871, SGN (pos or neg) is the charge sign,
CRN is the channel range, e.g. apau, apv, apaz1 or apaz2, and
STHR is the threshold in ADC counts, 40 for default calibration.

