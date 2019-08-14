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

out = opts.outputFile+".tex"
os.system("touch "+out)
f = open(opts.outputFile+".tex", "w+")
f.write("\documentclass[landscape]{article}\n")
f.write("\\usepackage{amsmath, amssymb, multirow, booktabs, graphicx}\n")
f.write("\\usepackage[margin=0.1in]{geometry}\n")
f.write("\\begin{document}\n")
f.write("\\begin{table}[htbp]\n")
f.write("	\centering\n")
f.write("\\resizebox{\\textwidth}{!}{%\n")
f.write("   \\begin{tabular}{c c c c c c c c c c c}\n")
f.write("   \\toprule\n")
f.write("   $\eta$ & R$_9$ & R/R$_0$ & Num Photons & Num Electrons & $\langle E_{\gamma} \\rangle$ & $\sigma_{\gamma}$ & $\langle E_{e} \\rangle$ & $\sigma_{\gamma}$ & systematic [\%] & error [\%] \\\\ \hline\n")

thisFile = pd.read_csv(opts.inputFile, sep=" ")
thisFile = np.matrix(thisFile)

for row in thisFile:
    row = np.ravel(row)
    f.write(" %f $<$ $\mid\eta\mid$ $<$ %f & %f $<$ R$_{9}$ $<$ %f & %f & %i & %i & %f & %f & %f & %f & %f & %f \\\\ \hline \n" % (row[1], row[2], row[3], row[4], row[6], row[8], row[11], row[7], row[9], row[10], row[12], row[13], row[14]))

f.write("\end{tabular}\n}\n\end{table}\n\end{document}")
f.close()
