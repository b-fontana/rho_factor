#include <iostream>
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
#include "TCut.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2.h"
#include "TLatex.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TBenchmark.h"

//DEFINITIONS
#define HISTOGRAM_NUMBER 81
#define GRAPH_NUMBER 10
#define FILE_NUMBER 2
#define CANVAS_NUMBER 27

void rho_factor () {
  //variables used to build the histograms
  Int_t NbinX_c1 = 32., NbinY_c1 = 16.;
  Int_t Xmin_c1 = -1., Xmax_c1 = 1.;
  Int_t Ymin_c1 = -180., Ymax_c1 = 180.;
  Float_t tex_x = -0.95, tex_y = 190.; 

  //open existing files
  TFile **f=new TFile*[FILE_NUMBER];
  f[0] = new TFile("/afs/cern.ch/work/b/bfontana/onia2MuMu_tree_validation.root", "READ");
  f[1] = new TFile("/afs/cern.ch/work/b/bfontana/singleMuonEff_L3ptg2_seagulls_final.root", "READ");

  //create a new file
  TFile *f_new = new TFile("rho_factor_histograms.root","RECREATE");

  //obtain the tree stored in one of the files that was opened
  TTree *data=(TTree*)f[0]->Get("data");

  //0: cut description; 1: X axis label; 2: Y axis label
  TString **words = new TString*[3];
  for (Long_t i=0; i<3; ++i) {
    words[i] = new TString[HISTOGRAM_NUMBER];
  }
  for (Long_t i=0; i<HISTOGRAM_NUMBER; ++i) {
    words[1][i] = "Cos(Theta)";
    words[2][i] = "Phi";
  }
  words[0][0]="gen, seagulls/fiducial/mu_match/id/qual cuts applied";
  words[0][1]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied";
  words[0][2]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied";
  words[0][3]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 12<=Jpsi_Pt<14,  0<=|y|<0.6";
  words[0][4]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 12<=Jpsi_Pt<14, 0<=|y|<0.6";
  words[0][5]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 12<=Jpsi_Pt<14, 0<=|y|<0.6";
  words[0][6]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 14<=Jpsi_Pt<16, 0<=|y|<0.6";
  words[0][7]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 14<=Jpsi_Pt<16, 0<=|y|<0.6";
  words[0][8]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 14<=Jpsi_Pt<16, 0<=|y|<0.6";
  words[0][9]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 16<=Jpsi_Pt<18, 0<=|y|<0.6";
  words[0][10]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 16<=Jpsi_Pt<18, 0<=|y|<0.6";
  words[0][11]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 16<=Jpsi_Pt<18, 0<=|y|<0.6";
  words[0][12]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 18<=Jpsi_Pt<20, 0<=|y|<0.6";
  words[0][13]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 18<=Jpsi_Pt<20, 0=|y|<0.6";
  words[0][14]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 18<=Jpsi_Pt<20, 0<=|y|<0.6";
  words[0][15]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 20<=Jpsi_Pt<22, 0<=|y|<0.6";
  words[0][16]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 20<=Jpsi_Pt<22, 0<=|y|<0.6";
  words[0][17]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 20<=Jpsi_Pt<22, 0<=|y|<0.6";
  words[0][18]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 22<=Jpsi_Pt<24, 0<=|y|<0.6";
  words[0][19]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 22<=Jpsi_Pt<24, 0<=|y|<0.6";
  words[0][20]="rho factor, seagulls only, fiducial/mu_match/id/qual cuts applied, 22<=Jpsi_Pt<24, 0<=|y|<0.6";
  words[0][21]="gen, seagulls only, fiducial/mu_match/id/qual cuts applied, 24<=Jpsi_Pt<26, 0<=|y|<0.6";
  words[0][22]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 24<=Jpsi_Pt<26, 0<=|y|<0.6";
  words[0][23]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 24<=Jpsi_Pt<26, 0<=|y|<0.6";
  words[0][24]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 26<=Jpsi_Pt<28, 0<=|y|<0.6";
  words[0][25]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 26<=Jpsi_Pt<28, 0<=|y|<0.6";
  words[0][26]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 26<=Jpsi_Pt<28, 0<=|y|<0.6";
  words[0][27]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 28<=Jpsi_Pt<30, 0<=|y|<0.6";
  words[0][28]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 28<=Jpsi_Pt<30, 0<=|y|<0.6";
  words[0][29]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 28<=Jpsi_Pt<30, 0<=|y|<0.6";
  words[0][30]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 30<=Jpsi_Pt<35, 0<=|y|<0.6";
  words[0][31]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 30<=Jpsi_Pt<35, 0<=|y|<0.6";
  words[0][32]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 30<=Jpsi_Pt<35, 0<=|y|<0.6";
  words[0][33]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 35<=Jpsi_Pt<40, 0<=|y|<0.6";
  words[0][34]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 35<=Jpsi_Pt<40, 0<=|y|<0.6";
  words[0][35]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 35<=Jpsi_Pt<40, 0<=|y|<0.6";
  words[0][36]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 40<=Jpsi_Pt<50, 0<=|y|<0.6";
  words[0][37]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 40<=Jpsi_Pt<50, 0<=|y|<0.6";
  words[0][38]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 40<=Jpsi_Pt<50, 0<=|y|<0.6";
  words[0][39]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 50<=Jpsi_Pt<70, 0<=|y|<0.6";
  words[0][40]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 50<=Jpsi_Pt<70, 0<=|y|<0.6";
  words[0][41]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 50<=Jpsi_Pt<70, 0<=|y|<0.6";
  words[0][42]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 12<=Jpsi_Pt<14,  0.6<=|y|<1.2";
  words[0][43]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 12<=Jpsi_Pt<14, 0.6<=|y|<1.2";
  words[0][44]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 12<=Jpsi_Pt<14, 0.6<=|y|<1.2";
  words[0][45]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 14<=Jpsi_Pt<16, 0.6<=|y|<1.2";
  words[0][46]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 14<=Jpsi_Pt<16, 0.6<=|y|<1.2";
  words[0][47]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 14<=Jpsi_Pt<16, 0.6<=|y|<1.2";
  words[0][48]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 16<=Jpsi_Pt<18, 0.6<=|y|<1.2";
  words[0][49]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 16<=Jpsi_Pt<18, 0.6<=|y|<1.2";
  words[0][50]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 16<=Jpsi_Pt<18, 0.6<=|y|<1.2";
  words[0][51]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 18<=Jpsi_Pt<20, 0.6<=|y|<1.2";
  words[0][52]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 18<=Jpsi_Pt<20, 0.6<=|y|<1.2";
  words[0][53]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 18<=Jpsi_Pt<20, 0.6<=|y|<1.2";
  words[0][54]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 20<=Jpsi_Pt<22, 0.6<=|y|<1.2";
  words[0][55]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 20<=Jpsi_Pt<22, 0.6<=|y|<1.2";
  words[0][56]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 20<=Jpsi_Pt<22, 0.6<=|y|<1.2";
  words[0][57]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 22<=Jpsi_Pt<24, 0.6<=|y|<1.2";
  words[0][58]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 22<=Jpsi_Pt<24, 0.6<=|y|<1.2";
  words[0][59]="rho factor, seagulls only, fiducial/mu_match/id/qual cuts applied, 22<=Jpsi_Pt<24, 0.6<=|y|<1.2";
  words[0][60]="gen, seagulls only, fiducial/mu_match/id/qual cuts applied, 24<=Jpsi_Pt<26, 0.6<=|y|<1.2";
  words[0][61]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 24<=Jpsi_Pt<26, 0.6<=|y|<1.2";
  words[0][62]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 24<=Jpsi_Pt<26, 0.6<=|y|<1.2";
  words[0][63]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 26<=Jpsi_Pt<28, 0.6<=|y|<1.2";
  words[0][64]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 26<=Jpsi_Pt<28, 0.6<=|y|<1.2";
  words[0][65]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 26<=Jpsi_Pt<28, 0.6<=|y|<1.2";
  words[0][66]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 28<=Jpsi_Pt<30, 0.6<=|y|<1.2";
  words[0][67]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 28<=Jpsi_Pt<30, 0.6<=|y|<1.2";
  words[0][68]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 28<=Jpsi_Pt<30, 0.6<=|y|<1.2";
  words[0][69]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 30<=Jpsi_Pt<35, 0.6<=|y|<1.2";
  words[0][70]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 30<=Jpsi_Pt<35, 0.6<=|y|<1.2";
  words[0][71]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 30<=Jpsi_Pt<35, 0.6<=|y|<1.2";
  words[0][72]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 35<=Jpsi_Pt<40, 0.6<=|y|<1.2";
  words[0][73]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 35<=Jpsi_Pt<40, 0.6<=|y|<1.2";
  words[0][74]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 35<=Jpsi_Pt<40, 0.6<=|y|<1.2";
  words[0][75]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 40<=Jpsi_Pt<50, 0.6<=|y|<1.2";
  words[0][76]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 40<=Jpsi_Pt<50, 0.6<=|y|<1.2";
  words[0][77]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 40<=Jpsi_Pt<50, 0.6<=|y|<1.2";
  words[0][78]="gen, seagulls/fiducial/mu_match/id/qual cuts applied, 50<=Jpsi_Pt<70, 0.6<=|y|<1.2";
  words[0][79]="reco + trig, weighted, seagulls/fiducial/mu_match/id/qual cuts applied, 50<=Jpsi_Pt<70, 0.6<=|y|<1.2";
  words[0][80]="rho factor, seagulls/fiducial/mu_match/id/qual cuts applied, 50<=Jpsi_Pt<70, 0.6<=|y|<1.2"; 

  TString saveChar_generic = "./Output/rho_factor_histograms_";
  TString pdf = ".pdf";
  TString *saveChar = new TString[CANVAS_NUMBER];
  for (Long_t i=0; i<CANVAS_NUMBER; ++i) {
    saveChar[i]= saveChar_generic+i+pdf;
  }
  
  TString graph_name = "gEffHybrid_MC_PT_AETA";
  TGraphAsymmErrors **g1 = new TGraphAsymmErrors*[GRAPH_NUMBER];
  for (Long_t i=0; i<GRAPH_NUMBER; ++i) {
    g1[i]=(TGraphAsymmErrors*)f[1]->Get(graph_name + i);
  }

  TString h_name = "h_";
  TH2D **h = new TH2D*[HISTOGRAM_NUMBER];
  for (Long_t i=0; i<HISTOGRAM_NUMBER; ++i) {
    h[i] = new TH2D(h_name+i,h_name+i, NbinX_c1, Xmin_c1, Xmax_c1, NbinY_c1, Ymin_c1, Ymax_c1);
  }
  
  gROOT->SetBatch();

  //storing TTree data for further manipulation
  TLorentzVector *muPosP_Gen = 0;  
  data->SetBranchAddress("muPosP_Gen", &muPosP_Gen);
  TLorentzVector *muNegP_Gen = 0;
  data->SetBranchAddress("muNegP_Gen", &muNegP_Gen);
  TLorentzVector *JpsiP_Gen = 0;
  data->SetBranchAddress("JpsiP_Gen", &JpsiP_Gen);

  Int_t muPosP_id = 0;
  data->SetBranchAddress("muPosP_id", &muPosP_id);
  Int_t muNegP_id = 0;
  data->SetBranchAddress("muNegP_id", &muNegP_id);
  Int_t muPosP_qual = 0;
  data->SetBranchAddress("muPosP_qual", &muPosP_qual);
  Int_t muNegP_qual = 0;
  data->SetBranchAddress("muNegP_qual", &muNegP_qual);
  Int_t muPosP_tk_muMatch = 0;
  data->SetBranchAddress("muPosP_tk_muMatch", &muPosP_tk_muMatch);
  Int_t muNegP_tk_muMatch = 0;
  data->SetBranchAddress("muNegP_tk_muMatch", &muNegP_tk_muMatch);
  Int_t HLT_Dimuon8_Jpsi_v3 = 0;
  data->SetBranchAddress("HLT_Dimuon8_Jpsi_v3", &HLT_Dimuon8_Jpsi_v3);
  Int_t HLT_Dimuon8_Jpsi_v4 = 0;
  data->SetBranchAddress("HLT_Dimuon8_Jpsi_v4", &HLT_Dimuon8_Jpsi_v4);
  Int_t HLT_Dimuon8_Jpsi_v5 = 0;
  data->SetBranchAddress("HLT_Dimuon8_Jpsi_v5", &HLT_Dimuon8_Jpsi_v5);
  Int_t HLT_Dimuon8_Jpsi_v6 = 0;
  data->SetBranchAddress("HLT_Dimuon8_Jpsi_v6", &HLT_Dimuon8_Jpsi_v6);
  Int_t HLT_Dimuon8_Jpsi_v7 = 0;
  data->SetBranchAddress("HLT_Dimuon8_Jpsi_v7", &HLT_Dimuon8_Jpsi_v7);

  //number of entriees of tree
  Int_t n_events = Int_t(data->GetEntries()); 

  //efficiencies
  Double_t e1 = 1., e2 = 1., e_product = 1.;

  //looping through all events in the tree
  for (Int_t i_event=1; i_event <= n_events; i_event++) {
    data->GetEvent(i_event-1);
  
    //cuts
    Bool_t Fid = ((TMath::Abs(muPosP_Gen->Eta())<1.2 && muPosP_Gen->Pt()>4.5) || (TMath::Abs(muPosP_Gen->Eta())>1.2 && TMath::Abs(muPosP_Gen->Eta())<1.4 && muPosP_Gen->Pt()>3.5) || (TMath::Abs(muPosP_Gen->Eta())>1.4 && TMath::Abs(muPosP_Gen->Eta())<1.6 && muPosP_Gen->Pt()>3.)) && ((TMath::Abs(muNegP_Gen->Eta())<1.2 && muNegP_Gen->Pt()>4.5) || (TMath::Abs(muNegP_Gen->Eta())>1.2 && TMath::Abs(muNegP_Gen->Eta())<1.4 && muNegP_Gen->Pt()>3.5) || (TMath::Abs(muNegP_Gen->Eta())>1.4 && TMath::Abs(muNegP_Gen->Eta())<1.6 && muNegP_Gen->Pt()>3.));
    Bool_t muMatch =  muPosP_tk_muMatch==1 && muNegP_tk_muMatch==1;
    Bool_t Seagull =  (muNegP_Gen->Phi() - muPosP_Gen->Phi()) > 0 && (muNegP_Gen->Phi() - muPosP_Gen->Phi()) < TMath::Pi();
    Bool_t Jpsi_12_14 = JpsiP_Gen->Pt()>=12 && JpsiP_Gen->Pt()<14;
    Bool_t Jpsi_14_16 = JpsiP_Gen->Pt()>=14 && JpsiP_Gen->Pt()<16;
    Bool_t Jpsi_16_18 = JpsiP_Gen->Pt()>=16 && JpsiP_Gen->Pt()<18;
    Bool_t Jpsi_18_20 = JpsiP_Gen->Pt()>=18 && JpsiP_Gen->Pt()<20;
    Bool_t Jpsi_20_22 = JpsiP_Gen->Pt()>=20 && JpsiP_Gen->Pt()<22;
    Bool_t Jpsi_22_24 = JpsiP_Gen->Pt()>=22 && JpsiP_Gen->Pt()<24;
    Bool_t Jpsi_24_26 = JpsiP_Gen->Pt()>=24 && JpsiP_Gen->Pt()<26;
    Bool_t Jpsi_26_28 = JpsiP_Gen->Pt()>=26 && JpsiP_Gen->Pt()<28;
    Bool_t Jpsi_28_30 = JpsiP_Gen->Pt()>=28 && JpsiP_Gen->Pt()<30;
    Bool_t Jpsi_30_35 = JpsiP_Gen->Pt()>=30 && JpsiP_Gen->Pt()<35;
    Bool_t Jpsi_35_40 = JpsiP_Gen->Pt()>=35 && JpsiP_Gen->Pt()<40;
    Bool_t Jpsi_40_50 = JpsiP_Gen->Pt()>=40 && JpsiP_Gen->Pt()<50;
    Bool_t Jpsi_50_70 = JpsiP_Gen->Pt()>=50 && JpsiP_Gen->Pt()<70;
    Bool_t Id_qual = muPosP_id == 1 && muPosP_qual == 1 && muNegP_id == 1 && muNegP_qual == 1;
    Bool_t Triggers = HLT_Dimuon8_Jpsi_v3==1 || HLT_Dimuon8_Jpsi_v4==1 || HLT_Dimuon8_Jpsi_v5==1 || HLT_Dimuon8_Jpsi_v6==1 || HLT_Dimuon8_Jpsi_v7==1;
    Bool_t Eta_Pos_00_02 = TMath::Abs(muPosP_Gen->Eta())>=0. && TMath::Abs(muPosP_Gen->Eta())<0.2;
    Bool_t Eta_Pos_02_03 = TMath::Abs(muPosP_Gen->Eta())>=0.2 && TMath::Abs(muPosP_Gen->Eta())<0.3;
    Bool_t Eta_Pos_03_06 = TMath::Abs(muPosP_Gen->Eta())>=0.3 && TMath::Abs(muPosP_Gen->Eta())<0.6;
    Bool_t Eta_Pos_06_08 = TMath::Abs(muPosP_Gen->Eta())>=0.6 && TMath::Abs(muPosP_Gen->Eta())<0.8;
    Bool_t Eta_Pos_08_10 = TMath::Abs(muPosP_Gen->Eta())>=0.8 && TMath::Abs(muPosP_Gen->Eta())<1.;
    Bool_t Eta_Pos_10_12 = TMath::Abs(muPosP_Gen->Eta())>=1. && TMath::Abs(muPosP_Gen->Eta())<1.2;
    Bool_t Eta_Pos_12_14 = TMath::Abs(muPosP_Gen->Eta())>=1.2 && TMath::Abs(muPosP_Gen->Eta())<1.4;
    Bool_t Eta_Pos_14_16 = TMath::Abs(muPosP_Gen->Eta())>=1.4 && TMath::Abs(muPosP_Gen->Eta())<1.6;
    Bool_t Eta_Pos_16_18 = TMath::Abs(muPosP_Gen->Eta())>=1.6 && TMath::Abs(muPosP_Gen->Eta())<1.8;
    Bool_t Eta_Pos_18_20 = TMath::Abs(muPosP_Gen->Eta())>=1.8 && TMath::Abs(muPosP_Gen->Eta())<2.;
    Bool_t Eta_Neg_00_02 = TMath::Abs(muNegP_Gen->Eta())>=0. && TMath::Abs(muNegP_Gen->Eta())<0.2;
    Bool_t Eta_Neg_02_03 = TMath::Abs(muNegP_Gen->Eta())>=0.2 && TMath::Abs(muNegP_Gen->Eta())<0.3;
    Bool_t Eta_Neg_03_06 = TMath::Abs(muNegP_Gen->Eta())>=0.3 && TMath::Abs(muNegP_Gen->Eta())<0.6;
    Bool_t Eta_Neg_06_08 = TMath::Abs(muNegP_Gen->Eta())>=0.6 && TMath::Abs(muNegP_Gen->Eta())<0.8;
    Bool_t Eta_Neg_08_10 = TMath::Abs(muNegP_Gen->Eta())>=0.8 && TMath::Abs(muNegP_Gen->Eta())<1.;
    Bool_t Eta_Neg_10_12 = TMath::Abs(muNegP_Gen->Eta())>=1. && TMath::Abs(muNegP_Gen->Eta())<1.2;
    Bool_t Eta_Neg_12_14 = TMath::Abs(muNegP_Gen->Eta())>=1.2 && TMath::Abs(muNegP_Gen->Eta())<1.4;
    Bool_t Eta_Neg_14_16 = TMath::Abs(muNegP_Gen->Eta())>=1.4 && TMath::Abs(muNegP_Gen->Eta())<1.6;
    Bool_t Eta_Neg_16_18 = TMath::Abs(muNegP_Gen->Eta())>=1.6 && TMath::Abs(muNegP_Gen->Eta())<1.8;
    Bool_t Eta_Neg_18_20 = TMath::Abs(muNegP_Gen->Eta())>=1.8 && TMath::Abs(muNegP_Gen->Eta())<2.;
    Bool_t Rapidity_1 = TMath::Abs(JpsiP_Gen->Rapidity())>=0. && TMath::Abs(JpsiP_Gen->Rapidity())<0.6;
    Bool_t Rapidity_2 = TMath::Abs(JpsiP_Gen->Rapidity())>=0.6 && TMath::Abs(JpsiP_Gen->Rapidity())<1.2;

    calcPol(*muPosP_Gen,*muNegP_Gen);

    //print to check that the program is running

    if (i_event%1000000==0) cout << "event number: " << i_event << endl;

    //filling the gen histograms, using pt and rapidity bins    
    Double_t costheta_onia = thisCosTh[onia::PHX];
    Double_t phi_onia = thisPhi[onia::PHX];

    if (Fid && muMatch && Seagull) {
      h[0]->Fill(costheta_onia, phi_onia);
      if (Jpsi_12_14) {
	if (Rapidity_1) h[3]->Fill(costheta_onia, phi_onia);
	else if (Rapidity_2) h[42]->Fill(costheta_onia, phi_onia);
      }
      else if (Jpsi_14_16) {
	if (Rapidity_1) h[6]->Fill(costheta_onia, phi_onia);
        else if (Rapidity_2) h[45]->Fill(costheta_onia, phi_onia);
      }
      else if (Jpsi_16_18) {
	if (Rapidity_1) h[9]->Fill(costheta_onia, phi_onia);
	else if (Rapidity_2) h[48]->Fill(costheta_onia, phi_onia);
      }
      else if (Jpsi_18_20) {
	if (Rapidity_1) h[12]->Fill(costheta_onia, phi_onia);
	else if (Rapidity_2) h[51]->Fill(costheta_onia, phi_onia);
      }
      else if (Jpsi_20_22) {
	if (Rapidity_1) h[15]->Fill(costheta_onia, phi_onia);
	else if (Rapidity_2) h[54]->Fill(costheta_onia, phi_onia);
      }
      else if (Jpsi_22_24) {
	if (Rapidity_1) h[18]->Fill(costheta_onia, phi_onia);
	else if (Rapidity_2) h[57]->Fill(costheta_onia, phi_onia);
      }
      else if (Jpsi_24_26) {
	if (Rapidity_1) h[21]->Fill(costheta_onia, phi_onia);
	else if (Rapidity_2) h[60]->Fill(costheta_onia, phi_onia);
      }
      else if (Jpsi_26_28) {
	if (Rapidity_1) h[24]->Fill(costheta_onia, phi_onia);
	else if (Rapidity_2) h[63]->Fill(costheta_onia, phi_onia);
      }
      else if (Jpsi_28_30) {
	if (Rapidity_1) h[27]->Fill(costheta_onia, phi_onia);
	else if (Rapidity_2) h[66]->Fill(costheta_onia, phi_onia);
      }
      else if (Jpsi_30_35) {
	if (Rapidity_1) h[30]->Fill(costheta_onia, phi_onia);
	else if (Rapidity_2) h[69]->Fill(costheta_onia, phi_onia);
      }
      else if (Jpsi_35_40) {
	if (Rapidity_1) h[33]->Fill(costheta_onia, phi_onia);
	else if (Rapidity_2) h[72]->Fill(costheta_onia, phi_onia);
      }
      else if (Jpsi_40_50) {
	if (Rapidity_1) h[36]->Fill(costheta_onia, phi_onia);
	else if (Rapidity_2) h[75]->Fill(costheta_onia, phi_onia);
      }
      else if (Jpsi_50_70) {
	if (Rapidity_1) h[39]->Fill(costheta_onia, phi_onia);
	else if (Rapidity_2) h[78]->Fill(costheta_onia, phi_onia);
      }
    }

    //filling the reco + trig histograms, which are weighted by the efficiencies in order to get the rho factor
    //pt and rapidity bins are used
    if (Fid && muMatch && Seagull && Id_qual && Triggers) {
      if (Eta_Pos_00_02) e1=g1[0]->Eval(muPosP_Gen->Pt());
      else if (Eta_Pos_02_03) e1=g1[1]->Eval(muPosP_Gen->Pt());
      else if (Eta_Pos_03_06) e1=g1[2]->Eval(muPosP_Gen->Pt());
      else if (Eta_Pos_06_08) e1=g1[3]->Eval(muPosP_Gen->Pt());
      else if (Eta_Pos_08_10) e1=g1[4]->Eval(muPosP_Gen->Pt());
      else if (Eta_Pos_10_12) e1=g1[5]->Eval(muPosP_Gen->Pt());
      else if (Eta_Pos_12_14) e1=g1[6]->Eval(muPosP_Gen->Pt());
      else if (Eta_Pos_14_16) e1=g1[7]->Eval(muPosP_Gen->Pt());
      else if (Eta_Pos_16_18) e1=g1[8]->Eval(muPosP_Gen->Pt());
      else if (Eta_Pos_18_20) e1=g1[9]->Eval(muPosP_Gen->Pt());
      else cout << "An error has ocurred while performing g1[]->Eval() for the positive muon." << endl;

      if (Eta_Neg_00_02) e2=g1[0]->Eval(muNegP_Gen->Pt());
      else if (Eta_Neg_02_03) e2=g1[1]->Eval(muNegP_Gen->Pt());
      else if (Eta_Neg_03_06) e2=g1[2]->Eval(muNegP_Gen->Pt());
      else if (Eta_Neg_06_08) e2=g1[3]->Eval(muNegP_Gen->Pt());
      else if (Eta_Neg_08_10) e2=g1[4]->Eval(muNegP_Gen->Pt());
      else if (Eta_Neg_10_12) e2=g1[5]->Eval(muNegP_Gen->Pt());
      else if (Eta_Neg_12_14) e2=g1[6]->Eval(muNegP_Gen->Pt());
      else if (Eta_Neg_14_16) e2=g1[7]->Eval(muNegP_Gen->Pt());
      else if (Eta_Neg_16_18) e2=g1[8]->Eval(muNegP_Gen->Pt());
      else if (Eta_Neg_18_20) e2=g1[9]->Eval(muNegP_Gen->Pt());
      else cout << "An error has ocurred while performing g1[]->Eval() for the negative muon. " << endl;

      e_product = e1*e2;

      h[1]->Fill(costheta_onia, phi_onia, e_product);
      if (Jpsi_12_14) {
	if (Rapidity_1) h[4]->Fill(costheta_onia, phi_onia, e_product);
	else if (Rapidity_2) h[43]->Fill(costheta_onia, phi_onia, e_product);
      }
      else if (Jpsi_14_16) {
        if (Rapidity_1) h[7]->Fill(costheta_onia, phi_onia, e_product);
        else if (Rapidity_2) h[46]->Fill(costheta_onia, phi_onia, e_product);
      }
      else if (Jpsi_16_18) {
	if (Rapidity_1) h[10]->Fill(costheta_onia, phi_onia, e_product);
	else if (Rapidity_2) h[49]->Fill(costheta_onia, phi_onia, e_product);
      }
      else if (Jpsi_18_20) {
        if (Rapidity_1) h[13]->Fill(costheta_onia, phi_onia, e_product);
        else if (Rapidity_2) h[52]->Fill(costheta_onia, phi_onia, e_product);
      }
      else if (Jpsi_20_22) {
        if (Rapidity_1) h[16]->Fill(costheta_onia, phi_onia, e_product);
        else if (Rapidity_2) h[55]->Fill(costheta_onia, phi_onia, e_product);
      }
      else if (Jpsi_22_24) {
        if (Rapidity_1) h[19]->Fill(costheta_onia, phi_onia, e_product);
        else if (Rapidity_2) h[58]->Fill(costheta_onia, phi_onia, e_product);
      }
      else if (Jpsi_24_26) {
        if (Rapidity_1) h[22]->Fill(costheta_onia, phi_onia, e_product);
        else if (Rapidity_2) h[61]->Fill(costheta_onia, phi_onia, e_product);
      }
      else if (Jpsi_26_28) {
        if (Rapidity_1) h[25]->Fill(costheta_onia, phi_onia, e_product);
        else if (Rapidity_2) h[64]->Fill(costheta_onia, phi_onia, e_product);
      }
      else if (Jpsi_28_30) {
        if (Rapidity_1) h[28]->Fill(costheta_onia, phi_onia, e_product);
        else if (Rapidity_2) h[67]->Fill(costheta_onia, phi_onia, e_product);
      }
      else if (Jpsi_30_35) {
        if (Rapidity_1) h[31]->Fill(costheta_onia, phi_onia, e_product);
        else if (Rapidity_2) h[70]->Fill(costheta_onia, phi_onia, e_product);
      }
      else if (Jpsi_35_40) {
        if (Rapidity_1) h[34]->Fill(costheta_onia, phi_onia, e_product);
        else if (Rapidity_2) h[73]->Fill(costheta_onia, phi_onia, e_product);
      }
      else if (Jpsi_40_50) {
        if (Rapidity_1) h[37]->Fill(costheta_onia, phi_onia, e_product);
        else if (Rapidity_2) h[76]->Fill(costheta_onia, phi_onia, e_product);
      }
      else if (Jpsi_50_70) {
        if (Rapidity_1) h[40]->Fill(costheta_onia, phi_onia, e_product);
        else if (Rapidity_2) h[79]->Fill(costheta_onia, phi_onia, e_product);
      }
    }

  }
  
  //create the canvas
  TString canvas = "canvas_";
  TCanvas **c = new TCanvas*[CANVAS_NUMBER];
  for (Long_t i=0; i<CANVAS_NUMBER; ++i) {
    c[i] = new TCanvas(canvas + i, canvas + i ,1000,800);
    c[i]->Divide(2,2);
  }
  gStyle->SetTitleOffset(1.4, "x");
  gStyle->SetTitleOffset(1.7, "y");

  gPad->SetFillColor(kWhite);
  gPad->SetTopMargin(0.1);
  gPad->SetRightMargin(0.175);
  gPad->SetLeftMargin(0.15);

  Int_t canvas_counter=0, pad_counter=1;
  TLatex **tex = new TLatex*[HISTOGRAM_NUMBER];
  for(Long_t i=0; i<HISTOGRAM_NUMBER; ++i) {
    tex[i] = new TLatex(tex_x,tex_y,words[0][i]);
    tex[i]->SetTextSize(0.0225);
    c[canvas_counter]->cd(pad_counter);
    if ((1+i)%3==0) {
      h[i] = (TH2D*)h[i-1]->Clone(h_name+i);
      h[i]->Divide(h[i-2]);
      ++canvas_counter;
    }
    h[i]->SetXTitle(words[1][i]);
    h[i]->SetYTitle(words[2][i]);
    h[i]->SetTitle(0);
    h[i]->SetStats(0);
    h[i]->Draw("colz");
    tex[i]->Draw("same");
    ++pad_counter;
    if (pad_counter==4) pad_counter=1;
  }
 
  for (Long_t i=0; i<CANVAS_NUMBER; ++i) { 
    c[i]->SetLogz(true);
    c[i]->SaveAs(saveChar[i]);
  }

  TString a = "rho_eff_MCtruth_PHX_pT";
  TString b = "_rap";
  Long_t rap_count = 1, pt_count = 1;
  f_new->cd();
  for (Long_t i=0; i<HISTOGRAM_NUMBER; ++i) {
    if (i==42) {
      pt_count = 1;
      rap_count = 2;
    }
    if ((i+1)%3==0 && i!=2) {
      h[i]->SetName(a+pt_count+b+rap_count);
      h[i]->Write();
      ++pt_count;
    }
  }  

  cout << "End of macro." << endl;
}
