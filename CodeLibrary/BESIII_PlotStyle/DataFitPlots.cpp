/**********************************************************
 *                                                        *
 *         BES III Plotstyle: example data/fit plot        *
 *                                                        *
 *         August 2009, Niklaus Berger                    *
 *         nberger@ihep.ac.cn                             *
 *                                                        *
 *********************************************************/

void DataFitPlots() {
  gROOT->ProcessLine(".L /beshome/shencp/plotstyle/bes3plotstyle.C");
  // Set general style options
  SetStyle();
  // Set options for "final" plots
  SetPrelimStyle();
  // OR: create meeting style plots with stat and fitbox
  //  SetMeetingStyle();

  // Create a dummy histogram - note that you have to call
  // SetStyle() BEFORE you create the histograms
  TH1F * datahist = new TH1F("datahist", "Data", 40, 0, 4);
  datahist->FillRandom("gaus",10000);
  
  //Do some fits - do not forget the "+" option
  datahist->Fit("gaus","+");
  datahist->Fit("landau","+");
  datahist->Fit("pol3","+");


  // Name the axes of the data histogram
  NameAxes(datahist, "p_{#pi} (GeV/c)", "Events / 0.1 GeV/c");
  

  // Names for the fits
  char * names[] = {"Good Fit",
		    "Fit 2",
		    "Fit 3",
		    "Bad Fit",
		    "Old Fit",
		    "Another Fit"};


  // Do the plot
  PlotDataFit("nicefit",
	      datahist, "BESIII #psi' Data", names);



}
