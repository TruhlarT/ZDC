#include <string>

void plotVoltages()
{
  std::string runNumber = "22180018";
  TFile *inf1 = new TFile(("../run21.ZdcCalibration.truhlar/analysis/"  + runNumber + "/" + runNumber + "_my_zdc_result_file.root").data());
  TFile *inf2 = new TFile(("../run21.ZdcCalibration.truhlar/analysis/"  + runNumber + "/" + runNumber + "_my_zdc_result_file.root").data());
  TFile *inf3 = new TFile(("../run21.ZdcCalibration.truhlar/analysis/"  + runNumber + "/" + runNumber + "_my_zdc_result_file.root").data());

  TCanvas *C1 = new TCanvas("C1", "east", 600, 400);

  TH1D *hEast1 = (TH1D*)inf1->Get("ZDC_ADC_east_sum");
  TH1D *hEast2 = (TH1D*)inf2->Get("ZDC_ADC_east_sum");
  TH1D *hEast3 = (TH1D*)inf3->Get("ZDC_ADC_east_sum");

  hEast2->SetLineColor(kRed);
  hEast3->SetLineColor(kBlue);

  hEast1->GetXaxis()->SetTitle("ADC sum east [-]");

  hEast1->GetYaxis()->SetTitle("N [-]");
  hEast1->GetYaxis()->SetTitleOffset(1.1);

  C1->cd();
  hEast1->Draw();
  hEast2->Draw("same");
  hEast3->Draw("same");

}
