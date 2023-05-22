#!/bin/bash

wwwDir=/afs/rhic.bnl.gov/star/users/truhlar/WWW/run23.ZdcCalibration

mkdir -p "$wwwDir"
cp *.htm "$wwwDir"
cp *.html "$wwwDir"
cp -r analysis "$wwwDir"
cp -r asym "$wwwDir"
cp -r pdf "$wwwDir"
