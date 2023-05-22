#include <string>
#include <iostream>
#include <fstream>  
#include "TString.h"
// NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
// 1  Constant     7.11954e+01   1.92490e+01   6.98087e-03  -1.45442e-05
// 2  BgConstant   1.91250e+03   3.33039e+02   8.66676e-02   1.43172e-06
// 3  BgSlope      2.24099e-02   2.98008e-03   4.67199e-07  -3.43983e-02
// 4  Yield        1.09016e+02   1.45410e+01   2.37760e-02   2.10045e-06
// 5  Mean         9.44266e+01   1.32988e+00   2.91330e-03   9.60399e-06
// 6  sigma        9.80875e+00   1.28593e+00   2.11360e-03   1.01395e-04


void plotSingleNeutron(const int runNmbr = 22180018)
{
  const std::string runNumber = Form("%i",runNmbr);
  TFile *inf1 = new TFile( ("../run23.ZdcCalibration.truhlar/analysis/" + runNumber + "/" + runNumber + "_my_zdc_result_file.root").data() );
  TString config_name = "../run23.ZdcCalibration.truhlar/analysis/" + runNumber + "/fit_parameters.in";
  std::ofstream configfile (config_name);
  if(!configfile) {cerr<<"Create data file failed !"<<endl; return;}

  TCanvas *C1 = new TCanvas("C1", "east", 600, 400);
  TCanvas *C2 = new TCanvas("C2", "west", 600, 400);

  TH1D *hEast = (TH1D*)inf1->Get("ZDC_ADC_east_sum");
  TH1D *hWest = (TH1D*)inf1->Get("ZDC_ADC_west_sum");

  TF1 *eastF = new TF1("eastF", "[0] + ([1])*(TMath::Exp(-[2]*x)) + ([3])*(TMath::Gaus(x,[4],[5],1)) + [6]*TMath::Gaus(x,2.*[4],[7],1)",50,400);
  TF1 *westF = new TF1("westF", "[0] + ([1])*(TMath::Exp(-[2]*x)) + ([3])*(TMath::Gaus(x,[4],[5],1)) + [6]*TMath::Gaus(x,2.*[4],[7],1)",50,400);

  eastF->SetParameters( -123600, 123600, -0.00001, 150500, 70, 14, 89200, 67);
  //eastF->SetParameters(  -3500, 3500, 0.00044, 15000, 80, 9.80875e+00, 5000, 10 );
  eastF->SetParName(0,"Constant");
  eastF->SetParName(1,"BgConstant");
  eastF->SetParName(2,"BgSlope");
  eastF->SetParName(3,"Yield");
  eastF->SetParName(4,"Mean");
  eastF->SetParName(5,"sigma");
  eastF->SetParName(6,"Yield Double");
  eastF->SetParName(7,"sigma Double");

  westF->SetParameters( -123600, 123600, -0.000006, 140000, 73, 19, 88000, 89);
  //westF->SetParameters( 7.11954e+01, 1.91250e+03 , 2.24099e-02, 14,  110 , 9.80875e+00 );
  westF->SetParName(0,"Constant");
  westF->SetParName(1,"BgConstant");
  westF->SetParName(2,"BgSlope");
  westF->SetParName(3,"Yield");
  westF->SetParName(4,"Mean");
  westF->SetParName(5,"sigma");
  westF->SetParName(6,"Yield Double");
  westF->SetParName(7,"sigma Double");

  hEast->Fit("eastF", "","", 10, 330);
  hWest->Fit("westF", "","", 10, 330);
  // hEast->SetAxisRange(50,180,"X");
  // hWest->SetAxisRange(50,180,"X");

  hEast->GetXaxis()->SetTitle("ADC sum east [-]");
  hWest->GetXaxis()->SetTitle("ADC sum west [-]");

  hEast->GetYaxis()->SetTitle("N [-]");
  hEast->GetYaxis()->SetTitleOffset(1.1);
  hWest->GetYaxis()->SetTitle("N [-]");
  hWest->GetYaxis()->SetTitleOffset(1.1);

  C1->cd();
  gStyle->SetOptFit(1111);
  hEast->Draw();

  C2->cd();
  gStyle->SetOptFit(1111);
  hWest->Draw();

  configfile << "EastSnpMean="<< eastF->GetParameter("Mean") <<"\n";
  configfile << "EastSnpSigma="<< eastF->GetParameter("sigma") <<"\n"; 
  configfile << "WestSnpMean="<< westF->GetParameter("Mean") <<"\n"; 
  configfile << "WestSnpSigma="<< westF->GetParameter("sigma") <<"\n"; 
  configfile.close();

  cout << "  const float eastSnpMean = "<< eastF->GetParameter("Mean") <<";" <<"\n";
  cout << "  const float eastSnpSigma = "<< eastF->GetParameter("sigma") <<";" <<"\n"; 
  cout << "  const float westSnpMean = "<< westF->GetParameter("Mean") <<";" <<"\n"; 
  cout << "  const float westSnpSigma = "<< westF->GetParameter("sigma") <<";" <<"\n"; 

  std::string eastFileName = "../run23.ZdcCalibration.truhlar/analysis/" + runNumber + "/snp" + runNumber + "east";
  C1->SaveAs( (eastFileName + ".pdf" ).data() );
  C1->SaveAs( (eastFileName + ".png" ).data() );
  C1->SaveAs( (eastFileName + ".root").data() );

  std::string westFileName = "../run23.ZdcCalibration.truhlar/analysis/" + runNumber + "/snp" + runNumber + "west";
  C2->SaveAs( (westFileName + ".pdf" ).data() );
  C2->SaveAs( (westFileName + ".png" ).data() );
  C2->SaveAs( (westFileName + ".root").data() );
}
