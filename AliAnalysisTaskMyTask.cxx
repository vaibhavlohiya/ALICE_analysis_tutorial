/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* AliAnaysisTaskMyTask
 *
 * empty task which can serve as a starting point for building an analysis
 * as an example, one histogram is filled
 */

#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TList.h"
#include "AliAnalysisTask.h"
#include "AliAnalysisManager.h"
#include <AliVTrack.h>
#include "AliAODEvent.h"
//#include "AliESDEvent.h"
#include "AliEventPoolManager.h"
#include "AliAODTrack.h"
#include "AliAODInputHandler.h"
//#include "AliESDInputHandler.h"
#include "AliAnalysisTaskMyTask.h"
#include "AliPIDResponse.h"
#include <AliMixedEvent.h>

class AliAnalysisTaskMyTask;    // your analysis class

using namespace std;            // std namespace: so you can do things like 'cout'

ClassImp(AliAnalysisTaskMyTask) // classimp: necessary for root

AliAnalysisTaskMyTask::AliAnalysisTaskMyTask() : AliAnalysisTaskSE(),   
fPIDResponse(0), fAOD(0), fOutputAODList(0), fPoolmgr(0X0), pool(0X0),
fHistPtKaon(0), fHistEtaKaon(0), fHistPKaon(0), fHistOneOverPtKaon(0), fHistTPCKaon(0),
fHistPtPion(0), fHistEtaPion(0), fHistPPion(0), fHistOneOverPtPion(0), fHistTPCPion(0),
fHistPtProton(0), fHistEtaProton(0), fHistPProton(0), fHistOneOverPtProton(0), fHistTPCProton(0),
fHistPtbyPt(0), fHistTPCElectron(0), fHistTPCMuon(0), fHistElectronCharge(0)//, fHistTPCPhoton(0), fHistTPCKaon0(0)
{
    // default constructor, don't allocate memory here!
    // this is used by root for IO purposes, it needs to remain empty
}
//_____________________________________________________________________________
AliAnalysisTaskMyTask::AliAnalysisTaskMyTask(const char* name) : AliAnalysisTaskSE(name),
fPIDResponse(0), fAOD(0), fOutputAODList(0),  fPoolmgr(0X0), pool(0X0),
fHistPtKaon(0), fHistEtaKaon(0), fHistPKaon(0), fHistOneOverPtKaon(0), fHistTPCKaon(0),
fHistPtPion(0), fHistEtaPion(0), fHistPPion(0), fHistOneOverPtPion(0), fHistTPCPion(0),
fHistPtProton(0), fHistEtaProton(0), fHistPProton(0), fHistOneOverPtProton(0), fHistTPCProton(0),
fHistPtbyPt(0), fHistTPCElectron(0), fHistTPCMuon(0), fHistElectronCharge(0)//, fHistTPCPhoton(0), fHistTPCKaon0(0)
{
    // constructor
    DefineInput(0, TChain::Class());    // define the input of the analysis: in this case we take a 'chain' of events
                                        // this chain is created by the analysis manager, so no need to worry about it, 
                                        // it does its work automatically
    DefineOutput(1, TList::Class());    // define the ouptut of the analysis: in this case it's a list of histograms 
                                        // you can add more output objects by calling DefineOutput(2, classname::Class())
                                        // if you add more output objects, make sure to call PostData for all of them, and to
                                        // make changes to your AddTask macro!
}
//_____________________________________________________________________________
AliAnalysisTaskMyTask::~AliAnalysisTaskMyTask()
{
    // destructor
    if(fOutputAODList) {
        delete fOutputAODList;     // at the end of your task, it is deleted from memory by calling this function
    }

}
//_____________________________________________________________________________
void AliAnalysisTaskMyTask::UserCreateOutputObjects()
{
    // create output objects
    //
    // this function is called ONCE at the start of your analysis (RUNTIME)
    // here you ceate the histograms that you want to use 
    //
    // the histograms are in this case added to a tlist, this list is in the end saved
    // to an output file
    //
    fOutputAODList = new TList();          // this is a list which will contain all of your histograms
                                        // at the end of the analysis, the contents of this list are written
                                        // to the output file
    fOutputAODList->SetOwner(kTRUE);       // memory stuff: the list is owner of all objects it contains and will delete them
                                        // if requested (dont worry about this now)



    AliAnalysisManager *man = AliAnalysisManager::GetAnalysisManager();

    if (man) 
    {
        AliInputEventHandler* inputHandler = (AliInputEventHandler*)(man->GetInputEventHandler());

        if (inputHandler)   
        fPIDResponse = inputHandler->GetPIDResponse();
    }

    Int_t trackdepth = 50000;
    Int_t poolsize = 1000;

    Int_t nCentralityBins = 15;

    Double_t centbins[] = {0, 1, 2, 3, 4, 5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    Int_t nZvtxBins = 7;

    Double_t zvtxbins[] = {-7, -5, -3, -1, 1, 3, 5, 7};


    //Kaon
    fHistPtKaon = new TH1F("fHistPtKaon", "fHistPt;Pt spectra;Counts", 1000, 0, 10);       
    fOutputAODList->Add(fHistPtKaon); 

    fHistEtaKaon = new TH1F("fHistEtaKaon","fHistEta;Pseudorapidity;Counts",1000,-5,5);
    fOutputAODList->Add(fHistEtaKaon);

    fHistPKaon = new TH1F("fHistPKaon","fHistP;P;Counts",1000, 0, 10);
    fOutputAODList->Add(fHistPKaon);

    fHistOneOverPtKaon = new TH1F("fHistOneOverPtKaon","fHistOneOverPt;1/Pt;Counts",1000,0,10);
    fOutputAODList->Add(fHistOneOverPtKaon);

    fHistTPCKaon = new TH2F("fHistTPCKaon", "fHistTPC;p/z;dE/dx",1000,0,10,1000,0,1000);
    fOutputAODList->Add(fHistTPCKaon);


    //Pion
    fHistPtPion = new TH1F("fHistPtPion", "fHistPt;Pt spectra;Counts", 1000, 0, 10);       
    fOutputAODList->Add(fHistPtPion); 

    fHistEtaPion = new TH1F("fHistEtaPion","fHistEta;Pseudorapidity;Counts",1000,-5,5);
    fOutputAODList->Add(fHistEtaPion);

    fHistPPion = new TH1F("fHistPPion","fHistP;P;Counts",1000, 0, 10);
    fOutputAODList->Add(fHistPPion);

    fHistOneOverPtPion = new TH1F("fHistOneOverPtPion","fHistOneOverPt;1/Pt;Counts",1000,0,10);
    fOutputAODList->Add(fHistOneOverPtPion);

    fHistTPCPion = new TH2F("fHistTPCPion", "fHistTPC;p/z;dE/dx",1000,0,10,1000,0,1000);
    fOutputAODList->Add(fHistTPCPion);

    //Proton
    fHistPtProton = new TH1F("fHistPtProton", "fHistPt;Pt spectra;Counts", 1000, 0, 10);       
    fOutputAODList->Add(fHistPtProton); 

    fHistEtaProton = new TH1F("fHistEtaProton","fHistEta;Pseudorapidity;Counts",1000,-5,5);
    fOutputAODList->Add(fHistEtaProton);

    fHistPProton = new TH1F("fHistPProton","fHistP;P;Counts",1000, 0, 10);
    fOutputAODList->Add(fHistPProton);

    fHistOneOverPtProton = new TH1F("fHistOneOverPtProton","fHistOneOverPt;1/Pt;Counts",1000,0,10);
    fOutputAODList->Add(fHistOneOverPtProton);

    fHistTPCProton = new TH2F("fHistTPCProton", "fHistTPC;p/z;dE/dx",1000,0,10,1000,0,1000);
    fOutputAODList->Add(fHistTPCProton);

    //Electron
    fHistTPCElectron = new TH2F("fHistTPCElectron", "fHistTPC;p/z;dE/dx",1000,0,10,1000,0,1000);
    fOutputAODList->Add(fHistTPCElectron);

    fHistElectronCharge = new TH1F("fHistElectronCharge", "fHistElectronCharge;Charge;Count",1000,-5,5);
    fOutputAODList->Add(fHistElectronCharge);

    //Muon
    fHistTPCMuon = new TH2F("fHistTPCMuon", "fHistTPC;p/z;dE/dx",1000,0,10,1000,0,1000);
    fOutputAODList->Add(fHistTPCMuon);       
       
    //2-D Histogram
    fHistPtbyPt = new TH2F("fHistPtbyPt", "fHistPtbyPt;Pt/Pt;Counts",1000,0,10,1000,0,10);
    fOutputAODList->Add(fHistPtbyPt);

    //Event Mixing

    fPoolmgr = new AliEventPoolManager(poolsize, trackdepth, nCentralityBins, (Double_t*) centbins, nZvtxBins, (Double_t*) zvtxbins);

    fPoolmgr->SetTargetValues(trackdepth, 0.1, 5);


    PostData(1, fOutputAODList);           // postdata will notify the analysis manager of changes / updates to the 
                                        // fOutputAODList object. the manager will in the end take care of writing your output to file
                                        // so it needs to know what's in the output
}
//_____________________________________________________________________________
void AliAnalysisTaskMyTask::UserExec(Option_t *)
{
    // user exec
    // this function is called once for each event
    // the manager will take care of reading the events from file, and with the static function InputEvent() you 
    // have access to the current event. 
    // once you return from the UserExec function, the manager will retrieve the next event from the chain
    fAOD = dynamic_cast<AliMixedEvent*>(InputEvent());    // get an event (called fAOD) from the input file
                                                        // there's another event format (ESD) which works in a similar wya
                                                        // but is more cpu/memory unfriendly. for now, we'll stick with aod's
    if(!fAOD) return;                                   // if the pointer to the event is empty (getting it failed) skip this event
        // example part: i'll show how to loop over the tracks in an event 
        // and extract some information from them which we'll store in a histogram
    Int_t iTracksAOD = fAOD->GetNumberOfTracks();           // see how many tracks there are in the event


    // float vertexZ = fAOD->GetPrimaryVertex()->GetZ();

        for(Int_t i(0); i < iTracksAOD; i++) 
    {                                                                                 // loop ove rall these tracks
        AliVTrack* track = static_cast<AliVTrack*>(fAOD->GetTrack(i));
                 
        // if(!track || !track->TestFilterBit(1)) continue;                       // get a track (type AliAODTrack) from the event 

        Double_t kaonSignal     = fPIDResponse->NumberOfSigmasTPC(track, AliPID::kKaon);
        Double_t pionSignal     = fPIDResponse->NumberOfSigmasTPC(track, AliPID::kPion);
        Double_t protonSignal   = fPIDResponse->NumberOfSigmasTPC(track, AliPID::kProton);
        Double_t electronSignal = fPIDResponse->NumberOfSigmasTPC(track, AliPID::kElectron);
        Double_t muonSignal = fPIDResponse->NumberOfSigmasTPC(track, AliPID::kMuon);        


        fHistPtbyPt->Fill(track->Pt(), track->OneOverPt());
                                                                       
        if(TMath::Abs(kaonSignal) < 3)
        {
            fHistTPCKaon->Fill(track->P(), track->GetTPCsignal());

            //Kaon
            fHistPtKaon->Fill(track->Pt());                     // plot the pt value of the track in a histogram
            fHistEtaKaon->Fill(track->Eta());
            fHistPKaon->Fill(track->P());
            fHistOneOverPtKaon->Fill(track->OneOverPt());

        };
        
        if(TMath::Abs(pionSignal) < 3)
        {     
            fHistTPCPion->Fill(track->P(), track->GetTPCsignal());

            //Pion
            fHistPtPion->Fill(track->Pt());                     // plot the pt value of the track in a histogram
            fHistEtaPion->Fill(track->Eta());
            fHistPPion->Fill(track->P());
            fHistOneOverPtPion->Fill(track->OneOverPt());
        };
        
        if(TMath::Abs(protonSignal) < 3)
        {   
            fHistTPCProton->Fill(track->P(), track->GetTPCsignal());
            
            //Proton
            fHistPtProton->Fill(track->Pt());                     // plot the pt value of the track in a histogram
            fHistEtaProton->Fill(track->Eta());
            fHistPProton->Fill(track->P());
            fHistOneOverPtProton->Fill(track->OneOverPt());
        };

        //Electron
        if(TMath::Abs(electronSignal) < 3)
        {            
            fHistTPCElectron->Fill(track->P(), track->GetTPCsignal());
            fHistElectronCharge->Fill(track->Charge());
        };

        //Muon
        if(TMath::Abs(muonSignal) < 3)         fHistTPCMuon->Fill(track->P(), track->GetTPCsignal());


    }

    /*fHistTPCElectron->Draw();
    fHistTPCKaon->Draw("SAME");
    fHistTPCMuon->Draw("SAME");
    fHistTPCProton->Draw("SAME");
    fHistTPCPion->Draw("SAME");*/

    /*hidst = new TFile("dedx.root","RECREATE");
    fHistTPCElectron->Write();
    fHistTPCKaon->Write();
    fHistTPCMuon->Write();
    fHistTPCProton->Write();
    fHistTPCPion->Write();*/


    PostData(1, fOutputAODList); 
                                                        // stream the results the analysis of this event to
                                                        // the output manager which will take care of writing
                                                        // it to a file
}
//_____________________________________________________________________________
void AliAnalysisTaskMyTask::Terminate(Option_t *)
{
    // terminate
    // called at the END of the analysis (when all events are processed)
}
//_____________________________________________________________________________
