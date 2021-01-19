#include <libs.h>

//// VARs ////

bool lastStateRED = LOW;
bool lastStateGREEN = LOW;

int current_mode = 0; // mode 0 -> éteint ou configuration / mode 1 -> standard / mode 2 -> économique / mode 3 -> maintenance
int *pt_current_mode = &current_mode;

//// FUNCTIONs ////

// MODES
void mode_standard()
{
    green();
}
void mode_configuration()
{
    yellow();
}
void mode_economique()
{
    blue();
}
void mode_maintenance()
{
    orange();
}

// SETMODE
void setMode()
{
    if (*pt_current_mode == 0)
    {
      if (currentStateRed == LOW && currentStateGreen == LOW)
      {
        mode_standard();
        *pt_current_mode = 1;
      }
      if (currentStateRed == HIGH && currentStateGreen == LOW)
      {
        mode_configuration();
        *pt_current_mode = 0;
      }
    }
    if (*pt_current_mode == 1)
    {
      if (RED_BUTTON_5S == false && GREEN_BUTTON_5S == true)
        {
            mode_economique();
            *pt_current_mode = 2;
            GREEN_BUTTON_5S = false;
        }
      if (RED_BUTTON_5S == true && GREEN_BUTTON_5S == false)
        {
            mode_maintenance();
            *pt_current_mode = 3;
            RED_BUTTON_5S = false;
        }
    }
    if (*pt_current_mode == 2)
    {
      if (RED_BUTTON_5S == true && GREEN_BUTTON_5S == false)
        {
            mode_maintenance();
            *pt_current_mode = 3;
            RED_BUTTON_5S = false;
        }
      if (RED_BUTTON_5S == false && GREEN_BUTTON_5S == true)
        {
            mode_standard();
            *pt_current_mode = 1;
            GREEN_BUTTON_5S = false;
        }
    }
    if (*pt_current_mode == 3)
    {
      if (RED_BUTTON_5S == false && GREEN_BUTTON_5S == true)
        {
            mode_economique();
            *pt_current_mode = 2;
            GREEN_BUTTON_5S = false;
        }
      if (RED_BUTTON_5S == true && GREEN_BUTTON_5S == false)
        {
            mode_standard();
            *pt_current_mode = 1;
            RED_BUTTON_5S = false;
        }
    }
}

// BOUTONS
void RED_B()
{
  currentStateRed = digitalRead(BUTTON_RED);

  if (lastStateRED == HIGH && currentStateRed == LOW)
  {
  pressedTime = millis();
  }
    if (lastStateRED == LOW && currentStateRed == HIGH)
    {
      currentTime = millis();

      if (currentTime - pressedTime >= LONG_PRESS_TIME)
      {
        RED_BUTTON_5S = true;
        setMode();
      }
    }

  lastStateRED = currentStateRed;
}
void GREEN_B()
{
  currentStateGreen = digitalRead(BUTTON_GREEN);

  if (lastStateGREEN == HIGH && currentStateGreen == LOW)
  {
    pressedTime = millis();
  }
    if (lastStateGREEN == LOW && currentStateGreen == HIGH)
    {
      currentTime = millis();

      if (currentTime - pressedTime >= LONG_PRESS_TIME)
      {
        GREEN_BUTTON_5S = true;
        setMode();
      }
    }

  lastStateGREEN = currentStateGreen;
}

// ERREURS
void clockError()
{
  bool STATE_BLUE = 1;
  unsigned long prevMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= INTERVAL)
  {
    if (STATE_BLUE == 1)
    {
      blue(); 
      STATE_BLUE = !STATE_BLUE;
      prevMillis = currentMillis;
    }
	else
    {
      red();
      STATE_BLUE = !STATE_BLUE;
      prevMillis = currentMillis;
    }
  }
}
void gpsError()
{
  bool STATE_RED = 1;
  unsigned long prevMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= INTERVAL)
  {
    if (STATE_RED == 1)
    {
      red(); 
      STATE_RED = !STATE_RED;
      prevMillis = currentMillis;
    }
	else
    {
      yellow();
      STATE_RED = !STATE_RED;
      prevMillis = currentMillis;
    }
  }
}
void sensorError()
{
  bool STATE_RED = 1;
  unsigned long prevMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= INTERVAL)
  {
    if (STATE_RED == 1)
    {
      red(); 
      STATE_RED = 0;
      prevMillis = currentMillis;
    }
	else
    {
      green();
      STATE_RED = 1;
      prevMillis = currentMillis;
    }
  }
}
void dataError() 
{
  bool STATE_RED = 1;
  unsigned long prevMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= INTERVAL && STATE_RED == 1)
  {
    red();
    STATE_RED = 0;
    prevMillis = currentMillis;
  }
  else
  {
    if (currentMillis - prevMillis >= INTERVAL*2 && STATE_RED != 1)
    {
      green();
      STATE_RED = 1;
      prevMillis = currentMillis;
    }
  }
}
void sdFull()
{
  bool STATE_RED = 1;
  unsigned long prevMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= INTERVAL)
  {
    if (STATE_RED == 1)
    {
      red(); 
      STATE_RED = 0;
      prevMillis = currentMillis;
    }
	else
    {
      white();
      STATE_RED = 1;
      prevMillis = currentMillis;
    }
  }
}
void sdError() 
{
  bool STATE_RED = 1;
  unsigned long prevMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= INTERVAL && STATE_RED == 1)
  {
    red();
    STATE_RED = 0;
    prevMillis = currentMillis;
  }
  else
  {
    if (currentMillis - prevMillis >= INTERVAL*2 && STATE_RED != 1)
    {
      white();
      STATE_RED = 0;
      prevMillis = currentMillis;
    }
  }
}

// ACQUISITION
void acquisitionCapteurs(){
  static int previousMillis;
  int currentMillis = millis();
  LOG_INTERVAL = LOG_INTERVAL * 60000;
  if(currentMillis - previousMillis >= LOG_INTERVAL){
    previousMillis = currentMillis;
    DateTime now = rtc.now();
    float luminValue = 0;
    float temperature = 0;
    float pression = 0;
    float humidite = 0;
  if(LUMIN == 1){luminValue = analogRead(0);}
  if(TEMP_AIR == 1){temperature = bme.readTemperature();}
  if(PRESSURE == 1){pression = bme.readPressure() / 100;}
  if(HYGR == 1){humidite = bme.readHumidity();}

  ANNEE = now.year();
  MOIS = now.month();
  JOUR = now.day();
  HEURE = now.hour();
  MINUTE = now.minute();
  SECONDE = now.second();

  if(current_mode != 3){
    sdcard_file = (SD.open("log.txt", FILE_WRITE));
    if (sdcard_file) {
          sdcard_file.print(HEURE, DEC);
          sdcard_file.print(":");
          sdcard_file.print(MINUTE, DEC);
          sdcard_file.print(":");
          sdcard_file.print(SECONDE, DEC);
          sdcard_file.print(" | ");
          
          if(luminValue != NULL){
              sdcard_file.print(luminValue);
              sdcard_file.print(" lux");
              sdcard_file.print(" | ");}
          else{sdcard_file.print("  N/A  | ");}
          
          if(temperature != NULL){
            if(temperature < MIN_TEMP_AIR || temperature > MAX_TEMP_AIR){
              dataError();
              sdcard_file.print("N/A");}
            else{
                sdcard_file.print(temperature);
                sdcard_file.print(" °C");
                sdcard_file.print(" | ");}}
          
          if(pression != NULL){
            if(pression < PRESSURE_MIN || pression > PRESSURE_MAX){
              dataError();
              sdcard_file.print("N/A");}
            else{
                sdcard_file.print(pression);
                sdcard_file.print(" hPa");
                sdcard_file.print(" | ");}}
          
          if(humidite != NULL){
            if(humidite < HYGR_MINT || humidite > HYGR_MAXT){
              dataError();
              sdcard_file.print("N/A");}
            else{
              sdcard_file.print(humidite);
              sdcard_file.print(" %");}}

          sdcard_file.println();
          sdcard_file.close();
        }
      else {
          sdError();}
      }
      else {
    Serial.print(HEURE);
    Serial.print(":");
    Serial.print(MINUTE);
    Serial.print(":");
    Serial.print(SECONDE);
    Serial.print(" | ");

    Serial.print(luminValue);
    Serial.print(" lux | ");

    Serial.print(temperature);
    Serial.print(" °C | ");

    Serial.print(pression);
    Serial.print(" hPa | ");

    Serial.print(humidite);
    Serial.print(" %");

    Serial.println();
  }
  }
}

// CONFIGURATION
void CONFIG()
{
  String setting;

  Serial.println("+======================================================+");
  Serial.println("Voici les differents mots-cles pour modifier les parametres principaux");
  Serial.println();
  Serial.println("Intervalle : Modifier l'intervalle entre 2 mesures");
  Serial.println("Taille : Modifier la taille maximale en octets d'un fichier");
  Serial.println("Timeout : Modifier la duree a partir de laquelle l'acquisition des donnees est abandonnee si il n'y a acune reponse des capteurs");
  Serial.println("+======================================================+");
  Serial.println();
  Serial.println("Quel parametre voulez vous modifier ?");
  setting = Serial.read();
  
  if (setting == "Intervalle")
  {
  	Serial.println("Entrez la valeur souhaitee");
	  LOG_INTERVAL =Serial.read();
  }
  else if (setting == "Taille")
  {
  	Serial.println("Entrez la valeur souhaitee");
  	FILE_MAX_SIZE = Serial.read();
  }
  else if (setting == "Timeout")
  {
  	Serial.println("Entrez la valeur souhaitee");
  	TIMEOUT = Serial.read();
  }
  else
  {
  	Serial.println("Valeur incorrecte");
  }
}
void CLOCK()
{
    Serial.println("Entrez le chiffre des heures");
    HEURE = Serial.read();
    if (HEURE < 0 && HEURE > 23)
    {
     HEURE = 1;
     Serial.println("Heure invalide");	
	}
	Serial.println("Entrez le chiffre des minutes");
	MINUTE = Serial.read();
	if (MINUTE < 0 && MINUTE > 59)
	{
	 MINUTE = 1;
	 Serial.println("Minutes invalides");
	}
	Serial.println("Entrez le chiffre des secondes");
	SECONDE = Serial.read();
	if (SECONDE <0 && SECONDE > 59)
	{
	 SECONDE = 1;
	 Serial.println("Secondes invalides");
	}
}
void DATE()
{
    Serial.println("Entrez le mois (1 = Janvier, 2 = F�vrier etc...)");
    MOIS = Serial.read();
    if (MOIS < 1 && MOIS > 12)
    {
     MOIS = 1;
     Serial.println("Mois invalide");
	}
	Serial.println("Entrez le jour");
	JOUR = Serial.read();
	if (JOUR < 1 && JOUR > 31)
	{
	 JOUR = 1;
	 Serial.println("Jour invalide");
	}
	Serial.println("Entrez l'ann�e");
	ANNEE = Serial.read();
	if (ANNEE <2000 && ANNEE > 2099)
	{
	 ANNEE = 2000;
	 Serial.println("Ann�e invalide");
	} 
}
char DAY()
{
    Serial.println("+==============================================+");
    Serial.println("Voici les differents mots-cles à utiliser pour selectionner un jour :");
    Serial.println();
    Serial.println("MON = Lundi | TUE = Mardi | WED = Mercredi | THU = Jeudi");
    Serial.println("FRI = Vendredi | SAT = Samedi | SUN = Dimanche");
    Serial.println("+==============================================+");
    Serial.println();
    Serial.println("Entrez le jour");
    jSEMAINE = Serial.read();
    if (jSEMAINE != "MON" || jSEMAINE != "TUE" || jSEMAINE != "WED" || jSEMAINE != "THU" || jSEMAINE != "FRI" || jSEMAINE != "SAT" || jSEMAINE != "SUN")
    {
     jSEMAINE = "MON";
     Serial.println("Jour invalide");
	  }
    return 0;
}
void RESET()
{
	LOG_INTERVAL = 10;
	FILE_MAX_SIZE = 4096;
	TIMEOUT = 30;

	LUMIN = 1;
	LUMIN_LOW = 255;
	LUMIN_HIGH = 768;

	TEMP_AIR = 1;
	MIN_TEMP_AIR = -10;
	MAX_TEMP_AIR = 60;

	HYGR = 1;
	HYGR_MINT = 0;
	HYGR_MAXT = 80;

	PRESSURE = 1;
	PRESSURE_MIN = 850;
	PRESSURE_MAX = 1080;
}
void changerVERSION()
{
    Serial.print("La version du programme est ");
    Serial.print(VERSION);
    Serial.print(" et le numero de lot est ");
    Serial.println(LOT);
}
void HELP()
{
	Serial.println("+================================+");
	Serial.println("Voici les differents mots-cles pour appeler les differentes fonctions :");
	Serial.println();
	Serial.println("- CONFIG : Sert à configurer le temps entre 2 acquisitions, la taille max d'un fichier ou la duree sans reponse à partir de laquelle l'acquisition des donnees");
	Serial.println("- CLOCK : Sert à modifier l'heure du systeme");
	Serial.println("- DATE : Sert à modifier la date du systeme");
	Serial.println("- DAY : Sert à modifier le jour du systeme (lundi, mardi etc...)");
	Serial.println("- RESET : Remet tous les parametres à leurs valeurs par defaut");
	Serial.println("+================================+");
}

// INTERRUPTION
void INTERRUPTION()
{
  attachInterrupt(digitalPinToInterrupt(BUTTON_RED), RED_B, HIGH);
  attachInterrupt(digitalPinToInterrupt(BUTTON_GREEN), GREEN_B, HIGH);
}

//// MAIN ////

void setup () {
  Serial.begin(9600);

  pinMode(BUTTON_RED, INPUT);
  pinMode(BUTTON_GREEN, INPUT);
  INTERRUPTION();
  setMode();
  
  if (!rtc.begin()){
    clockError();
  }

  if (! rtc.isrunning()) {
   Serial.println("RTC is NOT running!");
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));    //ajuste la date de l'horloge à la date de compilation
  }

  if (!bme.begin(0x76)) {
    sensorError();
  }

  if (!SD.begin(4))
  {
    sdError();
  }

 
}

void loop() {
  if(current_mode != 0){
    acquisitionCapteurs();
    Serial.println("Debut delay");
    delay(2000);
    Serial.println("Fin Delay");}
}
