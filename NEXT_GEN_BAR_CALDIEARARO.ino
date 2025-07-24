#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define robot 26
#define gin 28
#define vodka 30
#define tonica 32
#define lemon 34
#define OLED_RESET 4
#define ml1 4500  //dichiaro i secondi durante i quali la pompa va attivata per erogare 100ml
#define ml2 9000
#define TRIG_PIN 13  //definisco i pin e dichiaro le variabili per il sensore ad ultrasuoni
#define ECHO_PIN 12
int i;
unsigned long tempo;
float distanza;
Adafruit_SSD1306 display(OLED_RESET);  // pin reset schermo
char valore = 's';                     //dichiarazione variabile
void setup() {
  pinMode(8, OUTPUT);                // led rosso (quando va basso si accende)
  pinMode(9, OUTPUT);                // led blu
  for (int i = 26; i <= 34; i += 2)  //26 robot, 28 gin, 30 vodka, 32 tonica, 34 lemon
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH); //de-eccito tutti i relè
  }
  pinMode(TRIG_PIN, OUTPUT);  //inizializzo il sensore ad ultrasuoni
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  Serial.begin(9600);
  Serial3.begin(9600);                        //comunicazione schermo oled
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //imposto l'indirizzo i2c
  display.clearDisplay();                     //puslisco il buffer da inviare al display
  display.setTextSize(3);                     //imposto la grandezza del testo
  display.setTextColor(WHITE);                //Imposta il colore del testo (Solo bianco)
  display.setCursor(0, 8);                    //Imposta la posizione del cursore (Larghezza,Altezza)
  display.println("TABLE ?");                 //Stringa da visualizzare
  display.display();                          //Invia il buffer da visualizzare al display
  led_blu();
  digitalWrite(TRIG_PIN, HIGH);  //misuro la distanza iniziale
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  tempo = pulseIn(ECHO_PIN, HIGH);
  distanza = 0.03438 * tempo / 2;
}

void loop() {
  led_blu();
  digitalWrite(TRIG_PIN, HIGH);  //misuro la distanza iniziale
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  tempo = pulseIn(ECHO_PIN, HIGH);
  distanza = 0.03438 * tempo / 2;
  ultrasuoni();
  while (Serial3.available()) {
    valore = char(Serial3.read());  //se la comunicazione è disponibile, ciò vuol dire che è stato mandato un segnale dal modulo bluethoot e quindi vado a memorizzare il segnale char dentro alla variabile "valore"
  }
  switch (valore) {  //ogni volta vengono mandati 2 impulsi, uno numerico che sarebbe il numero del tavolo e uno sotto forma di lettera, ad ogni lettera è stato associato un drink, ho creato quindi una funzione switch case che regola cosa fare in base a "valore"
    case '1':
      Serial.println("tavolo 1");  //verifica sul computer che tutto sia funzionante
      schermo();                   //ciclo per impostare i parametri dello schermo e scrivere già "table", dato che è questa parola è sempre presente
      display.println("1");        //scrivo il numero del tavolo
      display.display();           //aggiorno lo schermo
      valore = 's';                //valore diverso da quelli presenti nella funzione switch in modo da uscire dallo switch dato che con la funzione break il programma riparte dall'inizio della funzione switch e non memorizzerebbe nuovi segnali
      break;
    case '2':
      Serial.println("tavolo 2");
      schermo();
      display.println("2");
      display.display();
      valore = 's';
      break;
    case '3':
      Serial.println("tavolo 3");
      schermo();
      display.println("3");
      display.display();
      valore = 's';
      break;
    case '4':
      Serial.println("tavolo 4");
      schermo();
      display.println("4");
      display.display();
      valore = 's';
      break;
    case '5':
      Serial.println("tavolo 5");
      schermo();
      display.println("5");
      display.display();
      valore = 's';
      break;
    case '6':
      Serial.println("tavolo 6");
      schermo();
      display.println("6");
      display.display();
      valore = 's';
      break;
    case '7':
      Serial.println("tavolo 7");
      schermo();
      display.println("7");
      display.display();
      valore = 's';
      break;
    case '8':
      Serial.println("tavolo 8");
      schermo();
      display.println("8");
      display.display();
      valore = 's';
      break;
    case '9':
      Serial.println("tavolo 9");
      schermo();
      display.println("9");
      display.display();
      valore = 's';
      break;
    case 'A':
      Serial.println("GIN_LEMON");  //verifica sul computer che tutto sia funzionante
      ginlemon();                   //ciclo del drink richiesto
      valore = 's';                 //variabile diversa come spiegato sopra
      break;
    case 'B':
      Serial.println("GIN_TONIC");
      gintonic();
      valore = 's';
      break;
    case 'C':
      Serial.println("VODKA_LEMON");
      vodkalemon();
      valore = 's';
      break;
    case 'D':
      Serial.println("VODKA_TONIC");
      vodkatonic();
      valore = 's';
      break;
    case 'E':
      Serial.println("LEMON");
      lemonsoda();
      valore = 's';
      break;
    case 'F':
      Serial.println("TONICA");
      tonic();
      valore = 's';
      break;
    default:

      break;
  }
}
void schermo() {
  display.clearDisplay();     //pulisco il display
  display.setTextSize(3);     //imposto la grandezza del testo
  display.setCursor(0, 5);    //imposto la posizione del cursore
  display.println("TABLE");   //stringa da stampare
  display.display();          //aggiorno il display
  display.setTextSize(4);     //imposto la grandella del numero
  display.setCursor(100, 0);  //imposto la posizione del cursore pronto a stampare il numero (imposto la grandezza e posizione in questo void dato che è uguale per tutti i numeri)
}

void ginlemon() {
  led_rosso();
  digitalWrite(robot, LOW);
  delay(1000);
  digitalWrite(robot, HIGH);
  delay(24000);
  digitalWrite(gin, LOW);
  digitalWrite(lemon, LOW);
  delay(ml1);
  digitalWrite(gin, HIGH);
  digitalWrite(lemon, HIGH);
  delay(27000);
  led_blu();
}

void gintonic() {
  led_rosso();
  digitalWrite(robot, LOW);
  delay(1000);
  digitalWrite(robot, HIGH);
  delay(24000);
  digitalWrite(gin, LOW);
  digitalWrite(tonica, LOW);
  delay(ml1);
  digitalWrite(gin, HIGH);
  digitalWrite(tonica, HIGH);
  delay(27000);
  led_blu();
}

void vodkalemon() {
  led_rosso();
  digitalWrite(robot, LOW);
  delay(1000);
  digitalWrite(robot, HIGH);
  delay(24000);
  digitalWrite(vodka, LOW);
  digitalWrite(lemon, LOW);
  delay(ml1);
  digitalWrite(vodka, HIGH);
  digitalWrite(lemon, HIGH);
  delay(27000);
  led_blu();
}

void vodkatonic() {
  led_rosso();
  digitalWrite(robot, LOW);
  delay(1000);
  digitalWrite(robot, HIGH);
  delay(24000);
  digitalWrite(vodka, LOW);
  digitalWrite(tonica, LOW);
  delay(ml1);
  digitalWrite(vodka, HIGH);
  digitalWrite(tonica, HIGH);
  delay(27000);
  led_blu();
}

void lemonsoda() {
  led_rosso();
  digitalWrite(robot, LOW);
  delay(1000);
  digitalWrite(robot, HIGH);
  delay(24000);
  digitalWrite(lemon, LOW);
  delay(ml2);
  digitalWrite(lemon, HIGH);
  delay(22500);
  led_blu();
}

void tonic() {
  led_rosso();
  digitalWrite(robot, LOW);
  delay(1000);
  digitalWrite(robot, HIGH);
  delay(24000);
  digitalWrite(tonica, LOW);
  delay(ml2);
  digitalWrite(tonica, HIGH);
  delay(22500);
  led_blu();
}

void ultrasuoni() {
  while (distanza < 30)  //viene fatta una misurazione nel setup, se la distanza è minore di 30cm, il programma continua a effettuare registrazioni della distanza e rimane "bloccato" nel ciclo fino a quando la distanza non è maggiore di 30 cm, e quindi esce dal ciclo continuando con il resto del loop
  {
    digitalWrite(8, LOW);  //led rosso
    digitalWrite(9, HIGH);
    digitalWrite(TRIG_PIN, HIGH);  //misurazione distanza
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    tempo = pulseIn(ECHO_PIN, HIGH);
    distanza = 0.03438 * tempo / 2;
  }
  delay(100);
}

void led_blu() {
  digitalWrite(8, HIGH);  //imposto il led blu
  digitalWrite(9, LOW);
}

void led_rosso() {
  digitalWrite(8, LOW);  //imposto il led rosso
  digitalWrite(9, HIGH);
}