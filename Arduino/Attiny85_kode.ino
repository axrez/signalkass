unsigned long comTimeOut = 10;
unsigned long comTimer;
unsigned long comInitTime;
bool comInitFlag = false;
bool startComFlag = false;

bool autoFlag = true;

uint8_t comInitDelay = 10;
uint8_t clockCounter;

uint8_t autoAdjustDelay = 500;
volatile bool adjustFlag = false;

uint8_t diodeOffset = 100;

void setup() {
  
  TCCR1 &= ~( (1<<COM1A1)|(1<<COM1A0) );
  TCCR1 &= ~( (1<<COM1B1)|(1<<COM1B0) );

  TCCR1 |= (1 << CTC1);  
  TCCR1 &= (0 << CS13) | (0 << CS12) | (0 << CS11) | (0 << CS10);
  TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10); 
  OCR1A = autoAdjustDelay; 
  TIMSK |= (1 << OCIE1A); 
    
  sei();

  TCNT1 = 0;
  
  DDRB &= ~(1 << PB4);
  DDRB |= 0b00000011;

  DDRB &= ~(1 << PB2);

  PORTB &= ~(0b00000011);
  
}

void loop() {
  
  checkForCom();
  if (startComFlag == true) {
    startComFlag = false;
    execCom();
  }
  
  if (autoFlag) {
    regulateAmplification(analogRead(PB2));
  }
  
}

void checkForCom() {
  if (digitalRead(PB4) == 1 && comInitFlag == false) {
    comInitTime = millis(); 
    comInitFlag = true;
  } else if (digitalRead(PB4) == 1 && (millis() - comInitTime) > comInitDelay && comInitFlag == true) {
    startComFlag = true;
    comInitFlag = false;
  } else if (digitalRead(PB4) == 0) {
    comInitFlag = false;
  }
}

void execCom() {
  clockCounter = 0;
  comTimer = millis();
  
  while (true) {
    if (digitalRead(PB4) == clockCounter % 2) {
      clockCounter++;
      comTimer = millis();
    } else if (millis() - comTimer > comTimeOut) {
      break;
    }
  }
  
  if (clockCounter > 8) {
    
    autoFlag = false;
    PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB1);
    
  } else if (clockCounter > 5) {
    
    autoFlag = false;
    PORTB |= (1 << PB0);
    PORTB &= ~(1 << PB1);
    
  } else if (clockCounter > 2) {
    
    autoFlag = false;
    PORTB &= ~(1 << PB0);
    PORTB |= (1 << PB1);
    
  } else {
    autoFlag = true;
  }
  
}

void regulateAmplification(int inputSignal) {
  
  if (inputSignal > (512 + diodeOffset)) {
    
    PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB1);
    TCNT1 = 0;
    return;
    
  } else if (inputSignal > (338 + diodeOffset) ) {
    
    PORTB |= (1 << PB0);
    PORTB &= ~(1 << PB1);
    TCNT1 = 0;
    return;
    
  } else if (adjustFlag == true) {
    
    PORTB &= ~(1 << PB0);
    PORTB |= (1 << PB1);
    
  }
}

ISR(TIMER1_COMPA_vect) {
  reAdjust = true;
}
