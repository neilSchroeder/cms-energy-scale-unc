#!/bin/bash

DIRECTORY=$1

if [ -d "$DIRECTORY" ]; then
    cd $DIRECTORY
    rm *.pdf
    rm *.C
    rm *.png
    if [ -d "tex" ]; then 
        mkdir tex
    fi
    cd ..
fi

if [ ! -d "$DIRECTORY" ]; then
    mkdir $DIRECTORY
    cd $DIRECTORY
    mkdir tex
    cd ..
fi
