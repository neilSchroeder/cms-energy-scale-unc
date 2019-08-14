import sys
import os
import pandas as pd
import numpy as np
import uproot

"""...function which produces csv file containing data from the provided root files..."""
def produce_Histograms( thisFile, outDir, outFile):
    print()
    print("[INFO] Beginning of analysis ")

    """...time to declare some variables..."""
    numR9bins=5
    r9Bins=[0, 0.8, 0.9, 0.92, 0.96, 1.00]

    numEtaBins=8
    etaBins=[0, 0.3, 0.7, 1.1, 1.4442, 1.566, 1.8, 2.1, 2.5]

    laserRespBins=100

    """...this dictionary will hold all of our information..."""
    myArrayCollection = {}


    """...read in the files with pandas and convert it to a matrix..."""
    theseFiles = pd.read_csv(thisFile, header=0, names=["fileNames"], dtype={"fileNames":str})
    theseFiles = np.matrix(theseFiles)

    elePho = ""
    electrons = True

    """...loop over the files..."""
    for key in theseFiles:
        fileName = np.ravel(key)[0] 
        if fileName.find("eGun") != -1: elePho = "electrons"+fileName[int(fileName.find("eGun")+4):int(fileName.find("eGun")+7)]+".dat"
        if fileName.find("gGun") != -1:
            elePho = "photons"+fileName[int(fileName.find("gGun")+4):int(fileName.find("gGun")+7)]+".dat"
            electrons = False

        """...read the root file using uproot..."""
        rootDir = uproot.rootio.open(fileName)
        myTree = rootDir.get("ntuples/data")
        en_default = myTree.array("Rechit_Energy_Sum_1")
        en_updated1 = myTree.array("apd_lce_RecHitSums1")
        en_updated2 = myTree.array("apd_lce_RecHitSums2")
        r9 = myTree.array("Full_5x5_R9")
        eta = myTree.array("Super_Cluster_Eta")
        dR = myTree.array("dR")
        en_def_1 = []
        en_def_2 = []
        for iii in range(0, 5000):
            a = []
            b = []
            for jjj in range(0,100):
                a.append(en_default[iii,0])
                b.append(en_default[iii,1])

            en_def_1.append(a)
            en_def_2.append(b)

        en_def_1 = np.matrix(en_def_1)
        en_def_2 = np.matrix(en_def_2)
        en_updated1 = np.divide(en_updated1, en_def_1)
        en_updated2 = np.divide(en_updated2, en_def_2)
        """...loop over events (there should be a faster way to do this, talk to David)..."""
        for event in range(0,en_updated1.shape[0]):
            etaIndex1 = -999
            etaIndex2 = -999
            r9Index1 = -999
            r9Index2 = -999
            if dR[event][0] != 999:
                for i in range(0, len(etaBins)-1): 
                    if eta[event][0] > etaBins[i] and eta[event][0] < etaBins[i+1]: etaIndex1 = i

                for i in range(0, len(r9Bins)-1):
                    if r9[event][0] > r9Bins[i] and r9[event][0] < r9Bins[i+1]: r9Index1 = i

            if dR[event][1] != 999:
                for i in range(0, len(etaBins)-1): 
                    if eta[event][1] > etaBins[i] and eta[event][1] < etaBins[i+1]: etaIndex2 = i

                for i in range(0, len(r9Bins)-1):
                    if r9[event][1] > r9Bins[i] and r9[event][1] < r9Bins[i+1]: r9Index2 = i

            """...event selection time..."""
            if etaIndex1 != -999 and r9Index1 != -999:
                eta_key = "absEta_"+str(etaBins[etaIndex1])+"_"+str(etaBins[etaIndex1+1])+"-"
                r9_key =  "r9_"+str(r9Bins[r9Index1])+"_"+str(r9Bins[r9Index1+1])+"-"
                apd_up = ""
                apd_down = ""
                for val in range(0,laserRespBins):
                    if val == 0: 
                        apd_up = "1.005"
                        apd_down = "0.995"
                    else:
                        apd_up = apd_down
                        apd_down = "0."+str(f'{(99-val):02}')+"5"

                    apd_key = "laserResp_"+apd_down+"_"+apd_up
                    this_key = "e-" 
                    if not electrons: this_key = "g-"
                    this_key += eta_key+r9_key+apd_key
                    if this_key in myArrayCollection: myArrayCollection[this_key].append(en_updated1[event,val])
                    else: myArrayCollection.update({this_key : [en_updated1[event,val]]})

            if etaIndex2 != -999 and r9Index2 != -999:
                eta_key = "absEta_"+str(etaBins[etaIndex2])+"_"+str(etaBins[etaIndex2+1])+"-"
                r9_key =  "r9_"+str(r9Bins[r9Index2])+"_"+str(r9Bins[r9Index2+1])+"-"
                apd_up = ""
                apd_down = ""
                for val in range(0,laserRespBins):
                    if val == 0: 
                        apd_up = "1.005"
                        apd_down = "0.995"
                    else:
                        apd_up = apd_down
                        apd_down = "0."+str(f'{(99-val):02}')+"5"

                    apd_key = "laserResp_"+apd_down+"_"+apd_up
                    this_key = "e-"
                    if not electrons: this_key = "g-"
                    this_key += eta_key+r9_key+apd_key
                    if this_key in myArrayCollection: myArrayCollection[this_key].append(en_updated2[event,val])
                    else: myArrayCollection.update({this_key : [en_updated2[event,val]]})
    

    """...now we need to print the information into dat files..."""
    f = open(outDir+"/"+outFile+"_"+elePho,"w+")
    print(outDir+"/"+outFile+"_"+elePho)
    for key in myArrayCollection:
        f.write(key+".dat")
        if not os.path.isdir(outDir+"/dat/"): os.system("mkdir "+outDir+"/dat/")
        f1 = open(outDir+"/dat/"+key+".dat","w+")
        for entry in myArrayCollection[key]:
            if entry != myArrayCollection[key][-1]: f1.write("%f," % entry)
            else: f1.write("%f\n" % entry)

        f1.close()

    f.close()

    return outDir+outFile+elePho


