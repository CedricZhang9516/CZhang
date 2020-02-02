//declarando background
bool reject;
double fline(double *x, double *par)
{
   //if true, and 50 < x < 130, reject 
   if (reject && x[0] > 50 && x[0] < 130)
   {
      TF1::RejectPoint();
      return 0;
   }
   //else return the function
   return(exp(par[0] + par[1]*x[0] + par[2]*pow(x[0],2) + par[3]*pow(x[0],3) + par[4]*pow(x[0],4) + par[5]*pow(x[0],5)));
}

// fit 
  TF1 *fl = new TF1("fl",fline,10,200,4);
  fl->SetParameters(0,0);
  fl->SetLineColor(kBlack); 
  tela.SetFillColor(33);
  tela.SetFrameFillColor(33);
  // fit only the background excluding the signal area
  reject = kTRUE;
  imass_z0->Fit(fl); //imass_z0 = histogram
  reject = kFALSE;  
