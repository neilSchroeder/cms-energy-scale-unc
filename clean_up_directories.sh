#!/bin/bash

DIRECTORY=$1

if [ -d "$DIRECTORY" ];
then
    cd $DIRECTORY
    rm *.pdf
    rm *.C
    rm *.png
    cd ..
fi

if [ ! -d "$DIRECTORY" ];
then
    mkdir $DIRECTORY
fi
