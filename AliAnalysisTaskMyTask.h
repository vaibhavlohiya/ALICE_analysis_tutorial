/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. */
/* See cxx source for full Copyright notice */
/* $Id$ */

#ifndef AliAnalysisTaskMyTask_H
#define AliAnalysisTaskMyTask_H

#include "AliAnalysisTaskSE.h"

class AliPIDResponse;
class AliEventPoolManager;
class AliVTrack;
class AliEventPool;
class AliMixedEvent;
class AliAODTrack;
class AliAODEvent;
class TFile;
class TList;
class TH1F;
class TH2F;

class AliAnalysisTaskMyTask : public AliAnalysisTaskSE  
{
    public:
                                AliAnalysisTaskMyTask();
                                AliAnalysisTaskMyTask(const char *name);
        virtual                 ~AliAnalysisTaskMyTask();

        virtual void            UserCreateOutputObjects();
        virtual void            UserExec(Option_t* option);
        virtual void            Terminate(Option_t* option);

    private:

        AliPIDResponse*         fPIDResponse;              //! pid response object
        AliEventPoolManager*    fPoolmgr;                  //! pool manager for event mixing
        AliEventPool*           pool;                      //! event pool
        AliMixedEvent*          fAOD;                      //! input event
        TList*                  fOutputAODList;            //! output list
        TH2F*                   fHistPtbyPt;               //! dummy histogram
        TFile*                  hidst;                     //! root file 
    
        //Kaon
        TH1F*                   fHistPtKaon;               //! dummy histogram
        TH1F*                   fHistEtaKaon;              //! dummy histogram
        TH1F*                   fHistVertexKaon;           //! dummy histogram
        TH1F*                   fHistPKaon;                //! dummy histogram
        TH1F*                   fHistOneOverPtKaon;        //! 1/Pt
        TH2F*                   fHistTPCKaon;              //! TPC Signal
        

        //Pion
        TH1F*                   fHistPtPion;               //! dummy histogram
        TH1F*                   fHistEtaPion;              //! dummy histogram
        TH1F*                   fHistVertexPion;           //! dummy histogram
        TH1F*                   fHistPPion;                //! dummy histogram
        TH1F*                   fHistOneOverPtPion;        //! 1/Pt
        TH2F*                   fHistTPCPion;              //! TPC Signal

        //Proton
        TH1F*                   fHistPtProton;             //! dummy histogram
        TH1F*                   fHistEtaProton;            //! dummy histogram
        TH1F*                   fHistVertexProton;         //! dummy histogram
        TH1F*                   fHistPProton;              //! dummy histogram
        TH1F*                   fHistOneOverPtProton;      //! 1/Pt
        TH2F*                   fHistTPCProton;            //! TPC Signal

        //Electron
        TH2F*                   fHistTPCElectron;           //! TPC Signal
        TH1F*                   fHistElectronCharge;        //! Charge of an electron

        //Muon
        TH2F*                   fHistTPCMuon;              //!TPC Signal

        AliAnalysisTaskMyTask(const AliAnalysisTaskMyTask&); // not implemented
        AliAnalysisTaskMyTask& operator=(const AliAnalysisTaskMyTask&); // not implemented

        ClassDef(AliAnalysisTaskMyTask, 1);
};

#endif
