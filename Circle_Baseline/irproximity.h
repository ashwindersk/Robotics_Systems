#ifndef _IRProximity_h
#define _IRProximity_h

class SharpIR {
    public:
        SharpIR(byte pin);
        int getDistanceRaw();
        float getDistanceInMM(float distance);
        void calibrate(float distance);
        float getDistanceCalibrated();

    private:
        byte pin;
        float delta;
        int NUM_OF_READINGS = 400;
};

SharpIR::SharpIR(byte _pin) {
  pin = _pin;
}

int SharpIR::getDistanceRaw( ) {
    return analogRead(pin);
}


void SharpIR::calibrate(float distance){
  // user specificies distance it will be calibrated to
  // difference is calculated over NUM_OF_READINGS
  // return difference
  float totalValues = 0.0f;
  float avgMM = 0.0f;

  for (int i = 0; i< NUM_OF_READINGS; i++){
    totalValues += getDistanceRaw(); 
  }
  
  float avgValue = totalValues/NUM_OF_READINGS; // find the average
  avgMM = getDistanceInMM(avgValue); //convert to MM
  delta = distance - avgMM; // find difference

  
  Serial.println("delta: " + (String)delta);
  Serial.println("distance: " + (String)distance);
  Serial.println("avgMM: " + (String)avgMM);
}

float SharpIR::getDistanceCalibrated(){
  return getDistanceInMM(getDistanceRaw()) + delta;
}

/*
 * This piece of code is quite crucial to mapping
 * obstacle distance accurately, so you are encouraged
 * to calibrate your own sensor by following the labsheet.
 * Also remember to make sure your sensor is fixed to your
 * Romi firmly and has a clear line of sight!
 */
float SharpIR::getDistanceInMM(float distance) {
    
    // map this to 0 : 5v range.
    distance *= 0.0048;

    const float exponent = (1/-0.616);
    distance = pow( ( distance / 12.494 ), exponent);
    distance *= 10; // to mm.
       
    return distance;
}


#endif
