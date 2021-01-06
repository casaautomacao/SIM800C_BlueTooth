/*
 * antes da flash 33% de flash e 44% de RAM
 * 
 * Depois da flash 34% de flash e 32% de RAM
 * 
 */
#include <Crescer.h>
#include "Adafruit_MCP23017.h"
Adafruit_MCP23017 mcp;

Tempora tempImprimir;
Tempora tempConectado1;
Tempora tempConectado2;
byte setaConecta = 0;
byte setaOldConecta = 0;

long bd = 9600;
int passo = 10;



void setup() {
  // Open serial communications and wait for port to open:

  Serial.begin(bd);
  Serial.println("oi");


 setupSIM800(0); //0 se mcp ou 1 se for sem mcp

 // setupSIM800(1); //0 se mcp ou 1 se for sem mcp

}



void loop() {

  loopSIM800(4); // pensar em binário, sendo o bit0 para SMS, bit1 para GPRS e bit2 para BT, então o númer 7 que em binário é 111, habilita as 3 funções

}
