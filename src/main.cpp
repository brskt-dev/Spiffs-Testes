#include <Arduino.h>
#include <SPIFFS.h>

typedef struct struct_message
{
    char mac[18];
    char date[30];
} struct_message;

File file;
char mac_addr[18] = "58:BF:25:82:C7:88";
struct_message myData;

void setup() {
  Serial.begin(115200);
  
  stpcpy(myData.mac, mac_addr);

  if(!SPIFFS.begin(true))
  {
    Serial.println("Erro ao montar SPIFFS");
    return;
  }

  file = SPIFFS.open("/testes.txt", FILE_WRITE);
  if(!file){
    Serial.println("Erro ao abrir arquivo para leitura");
    return;
  }

  file.print(myData.mac);
  file.close();

}

void loop() {
  file = SPIFFS.open("/testes.txt", FILE_READ);
  
  Serial.println("Conteudo do arquivo: ");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
  
}