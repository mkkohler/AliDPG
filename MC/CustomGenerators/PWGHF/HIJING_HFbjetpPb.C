AliGenerator *
GeneratorCustom(TString opt = "")
{
  AliGenCocktail *ctl  = GeneratorCocktail("HIJING_HF");
  Float_t randHF = gRandom->Rndm();
  if(randHF>0.176797){ // add HIJING generator for p-Pb
    AliGenerator *hij = GeneratorHijing();
    ctl->AddGenerator(hij, "Hijing", 1.);
  }
  //
  Int_t process[2] = {kPythia6HeavyProcess_Charm, kPythia6HeavyProcess_Beauty};
  Int_t decay[4]   = {kPythia6HeavyDecay_Hadrons, kPythia6HeavyDecay_HadronsWithV0, kPythia6HeavyDecay_Electron, kPythia6HeavyDecay_All};
  
  const Char_t *label[2][4] = {
    "chadr PYTHIA", "chadr PYTHIA", "cele PYTHIA", "ccbar PYTHIA",
    "bchadr PYTHIA", "bchadr PYTHIA", "bele PYTHIA", "bbbar PYTHIA"
  };
  
  Int_t iprocess = -1;
  
  if(opt.Contains("cc")) {iprocess = 0; printf("-- HF process = %s -- \n",opt.Data());}
  else if(opt.Contains("bb")) {iprocess = 1; printf("-- HF process = %s -- \n",opt.Data());}
  else {printf("-- no HF process set = %s -- \n",opt.Data());}
  
  TString optList[5] = {"had", "hv0", "ele", "all", "jetjet"};
  Int_t idecay = 0;
  for (Int_t iopt = 0; iopt < 5; iopt++){
    if (opt.Contains(optList[iopt]))
      idecay = iopt;
  }
  
  AliGenerator *phf;
  if(idecay < 4) {
    Float_t randHF = gRandom->Rndm();
    Int_t typeHF = -1;
    if(randHF < 0.9) {
      phf  = GeneratorPythia6Heavy(process[iprocess], decay[idecay], kPythia6Tune_Perugia2011, kFALSE);
      ctl->AddGenerator(phf, label[iprocess][idecay], 1.);
      printf(">>>>> added generator for HF production:  %s \n", label[iprocess][idecay]);
    }
    else{//10% with electron in acceptance.
      phf  = GeneratorPythia6Heavy(process[iprocess], decay[2], kPythia6Tune_Perugia2011, kFALSE);
      ctl->AddGenerator(phf, label[iprocess][2], 1.);
      printf(">>>>> added generator for HF production:  %s \n", label[iprocess][2]); 
    }
  }
  else if(idecay == 4) {
    phf  = GeneratorPythia6Jets(kPythia6Tune_Perugia2011);
    ctl->AddGenerator(phf, "jetjet", 1.);
    printf(">>>>> added generator for HF production:  %s \n", "jetjet");
  }   
  return ctl;
}

