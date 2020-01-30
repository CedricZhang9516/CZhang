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
	gPad->SetGrid();

}

void readdatax(string t){
	//ifstream k("data_z.txt");//4
	//ifstream k("data_x2.txt");//9
	ifstream k("data4x.txt");//9
	//ifstream k("data_y.txt");//17
	string  x,	y,	z, MeanX, MeanY, refer;
	double  x_,y_,	z_, MeanX_, MeanY_, refer_;
	
	int i = 0;
	TH1F * h = new TH1F("h","z",10,0,1);
	TGraph * g = new TGraph();
	TGraph * g2 = new TGraph();
	
	while(i<23){
		k>>x>>y>>z>>MeanX>>MeanY>>refer;
		//z>>z_;
		x_ = std::atof(x.c_str());
		y_ = std::atof(y.c_str());
		MeanX_ = std::atof(MeanX.c_str());
		MeanY_ = std::atof(MeanY.c_str());
		//MeanX>>MeanX_;
		//g->SetPoint(i,x_,MeanX_);
		//g->SetPoint(i,x_,MeanY_);
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