const char mAT[] PROGMEM = "AT";
const char mOK[] PROGMEM = "OK";




void loopSIM800(byte funcaoSIM800)
{

  if (passo == 10)
  {

    imprimePasso();
    logicaReset();
    tempoFalhaPasso.Saida(0);

  }



  if (passo == 20)
  {
    imprimePasso();
     comandoR_SIM800(economizaRAM(mAT), economizaRAM(mOK), 30, 10, 10000);
  }


  if (passo == 30)
  {
    imprimePasso();

    tempoTrocaPasso.defiSP(2000);

    //ficar 2 segundos sem receber nada na serial
    if (mySerial.available()) {
      Serial.write(mySerial.read());
      tempoTrocaPasso.Saida(0);
    }

    if (tempoTrocaPasso.Saida(1))
    {
      if (bitRead(funcaoSIM800, 0))passo = 100; // SMS
       if (bitRead(funcaoSIM800, 1))passo = 200; // GPRS
       if (bitRead(funcaoSIM800, 2)) passo = 300; // BT
      tempoTrocaPasso.Saida(0);
    }
  }




  sim800_BT();


/*

 

*/


}
