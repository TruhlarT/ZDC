#!/bin/bash

runNumber=${1:-0}
tofCut=${2:-32767}

echo $runNumber
echo $tofCut

root -l -b -q loadZDCtree.C 'run.cxx++g('$tofCut','$runNumber')'
root -l -q 'plotSingleNeutron.C('$runNumber')'
#root -l -b -q loadZDCtree.C 'run.cxx++g('$tofCut','$runNumber')'
#root -l -q 'html_maker.cpp('$runNumber')'
