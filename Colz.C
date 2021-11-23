#include "TH2D.h"

TH2D* h  = new TH2D("h", "", 10, 0, 10, 10, 0, 10);

h->SetBinContent(5, 7, 1.20); //this bin is drawn with color corresponding to palette
                              // level 1.0 (maximum), and I like it
h->SetBinContent(5, 6, 1.05);
h->SetBinContent(5, 5, 1.00);
h->SetBinContent(5, 4, 0.95);
h->SetBinContent(5, 3, 0.80); //this bin however is invisible, while I would like to
                              // see it
h->GetZaxis()->SetRangeUser(0.9, 1.1);
h->Draw("colz");