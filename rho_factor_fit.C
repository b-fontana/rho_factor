#include <iostream>
#include <fstream>
using namespace std;

//MINE
#include "commonVar.h"
#include "calcPol.C"

//ROOT
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2.h"
#include "TMath.h"
#include "TF2.h"
#include "TGraphErrors.h"
#include "TLine.h"
#include "TLegend.h"

#define RHO_FACTOR_HISTOGRAM_NUMBER 26

void rho_factor_fit () {

  gROOT->Reset();
  gROOT->SetBatch();
  TFile *file = new TFile("rho_factor_histograms.root", "READ");

  Long_t Types = 3, Rap_bins = 2, Pt_bins = 13;
  Double_t ****lambdas = new Double_t***[2];
  for (Long_t i=0; i<2; ++i) { 
    //i=0: lambda value, i=1: lambda error.
    lambdas[i] = new Double_t**[Types];
    for (Long_t j=0; j<Types; ++j) {
      //Types - 0: lambda_theta; 1: lambda_phi; 2: lambda_thetaphi 
      lambdas[i][j] = new Double_t*[Rap_bins];
      for (Long_t k=0; k<Rap_bins; ++k) {
	//Rap_bins - 0: 0<=|y|<0.6; 1: 0.6<|y|<1.2
	lambdas[i][j][k] = new Double_t[Pt_bins];
      }
    }
  }

  TF2 *fit_function = new TF2("fit_function", "[0]*(1.+[1]*x[0]*x[0]+[2]*(1.-x[0]*x[0])*cos(2.*x[1]*0.0174532925)+[3]*2.*x[0]*sqrt(1.-x[0]*x[0])*cos(x[1]*0.0174532925))", -1., 1., -180., 180. );
  fit_function->SetParameters(1.,0.,0.,0.);

  TString string_a = "rho_eff_MCtruth_PHX_pt";
  TString string_b = "_rap";
  
  TH2D **histo_rho = new TH2D*[RHO_FACTOR_HISTOGRAM_NUMBER];

  for (Long_t i=0; i<Types; ++i) {
    for (Long_t j=0; j<Rap_bins; ++j) {
      Long_t j_plus_one = j+1;
      for (Long_t k=1; k<=Pt_bins; ++k) {
	if (j==0) {
	  histo_rho[k-1] = (TH2D*)file->Get(string_a + k + string_b + j_plus_one);
	  histo_rho[k-1]->Fit("fit_function");
	}
	else if (j==1) {
	  histo_rho[k-1+Pt_bins] = (TH2D*)file->Get(string_a + k + string_b + j_plus_one);
          histo_rho[k-1+Pt_bins]->Fit("fit_function");
	}
	else {
	  cout << "ERROR!" << endl;
	}
	lambdas[0][i][j][k-1] = fit_function->GetParameter(i+1);
	lambdas[1][i][j][k-1] = fit_function->GetParError(i+1);
      }
    }
  }

  gStyle->SetTitleOffset(1.2, "x");
  gStyle->SetTitleOffset(1.2, "y");
  gPad->SetFillColor(kWhite);
  gPad->SetTopMargin(0.1);
  gPad->SetRightMargin(0.175);
  gPad->SetLeftMargin(0.15);

  TString *y_title = new TString[Types];
  y_title[0]="#lambda_{#theta}^{PX}";
  y_title[1]="#lambda_{#phi}^{PX}";
  y_title[2]="#lambda_{#theta #phi}^{PX}";

  TLine *line1 = new TLine(0.,0.,72.,0.);
 
  Double_t Pt_bins_central[14] = {13.,15.,17.,19.,21.,23.,25.,27.,29.,32.5,37.5,45.,60.};
  Double_t Pt_bins_error[14] = {1., 1., 1., 1., 1., 1., 1., 1., 1., 2.5, 2.5, 5., 10.};
 
  Int_t graph_counter = 0;
  Long_t graph_number = Types*Rap_bins;
  
  TGraphErrors **g = new TGraphErrors*[graph_number];
  for (Long_t i=0; i<Types; ++i) {
    for (Long_t j=0; j<Rap_bins; ++j) {
      g[graph_counter] = new TGraphErrors(13, Pt_bins_central, lambdas[0][i][j], Pt_bins_error, lambdas[1][i][j]);
      g[graph_counter]->SetTitle(0);
      g[graph_counter]->SetMarkerStyle(20);
      if (j==0) {
	g[graph_counter]->SetMarkerColor(kBlack);
	g[graph_counter]->SetMarkerStyle(20);
	g[graph_counter]->SetLineColor(kBlack);
	g[graph_counter]->SetMarkerSize(.5);
      }
      else if (j==1) {
	g[graph_counter]->SetLineColor(kRed);
	g[graph_counter]->SetMarkerColor(kRed);
	g[graph_counter]->SetMarkerStyle(24);
	g[graph_counter]->SetMarkerSize(1.);
      }
      else cout << "ERROR!" << endl;
      ++graph_counter;
    }
  }

  //writing the data of the fit to a .txt file called "fit_data.txt"
  /*ofstream FILE;
  FILE.open ("fit_data.txt");
  FILE << "Writing this to a file.\n";
  FILE.close();
  */

  TString graph = "graph";
  for(Long_t i=0; i<graph_number; ++i) {
    g[i]->SetName(graph+i);
  }

  TCanvas *canvas = new TCanvas("canvas","canvas",1000,800);
  canvas->Divide(2, 2);

  TLegend *leg =  new TLegend(0.15,0.75,0.35,0.85);

  Int_t count = 1;
  for (Long_t i=0; i<graph_number; ++i) {
    if ((i+2)%2==0) {
      canvas->cd(count);
      g[i]->Draw("AP");
      g[i]->GetXaxis()->SetTitle("p_{T} [GeV]");
      g[i]->GetYaxis()->SetTitle(y_title[count-1]);
      g[i]->GetXaxis()->SetLimits(0.,72.);
      if (i==0) {
	leg->AddEntry(graph+i,"0#leq |y|<0.6","lp");
	leg->SetTextSize(0.035);
	g[i]->SetMinimum(-8.);
	g[i]->SetMaximum(2.5);
      }
      if (i==2) {
	g[i]->SetMinimum(-.43);
	g[i]->SetMaximum(.43);
      }
      if (i==4) {
	g[i]->SetMinimum(-.6);
	g[i]->SetMaximum(.6);
      }
      g[i]->Draw("AP");
      g[i+1]->Draw("P");
      line1->SetLineColor(kGreen);
      line1->SetLineStyle(2);
      line1->Draw("same");
      canvas->Modified();
      ++count;
    }
    if (i==1) leg->AddEntry(graph+i,"0.6#leq |y|<1.2","lp");
    leg->Draw();  
  }

  /*for (Long_t i=0; i<graph_number; ++i) {
    if ((i+2)%2==0) leg->AddEntry(graph+i,"0<=|y|<0.6","lp");
    else leg->AddEntry(graph+i,"0.6<|y|<1.2","lp");
    }*/

  canvas->SaveAs("./Output/fit.pdf");
}
