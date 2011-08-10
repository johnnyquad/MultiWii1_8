// Written by JH

// *************************************************************************
// ************************** LED Flash Class ******************************
// *************************************************************************
class LEDs {
public: 
  bool on;
protected:
  unsigned long previousTime;
  unsigned long flashTime;
public:
  LEDs(void) { 
    on = false;
  }

  virtual void initialize(int *ledPins, int count);
  virtual void run(unsigned long currentTime);
  
  bool canRun(unsigned long currentTime)
  {
    if(on)
    {
      if (currentTime > previousTime + flashTime){
        previousTime = currentTime;
        return true;
      }
    }
    return false;
  }
};

// *************************************************************************
// ************************** Flash All LEDs  ******************************
// *************************************************************************
class LEDs_FlashAll : LEDs{
private:
  int *pin;
  int numOfPins;
  bool state;
  bool flash;

public:
  LEDs_FlashAll() : LEDs(){}

  void initialize(int *ledPins, int count)
  {
    numOfPins = count;
    pin = (int *)malloc(count * sizeof(int));
    
    state = false;
    flash = false;
    for(int i = 0; i < numOfPins; i++)
    {
      pin[i] = ledPins[i];
      pinMode(pin[i], OUTPUT);
      digitalWrite(pin[i], HIGH); //turn on the LEDs
    }
  }
  
  void run(unsigned long currentTime)
  {
    if(canRun(currentTime))
    {
      if(flash)
      {
        state = !state;
        for(int i = 0; i < numOfPins; i++)
        {
          digitalWrite(pin[i], state);
        }
      }else if(!state)
      {
        //Serial.println("Turning ON");
        for(int i = 0; i < numOfPins; i++)
          digitalWrite(pin[i], HIGH);
        state = true;
      }
    }
  }
  
  void off()
  {
     on = false;
     state = false;
     for(int i = 0; i < numOfPins; i++)
       digitalWrite(pin[i], LOW);
  }

  void alwaysOn()
  {
    on = true;
    flash = false;
    flashTime = 0; 
  }
  
  void flashSlow()
  {
    on = true;
    flash = true;
    flashTime = 500000; 
  }
  
  void flashFast()
  {
    on = true;
    flash = true;
    flashTime = 100000; 
  }
  
  void flashFaster()
  {
    on = true;
    flash = true;
    flashTime = 50000; 
  }
  
};









