{
   TCanvas *c1 = new TCanvas("c1","c1",600,400);
   TH2F *hcol2 = new TH2F("hcol2","Option COLor example ",40,-4,4,40,-20,20);
   Float_t px, py;
   for (Int_t i = 0; i < 1000000; i++) {
      gRandom->Rannor(px,py);
      px=TMath::Abs(px);
      py=TMath::Abs(py);
      hcol2->Fill( 5*px, 5*py,1.);
      hcol2->Fill(-5*px,-5*py,-1.);
   }
   const UInt_t Number = 5;
   Double_t Red[Number]    = { 1.00, 0.00, 1.00, 1.00, 0.00};
   Double_t Green[Number]  = { 0.00, 1.00, 1.00, 0.00, 0.00};
   Double_t Blue[Number]   = { 0.00, 0.00, 1.00, 1.00, 1.00};
   Double_t Length[Number] = { 0.00, 0.25, 0.50, 0.75, 1.00 };
   Int_t nb=50;

   TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
   hcol2->SetContour(nb);
   hcol2->SetMaximum(6000);
   hcol2->SetMinimum(-6000);
   hcol2->Draw("colz");
}