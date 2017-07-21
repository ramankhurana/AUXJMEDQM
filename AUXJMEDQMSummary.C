/* 

Run this macro using 

root -l -b -q karsilastiralim.C\(\"rootfiles.txt\",\"JetMET/Run\ summary/Jet/Cleanedak4PFJets/CHEn_mediumPt_EndCap\"\)


First argument is text file with list of the rootfiles 

Secind argument is name of the variable whose summary plot is needed
*/

#include "TH2D.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TProfile.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TMultiGraph.h"
#include "TGraphErrors.h"
#include "TMinuit.h"
#include "TMatrixD.h"


#include <vector>
#include <string>
using namespace std;



std::vector<std::string> split(const std::string& text, const std::string& delims);


void AUXJMEDQMSummary(TString rootfileList, TString postname){
  //TString postname = "JetMET/Run summary/Jet/Cleanedak4PFJets/CHEn_mediumPt_EndCap";
  TCanvas *st = new TCanvas("st","compare",100,100,1200,1200);
  std::vector<std::string> lines;
  lines.clear();
  
  string line;
  
  ifstream myfile (rootfileList);
  if (myfile.is_open())
    {
      while ( getline (myfile,line) )
        {
	  cout << line << '\n';
	  lines.push_back(line);
        }
      myfile.close();
    }
  
  else cout << "Unable to open file";
  
  const int nFiles = lines.size();
  //cout<<nFiles<<endl;
  TFile* fin;
  //TH1F* h;
  
  
  for (int ii=0; ii<(int)lines.size(); ii++){
    
    // Extract the number from the rootfile 
    std::vector<std::string> str_component  = split(lines.at(ii),"_");
    TString str_component2 = std::string(str_component[2]).c_str();
    TString runnumber = str_component2.ReplaceAll("R000","");
    
    // histogram name extraction
    TString prename = "DQMData/Run "+runnumber+"/";
    TString histname_ =  prename + postname;
    
    // Read the rootfile 
    fin = new TFile(lines.at(ii).c_str());
    //fin->ls();
    
    
    // Get the histogram
    TH1F* h = (TH1F*) fin->Get(histname_);
    
    std::cout<<" run number = "<<runnumber
	     <<"  file = "<<lines.at(ii)
	     <<"  histname = "<<histname_
	     <<"  integral ="<<h->Integral()
	     <<" mean = "<<h->GetMean()
	     <<" RMS = "<<h->GetRMS()
	     <<endl;
    

    if (ii==0) h->DrawNormalized();
    if (ii>0)  h->DrawNormalized("SAME");
    
    
    fin->Close();
        
    }
    
    
    
    
}




std::vector<std::string> split(const std::string& text, const std::string& delims)
{
  std::vector<std::string> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while((end = text.find_first_of(delims, start)) != std::string::npos)
    {
      tokens.push_back(text.substr(start, end - start));
      start = text.find_first_not_of(delims, end);
    }
  if(start != std::string::npos)
    tokens.push_back(text.substr(start));

  return tokens;
}
