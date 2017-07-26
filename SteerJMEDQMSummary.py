import os 
import sys 

## to download the files run
#python -m webbrowser -t  "https://cmsweb.cern.ch/dqm/offline/data/browse/ROOT/OfflineData/Run2017/JetHT/0002974xx/DQM_V0001_R000297467__JetHT__Run2017B-PromptReco-v1__DQMIO.root"

variable = '\\"JetMET/Run\ summary/Jet/Cleanedak4PFJets/CHEn_lowPt_EndCap\\"'
print  ('root -l -b -q AUXJMEDQMSummary.C\(\\"rootfiles.txt\\",'+variable+'\)')
os.system  ('root -l -b -q AUXJMEDQMSummary.C\(\\"rootfiles.txt\\",'+variable+'\)')

#os.system ('root -l -b -q AUXJMEDQMSummary.C\(\\"rootfiles.txt\\",\\"JetMET/Run\ summary/Jet/Cleanedak4PFJets/CHEn_lowPt_EndCap\\"\)')
