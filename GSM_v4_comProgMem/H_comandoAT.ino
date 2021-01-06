byte setaEnv = 0;

byte comando1_SIM800(String atEnviar, String Confirmacao, int etapaOK, int etapaRuim, long tempoFalha)
{

  tempoFalhaPasso.defiSP(tempoFalha);

  String retorno = "";
  retorno = "";


  if (!setaEnv)
  {
    mySerial.listen();
    mySerial.println(atEnviar);
    setaEnv = 1;
  }



  delay(50);// delay para possibilita a comunicação

  while (mySerial.available())
  {
    retorno += char(mySerial.read());
  }

  if (retorno != "")
  {
    Serial.println(retorno);
    tempoFalhaPasso.Saida(0);
  }


  if ( retorno.indexOf(Confirmacao) != -1)
  {
    passo = etapaOK;
    setaEnv = 0;
  }



  if (tempoFalhaPasso.Saida(1))
  {
    passo = etapaRuim;
    tempoFalhaPasso.Saida(0);
    setaEnv = 0;
  }


}





byte comando2SIM800(String atEnviar, String Confirmacao1, String Confirmacao2, int etapaOK1, int etapaOK2, int etapaRuim,  long tempoFalha)
{
  tempoFalhaPasso.defiSP(tempoFalha);
  String retorno = "";
  retorno = "";

  if (!setaEnv)
  {
    mySerial.listen();
    mySerial.println(atEnviar);
    setaEnv = 1;
  }


  delay(50);// delay para possibilita a comunicação

  while (mySerial.available())
  {
    retorno += char(mySerial.read());
    tempoFalhaPasso.Saida(0);
  }


  if (retorno != "")
  {
    Serial.println(retorno);
  }


  if ( retorno.indexOf(Confirmacao1) != -1)
  {
    passo = etapaOK1;
    setaEnv = 0;
  }

  else if ( retorno.indexOf(Confirmacao2) != -1)
  {
    passo = etapaOK2;
    setaEnv = 0;
  }



  else if (tempoFalhaPasso.Saida(1))
  {
    passo = etapaRuim;
    setaEnv = 0;
    tempoFalhaPasso.Saida(0);
  }


}






int passoOld = 0;

void imprimePasso()
{

  if (passo != passoOld)
  {
    Serial.println();
    Serial.print(economizaRAM(mPasso));
    Serial.println(passo);
    passoOld = passo;
  }

}









byte seta1 = 0;

void logicaReset()
{
  if (!seta1)
  {
    seta1 = 1;
    Serial.println(economizaRAM(mReset));
  }

  statusSIM800 = 0;
  saidaReset = 1;

  if (temp1500.Saida(1))
  {
    saidaReset = 0;

    if (temp200.Saida(1))
    {

      temp1500.Saida(0);
      temp200.Saida(0);
      passo = 20;
      seta1 = 0;
    }
  }

  if (tipoPlaca == 0)
  {
    mcp.digitalWrite(3, saidaReset);
 
    mcp.digitalWrite(12, 1 - saidaReset);
  }
  else  digitalWrite(A5, 1 - saidaReset);
}



// comando , condicao de sucesso, para onde ir se sucesso, para onde ir se fracasso
// acoes possíveis: ir ao próximo passo, resetar sim800             implementar as 2, e levantar outras



byte comandoR_SIM800(String atEnviar, String Confirmacao, int etapaOK, int etapaRuim, long tempoFalha)
{

  tempoFalhaPasso.defiSP(tempoFalha);

  String retorno = "";
  retorno = "";



  mySerial.listen();
  mySerial.println(atEnviar);

  delay(50);// delay para possibilita a comunicação

  while (mySerial.available())
  {
    retorno += char(mySerial.read());
  }

  if (retorno != "")
  {
    Serial.println(retorno);
    tempoFalhaPasso.Saida(0);
  }
  if ( retorno.indexOf(Confirmacao) != -1) passo = etapaOK;

  // reseta a cada 6 segundos sem mudar de status
  if (tempoFalhaPasso.Saida(1))
  {
    passo = etapaRuim;
    tempoFalhaPasso.Saida(0);
  }


}
