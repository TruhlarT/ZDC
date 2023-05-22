#!/bin/bash

runNumber=${1:-0}
tofCut=${2:-32767}
runDirectory="run23.ZdcCalibration.truhlar"

echo $runNumber
echo $tofCut

root -l -b -q loadZDCtree.C 'run.cxx++g('$tofCut','$runNumber')'
root -l -q 'html_maker.cpp('$runNumber')'

pushd ../$runDirectory  >> /dev/null
  ./moveToWww.sh
popd >> /dev/null