void V0_AP()
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptRecoNewFinal_masspipicut_nmin220_nmax260_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
  TH2D* hAP = (TH2D*)f->Get("v0ap_masspipicut");
  TH2D* hAP_nocut = (TH2D*)f->Get("v0ap");
  TH1D* hmass_pipi = (TH1D*)f->Get("v0masspipi");
  TH1D* hmass_ee = (TH1D*)f->Get("v0massee");

  TFile* f1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptRecoNewFinal_masspipicut12_nmin220_nmax260_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
  TH2D* hAP1 = (TH2D*)f1->Get("v0ap_masspipicut");
  TH2D* hAP1_nocut = (TH2D*)f1->Get("v0ap");
  TH1D* hmass1_pipi = (TH1D*)f1->Get("v0masspipi");
  TH1D* hmass1_ee = (TH1D*)f1->Get("v0massee");

// Inv Mass pi-pi, falsely identified Ks
  
TCanvas* c = new TCanvas("c","c",800,400);
  c->Divide(2,1);
  c->cd(1);
  hmass_pipi->Draw("PE");
  //hmass_pipi->GetXaxis()->SetTitle("");
  c->cd(2);
  hmass1_pipi->Draw("PE");
  	

// Inv Mass elec-pos, falsely identified photons
 
 TCanvas* c1 = new TCanvas("c1","c1",800,400);
  c1->Divide(2,1);
  c1->cd(1);
  hmass_ee->Draw("PE");
  c1->cd(2);
  hmass1_ee->Draw("PE");

// After Cut
 
TCanvas* c2 = new TCanvas("c2","c2",800,400);
  c2->Divide(2,1);
  c2->cd(1);
  c2->GetPad(1)->SetLogz();
  hAP->Draw("colz");
  c2->cd(2);
  c2->GetPad(2)->SetLogz();
  hAP1->Draw("colz");

// Before Cut
  TCanvas* c3 = new TCanvas("c3","c3",800,400);
  c3->Divide(2,1);
  c3->cd(1);
  c3->GetPad(1)->SetLogz();
  hAP_nocut->Draw("colz");
  c3->cd(2);
  c3->GetPad(2)->SetLogz();
  hAP1_nocut->Draw("colz");

  char label_energy[2][200]={"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV","CMS pPb #sqrt{s_{NN}} = 5.02 TeV"};
    char label_energy_n[4][200]={"pPb   #sqrt{s_{NN}} = 5.02 TeV","(d) CMS pPb #sqrt{s_{NN}} = 5.02 TeV, N < 35",
                                 "(a) CMS pPb #sqrt{s_{NN}} = 5.02 TeV, 220 #leq N < 260","(b) CMS pPb #sqrt{s_{NN}} = 5.02 TeV, N < 35"};
    char label_n[2][200]={"220 #leq N_{trk} < 260","N < "};  
    char label_pt[2][200]={"1 < p^{trig}_{T} < 3 GeV/c","1 < p^{assoc}_{T} < 3 GeV/c"};
     char label_PID[3][200]={"K^{0}_{S}","#Lambda/#bar{#Lambda}","charged hadron"};
    char label_pt[2][200]={"0.6 < p_{T} < 0.8 GeV/c","1 < p_{T} < 2 GeV/c"};
//    char label_pt[2][200]={"1 < p^{trig}_{T} < 3 GeV/c","1 < p^{assoc}_{T} < 3 GeV/c"};
    char label_region[2][200]={"Long range","Short minus Long range"};
    char label_extra[6][200]={"#Lambda daughters","assumed to be #pi^{+}#pi^{-}","assumed to be e^{+}e^{-}","#Lambda Candidates","after mis ID rejection","before mis ID rejection"};	      

    TLatex *tex1= new TLatex();
    tex1->SetNDC();
    // pi-pi
    c->cd(1);
    tex1->SetTextSize(tex1->GetTextSize()*0.75);
    tex1->DrawLatex(0.2,0.84,label_pt[0]);
    tex1->DrawLatex(0.2,0.75,label_extra[0]);
    tex1->DrawLatex(0.2,0.65,label_extra[1]);
    tex1->DrawLatex(0.61,0.83,"m^{PDG}=0.4976 GeV/c^{2}");
    tex1->DrawLatex(0.61,0.77,"m^{peak}=0.4965 GeV/c^{2}");
    hmass_pipi->GetXaxis()->SetTitle("m(#pi^{+}#pi^{-}) GeV/c^{2}");
    hmass_pipi->GetXaxis()->CenterTitle();
    c->cd(2);
    tex1->DrawLatex(0.2,0.84,label_pt[1]);
    tex1->DrawLatex(0.2,0.74,label_energy_n[0]);
    tex1->DrawLatex(0.2,0.64,label_n[0]);
    tex1->DrawLatex(0.62,0.83,"m^{PDG}=0.4976 GeV/c^{2}");
    tex1->DrawLatex(0.62,0.77,"m^{peak}=0.4972 GeV/c^{2}");
    hmass1_pipi->GetXaxis()->SetTitle("m(#pi^{+}#pi^{-}) GeV/c^{2}");
    hmass1_pipi->GetXaxis()->CenterTitle();
   // e-e
    c1->cd(1);
    tex1->SetTextSize(tex1->GetTextSize()*0.75);
    tex1->DrawLatex(0.6,0.84,label_pt[0]);
    tex1->DrawLatex(0.6,0.75,label_extra[0]);
    tex1->DrawLatex(0.6,0.65,label_extra[2]);
    hmass_ee->GetXaxis()->SetTitle("m(e^{+}e^{-}) GeV/c^{2}");
    hmass_ee->GetXaxis()->CenterTitle();
    c1->cd(2);
    tex1->DrawLatex(0.2,0.84,label_pt[1]);
    tex1->DrawLatex(0.2,0.74,label_energy_n[0]);
    tex1->DrawLatex(0.2,0.64,label_n[0]);
    hmass1_ee->GetXaxis()->SetTitle("m(e^{+}e^{-}) GeV/c^{2}");
    hmass1_ee->GetXaxis()->CenterTitle();
   // AP After Cut
    c2->cd(1);
    tex1->SetTextSize(tex1->GetTextSize()*1.);
    tex1->DrawLatex(0.4,0.84,label_pt[0]);
    tex1->DrawLatex(0.4,0.75,label_extra[3]);
    tex1->DrawLatex(0.4,0.65,label_extra[4]);
    hAP->GetXaxis()->SetTitle("#alpha");
    hAP->GetXaxis()->CenterTitle();
    hAP->GetYaxis()->SetRange(0,400);
    hAP->GetYaxis()->SetTitle("q_{T} (GeV/c)");
    hAP->GetYaxis()->CenterTitle();	
    c2->cd(2);
    tex1->DrawLatex(0.4,0.84,label_pt[1]);
    tex1->DrawLatex(0.4,0.74,label_energy_n[0]);
    tex1->DrawLatex(0.4,0.64,label_n[0]);
    hAP1->GetXaxis()->SetTitle("#alpha");
    hAP1->GetXaxis()->CenterTitle();
    hAP1->GetYaxis()->SetRange(0,400);
    hAP1->GetYaxis()->SetTitle("q_{T} (GeV/c)");
    hAP1->GetYaxis()->CenterTitle();      

 // AP Before Cut
    c3->cd(1);
    tex1->SetTextSize(tex1->GetTextSize()*1.);
    tex1->DrawLatex(0.4,0.84,label_pt[0]);
    tex1->DrawLatex(0.4,0.75,label_extra[3]);
    tex1->DrawLatex(0.4,0.65,label_extra[5]);
    hAP_nocut->GetXaxis()->SetTitle("#alpha");
    hAP_nocut->GetXaxis()->CenterTitle();
    hAP_nocut->GetYaxis()->SetRange(0,400);
    hAP_nocut->GetYaxis()->SetTitle("q_{T} (GeV/c)");
    hAP_nocut->GetYaxis()->CenterTitle();
    c3->cd(2);
    tex1->DrawLatex(0.4,0.84,label_pt[1]);
    tex1->DrawLatex(0.4,0.74,label_energy_n[0]);
    tex1->DrawLatex(0.4,0.64,label_n[0]);
    hAP1_nocut->GetXaxis()->SetTitle("#alpha");
    hAP1_nocut->GetXaxis()->CenterTitle();
    hAP1_nocut->GetYaxis()->SetRange(0,400);
    hAP1_nocut->GetYaxis()->SetTitle("q_{T} (GeV/c)");
    hAP1_nocut->GetYaxis()->CenterTitle();


  SaveCanvas(c,"HI/V0","mass_pipi_Lambda");
  SaveCanvas(c1,"HI/V0","mass_ee_Lambda");
  SaveCanvas(c2,"HI/V0","AP_Lambda_cut");
  SaveCanvas(c3,"HI/V0","AP_Lambda_nocut");
}
