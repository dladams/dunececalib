Calibration procedure

David Adams
February 2020

The goal is to evaluate the area gain for each channel based on
pulser dataset with runs taken with different DAC settings.
The calibrated signal s can then be obtained with this gain:
> s = g (A - p)
where A is the raw ADC signal, p is the pedestal and g is the gain.

A height calibration and shaping time measurement for each channel can also be obtained.

1. Area evaluation

We begin by evaluating the mean area for each channel at each DAC setting.
