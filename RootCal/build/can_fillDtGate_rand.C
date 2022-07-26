void can_fillDtGate_rand()
{
//=========Macro generated from canvas: can_fillDtGate_rand/can
//=========  (Thu Oct  6 15:21:58 2022) by ROOT version 6.22/00
   TCanvas *can_fillDtGate_rand = new TCanvas("can_fillDtGate_rand", "can",813,251,1920,1080);
   can_fillDtGate_rand->SetHighLightColor(2);
   can_fillDtGate_rand->Range(-2.5e-10,-13483.71,2.5e-10,121353.4);
   can_fillDtGate_rand->SetFillColor(0);
   can_fillDtGate_rand->SetBorderMode(0);
   can_fillDtGate_rand->SetBorderSize(2);
   can_fillDtGate_rand->SetFrameBorderMode(0);
   can_fillDtGate_rand->SetFrameBorderMode(0);
   
   TH1F *h__2 = new TH1F("h__2","h",100,-2e-10,2e-10);
   h__2->SetBinContent(0,6371);
   h__2->SetBinContent(1,31);
   h__2->SetBinContent(2,27);
   h__2->SetBinContent(3,43);
   h__2->SetBinContent(4,40);
   h__2->SetBinContent(5,64);
   h__2->SetBinContent(6,45);
   h__2->SetBinContent(7,48);
   h__2->SetBinContent(8,66);
   h__2->SetBinContent(9,71);
   h__2->SetBinContent(10,67);
   h__2->SetBinContent(11,80);
   h__2->SetBinContent(12,93);
   h__2->SetBinContent(13,137);
   h__2->SetBinContent(14,133);
   h__2->SetBinContent(15,180);
   h__2->SetBinContent(16,202);
   h__2->SetBinContent(17,263);
   h__2->SetBinContent(18,319);
   h__2->SetBinContent(19,414);
   h__2->SetBinContent(20,513);
   h__2->SetBinContent(21,645);
   h__2->SetBinContent(22,839);
   h__2->SetBinContent(23,990);
   h__2->SetBinContent(24,1264);
   h__2->SetBinContent(25,1580);
   h__2->SetBinContent(26,2073);
   h__2->SetBinContent(27,2701);
   h__2->SetBinContent(28,3534);
   h__2->SetBinContent(29,4877);
   h__2->SetBinContent(30,7445);
   h__2->SetBinContent(31,10904);
   h__2->SetBinContent(32,14326);
   h__2->SetBinContent(33,17497);
   h__2->SetBinContent(34,21262);
   h__2->SetBinContent(35,24945);
   h__2->SetBinContent(36,28636);
   h__2->SetBinContent(37,32739);
   h__2->SetBinContent(38,36736);
   h__2->SetBinContent(39,40696);
   h__2->SetBinContent(40,45101);
   h__2->SetBinContent(41,49578);
   h__2->SetBinContent(42,54547);
   h__2->SetBinContent(43,59506);
   h__2->SetBinContent(44,64487);
   h__2->SetBinContent(45,70134);
   h__2->SetBinContent(46,75535);
   h__2->SetBinContent(47,82181);
   h__2->SetBinContent(48,88701);
   h__2->SetBinContent(49,95184);
   h__2->SetBinContent(50,102657);
   h__2->SetBinContent(51,102733);
   h__2->SetBinContent(52,95288);
   h__2->SetBinContent(53,87991);
   h__2->SetBinContent(54,81661);
   h__2->SetBinContent(55,75859);
   h__2->SetBinContent(56,70099);
   h__2->SetBinContent(57,64829);
   h__2->SetBinContent(58,59659);
   h__2->SetBinContent(59,54562);
   h__2->SetBinContent(60,50020);
   h__2->SetBinContent(61,45101);
   h__2->SetBinContent(62,41061);
   h__2->SetBinContent(63,36443);
   h__2->SetBinContent(64,32526);
   h__2->SetBinContent(65,28543);
   h__2->SetBinContent(66,24916);
   h__2->SetBinContent(67,21531);
   h__2->SetBinContent(68,17960);
   h__2->SetBinContent(69,14294);
   h__2->SetBinContent(70,10850);
   h__2->SetBinContent(71,7523);
   h__2->SetBinContent(72,4853);
   h__2->SetBinContent(73,3443);
   h__2->SetBinContent(74,2723);
   h__2->SetBinContent(75,2136);
   h__2->SetBinContent(76,1671);
   h__2->SetBinContent(77,1231);
   h__2->SetBinContent(78,1071);
   h__2->SetBinContent(79,789);
   h__2->SetBinContent(80,640);
   h__2->SetBinContent(81,508);
   h__2->SetBinContent(82,419);
   h__2->SetBinContent(83,355);
   h__2->SetBinContent(84,248);
   h__2->SetBinContent(85,213);
   h__2->SetBinContent(86,184);
   h__2->SetBinContent(87,166);
   h__2->SetBinContent(88,136);
   h__2->SetBinContent(89,126);
   h__2->SetBinContent(90,95);
   h__2->SetBinContent(91,94);
   h__2->SetBinContent(92,80);
   h__2->SetBinContent(93,63);
   h__2->SetBinContent(94,51);
   h__2->SetBinContent(95,54);
   h__2->SetBinContent(96,42);
   h__2->SetBinContent(97,46);
   h__2->SetBinContent(98,47);
   h__2->SetBinContent(99,47);
   h__2->SetBinContent(100,25);
   h__2->SetBinContent(101,6256);
   h__2->SetEntries(2101768);
   
   TPaveStats *ptstats = new TPaveStats(0.7810219,0.78125,0.9807091,0.9412879,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("h");
   ptstats_LaTex->SetTextSize(0.01840436);
   ptstats_LaTex = ptstats->AddText("Entries = 2101768");
   ptstats_LaTex = ptstats->AddText("Mean  = 4.242e-14");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 3.75e-11");
   ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf = 1.737e+04 / 97");
   ptstats_LaTex = ptstats->AddText("Constant = 8.933e+04 #pm 7.611e+01 ");
   ptstats_LaTex = ptstats->AddText("Mean     = 3.009e-14 #pm 2.571e-14 ");
   ptstats_LaTex = ptstats->AddText("Sigma    = 3.701e-11 #pm 1.826e-14 ");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(1);
   ptstats->Draw();
   h__2->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(h__2);
   
   TF1 *PrevFitTMP4 = new TF1("PrevFitTMP","gaus",-2e-10,2e-10, TF1::EAddToList::kNo);
   PrevFitTMP4->SetFillColor(19);
   PrevFitTMP4->SetFillStyle(0);
   PrevFitTMP4->SetLineColor(2);
   PrevFitTMP4->SetLineWidth(2);
   PrevFitTMP4->SetChisquare(17368.41);
   PrevFitTMP4->SetNDF(97);
   PrevFitTMP4->GetXaxis()->SetLabelFont(42);
   PrevFitTMP4->GetXaxis()->SetTitleOffset(1);
   PrevFitTMP4->GetXaxis()->SetTitleFont(42);
   PrevFitTMP4->GetYaxis()->SetLabelFont(42);
   PrevFitTMP4->GetYaxis()->SetTitleFont(42);
   PrevFitTMP4->SetParameter(0,89328.91);
   PrevFitTMP4->SetParError(0,76.11487);
   PrevFitTMP4->SetParLimits(0,0,0);
   PrevFitTMP4->SetParameter(1,3.009417e-14);
   PrevFitTMP4->SetParError(1,2.571282e-14);
   PrevFitTMP4->SetParLimits(1,0,0);
   PrevFitTMP4->SetParameter(2,3.701009e-11);
   PrevFitTMP4->SetParError(2,1.825506e-14);
   PrevFitTMP4->SetParLimits(2,0,3.751495e-10);
   PrevFitTMP4->SetParent(h__2);
   h__2->GetListOfFunctions()->Add(PrevFitTMP4);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h__2->SetLineColor(ci);
   h__2->GetXaxis()->SetTitle("testTitlexaxis");
   h__2->GetXaxis()->SetLabelFont(42);
   h__2->GetXaxis()->SetTitleOffset(1);
   h__2->GetXaxis()->SetTitleFont(42);
   h__2->GetYaxis()->SetTitle("testTitleyaxis");
   h__2->GetYaxis()->SetLabelFont(42);
   h__2->GetYaxis()->SetTitleFont(42);
   h__2->GetZaxis()->SetLabelFont(42);
   h__2->GetZaxis()->SetTitleOffset(1);
   h__2->GetZaxis()->SetTitleFont(42);
   h__2->Draw("");
   
   TPaveText *pt = new TPaveText(0.4821794,0.94,0.5178206,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("h");
   pt->Draw();
   can_fillDtGate_rand->Modified();
   can_fillDtGate_rand->cd();
   can_fillDtGate_rand->SetSelected(can_fillDtGate_rand);
}
