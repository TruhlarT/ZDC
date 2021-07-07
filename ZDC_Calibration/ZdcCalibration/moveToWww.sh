#!/bin/bash

wwwDir=/afs/rhic.bnl.gov/star/users/truhlar/WWW/run21.ZdcCalibration

mkdir -p "$wwwDir"
cp *.html "$wwwDir"
cp -r analysis "$wwwDir"
cp -r asym "$wwwDir"
cp -r pdf "$wwwDir"
