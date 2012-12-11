#!/bin/bash

mkdir -p ${2}
$ROOTSYS/bin/hadd ${2}/${1}_histo.root ${1}_job*/Analysis.Data1.Reco.root
