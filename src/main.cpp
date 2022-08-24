#include <Arduino.h>
#include <SPIFFS.h>

typedef struct struct_message
{
    char mac[18];
    char date[30];
} struct_message;

File file;
String txt;
time_t horaInicio, horaFinal;
char mac_addr[18] = "19:ED:33:49:L3:BR";
char date_addr[30] = "00/00/2000;01:28:45";

char date_1[30] = "01:28:00";
char date_2[30] = "01:48:00";
double diff_t;
struct_message myData;

void calcDif()
{
  horaInicio = (time_t) atoll(date_1);
  horaFinal = (time_t) atoll(date_2);

  diff_t = difftime(horaFinal, horaInicio);
}

void setup() {
  Serial.begin(115200);
  
  calcDif();

  stpcpy(myData.mac, mac_addr);
  stpcpy(myData.date, date_addr);

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

  file = SPIFFS.open("/testes.txt", FILE_APPEND);
  file.print(myData.date);
  file.close();

}

void loop() {
  file = SPIFFS.open("/testes.txt", FILE_READ);

  Serial.print("Conteudo do arquivo: ");
  while (file.available())
    txt = file.readString();

  file.close();
  Serial.println(txt);

  Serial.print("Diferença de tempo: ");
  Serial.println(diff_t);
  delay(3000);

}