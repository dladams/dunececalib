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
The examples here assume the file is [./infiles.txt](infiles.txt) which lists the files for run 6045
taken 2108-12-05 with external pulser DAC setting 3 and HV off.
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
These are followed by a signal finder `adcThresholdSignalFinder` which identifies ROIs (regions of interest)
and an ROI viewer `adcRoiFitter` which processes each of those to generate the histograms from which the calibration is derived.

This configuration can be used directly in a lar job but will not produce any histograms because
adcRoiFitter.ChannelRanges is empty.
The example configuration [exampleCalib.fcl](exampleCalib.fcl) demonstrates how to start from
that configuration and specify the channel range to include in the output histograms.
The example configuration also shows how to pick on charge sign and adjust the signal finder threshold.

When events are processed, the ROI viewer creates a histogram for each ROI and,
with the configuration here, fits it using the CE response function.
The example configuration shows how to make plots of the ROI histogram or save them in a Root file.
By default, they are not plotted or saved.

The ROI viewer fills the *summary* histograms specified in the tool configuration.
Typically one entry is added to each summary histogram for each ROI histogram.
Most interesting here, the signal area histogram is filled with the integral of the ROI histogram.
Distributions of signal height, shaping time and other variables are also reorded.
The example configuration shows how to plot or save these histograms.

At the end of the job, *channel summary* histograms are created from the summary histograms
with one entry for each channel or a distribution over channels.
Of greatest interest here, is the area channel summary which holds the mean and RMS of
the area for each channel.
Similar histograms are constructed for the fitted height and shaping time.

To see some of these result, copy exampleCalib.fcl and infiles.txt to an empty directory and
run the example job over 5 events:

> lar --no-output -c exampleCalib.fcl -S infiles.txt -n 5

The output will include roicha.root with the channel summary histograms and a png plot for each
channel summary variable, e.g. hcsArea_femb101x.png shows the area channel summary.
To view ROIs or the the summary histograms, modify the configuration to generate those plots or
record those histograms and rerun over the desired events and channel range.

### Gain evaluation

Run jobs like these for each sign, DAC setting and channel range.
Then, for each channel, we can graph area vs. signed DAC setting
and fit these to extract slopes in units of (ADC count)/(DAC step).
These can then be inverted and normalized, e.g.

> DAC step = 21.4 ke

to obtain the gains.

The utility class [AdcCalibGraphs](../src/AdcCalibGraphs.h) can help with this task.
It can make plots and do fits for area, height shaping time and more.
The user must first create and register an [AdcCalibData](../src/AdcCalibData.h)
that describes a calibration dataset with a DAC setting, run number and full path to
the channel summary Root file for each entry.

