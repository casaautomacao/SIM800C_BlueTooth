void debugSIM800()
{
  int setaL = 0;
  while (Serial.available())
  {
    byte teste = Serial.read();
    mySerial.write(teste);
    if (teste == 0x23) logicaReset();
    setaL = 1;
  }

  if (setaL) delay(1500), Serial.println();
  if (setaL)
  {
    while (mySerial.available())
    {
      byte teste = mySerial.read();
      Serial.write(teste);
    }
    setaL = 0;
  }
}


void imprimirLocal(long intervalo)
{

  tempImprimir.defiSP(intervalo);

  if (tempImprimir.Saida(1))
  {
    Serial.println();
    Serial.print(economizaRAM(mPasso));
    Serial.print(passo);
    Serial.println();
    tempImprimir.Saida(0);
  }


}



//definir quanto tempo acumulará a leitura

String acumula = "";
byte inicioEspera = 0;

String leRetorno(long espera)
{

  delayLeitura.defiSP(espera);
  char leitura = "";


  if (inicioEspera == 0) acumula = "";


  if (mySerial.available())
  {
    inicioEspera = 1;
    leitura = mySerial.read();
    acumula += leitura;
  }

  if (delayLeitura.Saida(inicioEspera))
  {
    inicioEspera = 0;
    delayLeitura.Saida(0);
    return acumula;
  }

  return "";
}


byte luzStatus = 0;
void piscaLedBT()
{

 
  if (passo < 324 and passo >= 308)
  {
     tempoStatusBT.defiSP(50);
  }
  if (passo >= 324 and passo < 332)
  {
     tempoStatusBT.defiSP(300);
  }
  if (passo >= 332)
  {
    tempoStatusBT.defiSP(1500);
  }
 
 if (passo < 308)
  {
    digitalWrite (10, 1); 
  }
  
  else if (tempoStatusBT.Saida(1))
  {
    luzStatus = 1 - luzStatus;
    digitalWrite (10, luzStatus);
    tempoStatusBT.Saida(0);
  }
}








String verificador;
String economizaRAM(char enviarGSM[])
{
  verificador = "";

  for (int k = 0; k < strlen_P(enviarGSM); k++) {
    verificador += char(pgm_read_byte_near(enviarGSM + k));
  }

  return verificador;

}



/*

void imprimeSIM800(char enviarGSM[])
{

  for (int k = 0; k < strlen_P(enviarGSM); k++) {
    mySerial.print(char(pgm_read_byte_near(enviarGSM + k)));
  }

  mySerial.println();
}
*/
