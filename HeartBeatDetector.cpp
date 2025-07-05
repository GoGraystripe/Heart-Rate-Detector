// Arduino code
float alpha = 0.1;
float smoothed_data = 0;
float previous_data = 0;
float IBI = 0;
float bpm  = 0;

unsigned long currentTime = 0;
unsigned long lastBeatTime = 0;



int threshold = 520; //adjustable
bool pulseDetected = false;

void setup(){
    Serial.begin(9600);
}


void loop() {

    int raw_data = analogRead(A0);

    //EMA
    smoothed_data = (1 - alpha) * raw_data + alpha * previous_data;
    previous_data = smoothed_data;

    //Record beat
    
    if(smoothed_data > threshold && !pulseDetected) {
        
        currentTime = millis();
        IBI = currentTime - lastBeatTime;
        bpm = 60000 / IBI;
        lastBeatTime = currentTime;

        pulseDetected = true;

        if(bpm > 30 && bpm < 250){
            Serial.print("BPM: ");
            Serial.println(bpm);
        }
    }
    else if(smoothed_data < threshold){
        pulseDetected = false;
    }
}