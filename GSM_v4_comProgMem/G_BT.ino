const char mReset[] PROGMEM = "reseta SIM";
const char mPasso[] PROGMEM = "passo ";
const char mEnvio300[] PROGMEM = "AT+BTSTATUS?";
const char mRec1_300[] PROGMEM = "BTSTATUS: 0";
const char mRec2_300[] PROGMEM = "BTSTATUS: 5";
const char mEnvio304[] PROGMEM = "AT+BTPOWER=1";
const char mRec1_308[] PROGMEM = "+BTCONNECTING";
const char mRec2_308[] PROGMEM = "BTCONNECT:";
const char mRec3_308[] PROGMEM = "+BTPAIRING";

const char  mEnvio312[] PROGMEM = "AT+BTPAIR=1,1";
const char  mRec1_312[] PROGMEM = "+BTDISCONN";

const char  mEnvio316[] PROGMEM = "AT+BTSPPCFG=\"MC\",1";
const char  mEnvio320[] PROGMEM = "AT+BTSPPCFG=\"MC\",2";

const char  mRec1_324[] PROGMEM = "+BTCONNECTING";
const char  mEnvio328[] PROGMEM = "AT+BTACPT=1";

const char  mEnvio332[] PROGMEM = "AT+BTSPPCFG?";


const char  mRec1_332[] PROGMEM = "+BTSPPDATA:";
const char  mRec2_332[] PROGMEM = "+BTSPPCFG: S";






void sim800_BT()
{

  debugSIM800();
  piscaLedBT();

  if (passo == 300)
  {
    imprimePasso();
    comando2SIM800(economizaRAM(mEnvio300), economizaRAM(mRec1_300), economizaRAM(mRec2_300), 304, 308, 10, 2000);

  }


  if (passo == 304)
  {
    imprimePasso();
    comando1_SIM800(economizaRAM(mEnvio304), economizaRAM(mOK), 308, 10, 5000);

  }


  if (passo == 308)
  {
    imprimePasso();

    String retorno = leRetorno(1000);

    if (retorno != "")
    {
      Serial.print(retorno);
      if ( retorno.indexOf(economizaRAM(mRec1_308)) != -1) passo = 328;
      else if ( retorno.indexOf(economizaRAM(mRec2_308)) != -1) passo = 324;
      else if ( retorno.indexOf(economizaRAM(mRec3_308)) != -1) passo = 312;

    }
    zeraPasso332();

  }


  if (passo == 312)
  {
    imprimePasso();
    //   comando2SIM800("AT+BTPAIR=1,1", "+BTDISCONN:", "BTCONNECT", 316, 316, 308, 20000);  // +BTDISCONN: se for o tablet     no celular galaxu é BTCONNECT:
    comando2SIM800(economizaRAM(mEnvio312), economizaRAM(mRec1_312), economizaRAM(mRec2_308), 316, 316, 308, 20000);
  }


  if (passo == 316)
  {
    imprimePasso();
    // comando1_SIM800("AT+BTSPPCFG=\"MC\",1", "OK", 320, 308, 2000);
    comando1_SIM800( economizaRAM(mEnvio316) , economizaRAM(mOK), 320, 308, 2000);
  }


  if (passo == 320)
  {
    imprimePasso();
    //   comando1_SIM800("AT+BTSPPCFG=\"MC\",2", "OK", 324, 308, 2000);
    comando1_SIM800( economizaRAM(mEnvio320) , economizaRAM(mOK), 324, 308, 2000);
  }


  if (passo == 324)
  {
    imprimePasso();

    String retorno = leRetorno(100);

    if (retorno != "")
    {

      Serial.print(retorno);

      if ( retorno.indexOf(economizaRAM(mRec1_312)) != -1) passo = 308;
      else if ( retorno.indexOf(economizaRAM(mRec1_324)) != -1) passo = 328;

    }


    //  debugSIM800();

  }


  if (passo == 328)
  {
    imprimePasso();
    //  comando1_SIM800("AT+BTACPT=1", "+BTCONNECT", 332, 308, 3000);
    comando1_SIM800(economizaRAM(mEnvio328), economizaRAM(mRec2_308), 332, 308, 3000);
  }




  if (passo == 332)
  {
    imprimePasso();


    tempConectado1.defiSP(20000);
    tempConectado2.defiSP(2000);

    if (tempConectado1.Saida(1))
    {
      setaConecta = 1;
      tempConectado1.Saida(0);
    }

    if (tempConectado2.Saida(setaConecta) )
    {
      setaConecta = 0;
      tempConectado2.Saida(0);
    }

    if (setaConecta != setaOldConecta)
    {

      if (!setaOldConecta)
      {

        mySerial.listen();
        // mySerial.println("AT+BTSPPCFG?");
        mySerial.println(economizaRAM(mEnvio332));
      }
      else
      {
        passo = 308;
        zeraPasso332();
      }
      setaOldConecta = setaConecta;
    }


    String retorno = leRetorno(100);
    if (retorno != "")
    {

      Serial.println(retorno);

      // if ( retorno.indexOf("+BTDISCONN") != -1)
      if ( retorno.indexOf(economizaRAM(mRec1_312)) != -1)
      {
        passo = 308;
      }

      //    if ( retorno.indexOf("+BTSPPDATA:") != -1)
      else if ( retorno.indexOf(economizaRAM(mRec1_332)) != -1)
      {
        zeraPasso332();
      }

      //    if ( retorno.indexOf("+BTSPPCFG: S") != -1 and setaConecta)
      else if ( retorno.indexOf(economizaRAM(mRec2_332)) != -1 and setaConecta)
      {
        zeraPasso332();
      }
    }
  }

}



void zeraPasso332()
{

  setaConecta = 0;
  setaOldConecta = 0;
  tempConectado1.Saida(0);
  tempConectado2.Saida(0);
}
