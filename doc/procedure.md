## Calibration procedure

David Adams   
February 2020

The goal is to evaluate the area gain for each channel based on
pulser dataset with runs taken with different DAC settings.
The calibrated signal s can then be obtained with this gain:
> s = g (A - p)

where A is the raw ADC signal, p is the pedestal and g is the gain.

A height calibration and shaping time measurement for each channel can also be obtained.

The following sections provide step-by-step instructions for generating a calibration
with a combination of dunetpc lar and Root jobs making use of the scripts and configuration
files provided in this package ([dunececalib](https://github.com/dladams/dunececalib)).
For instructions on getting started, see the tutorial in package [duneproc](https://github.com/dladams/duneproc).

### 1. Area evaluation

We begin by evaluating the mean area for each channel at each DAC setting.
The starting top-level configuration [roifitpos100.fcl](../fcl/roifitpos100.fcl) runs the tool `AdcRoiViewer`
with configuration `adcRoiFitter`.
