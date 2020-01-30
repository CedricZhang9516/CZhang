double calculate_er(double p1){
    double error;
    error = 1.0/sqrt(p1);
    return error;
}

void format_h(TH1F* h, int linecolor)
{
    h->SetLineWidth(2); /****** 关于format_h   统一设置了线条的宽度******/
    h->SetLineColor(linecolor);  /*** 关于format_h  分别设置线条的颜色***/    /****若没有具体设置线条颜色，默认为蓝色***/
    
}

void plot3()
{
    TFile *file1 = new TFile("data.root","read"); // Data
    TFile *file2 = new TFile("mc.root","read"); //MC
    
    TList *MyOutputContainer1 = (TList *)file1->Get("UE;1");
    TList *MyOutputContainer2 = (TList *)file2->Get("UE;1");
    
    /***********************************************************************************/
    gStyle->SetOptStat(0);
    //=========================
    
    //TH1F *fHistRecTracks = (TH1F *)MyOutputContainer1->FindObject("fHistTracks");
    //TH1F *fHistGenTracks = (TH1F *)MyOutputContainer1->FindObject("fHistGenTracks");
    //TH1F *fHistDataTracks = (TH1F *)MyOutputContainer2->FindObject("fHistTracks");
    
    TH1F *fHistDataLeadPt = (TH1F *)MyOutputContainer1->FindObject("fHistLeadPt");
    TH1F *fHistRecLeadPt = (TH1F *)MyOutputContainer2->FindObject("fHistLeadPt");
    TH1F *fHistGenLeadPt = (TH1F *)MyOutputContainer2->FindObject("fHistGenLeadPt");
    
    
    
    /***********************************************************************************/
    //Fluctuation===================start
    
    Int_t tracks; Double_t fpt_lead;
    Int_t tracks_mc; Double_t fpt_lead_mc;
    Int_t tracks_g; Double_t fpt_lead_g;
    
    TTree *t1 = (TTree*)file1->Get("fTreeAna");
    t1->SetBranchAddress("fTracks_trans",&tracks);
    t1->SetBranchAddress("fPt_lead",&fpt_lead);
    
    TTree *t1_mc = (TTree*)file2->Get("fTreeAna");
    t1_mc->SetBranchAddress("fTracks_trans",&tracks_mc);
    t1_mc->SetBranchAddress("fPt_lead",&fpt_lead_mc);
    
    TTree *t1_g = (TTree*)file2->Get("fTreeAna_g");
    t1_g->SetBranchAddress("fTracks_trans_g",&tracks_g);
    t1_g->SetBranchAddress("fPt_lead_g",&fpt_lead_g);
    
    /*
    Double_t ntracks_mc[3];
    TTree *t1_mc = (TTree*)MyOutputContainer2->FindObject("TreeAna");
    t1_mc->SetBranchAddress("ntracks",&ntracks_mc);
    
    Double_t ntracks_g[3];
    TTree *t1_g = (TTree*)MyOutputContainer2->FindObject("TreeAna_g");
    t1_g->SetBranchAddress("ntracks_g",&ntracks_g);
    */
    Int_t number_nt = t1->GetEntries();
    Int_t number_nt_mc = t1_mc->GetEntries();
    Int_t number_nt_g = t1_g->GetEntries();
    
    const Double_t ptbins1[37] = {0.0, 0.1, 0.15,  0.2,  0.25,  0.3,   0.35,  0.4,   0.45,  0.5,   0.6,   0.7,   0.8,   0.9,   1.0,   1.5,   2.0,   2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 25.0, 30.0, 40.0, 50.0};
    
    

    TH1D *hist_RMS = new TH1D("","",36,ptbins1);
    TH1D *hist_RMS_mc = new TH1D("","",36,ptbins1);
    TH1D *hist_RMS_g = new TH1D("","",36,ptbins1);
    
    TH1D *hist_Skew = new TH1D("","",36,ptbins1);
    TH1D *hist_Skew_mc = new TH1D("","",36,ptbins1);
    TH1D *hist_Skew_g = new TH1D("","",36,ptbins1);
    
    TH1D *hist_Kur = new TH1D("","",36,ptbins1);
    TH1D *hist_Kur_mc = new TH1D("","",36,ptbins1);
    TH1D *hist_Kur_g = new TH1D("","",36,ptbins1);
    
    TH1D *hist_RMS->Sumw2();
    TH1D *hist_RMS_mc->Sumw2();
    TH1D *hist_RMS_g->Sumw2();
    
    TH1D *hist_Skew->Sumw2();
    TH1D *hist_Skew_mc->Sumw2();
    TH1D *hist_Skew_g->Sumw2();
    
    TH1D *hist_Kur->Sumw2();
    TH1D *hist_Kur_mc->Sumw2();
    TH1D *hist_Kur_g->Sumw2();
    

    
    

    for(int nev_=0;nev_<36;nev_++){               //start of the loop
        TH1D * hist = new TH1D("","",100,0,100);
        TH1D * hist_mc = new TH1D("","",100,0,100);
        TH1D * hist_g = new TH1D("","",100,0,100);
        for(int nn=0;nn<number_nt;nn++){
            t1->GetEntry(nn);
            if(fpt_lead<ptbins1[nev_+1] && fpt_lead>=ptbins1[nev_])hist->Fill(tracks);
        }
        for(int nn=0;nn<number_nt_mc;nn++){
            t1_mc->GetEntry(nn);
            if(fpt_lead_mc<ptbins1[nev_+1] && fpt_lead_mc>=ptbins1[nev_])hist_mc->Fill(tracks_mc);
        }
        for(int nn=0;nn<number_nt_g;nn++){
            t1_g->GetEntry(nn);
            if(fpt_lead_g<ptbins1[nev_+1] && fpt_lead_g>=ptbins1[nev_])hist_g->Fill(tracks_g);
        }
        /*
        for(int nn=0;nn<number_nt_mc;nn++){
            t1_mc->GetEntry(nn);
            if(ntracks_mc[2]==nev_){
                hist_mc->Fill(ntracks_mc[1]);
            }
        }
        for(int nn=0;nn<number_nt_g;nn++){
            t1_g->GetEntry(nn);
            if(ntracks_g[2]==nev_){
                hist_g->Fill(ntracks_g[1]);
            }
        }
        cout<<hist->GetEntries()<<endl;
        //cout<<hist_nt->GetRMS()<<endl;
        */
        
        
        /*
         cout<<hist_nt->GetSkewness()<<endl;
         cout<<hist_mc->GetSkewness()<<endl;
         cout<<hist_g->GetSkewness()<<endl;
         */
        /*
         cout<<hist->GetKurtosis()<<endl;
         cout<<hist_mc->GetKurtosis()<<endl;
         cout<<hist_g->GetKurtosis()<<endl;
         */
        
        //cout<<hist->GetRMS()<<endl;

        hist_RMS->SetBinContent(nev_,hist->GetRMS()/((1.6*(2./3)*TMath::Pi())));
        hist_RMS->SetBinError(nev_,hist->GetRMSError()/((1.6*(2./3)*TMath::Pi())));
        hist_RMS_mc->SetBinContent(nev_,hist_mc->GetRMS()/((1.6*(2./3)*TMath::Pi())));
        hist_RMS_g->SetBinContent(nev_,hist_g->GetRMS()/((1.6*(2./3)*TMath::Pi())));

        
        
        if(hist->GetEntries()!=0 && hist->GetRMS()!=0){cout<<hist->GetRMS()<<" "<<hist->GetSkewness()<<endl;hist_Skew->SetBinContent(nev_,hist->GetSkewness());hist_Skew->SetBinError(nev_,calculate_er(hist->GetEntries()));}
        if(hist_mc->GetEntries()!=0 && hist_mc->GetRMS()!=0) hist_Skew_mc->SetBinContent(nev_,hist_mc->GetSkewness());
        if(hist_g->GetEntries()!=0 && hist_g->GetRMS()!=0)hist_Skew_g->SetBinContent(nev_,hist_g->GetSkewness());
        
        
        
        if(hist->GetEntries()!=0 && hist->GetRMS()!=0)hist_Kur->SetBinContent(nev_,hist->GetKurtosis());
        if(hist_mc->GetEntries()!=0 && hist_mc->GetRMS()!=0)hist_Kur_mc->SetBinContent(nev_,hist_mc->GetKurtosis());
        if(hist_g->GetEntries()!=0 && hist_g->GetRMS()!=0)hist_Kur_g->SetBinContent(nev_,hist_g->GetKurtosis());
        //When RMS=0, Skweness and Kurtosis have indeterminate form

        
    }
    //end of the loop
    
    
    
    hist_RMS->SetTitle(" Particle Density Transverse RMS; Leading p_{T}(GeV/c); N_{ch} RMS");
    hist_RMS->SetMarkerStyle(8);
    hist_RMS->SetMarkerSize(1.4);
    hist_RMS->SetMarkerColor(kBlack);
    hist_RMS->SetLineColor(kBlack);
    
    hist_RMS_mc->SetTitle(" Particle Density Transverse RMS; Leading p_{T}(GeV/c); N_{ch} RMS");
    hist_RMS_mc->SetMarkerStyle(8);
    hist_RMS_mc->SetMarkerSize(1.4);
    hist_RMS_mc->SetMarkerColor(kBlue);
    hist_RMS_mc->SetLineColor(kBlue);
    
    hist_RMS_g->SetTitle(" Particle Density Transverse RMS; Leading p_{T}(GeV/c); N_{ch} RMS");
    hist_RMS_g->SetMarkerStyle(8);
    hist_RMS_g->SetMarkerSize(1.4);
    hist_RMS_g->SetMarkerColor(kRed);
    hist_RMS_g->SetLineColor(kRed);
    
    
    hist_Skew->SetTitle(" Particle Density Transverse Skewness; Leading p_{T}(GeV/c); N_{ch} Skwe");
    hist_Skew->SetMarkerStyle(8);
    hist_Skew->SetMarkerSize(1.4);
    hist_Skew->SetMarkerColor(kBlack);
    hist_Skew->SetLineColor(kBlack);
    
    hist_Skew_mc->SetTitle(" Particle Density Transverse Skewness; Leading p_{T}(GeV/c); N_{ch} Skew");
    hist_Skew_mc->SetMarkerStyle(8);
    hist_Skew_mc->SetMarkerSize(1.4);
    hist_Skew_mc->SetMarkerColor(kBlue);
    hist_Skew_mc->SetLineColor(kBlue);
    
    hist_Skew_g->SetTitle(" Particle Density Transverse Skewness; Leading p_{T}(GeV/c); N_{ch} Skew");
    hist_Skew_g->SetMarkerStyle(8);
    hist_Skew_g->SetMarkerSize(1.4);
    hist_Skew_g->SetMarkerColor(kRed);
    hist_Skew_g->SetLineColor(kRed);
    
    
    
    hist_Kur->SetTitle(" Particle Density Transverse Kurtosis; Leading p_{T}(GeV/c); N_{ch} Kurtosis");
    hist_Kur->SetMarkerStyle(8);
    hist_Kur->SetMarkerSize(1.4);
    hist_Kur->SetMarkerColor(kBlack);
    hist_Kur->SetLineColor(kBlack);
    
    hist_Kur_mc->SetTitle(" Particle Density Transverse Kurtosis; Leading p_{T}(GeV/c); N_{ch} Kurtosis");
    hist_Kur_mc->SetMarkerStyle(8);
    hist_Kur_mc->SetMarkerSize(1.4);
    hist_Kur_mc->SetMarkerColor(kBlue);
    hist_Kur_mc->SetLineColor(kBlue);
    
    hist_Kur_g->SetTitle(" Particle Density Transverse Kurtosis; Leading p_{T}(GeV/c); N_{ch} Kurtosis");
    hist_Kur_g->SetMarkerStyle(8);
    hist_Kur_g->SetMarkerSize(1.4);
    hist_Kur_g->SetMarkerColor(kRed);
    hist_Kur_g->SetLineColor(kRed);
    
    
    
    TCanvas *c_RMS = new TCanvas("c_RMS", "c_RMS", 1200, 1000);
    //  c_nt->Divide(1,3);
    c_RMS->SetGrid(1,1);
    //  c_nt->cd(1);
    hist_RMS->Draw("PE");
    //  c_nt->cd(2);
    hist_RMS_mc->Draw("PEsame");
    //  c_nt->cd(3);
    hist_RMS_g->Draw("PEsame");
    
    TLegend *legend2 = new TLegend(0.12, 0.15+0.63, 0.35, 0.25+0.63);
    legend2->SetFillColor(0);
    legend2->SetBorderSize(0);
    legend2->SetTextFont(42);
    legend2->SetTextSize(0.03);
    legend2->AddEntry(hist_RMS, "Data  ", "pl");
    legend2->AddEntry(hist_RMS_mc, "MC (EPOS)", "pl");
    legend2->AddEntry(hist_RMS_g, "MC (Generated, EPOS)", "pl");
    legend2->Draw("same");
    
    c_RMS->SaveAs("plots/signal/ParticleDensityTr_RMS.pdf");
    
   
    TCanvas *c_Skew = new TCanvas("c_Skew", "c_Skew", 1200, 1000);
    //  c_nt->Divide(1,3);
    c_Skew->SetGrid(1,1);
    //  c_nt->cd(1);
    hist_Skew->Draw("PE");
    //  c_nt->cd(2);
    hist_Skew_mc->Draw("PEsame");
    //  c_nt->cd(3);
    hist_Skew_g->Draw("PEsame");
    
    TLegend *legend2 = new TLegend(0.12, 0.15+0.63, 0.35, 0.25+0.63);
    legend2->SetFillColor(0);
    legend2->SetBorderSize(0);
    legend2->SetTextFont(42);
    legend2->SetTextSize(0.03);
    legend2->AddEntry(hist_Skew, "Data  ", "pl");
    legend2->AddEntry(hist_Skew_mc, "MC (EPOS)", "pl");
    legend2->AddEntry(hist_Skew_g, "MC (Generated, EPOS)", "pl");
    legend2->Draw("same");
    
    c_Skew->SaveAs("plots/signal/ParticleDensityTr_Skew.pdf");
    
    TCanvas *c_Kur = new TCanvas("c_Kur", "c_Kur", 1200, 1000);
    //  c_nt->Divide(1,3);
    c_Kur->SetGrid(1,1);
    //  c_nt->cd(1);
    hist_Kur->Draw("PE");
    //  c_nt->cd(2);
    hist_Kur_mc->Draw("PEsame");
    //  c_nt->cd(3);
    hist_Kur_g->Draw("PEsame");
    
    TLegend *legend2 = new TLegend(0.12, 0.15+0.63, 0.35, 0.25+0.63);
    legend2->SetFillColor(0);
    legend2->SetBorderSize(0);
    legend2->SetTextFont(42);
    legend2->SetTextSize(0.03);
    legend2->AddEntry(hist_Kur, "Data  ", "pl");
    legend2->AddEntry(hist_Kur_mc, "MC (EPOS)", "pl");
    legend2->AddEntry(hist_Kur_g, "MC (Generated, EPOS)", "pl");
    legend2->Draw("same");
    
    c_Kur->SaveAs("plots/signal/ParticleDensityTr_Kur.pdf");
    
    //Fluctuation===================end
    /***********************************************************************************/
    
    cout << "Data events = " << fHistDataLeadPt->Integral() << "  MC rec events = " << fHistRecLeadPt->Integral()<< "  gen events = " << fHistGenLeadPt->Integral() << endl;
    
    
    //particle density(Transverse)===================
    
    TCanvas *cParticleTr = new TCanvas("cParticleTr", "cParticleTr", 1200, 1000);
    cParticleTr->SetGrid(1,1);
    
    
    
    TProfile *fHistDataParticleDensityTr = (TProfile *)MyOutputContainer1->FindObject("fHistParticleDensityTransverse");
    TProfile *DataParticleDensityTr = new TProfile(*fHistDataParticleDensityTr);
    DataParticleDensityTr->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    TProfile *fHistGenParticleDensityTr = (TProfile *)MyOutputContainer2->FindObject("fHistGenParticleDensityTransverse");
    TProfile *GenParticleDensityTr = new TProfile(*fHistGenParticleDensityTr);
    GenParticleDensityTr->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    TProfile *fHistRecParticleDensityTr = (TProfile *)MyOutputContainer2->FindObject("fHistParticleDensityTransverse");
    TProfile *RecParticleDensityTr = new TProfile(*fHistRecParticleDensityTr);
    RecParticleDensityTr->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    DataParticleDensityTr->GetXaxis()->SetRangeUser(0,40.0);
    DataParticleDensityTr->GetYaxis()->SetRangeUser(0,3.0);
    
    DataParticleDensityTr->Draw("P");
    DataParticleDensityTr->SetTitle(" Particle Density Transverse; Leading p_{T}(GeV/c); N_{ch}/(N_{ev}#Delta#eta#Delta#phi) ");
    DataParticleDensityTr->SetMarkerStyle(8);
    DataParticleDensityTr->SetMarkerSize(1.4);
    DataParticleDensityTr->SetMarkerColor(kBlack);
    DataParticleDensityTr->SetLineColor(kBlack);
    
    RecParticleDensityTr->Draw("Same");
    RecParticleDensityTr->SetMarkerStyle(8);
    RecParticleDensityTr->SetMarkerSize(1.4);
    RecParticleDensityTr->SetMarkerColor(kBlue);
    RecParticleDensityTr->SetLineColor(kBlue);
    
    
    GenParticleDensityTr->Draw("Same");
    GenParticleDensityTr->SetMarkerStyle(8);
    GenParticleDensityTr->SetMarkerSize(1.4);
    GenParticleDensityTr->SetMarkerColor(kRed);
    GenParticleDensityTr->SetLineColor(kRed);
    
    
    
    TLegend *legend = new TLegend(0.12, 0.15+0.63, 0.35, 0.25+0.63);
    legend->SetFillColor(0);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->AddEntry(DataParticleDensityTr, "Data  ", "pl");
    legend->AddEntry(RecParticleDensityTr, "MC (EPOS)", "pl");
    legend->AddEntry(GenParticleDensityTr, "MC (Generated, EPOS)", "pl");
    legend->Draw("same");
    
    gPad->SetRightMargin(0.15);
    
    cParticleTr->SaveAs("plots/signal/ParticleDensityTr.pdf");
    
    //particle density(Toward)===================
    
    
    TCanvas *cParticleTo = new TCanvas("cParticleTo", "cParticleTo", 1200, 1000);
    cParticleTo->SetGrid(1,1);
    
    
    TProfile *fHistRecParticleDensityTo = (TProfile *)MyOutputContainer2->FindObject("fHistParticleDensityTowards");
    TProfile *RecParticleDensityTo = new TProfile(*fHistRecParticleDensityTo);
    RecParticleDensityTo->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    TProfile *fHistGenParticleDensityTowards = (TProfile *)MyOutputContainer2->FindObject("fHistGenParticleDensityTowards");
    TProfile *GenParticleDensityTowards = new TProfile(*fHistGenParticleDensityTowards);
    GenParticleDensityTowards->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    TProfile *fHistDataParticleDensityTo = (TProfile *)MyOutputContainer1->FindObject("fHistParticleDensityTowards");
    TProfile *DataParticleDensityTo = new TProfile(*fHistDataParticleDensityTo);
    DataParticleDensityTo->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    DataParticleDensityTo->GetXaxis()->SetRangeUser(0,40.0);
    DataParticleDensityTo->GetYaxis()->SetRangeUser(0,5.0);
    
    DataParticleDensityTo->Draw("P");
    DataParticleDensityTo->SetTitle(" Particle Density Towards; Leading p_{T}(GeV/c); N_{ch}/(N_{ev}#Delta#eta#Delta#phi) ");
    DataParticleDensityTo->SetMarkerStyle(8);
    DataParticleDensityTo->SetMarkerSize(1.4);
    DataParticleDensityTo->SetMarkerColor(kBlack);
    DataParticleDensityTo->SetLineColor(kBlack);
    
    
    RecParticleDensityTo->Draw("Same");
    RecParticleDensityTo->SetMarkerStyle(8);
    RecParticleDensityTo->SetMarkerSize(1.4);
    RecParticleDensityTo->SetMarkerColor(kBlue);
    RecParticleDensityTo->SetLineColor(kBlue);
    
    
    GenParticleDensityTowards->Draw("Same");
    GenParticleDensityTowards->SetMarkerStyle(8);
    GenParticleDensityTowards->SetMarkerSize(1.4);
    GenParticleDensityTowards->SetMarkerColor(kRed);
    GenParticleDensityTowards->SetLineColor(kRed);
    
    
    TLegend *legend = new TLegend(0.12, 0.15+0.63, 0.35, 0.25+0.63);
    legend->SetFillColor(0);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->AddEntry(DataParticleDensityTo, "Data  ", "pl");
    legend->AddEntry(RecParticleDensityTo, "MC (EPOS)", "pl");
    legend->AddEntry(GenParticleDensityTowards, "MC (Generated, EPOS)", "pl");
    legend->Draw("same");
    
    gPad->SetRightMargin(0.15);
    
    cParticleTo->SaveAs("plots/signal/ParticleDensityTo.pdf");
    
    //particle density(Away)===================
    
    
    TCanvas *cParticleAw = new TCanvas("cParticleAw", "cParticleAw", 1200, 1000);
    cParticleAw->SetGrid(1,1);
    
    
    TProfile *fHistRecParticleDensityAw = (TProfile *)MyOutputContainer2->FindObject("fHistParticleDensityAway");
    TProfile *RecParticleDensityAw = new TProfile(*fHistRecParticleDensityAw);
    RecParticleDensityAw->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    TProfile *fHistGenParticleDensityAw = (TProfile *)MyOutputContainer2->FindObject("fHistGenParticleDensityAway");
    TProfile *GenParticleDensityAw = new TProfile(*fHistGenParticleDensityAw);
    GenParticleDensityAw->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    TProfile *fHistDataParticleDensityAw = (TProfile *)MyOutputContainer1->FindObject("fHistParticleDensityAway");
    TProfile *DataParticleDensityAw = new TProfile(*fHistDataParticleDensityAw);
    DataParticleDensityAw->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    DataParticleDensityAw->GetXaxis()->SetRangeUser(0,40.0);
    DataParticleDensityAw->GetYaxis()->SetRangeUser(0,4.0);
    
    DataParticleDensityAw->Draw("P");
    DataParticleDensityAw->SetTitle(" Particle Density Away; Leading p_{T}(GeV/c); N_{ch}/(N_{ev}#Delta#eta#Delta#phi) ");
    DataParticleDensityAw->SetMarkerStyle(8);
    DataParticleDensityAw->SetMarkerSize(1.4);
    DataParticleDensityAw->SetMarkerColor(kBlack);
    DataParticleDensityAw->SetLineColor(kBlack);
    
    
    RecParticleDensityAw->Draw("Same");
    RecParticleDensityAw->SetMarkerStyle(8);
    RecParticleDensityAw->SetMarkerSize(1.4);
    RecParticleDensityAw->SetMarkerColor(kBlue);
    RecParticleDensityAw->SetLineColor(kBlue);
    
    
    GenParticleDensityAw->Draw("Same");
    GenParticleDensityAw->SetMarkerStyle(8);
    GenParticleDensityAw->SetMarkerSize(1.4);
    GenParticleDensityAw->SetMarkerColor(kRed);
    GenParticleDensityAw->SetLineColor(kRed);
    
    
    
    TLegend *legend = new TLegend(0.12, 0.15+0.63, 0.35, 0.25+0.63);
    legend->SetFillColor(0);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->AddEntry(DataParticleDensityAw, "Data   ", "pl");
    legend->AddEntry(RecParticleDensityAw, "MC (EPOS)", "pl");
    legend->AddEntry(GenParticleDensityAw, "MC (Generated, EPOS)", "pl");
    legend->Draw("same");
    
    gPad->SetRightMargin(0.15);
    
    cParticleAw->SaveAs("plots/signal/ParticleDensityAw.pdf");
    
    //Energy density(Transverse)===================
    
    TCanvas *cEnergyTr = new TCanvas("cEnergyTr", "cEnergyTr", 1200, 1000);
    cEnergyTr->SetGrid(1,1);
    
    
    TProfile *fHistDataEnergyDensityTr = (TProfile *)MyOutputContainer1->FindObject("fHistEnergyDensityTransverse");
    TProfile *DataEnergyDensityTr = new TProfile(*fHistDataEnergyDensityTr);
    DataEnergyDensityTr->Scale(1./(1.6*(2./3)*TMath::Pi()));
    DataEnergyDensityTr->SetTitle(" Energy Density Transverse; Leading p_{T}(GeV/c); #Sigmap_{T}/(N_{ev}#Delta#eta#Delta#phi)(GeV/c) ");
    
    TProfile *fHistRecEnergyDensityTr = (TProfile *)MyOutputContainer2->FindObject("fHistEnergyDensityTransverse");
    TProfile *RecEnergyDensityTr = new TProfile(*fHistRecEnergyDensityTr);
    RecEnergyDensityTr->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    TProfile *fHistGenEnergyDensityTr = (TProfile *)MyOutputContainer2->FindObject("fHistGenEnergyDensityTransverse");
    TProfile *GenEnergyDensityTr = new TProfile(*fHistGenEnergyDensityTr);
    GenEnergyDensityTr->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    DataEnergyDensityTr->GetXaxis()->SetRangeUser(0,40.0);
    DataEnergyDensityTr->GetYaxis()->SetRangeUser(0,4.0);
    
    DataEnergyDensityTr->Draw("P");
    DataEnergyDensityTr->SetTitle(" Energy Density Transverse; Leading p_{T}(GeV/c); #Sigmap_{T}/(N_{ev}#Delta#eta#Delta#phi)(GeV/c) ");
    DataEnergyDensityTr->SetMarkerStyle(8);
    DataEnergyDensityTr->SetMarkerSize(1.4);
    DataEnergyDensityTr->SetMarkerColor(kBlack);
    DataEnergyDensityTr->SetLineColor(kBlack);
    
    
    RecEnergyDensityTr->Draw("Same");
    RecEnergyDensityTr->SetMarkerStyle(8);
    RecEnergyDensityTr->SetMarkerSize(1.4);
    RecEnergyDensityTr->SetMarkerColor(kBlue);
    RecEnergyDensityTr->SetLineColor(kBlack);
    
    
    GenEnergyDensityTr->Draw("Same");
    GenEnergyDensityTr->SetMarkerStyle(8);
    GenEnergyDensityTr->SetMarkerSize(1.4);
    GenEnergyDensityTr->SetMarkerColor(kRed);
    GenEnergyDensityTr->SetLineColor(kRed);
    
    
    
    TLegend *legend = new TLegend(0.12, 0.15+0.63, 0.35, 0.25+0.63);
    legend->SetFillColor(0);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->AddEntry(DataEnergyDensityTr, "Data  ", "pl");
    legend->AddEntry(RecEnergyDensityTr, "MC (EPOS)", "pl");
    legend->AddEntry(GenEnergyDensityTr, "MC (Generated, EPOS)", "pl");
    legend->Draw("same");
    
    gPad->SetRightMargin(0.15);
    
    cEnergyTr->SaveAs("plots/signal/EnergyDensityTr.pdf");
    
    //Energy density(Towards)===================
    
    
    TCanvas *cEnergyTo = new TCanvas("cEnergyTo", "cEnergyTo", 1200, 1000);
    cEnergyTo->SetGrid(1,1);
    
    
    
    
    TProfile *fHistDataEnergyDensityTo = (TProfile *)MyOutputContainer1->FindObject("fHistEnergyDensityTowards");
    TProfile *DataEnergyDensityTo = new TProfile(*fHistDataEnergyDensityTo);
    DataEnergyDensityTo->SetTitle(" Energy Density Towards; Leading p_{T}(GeV/c); #Sigmap_{T}/(N_{ev}#Delta#eta#Delta#phi)(GeV/c) ");
    DataEnergyDensityTo->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    TProfile *fHistRecEnergyDensityTo = (TProfile *)MyOutputContainer2->FindObject("fHistEnergyDensityTowards");
    TProfile *RecEnergyDensityTo = new TProfile(*fHistRecEnergyDensityTo);
    RecEnergyDensityTo->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    TProfile *fHistGenEnergyDensityTo = (TProfile *)MyOutputContainer2->FindObject("fHistGenEnergyDensityTowards");
    TProfile *GenEnergyDensityTo = new TProfile(*fHistGenEnergyDensityTo);
    GenEnergyDensityTo->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    DataEnergyDensityTo->GetXaxis()->SetRangeUser(0,40.0);
    DataEnergyDensityTo->GetYaxis()->SetRangeUser(0,14.0);
    
    DataEnergyDensityTo->Draw("P");
    DataEnergyDensityTo->SetTitle(" Energy Density Towards; Leading p_{T}(GeV/c); #Sigmap_{T}/(N_{ev}#Delta#eta#Delta#phi)(GeV/c) ");
    DataEnergyDensityTo->SetMarkerStyle(8);
    DataEnergyDensityTo->SetMarkerSize(1.4);
    DataEnergyDensityTo->SetMarkerColor(kBlack);
    DataEnergyDensityTo->SetLineColor(kBlack);
    
    
    RecEnergyDensityTo->Draw("Same");
    RecEnergyDensityTo->SetMarkerStyle(8);
    RecEnergyDensityTo->SetMarkerSize(1.4);
    RecEnergyDensityTo->SetMarkerColor(kBlue);
    RecEnergyDensityTo->SetLineColor(kBlue);
    
    
    GenEnergyDensityTo->Draw("Same");
    GenEnergyDensityTo->SetMarkerStyle(8);
    GenEnergyDensityTo->SetMarkerSize(1.4);
    GenEnergyDensityTo->SetMarkerColor(kRed);
    GenEnergyDensityTo->SetLineColor(kRed);
    
    
    
    TLegend *legend = new TLegend(0.12, 0.15+0.63, 0.35, 0.25+0.63);
    legend->SetFillColor(0);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->AddEntry(DataEnergyDensityTo, "Data  ", "pl");
    legend->AddEntry(RecEnergyDensityTo, "MC (EPOS)", "pl");
    legend->AddEntry(GenEnergyDensityTo, "MC (Generated, EPOS)", "pl");
    legend->Draw("same");
    
    gPad->SetRightMargin(0.15);
    
    cEnergyTo->SaveAs("plots/signal/EnergyDensityTo.pdf");
    
    
    TCanvas *cEnergyAw = new TCanvas("cEnergyAw", "cEnergyAw", 1200, 1000);
    cEnergyAw->SetGrid(1,1);
    
    TProfile *fHistDataEnergyDensityAw = (TProfile *)MyOutputContainer1->FindObject("fHistEnergyDensityAway");
    TProfile *DataEnergyDensityAw = new TProfile(*fHistDataEnergyDensityAw);
    DataEnergyDensityAw->Scale(1./(1.6*(2./3)*TMath::Pi()));
    DataEnergyDensityAw->SetTitle(" Energy Density Transverse; Leading p_{T}(GeV/c); #Sigmap_{T}/(N_{ev}#Delta#eta#Delta#phi)(GeV/c) ");
    
    
    TProfile *fHistRecEnergyDensityAw = (TProfile *)MyOutputContainer2->FindObject("fHistEnergyDensityAway");
    TProfile *RecEnergyDensityAw = new TProfile(*fHistRecEnergyDensityAw);
    RecEnergyDensityAw->Scale(1./(1.6*(2./3)*TMath::Pi()));
    RecEnergyDensityAw->SetTitle(" Energy Density Transverse; Leading p_{T}(GeV/c); #Sigmap_{T}/(N_{ev}#Delta#eta#Delta#phi)(GeV/c) ");
    
    TProfile *fHistGenEnergyDensityAway = (TProfile *)MyOutputContainer2->FindObject("fHistGenEnergyDensityAway");
    TProfile *GenEnergyDensityAw = new TProfile(*fHistGenEnergyDensityAway);
    GenEnergyDensityAw->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    DataEnergyDensityAw->GetXaxis()->SetRangeUser(0,40.0);
    DataEnergyDensityAw->GetYaxis()->SetRangeUser(0,5.0);
    
    DataEnergyDensityAw->Draw("P");
    DataEnergyDensityAw->SetTitle(" Energy Density Away; Leading p_{T}(GeV/c); #Sigmap_{T}/(N_{ev}#Delta#eta#Delta#phi)(GeV/c) ");
    
    DataEnergyDensityAw->SetMarkerStyle(8);
    DataEnergyDensityAw->SetMarkerSize(1.4);
    DataEnergyDensityAw->SetMarkerColor(kBlack);
    DataEnergyDensityAw->SetLineColor(kBlack);
    
    
    RecEnergyDensityAw->Draw("Same");
    RecEnergyDensityAw->SetMarkerStyle(8);
    RecEnergyDensityAw->SetMarkerSize(1.4);
    RecEnergyDensityAw->SetMarkerColor(kBlue);
    RecEnergyDensityAw->SetLineColor(kBlue);
    
    GenEnergyDensityAw->Draw("Same");
    GenEnergyDensityAw->SetMarkerStyle(8);
    GenEnergyDensityAw->SetMarkerSize(1.4);
    GenEnergyDensityAw->SetMarkerColor(kRed);
    GenEnergyDensityAw->SetLineColor(kRed);
    
    
    TLegend *legend = new TLegend(0.12, 0.15+0.63, 0.35, 0.25+0.63);
    legend->SetFillColor(0);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->AddEntry(DataEnergyDensityAw, "Data  ", "pl");
    legend->AddEntry(RecEnergyDensityAw, "MC (EPOS)", "pl");
    legend->AddEntry(GenEnergyDensityAw, "MC (Generated, EPOS)", "pl");
    legend->Draw("same");
    
    gPad->SetRightMargin(0.15);
    
    cEnergyAw->SaveAs("plots/signal/EnergyDensityAw.pdf");
    
    
    TCanvas *cDPhiDEta = new TCanvas("cDPhiDEta", "cDPhiDEta", 1200, 1000);
    
    TH2F *DPhiDEta = (TH2F *)MyOutputContainer1->FindObject("fHistDPhiEta");
    
    TH2F *RecDPhiDEta = new TH2F(*DPhiDEta);
    RecDPhiDEta->Scale(1./(1.6*(2./3)*TMath::Pi()));
    
    RecDPhiDEta->SetTitle("#Delta#phi-#Delta#eta Distribution ");
    RecDPhiDEta->GetXaxis()->SetTitle("#Delta#phi");
    RecDPhiDEta->GetYaxis()->SetTitle("#Delta#eta");
    
    
    RecDPhiDEta->Draw("surf1");
    cDPhiDEta->SaveAs("plots/signal/DPhiDEta_data.pdf");
    
    
    TCanvas *cDeltaPhi = new TCanvas("cDeltaPhi", "cDeltaPhi", 1200, 1000);
    
    
    TH2F *DeltaPhiG = (TH2F *)MyOutputContainer2->FindObject("fHistDPhiEta");
    TH1 *GenDeltaPhi = (TH1 *)DeltaPhiG->ProjectionX("GenDeltaPhi");
    GenDeltaPhi->SetTitle("#Delta#phi Distribution ");
    GenDeltaPhi->Scale(1./(1.6)); // delta eta scaling
    GenDeltaPhi->Scale(1. / (fHistGenLeadPt->Integral()),"width");  // change the number of events later
    GenDeltaPhi->GetXaxis()->SetTitle("#Delta#phi");
    GenDeltaPhi->GetYaxis()->SetTitle("1/(N_{ev}#Delta#eta)dN_{ch}/d(#Delta#phi)");
    GenDeltaPhi->SetMarkerColor(kRed);
    GenDeltaPhi->SetLineColor(kRed);
    GenDeltaPhi->SetMarkerStyle(8);
    GenDeltaPhi->SetMarkerSize(1.4);
    GenDeltaPhi->Draw("P");
    //  GenDeltaPhi->GetYaxis()->SetRangeUser(0.31,0.65);
    GenDeltaPhi->GetYaxis()->SetRangeUser(0.0,1.0);
    
    
    
    TH2F *DeltaPhi = (TH2F *)MyOutputContainer2->FindObject("fHistDPhiEta");
    TH1 *RecDeltaPhi = (TH1 *)DeltaPhi->ProjectionX("RecDeltaPhi");
    RecDeltaPhi->SetTitle("#Delta#phi Distribution ");
    //RecDeltaPhi->GetYaxis()->SetRangeUser(0.0,1.0);
    RecDeltaPhi->Scale(1./(1.6)); // delta eta scaling
    RecDeltaPhi->Scale(1. / (fHistRecLeadPt->Integral()),"width");  // change the number of events later
    RecDeltaPhi->GetXaxis()->SetTitle("#Delta#phi");
    RecDeltaPhi->GetYaxis()->SetTitle("1/(N_{ev}#Delta#eta)dN_{ch}/d(#Delta#phi)");
    RecDeltaPhi->SetMarkerColor(kBlue);
    RecDeltaPhi->SetLineColor(kBlue);
    RecDeltaPhi->SetMarkerStyle(8);
    RecDeltaPhi->SetMarkerSize(1.4);
    RecDeltaPhi->Draw("same");
    
    
    
    
    TH2F *DeltaPhi1 = (TH2F *)MyOutputContainer1->FindObject("fHistDPhiEta");
    TH1 *DataDeltaPhi = (TH1 *)DeltaPhi1->ProjectionX("DataDeltaPhi");
    DataDeltaPhi->SetTitle("#Delta#phi Distribution ");
    
    DataDeltaPhi->Scale(1./(1.6)); // delta eta scaling
    //  DataDeltaPhi->Scale(1. / (fHistDataLeadPt->Integral()),"width");  // change the number of events later
    DataDeltaPhi->GetXaxis()->SetTitle("#Delta#phi");
    DataDeltaPhi->GetYaxis()->SetTitle("1/(N_{ev}#Delta#eta)dN_{ch}/d(#Delta#phi)");
    //  DataDeltaPhi->GetYaxis()->SetRangeUser(0.0,1.0);
    DataDeltaPhi->SetMarkerStyle(8);
    DataDeltaPhi->SetMarkerSize(1.4);
    DataDeltaPhi->SetMarkerColor(kBlack);
    DataDeltaPhi->SetLineColor(kBlack);
    //  DataDeltaPhi->Draw("same");
    
    
    
    
    
    
    //RecDeltaPhi->Draw("same");
    
    TLegend *legend = new TLegend(0.5, 0.15+0.63, 0.8, 0.25+0.63);
    legend->SetFillColor(0);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    //  legend->AddEntry(DataDeltaPhi, "Data ", "pl");
    legend->AddEntry(RecDeltaPhi, "MC (Reconstructed, EPOS)", "pl");
    legend->AddEntry(GenDeltaPhi, "MC (Generated, EPOS)", "pl");
    legend->Draw("same");
    
    
    
    cDeltaPhi->SaveAs("plots/signal/DPhiTotal.pdf");
    
    
    TCanvas *cDeltaPhiDeltaEtaData = new TCanvas("cDeltaPhiDeltaEtaData", "cDeltaPhiDeltaEtaData", 1200, 1000);
    
    TH2F *DeltaPhiDeltaEtaData = (TH2F *)MyOutputContainer1->FindObject("fHistDPhiEta");
    TH2F *DataDeltaPhiDEta = new TH2F(*DeltaPhiDeltaEtaData);
    DataDeltaPhiDEta->Scale(1./(1.6*(2./3)*TMath::Pi()));
    DataDeltaPhiDEta->SetTitle("#Delta#phi-#Delta#eta Distribution (Data)");
    DataDeltaPhiDEta->GetXaxis()->SetTitle("#Delta#phi");
    DataDeltaPhiDEta->GetYaxis()->SetTitle("#Delta#eta");
    //  GenDeltaPhi->Scale(1. / (fHistGenLeadPt->Integral()),"width");  // change the number of events later
    DataDeltaPhiDEta->Draw("surf1");
    cDeltaPhiDeltaEtaData->SaveAs("plots/signal/DPhiDEtaData.pdf");
    
    
    TCanvas *cDeltaPhiDeltaEtaRec = new TCanvas("cDeltaPhiDeltaEtaRec", "cDeltaPhiDeltaEtaRec", 1200, 1000);
    
    TH2F *DeltaPhiDeltaEtaRec = (TH2F *)MyOutputContainer2->FindObject("fHistDPhiEta");
    TH2F *RecDeltaPhiDEta = new TH2F(*DeltaPhiDeltaEtaRec);
    RecDeltaPhiDEta->Scale(1./(1.6*(2./3)*TMath::Pi()));
    RecDeltaPhiDEta->SetTitle("#Delta#phi-#Delta#eta Distribution (Reconstructed)");
    RecDeltaPhiDEta->GetXaxis()->SetTitle("#Delta#phi");
    RecDeltaPhiDEta->GetYaxis()->SetTitle("#Delta#eta");
    //  GenDeltaPhi->Scale(1. / (fHistGenLeadPt->Integral()),"width");  // change the number of events later
    RecDeltaPhiDEta->Draw("surf1");
    cDeltaPhiDeltaEtaRec->SaveAs("plots/signal/DPhiDEtaRec.pdf");
    
    TCanvas *cDeltaPhiGen = new TCanvas("cDeltaPhiGen", "cDeltaPhiGen", 1200, 1000);
    
    TH2F *DeltaPhiGen = (TH2F *)MyOutputContainer2->FindObject("fHistGenDPhiEta");
    TH2F *GenDeltaPhiDEta = new TH2F(*DeltaPhiGen);
    GenDeltaPhiDEta->SetTitle("#Delta#phi-#Delta#eta Distribution (Generated)");
    GenDeltaPhiDEta->GetXaxis()->SetTitle("#Delta#phi");
    GenDeltaPhiDEta->GetYaxis()->SetTitle("#Delta#eta");
    GenDeltaPhiDEta->Scale(1./(1.6*(2./3)*TMath::Pi()));
    //  GenDeltaPhi->Scale(1. / (fHistGenLeadPt->Integral()),"width");  // change the number of events later
    GenDeltaPhiDEta->Draw("surf1");
    cDeltaPhiGen->SaveAs("plots/signal/DPhiDEtaGen.pdf");
    
}


