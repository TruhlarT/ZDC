#!/bin/bash
runYear=${1}
ls /gpfs01/star/pwg/truhlar/ZDC/ZDC_code/data/${runYear}.ZdcCalibration.truhlar/ > tmp.list
sort seenRuns/seenRuns_${runYear}.truhlar.txt tmp.list | uniq -u > unSeenRuns.list
rm tmp.list
