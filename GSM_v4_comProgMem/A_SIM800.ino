/*
   informa se é 800C ou L
   se o reset será com MCP ou sem


  criar uma função para start do sim800c

  seleciona se é 800L ou C

  tentar ter as váriaveis, bibliotecas, funcao de setup e loop na aba,

  sendo que no código chamará o setup e o loop somente

  funcoes para BT e GSM


  função para pareamento


  FUNCAO 1:
  função para conexão bluetooth

  inicia com: somente GPRS, GPRS e Bluetooth
  com mcp ou sem mpc

  retorno com inicio ok

  SIM800L deve ir at até chegar o SMS Ready
  SIM880C se resetar e vier o NORMAL POWER DOWN, já pode resetar novamente

  se não é at até o smsready

  3 chances de reset

*/
#include <SoftwareSerial.h>
SoftwareSerial mySerial(A3, A2); // RX, TX

Tempora tempoFalhaPasso;
Tempora temp200;
Tempora temp1500;
Tempora delayLeitura;
Tempora tempoTrocaPasso;
Tempora tempoStatusBT;

byte statusSIM800 = 0; // 1 sendo resetado, 2 aguardando retorno de At, 3 aguardano SMS Ready
byte tipoPlaca = 0; // 0 se tiver MCP e 1 se for sem MCP

byte saidaReset = 0; // colocar o estado normal;


void setupSIM800(byte placa)
{

  pinMode(10, OUTPUT); //Status do BT
  digitalWrite(10,0);
  temp200.defiSP(1500);
  temp1500.defiSP(1500);
  

  if (placa == 0)
  {
    mcp.begin();
    //serve somente para visualizar quando resetou o sim800
    mcp.pinMode(12, OUTPUT);
    mcp.digitalWrite(12, 1);


    mcp.pinMode(3, OUTPUT);
    mcp.digitalWrite(3, 0);


  }
  else
  {
    pinMode(A5, OUTPUT);
    digitalWrite(A5, saidaReset);
    digitalWrite(A5, 1);
  }



  tipoPlaca = placa;
  delay(100);
  mySerial.begin(bd);

}
