## Calibration procedure

David Adams   
February 2020

The goal is to evaluate the area gain for each channel based on
pulser dataset with runs taken with different DAC settings.
The calibrated signal s can then be obtained with this gain:
> s = g (A - p)

where A is the raw ADC signal, p is the pedestal and g is the gain.

A height calibration and shaping time measurement for each channel can also be obtained.

The procedure here assumes the area of the pulser signals is proportional
to the DAC setting and so is appropriate for data taken with the protoDUNE
external (FEMB based) signal generation.
Thus, gains can be derived from data taken with a single DAC setting but more are
typically used to average over non-linearity in the pulser response.
The standard is DAC settings 1-7 because these do not show saturation
for amplifier gain 14 mV/fC and there is a jump in the puilser reponse after these.

The following sections provide step-by-step instructions for generating a calibration
with a combination of dunetpc lar and Root jobs making use of the scripts and configuration
files provided in this package ([dunececalib](https://github.com/dladams/dunececalib)).
For instructions on getting started, see the tutorial in package [duneproc](https://github.com/dladams/duneproc).
Instead of (or in addition to) the package dunenoise, check out and set up up this package (dunececalib).

### 1. Input data

Choose the runs to be used for the calibration and create and list of raw data files for each DAC setting.
The examples here assume the file is [./infiles.txt](infiles.txt) which lists the files for.
My [protoDUNE run list](https://wiki.dunescience.org/wiki/ProtoDUNE_commissioning_runs_(dla)) lists
runs I have used for calibration and other studies.
There are links to other run lists at the bottom of that page.
You can find my file lists on the dunegpvm machines at /dune/data2/users/dladams/data/dune/np04/run_slices/files.
These are pnfs locations.
To get the xrootd location, replace the leading "/pnfs" with "xroot://fndca1.fnal.gov:1094/pnfs/fnal.gov".

### 2. Area evaluation

We begin by running lar jobs to evaluate the mean area for each channel at each DAC setting.
The top-level configuration [roifitpos100.fcl](../fcl/roifitpos100.fcl) provides the good starting point.
It runs a job that reads raw data and runs the indicated dataprep tool sequence.
That sequence reads raw data, finds pedestals, applies unit calibration (gain=1) and mitigates sticky codes.
These are followed by a signal finder `adcThresholdSignalFinder` which indentifies ROIs (regions of interest)
and `adcRoiFitter` which processes each of those to generate the histograms from which the calibration is derived.
with configuration `adcRoiFitter`.
