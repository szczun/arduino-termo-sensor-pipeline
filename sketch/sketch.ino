void setup(){ 
   Serial.begin(9600);
}

void loop(){
    int sensorPin = A0;
    float ADCres = 1023.;
    float beta = 3950;
    float kelvin = 273.15;
    float Rb = 10000;
    float Ginf = 120.6685;
    float Rterm = Rb * (ADCres / analogRead(sensorPin) - 1);
    float tempC = beta / (log(Rterm * Ginf));

    Serial.println(tempC - kelvin);
    delay(1000);
}
