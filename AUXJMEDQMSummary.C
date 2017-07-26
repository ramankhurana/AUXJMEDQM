/* 

Run this macro using 

root -l -b -q karsilastiralim.C\(\"rootfiles.txt\",\"JetMET/Run\ summary/Jet/Cleanedak4PFJets/CHEn_mediumPt_EndCap\"\)


First argument is text file with list of the rootfiles 

Second argument is name of the variable whose summary plot is needed
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
   // int colors[] = {1,2,3,4,5,6,7,8};
    
  std::cout<<" Now making summary plots for run number provided in the "<<rootfileList<<std::endl;

  int counter;
  
  //TString postname = "JetMET/Run summary/Jet/Cleanedak4PFJets/CHEn_mediumPt_EndCap";
  // TCanvas *st = new TCanvas("st","compare",100,100,800,600);
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
  
  TString runno[nFiles];
  double mean[nFiles];
  double RMS[nFiles];
  
  
  TLegend *leg = new TLegend(0.6269616,0.5475207,0.6837229,0.7692837,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  
  
  
  //st->SetLogy();
  //st->SetLogx();
  
  std::cout<<" before for loop"<<std::endl;

  TString pdfname;
  for (int ii=0; ii<(int)lines.size(); ii++){
    
    // Extract the number from the rootfile
    std::vector<std::string> str_component  = split(lines.at(ii),"_");
    std::vector<std::string> str_component_pdf  = split(std::string(postname),"/");
    pdfname = TString(str_component_pdf[2].c_str()) + "_" + TString(str_component_pdf[3].c_str()) + "_" + TString(str_component_pdf[4].c_str()) +".pdf";
    
    cout<<pdfname<<endl;
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
    
    std::cout<<" run number = "<<runnumber << endl
	     <<"  file = "<<lines.at(ii) << endl
	     <<"  histname = "<<histname_ << endl
	     <<"  integral ="<<h->Integral() << endl
	     <<" mean = "<<h->GetMean() << endl
	     <<" RMS = "<<h->GetRMS()
	     <<endl;
    
    
    runno[ii] = runnumber;
    mean[ii] = h->GetMean();
    RMS[ii]= h->GetRMS();
    
    // h->SetLineColor(colors[ii]);
    
    //if (ii==0) h->DrawNormalized();
    //if (ii>0)  h->DrawNormalized("SAME");
    
      
    //leg->AddEntry(h,prename,"l");
    //leg->Draw();
    //cout << ii << endl << endl ;
    
    //st->SaveAs("test.pdf");
    
    
    
    fin->Close();
    
  }
  

    TCanvas *c1 = new TCanvas("c1","demo bin labels",800,800);
    c1->SetGrid();
    c1->SetLeftMargin(0.15);
    c1->SetBottomMargin(0.15);
    TH2F *h1 = new TH2F("h1","Mean Values",(nFiles+1)*16,0,(nFiles+1),24000,0,2400);
    for (Int_t i=1;i<(nFiles+1);i++) {
      cout << mean[i] << endl;
      h1->Fill(i, mean[i-1]);
    }
    h1->SetStats(0);
    h1->GetXaxis()->SetLabelOffset(99);
    //h1->GetYaxis()->SetLabelOffset(99);
    h1->SetMarkerStyle(20);
    h1->Draw("p");

    // draw labels along X
    Float_t x, y;
    y = gPad->GetUymin() - 63*h1->GetYaxis()->GetBinWidth(1);
    TText t;
    t.SetTextAngle(60);
    t.SetTextSize(0.02);
    t.SetTextAlign(33);
    for (i=1;i<(nFiles+1);i++) {
      x = h1->GetXaxis()->GetBinCenter(i+1);
      t.DrawText(i,y,runno[i-1]);
    }
    c1->SaveAs("Plots/mean_"+pdfname);
    
      
    TCanvas *c2 = new TCanvas("c2","demoo",800,800);
    c2->SetGrid();
    c2->SetLeftMargin(0.15);
    c2->SetBottomMargin(0.15);
    TH2F *h2 = new TH2F("h2","RMS",(nFiles+1)*16,0,(nFiles+1),6000,0,600);
    for (Int_t i=1;i<(nFiles+1);i++) {
      cout << RMS[i] << endl;
      h2->Fill(i, RMS[i-1]);
    }
    h2->SetStats(0);
    h2->GetXaxis()->SetLabelOffset(99);
    //h1->GetYaxis()->SetLabelOffset(99);
    h2->SetMarkerStyle(20);
    h2->Draw("p");
    // draw labels along X
    
    
    //  Float_t x, y;
    y = gPad->GetUymin() - 0.2*h1->GetYaxis()->GetBinWidth(1);
    //TText t;
    t.SetTextAngle(60);
    t.SetTextSize(0.02);
    t.SetTextAlign(33);
    for (i=1;i<(nFiles+1);i++) {
      x = h2->GetXaxis()->GetBinCenter(i+1);
      t.DrawText(i,y,runno[i-1]);
    }
    c2->SaveAs("Plots/rms_"+pdfname);
    
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
