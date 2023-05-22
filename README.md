# ZDC

## Compile the code
```sh
cd ZDC_code
starver dev
cons
```


## Analysis of the new runs
Check your run in [STAR RunLog Browser](https://online.star.bnl.gov/RunLog/).
Sometimes it is useful to check if the run***.tgz exists (it might not for some runs). To log to HPSS from RACF, enter:
```sh
hsi
```
Data files are there in the folder:
```sh
/home/starsink/raw/daq/#YYYY/#DAY/#RUN
```
Enter number of the run, that you are going analyse to script `ZDC_code/data/transferTarFiles.cpp` as variable `int RunNumber` and run `transferTarFiles.sh` script to download the run***.tgz file:

Download progress could be checked at https://www.star.bnl.gov/devcgi/display_accnt.cgi.
Once the file is download, the only think you need to do is run:
```sh
./readRunList.sh 
```
Check the quality of fits in
```sh
ZDC_Calibration/runXX.ZdcCalibration.truhlar/analysis/RUNNUMBER
```
The results of SNP fits (mean and sigma) have to be put into zdcTree.C in lines 161-164
The results of SNP fits are stored in 
```sh
ZDC_Calibration/runXX.ZdcCalibration.truhlar/analysis/RUNNUMBER/fit_parameters.in
```
to load the results from fit_parameters.in in zdcTree.C automatically is work in progress...

To refit the SNP, run 
```sh
./plotSingleNeutron.C
```
in ZDC_Calibration/ZdcCalibration/
You may want to change the initial parametrs of fits in lines 31 and 42. 

When fitting is done and the SNP results are changed in zdcTree.C in lines 161-164, run
```sh
./runFinal.sh RUNNUMBER TOFCUT 
```

Before running this script, update all files and create appropriate folders. For details see the section below.

## Changes needed at the beginning of the new year run
New files and folders or you can just run `prepareFolders.sh`:
```sh
touch ZDC_code/seenRuns/seenRuns_run21.truhlar.txt
mkdir ZDC_code/data/run21.ZdcCalibration.truhlar
mkdir ZDC_Calibration/run21.ZdcCalibration.truhlar
mkdir /afs/rhic.bnl.gov/star/users/truhlar/WWW/run21.ZdcCalibration
```
Here is the list of files and lines in them, that need to be modified:

`ZDC_code/config.C`:
```sh
dirOut = "/gpfs01/star/pwg/truhlar/ZDC/ZDC_Calibration/run19.ZdcCalibration.truhlar";
seenRuns = "/gpfs01/star/pwg/truhlar/ZDC/ZDC_code/seenRuns/seenRuns_run19.truhlar.txt";
filename = "/gpfs01/star/pwg/truhlar/ZDC/ZDC_code/data/run19.ZdcCalibration.truhlar.list";
```

`ZDC_code/StRoot/StZDCPool/StZDCOnlineMonitoring/StReadTrg.cxx`
```sh
#include <StTriggerData2021.h>
```

`ZDC_code/StRoot/StZDCPool/StZDCOnlineMonitoring/TriggerData.cxx`
```sh
#include "StDaqLib/TRG/trgStructures2021.h" 
#include "StEvent/StTriggerData2021.h"
...
if(td[3] == 0x46){
TriggerDataBlk2021* trgdata2021 = (TriggerDataBlk2021*)td; 
StTriggerData2021* trgd = new StTriggerData2021(trgdata2021,run); 
```

`ZDC_Calibration/ZdcCalibration/zdcTree.h`:
```sh
TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(Form("/gpfs01/star/pwg/truhlar/ZDC/ZDC_Calibration/run19.ZdcCalibration.truhlar/histo/run_%d.histo.root", mRunNumber));    
f = new TFile(Form("/gpfs01/star/pwg/truhlar/ZDC/ZDC_Calibration/run19.ZdcCalibration.truhlar/histo/run_%d.histo.root", mRunNumber));
```

And finally, some straighforward changes in these files:
```sh
ZDC_Calibration/ZdcCalibration/moveToWww.sh
ZDC_Calibration/ZdcCalibration/html_maker.cpp
ZDC_Calibration/ZdcCalibration/runFinal.sh
ZDC_code/readRunList.sh
ZDC_code/data/ls.csh
```
