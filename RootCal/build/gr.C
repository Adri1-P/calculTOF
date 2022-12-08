void gr()
{
//=========Macro generated from canvas: gr/MyGraph
//=========  (Thu Nov 24 13:59:30 2022) by ROOT version 6.22/00
   TCanvas *gr = new TCanvas("gr", "MyGraph",167,159,1920,1080);
   gr->SetHighLightColor(2);
   gr->Range(-21,2.20375,21,6.46525);
   gr->SetFillColor(0);
   gr->SetBorderMode(0);
   gr->SetBorderSize(2);
   gr->SetFrameBorderMode(0);
   gr->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1[9] = {
   -14,
   -11,
   -8,
   -5,
   1,
   5,
   8,
   11,
   14};
   Double_t Graph0_fy1[9] = {
   4.869,
   4.477,
   3.407,
   2.942,
   3.046,
   2.914,
   3.559,
   4.726,
   5.755};
   TGraph *graph = new TGraph(9,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(2);
   
   TH1F *Graph_Graph01 = new TH1F("Graph_Graph01","",100,-16.8,16.8);
   Graph_Graph01->SetMinimum(2.6299);
   Graph_Graph01->SetMaximum(6.0391);
   Graph_Graph01->SetDirectory(0);
   Graph_Graph01->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph01->SetLineColor(ci);
   Graph_Graph01->GetXaxis()->SetTitle("Distance of source from the center (cm)");
   Graph_Graph01->GetXaxis()->SetLabelFont(42);
   Graph_Graph01->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01->GetXaxis()->SetTitleFont(42);
   Graph_Graph01->GetYaxis()->SetTitle("Spatial resolution FWHM (mm)");
   Graph_Graph01->GetYaxis()->SetLabelFont(42);
   Graph_Graph01->GetYaxis()->SetTitleFont(42);
   Graph_Graph01->GetZaxis()->SetLabelFont(42);
   Graph_Graph01->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph01);
   
   graph->Draw("ap");
   
   Double_t Graph1_fx2[9] = {
   -14,
   -11,
   -8,
   -5,
   1,
   5,
   8,
   11,
   14};
   Double_t Graph1_fy2[9] = {
   5.374,
   4.493,
   3.946,
   2.874,
   3.164,
   2.579,
   3.691,
   4.263,
   5.677};
   graph = new TGraph(9,Graph1_fx2,Graph1_fy2);
   graph->SetName("Graph1");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(2);
   graph->SetMarkerStyle(3);
   graph->SetMarkerSize(2);
   
   TH1F *Graph_Graph12 = new TH1F("Graph_Graph12","Graph",100,-16.8,16.8);
   Graph_Graph12->SetMinimum(2.2692);
   Graph_Graph12->SetMaximum(5.9868);
   Graph_Graph12->SetDirectory(0);
   Graph_Graph12->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph12->SetLineColor(ci);
   Graph_Graph12->GetXaxis()->SetLabelFont(42);
   Graph_Graph12->GetXaxis()->SetTitleOffset(1);
   Graph_Graph12->GetXaxis()->SetTitleFont(42);
   Graph_Graph12->GetYaxis()->SetLabelFont(42);
   Graph_Graph12->GetYaxis()->SetTitleFont(42);
   Graph_Graph12->GetZaxis()->SetLabelFont(42);
   Graph_Graph12->GetZaxis()->SetTitleOffset(1);
   Graph_Graph12->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph12);
   
   graph->Draw("pp");
   
   TLegend *leg = new TLegend(0.3501043,0.6998106,0.6498957,0.8996212,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextSize(0.03);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph0","FWHM blurring 1mm simu","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1","FWHM exp","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(3);
   entry->SetMarkerSize(2);
   entry->SetTextFont(42);
   leg->Draw();
   gr->Modified();
   gr->cd();
   gr->SetSelected(gr);
}
