#define analyze_trb3_cxx
// The class definition in analyze_trb3.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("analyze_trb3.C")
// Root > T->Process("analyze_trb3.C","some options")
// Root > T->Process("analyze_trb3.C+")
//

#include "analyze_trb3.h"
#include <TH2.h>
#include <TStyle.h>

TH1F* timeDiffAC;
TH1F* timeDiffACFine;
TH1F* timeDiffBD;
TH1F* timeTOTA;
TH1F* timeTOTC;

TH1F * tdchitsChannel;




UInt_t channelA = 41;
UInt_t channelB = 43;
UInt_t channelC = 45;
UInt_t channelD = 47;

UInt_t channelA1 = 42;
UInt_t channelB1 = 44;
UInt_t channelC1 = 46;
UInt_t channelD1 = 48;


void analyze_trb3::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   timeDiffACFine = new TH1F("timeDiffACFine", "timeDiffACFine", 20000, -10000, 10000);
   timeDiffAC = new TH1F("timeDiffAC", "timeDiffAC", 20000, -10000, 10000);
   timeDiffBD = new TH1F("timeDiffBD", "timeDiffBD", 20000, -10000, 10000);
   timeTOTA = new TH1F("timeTotA", "timeTotA", 100000, -50000, 50000);
   timeTOTC = new TH1F("timeTotC", "timeTotC", 100000, -50000, 50000);
   tdchitsChannel = new TH1F("tdcHitsChannel", "tdcHitsChannel", 260, 0, 260);
}

void analyze_trb3::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t analyze_trb3::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either analyze_trb3::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   
    b_event_totalNTDCHits->GetEntry(entry);
    b_event_TDCHits_->GetEntry(entry);
    
    float leadA = -1;
    float leadB = -1;
    float leadC = -1;
    float leadD = -1;
    float leadA1 = -1;
    float leadB1 = -1;
    float leadC1 = -1;
    float leadD1 = -1;

    float finetime1 = -1;
    float finetime2 = -1;
    
    for(int i = 0; i < totalNTDCHits; i++) {
    tdchitsChannel->Fill(TDCHits_channel[i]);
	if (TDCHits_channel[i] == channelA) {
	  leadA = TDCHits_leadTime1[i];
	  finetime1 = TDCHits_fineTime1[i];
	}
	else if (TDCHits_channel[i] == channelB) {
	  leadB = TDCHits_leadTime1[i];
	}
	else if (TDCHits_channel[i] == channelC)
	{
	  leadC = TDCHits_leadTime1[i];
	  finetime2 = TDCHits_fineTime1[i];
	}
	else if (TDCHits_channel[i] == channelD)
	{
	  leadD = TDCHits_leadTime1[i];

	}
	else if (TDCHits_channel[i] == channelA1)
	{
	  leadA1 = TDCHits_leadTime1[i];

	}
	else if (TDCHits_channel[i] == channelB1)
	{
	  leadB1 = TDCHits_leadTime1[i];

	}
	else if (TDCHits_channel[i] == channelC1)
	{
	  leadC1 = TDCHits_leadTime1[i];

	}
	else if (TDCHits_channel[i] == channelD1)
	{
	  leadD1 = TDCHits_leadTime1[i];

	}


    }

    
    if(leadA > 0 && leadB > 0 && leadC > 0 && leadD > 0) {
//      timeDiffAC->Fill( (leadA+leadB+leadC+leadD)/4 - (leadA1+leadB1+leadC1+leadD1)/4);
      timeDiffAC->Fill(leadA-leadC);

      timeDiffBD->Fill(leadB - leadD);


//      timeTOTA->Fill(leadC - leadC1);
//      timeTOTC->Fill(leadD - leadD1);
    }

//      timeDiffACFine->Fill(finetime1 - finetime2);
   

   return kTRUE;
}

void analyze_trb3::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

	timeDiffBD->Fit("gaus");
	timeDiffAC->Fit("gaus");
}

void analyze_trb3::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
  /*TCanvas *canvi =new TCanvas ("can1","can1",600,600);
  canvi->Divide(2,3); 
  canvi->cd(1);
   tdchitsChannel->Draw();
  canvi->cd(2);
   timeDiffAC->Draw();
  canvi->cd(3);
   timeDiffBD->Draw();
  canvi->cd(4);
   timeTOTA->Draw();
  canvi->cd(5);
   timeTOTC->Draw();
  canvi->cd(6);
   timeDiffACFine->Draw();
*/
//     tdchitsChannel->Draw();
//     canvi->Print("hits.png", "png");
//     timeDiffAC->Draw();
//         canvi->Print("diffAC.png", "png");
//     timeDiffBD->Draw();
//         canvi->Print("diffBD.png", "png");
//     timeTOTA->Draw();
//         canvi->Print("totA.png", "png");
//     timeTOTC->Draw();
//         canvi->Print("totC.png", "png");
//     timeDiffACFine->Draw();
//         canvi->Print("diffAC.png", "png");
}
