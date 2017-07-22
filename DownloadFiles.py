import os

runs = [299061, 299062]#, 299064, 299065, 299067, 299096, 299149, 299178, 299180, 299184, 299185, 299316, 299317, 299318, 299324, 299325, 299326]
dataset = '/JetHT/Run2017B-PromptReco-v2/DQMIO'
for run in runs:
    run_=str(run)
    
    os.system('mkdir /tmp/DQMData/')
    os.system('das_client --limit=100 --query="file dataset='+dataset+' run='+run_+' | grep file.name" | grep -v  "Showing" | grep -v -e "^[[:space:]]*$">&files.txt')
    
    for line in open('files.txt'):
        print line
        line = line.replace('"', '')
        outfilename = 'DQM_V0001_R000'+run_+'__JetHT__Run2017B-PromptReco__DQMIO.root'
        #print ('xrdcp root://cms-xrd-global.cern.ch//'+line.rstrip()+' /tmp/DQMData/file_'+run_+'.root')
        print  ('xrdcp root://cms-xrd-global.cern.ch//'+line.rstrip()+' /tmp/DQMData/'+outfilename)
        os.system ('xrdcp root://cms-xrd-global.cern.ch//'+line.rstrip()+' /tmp/DQMData/'+outfilename)

        
