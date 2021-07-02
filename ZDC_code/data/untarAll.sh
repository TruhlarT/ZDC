#!/bin/bash
#baseFolder=${1}
baseFolder=/gpfs01/star/pwg/truhlar/ZDC/ZDC_code/data/run21.ZdcCalibration.truhlar/22180018

pushd $baseFolder >> /dev/null

for run in $( ls ./ ); do
  pushd $run >> /dev/null
  tarFile=run"$run".tgz

  if [ -f $tarFile ]; then
    echo Unzipping $tarFile
    tar -xzf $tarFile
    rm $tarFile
  fi

  popd >> /dev/null 
done

popd >> /dev/null

echo Done unzipping all .tgz files
