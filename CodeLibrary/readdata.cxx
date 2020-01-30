#include <iostream>
using namespace std;

void readdatax(string t);
void readdatay(string t);
void readdataz(string t);
void readdata2(string t);



void readdata(){



	readdatax("point_source;shift_x [mm];MeanX [mm]");
	//readdatax("point_source;shift_x [mm];MeanY [mm]");
	//readdatay("point_source;shift_y [mm];MeanX [mm]");
	//readdatay("point_source;shift_y [mm];MeanY [mm]");
	//readdataz("point_source;shift_z [mm];MeanX [mm]");
	//readdataz("point_source;shift_z [mm];MeanY [mm]");
	//readdata2("point_source;shift_z [mm];MeanY [mm]");
	

}

void readdatax(string t){
	//ifstream k("data_z.txt");//4
	//ifstream k("data_x2.txt");//9
	//ifstream k("Data_TOF2.txt");//9
	ifstream k("Data_TOF_191128.txt");//9
	//ifstream k("data_y.txt");//17
	string Ek, TOF, TOFerr, TOFtheo349,  refer1, refer2, TOFtheo277, TOFsim, TOFsimerr, N;
	double Ek_, TOF_, TOFerr_, TOFtheo349_, refer1_, refer2_, TOFtheo277_, TOFsim_, TOFsimerr_, N_;
	string  x,	y,	z, MeanX, MeanY, MeanZ, refer;
	double  x_, y_,	z_, MeanX_, MeanY_, MeanZ_, refer_;

	double shift1 = 0.384375;
	double shift2 = 1.21673;
	double shift3 = 0.8366;
	
	int i = 0;
	TH1F * h = new TH1F("h","z",10,0,1);
	TGraphErrors * g1 = new TGraphErrors();
	TGraphErrors * g2 = new TGraphErrors();
	TGraphErrors * g3 = new TGraphErrors();
	TGraphErrors * g4 = new TGraphErrors();
	TGraphErrors * g5 = new TGraphErrors();
	TGraphErrors * g6 = new TGraphErrors();
	TGraphErrors * g7 = new TGraphErrors();

	TGraph * e2 = new TGraph();
	TGraph * e3 = new TGraph();
	TGraphErrors * e4 = new TGraphErrors();

	TH1F * h2 = new TH1F("err2","err",25,0,2);
	TH1F * h3 = new TH1F("err3","err",25,0,2);
	TH1F * h4 = new TH1F("err4","err",25,0,2);
	
	while(i<11){
		//k>>x>>y>>MeanY>>z>>MeanZ>>refer;
		//k>>Ek>> TOF>> TOFerr>> TOFtheo349>> refer1>> refer2>> TOFtheo277>> TOFsim>> TOFsimerr>> N;
		k>>Ek>> TOF>>TOFerr>> TOFsim>> TOFsimerr>> TOFtheo277;
		//z>>z_;
		
		Ek_ = std::atof(Ek.c_str());
		TOF_ = std::atof(TOF.c_str());
		TOFerr_ = std::atof(TOFerr.c_str());
		TOFtheo349_ = std::atof(TOFtheo349.c_str());
		//TOFtheo349err_ = std::atof(TOFtheo349err.c_str());
		refer1_ = std::atof(refer1.c_str());
		refer2_ = std::atof(refer2.c_str());
		TOFtheo277_ = std::atof(TOFtheo277.c_str());
		TOFsim_ = std::atof(TOFsim.c_str());
		TOFsimerr_ = std::atof(TOFsimerr.c_str());
		N_ = std::atof(N.c_str());

		//MeanX>>MeanX_;
		//g->SetPoint(i,x_,MeanX_);
		//g->SetPoint(i,x_,MeanY_);
		g1->SetPoint(i,Ek_,TOF_);
		g1->SetPointError(i,0,TOFerr_);

		//g2->SetPoint(i,x_,z_+0.8366);
		g2->SetPoint(i,Ek_,TOFtheo349_);
		e2->SetPoint(i,Ek_,TOF_- TOFtheo349_ );
		h2->Fill(TOF_- TOFtheo349_);

		//g->SetPointError(i,x_,y_);
		g3->SetPoint(i,Ek_,TOFtheo277_);
		e3->SetPoint(i,Ek_,TOF_- TOFtheo277_ );
		h3->Fill(TOF_- TOFtheo277_);

		g4->SetPoint(i,Ek_,TOFsim_);
		g4->SetPointError(i,0,TOFsimerr_);
		e4->SetPoint(i,Ek_,TOF_- TOFsim_ );
		e4->SetPointError(i,0,sqrt(TOFerr_*TOFerr_+TOFsimerr_*TOFsimerr_)/2);
		h4->Fill(TOF_- TOFsim_);

		g5->SetPoint(i,Ek_,TOFtheo349_+shift1);
		//g5->SetPointError(i,0,TOFsimerr_);

		g6->SetPoint(i,Ek_,TOFtheo277_+shift2);
		//g6->SetPointError(i,0,TOFsimerr_);

		g7->SetPoint(i,Ek_,TOFsim_+shift3);
		g7->SetPointError(i,0,TOFsimerr_);
		
		//h2->Fill(y_-z_);

		i++;
	}

	//g1: TOF_measurement
	g1->SetLineColor(1);
	g1->SetMarkerStyle(20);
	g1->SetMarkerSize(0.3);
	g1->SetMarkerColor(1);
	g1->GetYaxis()->SetRangeUser(1,10);

	//g2: TOF_theo349
	g2->SetLineColor(3);
	g2->SetMarkerStyle(20);
	g2->SetMarkerSize(0.3);
	g2->SetMarkerColor(3);
	g2->GetYaxis()->SetRangeUser(1,10);

	//g3: TOF_theo277
	g3->SetLineColor(4);
	g3->SetMarkerStyle(20);
	g3->SetMarkerSize(0.3);
	g3->SetMarkerColor(4);
	g3->GetYaxis()->SetRangeUser(1,10);

	//g4: TOF_simulation
	g4->SetLineColor(kRed);
	g4->SetMarkerStyle(20);
	g4->SetMarkerSize(0.3);
	g4->SetMarkerColor(kRed);
	g4->GetYaxis()->SetRangeUser(1,10);

	//g5: TOF_theo349-SHIFTED
	g5->SetLineColor(3);
	g5->SetMarkerStyle(20);
	g5->SetMarkerSize(0.3);
	g5->SetMarkerColor(3);
	g5->GetYaxis()->SetRangeUser(1,10);

	//g6: TOF_theo277-SHIFTED
	g6->SetLineColor(4);
	g6->SetMarkerStyle(20);
	g6->SetMarkerSize(0.3);
	g6->SetMarkerColor(4);
	g6->GetYaxis()->SetRangeUser(1,10);

	//g7: TOF_sim-SHIFTED
	g7->SetLineColor(2);
	g7->SetMarkerStyle(20);
	g7->SetMarkerSize(0.3);
	g7->SetMarkerColor(2);
	g7->GetYaxis()->SetRangeUser(1,10);


	//TF1 *f1 = new TF1("f1","2.77/(3*10^2*sqrt(1-1/((1+x/938000)^2)))+[0]",10,20);
	TF1 *f1 = new TF1("f1","[0]/(3*10^2*sqrt(1-1/((1+x/938000)^2)))+[1]",10,20);
	f1->SetParameter(0,2);
	//f1->SetParameter(0,0.5);
	f1->SetParameter(1,0.5);
	
	Int_t c_i = 1;

	TLegend * l = new TLegend(0.5,0.7,0.9,0.9);


	TCanvas *c = new TCanvas("c","c",1500,1000);
	c->Divide(3,3);
	
	c->cd(c_i++);
	g1->Draw("APLE");
	//g2->Draw("sameLP");
	g1->Fit(f1);
	f1->Draw("same");

	l->AddEntry(g1,"TOF_measured","L");
	l->AddEntry(f1,"Fitting","L");
	l->Draw();
	//g3->Draw("same*L");
	//g4->Draw("same*L");
	//g2->Draw("same*L");
	cout<<"h2 "<<h2->GetMean()<<endl;
/*
	c->cd(c_i++);
	//c->cd(2);
	g1->Draw("APLE");
	g2->Draw("sameLP");
	//g->Fit(f1);
	//f1->Draw("same");
*/	
	c->cd(c_i++);
	g1->Draw("APLE");
	g3->Draw("sameLP");
	h3->Draw();
	cout<<"h3 "<<h3->GetMean()<<endl;
	
	c->cd(c_i++);
	g1->Draw("APLE");
	g6->Draw("sameLP");
	g7->Draw("sameLPE");
	cout<<"h4 "<<h4->GetMean()<<endl;

	l = new TLegend(0.5,0.7,0.9,0.9);

	l->AddEntry(g1,"TOF_measured","L");
	l->AddEntry(g6,"TOF_theory277-corrected","L");
	l->AddEntry(g7,"TOF_G4Simulation-corrected","L");
	l->AddEntry(f1,"Fitting","L");
	l->Draw();

	c->cd(c_i++);
	e2->Draw("APL*");

	c->cd(c_i++);
	e3->Draw("APL*");

	c->cd(c_i++);
	e4->Draw("APL*");

	c->cd(c_i++);
	g1->Draw("APLE");
	g5->Draw("sameLP");

	c->cd(c_i++);
	g1->Draw("APLE");
	g6->Draw("sameLP");

	c->cd(c_i++);
	g1->Draw("APLE");
	g7->Draw("sameLPE");
	
	//h2->Draw();
	//g2->SetTitle(t.c_str());
	//g2->Draw("AP*L");

	

	TCanvas *c2 = new TCanvas("c2","c2",1000,600);
	c2->Divide(2,3);
	c_i = 1;
	c2->cd(c_i++);
	g1->Draw("APLE");
	g3->Draw("sameLP");
	cout<<"h3 "<<h3->GetMean()<<endl;
	gPad->SetGrid();
	g1->SetTitle("TOF vs. EK; Ek [keV]; TOF [us]");
	g1->GetYaxis()->SetTitleOffset(0.58);
	g1->GetYaxis()->SetTitleSize(0.06);
	g1->GetXaxis()->SetTitleSize(0.06);
	g1->GetXaxis()->SetTitleOffset(0.8);
	l = new TLegend(0.6,0.7,0.9,0.9);
	l->AddEntry(g1,"TOF_measured","L");
	l->AddEntry(g3,"TOF_theory277","L");
	l->Draw();


	c2->cd(c_i++);
	g1->Draw("APLE");
	g3->Draw("sameLP");
	g4->Draw("sameLPE");

	l = new TLegend(0.6,0.7,0.9,0.9);
	l->AddEntry(g1,"TOF_measured","L");
	l->AddEntry(g3,"TOF_theory277","L");
	l->AddEntry(g4,"TOF_G4Simulation","L");
	l->AddEntry(f1,"Fitting","L");
	l->Draw();


	cout<<"h4 "<<h4->GetMean()<<endl;
	gPad->SetGrid();



	c2->cd(c_i++);
	e3->Draw("APL*");
	e3->SetTitle("TOF_measured - TOF_theory; Ek [keV]; #Delta_{TOF} [us]");
	e3->GetYaxis()->SetTitleOffset(0.58);
	e3->GetYaxis()->SetTitleSize(0.08);
	e3->GetXaxis()->SetTitleOffset(0.8);
	e3->GetXaxis()->SetTitleSize(0.06);




	c2->cd(c_i++);
	e4->Draw("AP*");
	e4->SetTitle("TOF_measured - TOF_simulation; Ek [keV]; #Delta_{TOF} [us]");
	e4->GetYaxis()->SetTitleOffset(0.58);
	e4->GetYaxis()->SetTitleSize(0.08);
	e4->GetXaxis()->SetTitleOffset(0.8);
	e4->GetXaxis()->SetTitleSize(0.06);
	gPad->SetGrid();

	c2->cd(c_i++);
	g1->Draw("APLE");
	g6->Draw("sameLP");
	gPad->SetGrid();

	c2->cd(c_i++);
	g1->Draw("APLE");
	g7->Draw("sameLPE");
	gPad->SetGrid();

}

void readdatay(string t){
	//ifstream k("data_z.txt");//4
	//ifstream k("data_x.txt");//9
	//ifstream k("data_y2.txt");//17
	ifstream k("data4y.txt");//17
	string  x,	y,	z, MeanX, MeanY, refer;
	double  x_,	y_,	z_, MeanX_, MeanY_, refer_;
	
	int i = 0;
	TH1F * h = new TH1F("h","z",10,0,1);
	TGraph * g = new TGraph();
	TGraph * g2 = new TGraph();
	
	while(i<31){
		k>>x>>y>>z>>MeanX>>MeanY>>refer;
		//z>>z_;
		y_ = std::atof(y.c_str());
		MeanX_ = std::atof(MeanX.c_str());
		MeanY_ = std::atof(MeanY.c_str());
		//MeanX>>MeanX_;
		//g->SetPoint(i,y_,MeanX_);
		g->SetPoint(i,x_,y_);
		g2->SetPoint(i,MeanX_,MeanY_);
		i++;
	}

	TCanvas *c = new TCanvas("c","c",1000,500);
	c->Divide(2,1);
	c->cd(1);
	//g->SetTitle(t.c_str());
	g->Draw("AP*L");
	c->cd(2);
	//g2->SetTitle(t.c_str());
	g2->Draw("AP*L");

}

void readdataz(string t){
	ifstream k("data_z2.txt");//4
	//ifstream k("data_x.txt");//9
	//ifstream k("data_y.txt");//17
	string  x,	y,	z, MeanX, MeanY, refer;
	double  x_,	y_,	z_, MeanX_, MeanY_, refer_;
	
	int i = 0;
	TH1F * h = new TH1F("h","z",10,0,1);
	TGraph * g = new TGraph();
	
	while(i<5){
		k>>x>>y>>z>>MeanX>>MeanY>>refer;
		//z>>z_;
		z_ = std::atof(z.c_str());
		MeanX_ = std::atof(MeanX.c_str());
		MeanY_ = std::atof(MeanY.c_str());
		//MeanX>>MeanX_;
		//g->SetPoint(i,z_,MeanX_);
		g->SetPoint(i,z_,MeanY_);
		//cout<<z_<<MeanY_<<endl;
		i++;
	}

	g->SetTitle(t.c_str());
	g->Draw("AP*L");

}

void readdata2(string t){
	//ifstream k("data_z.txt");//4
	ifstream k2("data2.txt");//9
	ifstream k("data3.txt");//9
	//ifstream k("data_y.txt");//17
	string  x,	y,	z, MeanX, MeanY, refer;
	double  x_,y_,	z_, MeanX_, MeanY_, refer_;
	
	int i = 0;
	TH1F * h = new TH1F("h","z",10,0,1);
	TGraph * g = new TGraph();
	TGraph * g0 = new TGraph();
	TGraph * g2 = new TGraph();
	TGraph * g3 = new TGraph();
	
	while(i<9){
		k>>x>>y>>z>>MeanX>>MeanY>>refer;
		//z>>z_;
		x_ = std::atof(x.c_str());
		y_ = std::atof(y.c_str());
		MeanX_ = std::atof(MeanX.c_str());
		MeanY_ = std::atof(MeanY.c_str());
		//MeanX>>MeanX_;
		g->SetPoint(i,x_,y_);
		g2->SetPoint(i,MeanX_,MeanY_);
		g0->SetPoint(2*i,MeanX_,MeanY_);

		k2>>x>>y>>z>>MeanX>>MeanY>>refer;
		x_ = std::atof(x.c_str());
		y_ = std::atof(y.c_str());
		MeanX_ = std::atof(MeanX.c_str());
		MeanY_ = std::atof(MeanY.c_str());
		g3->SetPoint(i,MeanX_,MeanY_);		
		g0->SetPoint(2*i+1,MeanX_,MeanY_);

		i++;
	}
	//g->SetPoint(i,0,0);
	//g2->SetPoint(i,6.62248,-1.12181);
	TCanvas *c = new TCanvas("c","c",1000,500);
	c->Divide(2,1);
	//g->SetTitle(t.c_str());
	c->cd(1);
	g->Draw("AP*");
	//g->SetTitle(t.c_str());
	c->cd(2);
	//TAxis *axis = g2->GetXaxis();
	//g2->GetXaxis()->SetLimits(-12,20);

	//c->Update(); 
	//g2->GetHistogram()->SetMaximum(20);   // along          
   	//g2->GetHistogram()->SetMinimum(-12);
	//g2->GetXaxis()->SetLimits(-12,20);
	g0->Draw("AP*");
	g2->Draw("sameP*");
	//g3->SetMarkerColor(kRed);
	g3->Draw("sameP*");

}