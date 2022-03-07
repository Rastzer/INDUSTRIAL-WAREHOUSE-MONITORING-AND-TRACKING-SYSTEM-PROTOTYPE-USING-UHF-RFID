#include <FlashStorage_STM32.h>

int led1 = PB12;
int led2 = PB13;
int EN = PA8;

int photoelectric1 = PB0;
int photoelectric2 = PA7;

int delay_single;
int counting_read;
int counting_request;
int datain = 0;
int condition_read = 0;
bool condition = false;
bool parsing = false;
bool pharse_data = false;
bool Read = false;
bool serial = false;

int condition_data = 0;

char read_rfid;
char dbase[50];

String data_read = "", data_rfid;
String data_pharse[50];
String rfid;

unsigned long timeA, timeB, timeC;
bool arduinouno = false, arduinonano = false, arduinopromini = false, arduinodue = false;
bool stm32blackpill = false, stm32bluepill = false;
bool arduinomega = false, esp32 = false;
bool arduinouno2 = false, arduinonano2 = false, arduinopromini2 = false, arduinodue2 = false;
bool stm32blackpill2 = false, stm32bluepill2 = false;
bool arduinomega2 = false, esp322 = false;

int countesp32 = 0, countmega = 0, countuno = 0, countnano = 0, countmini = 0, countdue = 0, countblack = 0, countblue = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("CLEARDATA");
  Serial.println("LABEL,Acolumn,Bcolumn,...");
  Serial.println("RESETTIMER");

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(EN, OUTPUT);

  pinMode(photoelectric1, INPUT);
  pinMode(photoelectric2, INPUT);

  digitalWrite(EN, HIGH);
  delay_single = 500;

  read_eeprom();
}

void loop() {
  // put your main code here, to run repeatedly:
  timeA = millis();
  //pembacaan sensor photolectric
  int read1 = digitalRead(photoelectric1);
  int read2 = digitalRead(photoelectric2);

  //kondisi ktika photoelectric 1 mmbaca
  if (read1 == LOW && condition == false) {
    //saat kondisi input 0 (belum ada kondisi masuk atau keluar)
    //deklarasikan kondisi menjadi data masuk
    if (condition_read == 0) {
      condition_read = 1;
      condition = true;
      datain = 1;
    }

    //saat kondisi sudah terdeklarasi meminta untuk mengirim data
    if (condition_read == 2) {
      condition_read = 0;
      condition = true;
      Read = true;
      datain = 0;
      condition_data = 1;
    }
  }

  //kondisi ktika photoelectric 2 membaca
  if (read2 == LOW && condition == false) {
    //saat kondisi input 0 (belum ada kondisi masuk atau keluar)
    //deklarasikan kondisi menjadi data keluar
    if (condition_read == 0) {
      condition_read = 2;
      condition = true;
      datain = 2;
    }

    //saat kondisi sudah terdeklarasi meminta untuk mengirim data
    if (condition_read == 1) {
      condition_read = 0;
      condition = true;
      Read = true;
      datain = 0;
      condition_data = 2;
    }
  }

  //untuk indikator led kondisi standby
  if (condition_read == 0) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
  //untuk indikator led kondisi membaca
  if (condition_read == 1 || condition_read == 2) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);

    //mengirim command pada sensor untuk membaca mode single read
    if (timeA - timeB > delay_single) {
      counting_request + 1;
      if (counting_request < 3) {
        Read_Single();
      }
      timeB = timeA;
    }
    serialevent1();
  }

  //mereset kondisi pada saat photoelectric membaca(lock kondisi ketika salah satu membaca, dan menreset kondisi ketika tidak ada yang membaca
  if (read1 == HIGH && read2 == HIGH) {
    condition = false;
  }

  //filtering data yang terbaca dan memulai pemrosesan pada database
  if (Read == true) {
    for (int i = 0; i < 50; i++) {
      if (data_pharse[i].length() > 20) {
        data_pharse[i].toCharArray(dbase, 50);
        database();
      }
      data_pharse[i] = "";
    }
    Read = false;
  }
}
