# dunececalib
Dune TPC cold electronics gain calibration

David Adams  
Octover 2022

This package holds configuration files and Root scripts used in charge calibration
of the protoDUNE TPC.

# Installation

First install [*duneproc*](https://github.com/dladams/duneproc).
Then check out and build this package after setting up *dunerun*, e.g.
<pre>
cd &lt;package-dir>
git clone https://github.com/dladams/dunececalib.git
cd dunececalib
dune-run -e dunebuild ./build
</pre>

# Running

To use the this package, install and set up the top-level package for the relevant detector.

For HD coldbox data, use [*hdcoldbox*](https://github.com/dladams/hdcoldbox):
<pre>
cd &lt;run-dir>
git clone https://github.com/dladams/hdcoldbox.git
cd hdcoldbox
./start-shell dunececalib
</pre>

# More information

The calibration procedure is described in [doc/procedure.md](doc/procedure.md).

Details for protoDUNE-SP are in [doc/pdspCalibration.md](doc/pdspCalibration.md).

Details for Iceberg are in [doc/icebergCalibration.md](doc/icebergCalibration.md).

### Some useful links.
* [DA's run list] (https://wiki.dunescience.org/wiki/ProtoDUNE_commissioning_runs_(dla))
* DA paper on protoDUNE-I-SP charge calibration: [DUNE doc 15523](https://docs.dunescience.org/cgi-bin/sso/ShowDocument?docid=15523)
* * [DA last talk of protoDUNE-I-SP calibration](https://indico.fnal.gov/event/22661/contributions/68849/attachments/43332/52259/adams_dunepdsimreco_20191211_calib.pdf)
