// qstep.C
//
// David Adams
// July 2020
//
// Evaluate step charge for protoDUNE external pulser using a given
// injection capacitance and DAC setting.

double qstep(int dac =7, double cinj =187.8, double vfpga =1.8) {
  double xdac = dac;
  double cr0 = vfpga*cinj;
  TF1* pfun = cePulserTF1("mypulser");
  pfun->SetParameter(7, cr0);
  double vout = pfun->Eval(xdac);
  return vout/xdac;
}
