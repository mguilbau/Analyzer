void diagram()
{
  TCanvas* c = new TCanvas("c","",800,400);

  TBox* b = new TBox(0.5-0.24*0.9,0.2,0.5+0.24*0.9,0.7);
  b->SetFillColor(kBlue-10);
  b->Draw();

  TBox* b1 = new TBox(0.5+0.3*0.9,0.2,0.5+0.52*0.9,0.7);
  b1->SetFillColor(kRed-10);
  b1->Draw();

  TBox* b2 = new TBox(0.5-0.52*0.9,0.2,0.5-0.3*0.9,0.7);
  b2->SetFillColor(kRed-10);
  b2->Draw();

  TBox* b3 = new TBox(0.5-0.15*0.9,0.2,0.5-0.12*0.9,0.7);
  b3->SetFillColor(kBlue-7);
  b3->Draw();

  TBox* b4 = new TBox(0.5+0.12*0.9,0.2,0.5+0.15*0.9,0.7);
  b4->SetFillColor(kBlue-7);
  b4->Draw();

  TBox* b5 = new TBox(0.5+0.44*0.9,0.2,0.5+0.5*0.9,0.7);
  b5->SetFillColor(kRed-7);
  b5->Draw();

  TLine* l = new TLine(0.5,0.19,0.5,0.73);
  l->SetLineStyle(7);
  l->Draw();
  TLine* l1 = new TLine(0.5,0.13,0.5,0.15);
  l1->Draw();
  TLine* l2 = new TLine(0.5-0.24*0.9,0.13,0.5-0.24*0.9,0.15);
  l2->Draw();
  TLine* l3 = new TLine(0.5+0.24*0.9,0.13,0.5+0.24*0.9,0.15);
  l3->Draw();
  TLine* l4 = new TLine(0.5-0.3*0.9,0.13,0.5-0.3*0.9,0.15);
  l4->Draw();
  TLine* l5 = new TLine(0.5+0.3*0.9,0.13,0.5+0.3*0.9,0.15);
  l5->Draw();
  TLine* l6 = new TLine(0.5-0.52*0.9,0.13,0.5-0.52*0.9,0.15);
  l6->Draw();
  TLine* l7 = new TLine(0.5+0.52*0.9,0.13,0.5+0.52*0.9,0.15);
  l7->Draw();
  TLine* l8 = new TLine(0.62,0.74,0.92,0.74);
  l8->Draw();
  TLine* l9 = new TLine(0.62,0.72,0.62,0.74);
  l9->Draw();
  TLine* l10 = new TLine(0.92,0.72,0.92,0.74);
  l10->Draw();
  TLine* l11 = new TLine(0.77,0.74,0.77,0.76);
  l11->Draw();

  TLine* l12 = new TLine(0.38,0.86,0.93,0.86);
  l12->Draw();
  TLine* l13 = new TLine(0.38,0.84,0.38,0.86);
  l13->Draw();
  TLine* l14 = new TLine(0.93,0.84,0.93,0.86);
  l14->Draw();
  TLine* l15 = new TLine(0.655,0.86,0.655,0.88);
  l15->Draw();

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.1);
  latex->DrawLatex(0.42,0.4,"Tracker");
  latex->DrawLatex(0.13,0.4,"HF-");
  latex->DrawLatex(0.8,0.4,"HF+");
  latex->SetTextSize(0.07);
//  latex->DrawLatex(0.475,0.75,"#eta=0");
  latex->DrawLatex(0.92,0.11-0.08,"#eta");
  latex->DrawLatex(0.37,0.415,"a");
  latex->DrawLatex(0.613,0.415,"a");
  latex->DrawLatex(0.915,0.415,"b");
  latex->SetTextSize(0.05);
  latex->DrawLatex(0.955,0.17-0.1,"5.2");
  latex->DrawLatex(0.015,0.17-0.1,"-5.2");
  latex->DrawLatex(0.758,0.17-0.1,"3.0");
  latex->DrawLatex(0.21,0.17-0.1,"-3.0");
  latex->DrawLatex(0.702,0.17-0.1,"2.4");
  latex->DrawLatex(0.265,0.17-0.1,"-2.4");
  latex->DrawLatex(0.495,0.17-0.1,"0");
//  latex->SetTextSize(0.85);
//  latex->SetTextAngle(-90);
//  latex->SetTextFont(82);
  latex->DrawLatex(0.73,0.79,"V_{n#Delta}(#eta^{a},#eta^{b})");
  latex->DrawLatex(0.61,0.91,"V_{n#Delta}(-#eta^{a},#eta^{b})");
  latex->SetTextSize(0.055);
  latex->DrawLatex(0.05,0.82,"r_{n}(#eta^{a},#eta^{b}) #equiv #frac{V_{n#Delta}(-#eta^{a},#eta^{b})}{V_{n#Delta}(#eta^{a},#eta^{b})}");

  TArrow* arrow = new TArrow(0.5-0.52*0.95,0.13,0.5+0.52*0.95,0.13,0.02,"|>");
  arrow->Draw();

  SaveCanvas(c,"HI/FactBreak","eta_fact_schematic");
}
