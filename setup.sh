# setup.sh
#
# David Adams
# January 2020

if [ -n "$DUNECECALIB_DIR" ]; then
  echo It appears dunececalib is already set up.
  echo DUNECECALIB_DIR = $DUNECECALIB_DIR

elif [ -z "$DUNEPROC_DIR" ]; then
  echo First set up duneproc

else

echo Setting up dunececalib
export DUNECECALIB_DIR=$(dirname $(readlink -f $BASH_SOURCE))
PATH=$DUNECECALIB_DIR/bin:$PATH
TMPPATH=.:./job:
if [ ${FHICL_FILE_PATH:0:8} = $TMPPATH ]; then FHICL_FILE_PATH=${FHICL_FILE_PATH:8}; fi
FHICL_FILE_PATH=${TMPPATH}$DUNECECALIB_DIR/fcl:$FHICL_FILE_PATH
unset TMPPATH

fi
