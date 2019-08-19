import os
import sys
import pandas as pd
import numpy as np
from optparse import OptionParser

parser = OptionParser()
parser.add_option("--inputFile",
        "-i",
        help="input file")
parser.add_option("--outputFile",
        "-o",
        help="output file")

(opts, args) = parser.parse_args()

print("----------------------------")
print("[INFO] producing .tex tables")
print("----------------------------")

out = opts.outputFile+".txt"
os.system("touch "+out)
f = open(opts.outputFile+".txt", "w+")

thisFile = pd.read_csv(opts.inputFile, sep=" ")
thisFile = np.matrix(thisFile)

for row in thisFile:
    row = np.ravel(row)
    f.write("cms.PSet( lowBounds = cms.vdouble( %f, %f ) , upBounds = cms.vdouble( %f, %f ) , values = cms.vdouble( 0. ) , uncertainties = cms.vdouble( %f ) ) ,\n" % (row[1], row[3], row[2], row[4], row[13]/100.))

f.close()
