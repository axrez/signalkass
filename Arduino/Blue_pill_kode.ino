#include <HardwareTimer.h>
#include <STM32ADC.h>
#include <SPI.h>
#include <cstdint>

#define pinLED  PC13
#define pinOUT  PB0

// A0 (adc1 channel 1)
uint8 pins = 0;

#define maxSamples  1024
uint16_t buffer[maxSamples];
uint16_t *buffers[2];
uint8_t bufr;
uint8_t bufw;

//uint16_t staticBuffer[maxSamples];

#define sampleFreqKhz       192*1000
#define samplePeriodus      1000 / sampleFreqKhz
#define ticksPerSecond      2 * sampleFreqKhz * 1000 / maxSamples

STM32ADC myADC(ADC1);

void DmaIRQ(void) {
  digitalWrite(pinOUT, ! digitalRead(pinOUT));
  bufw = (bufw + 1) % 2;
}

void setupSPI(void) {
  pinMode(PA7, INPUT);
  pinMode(PA6, INPUT);
  pinMode(PA5, INPUT);
  pinMode(BOARD_SPI_DEFAULT_SS, INPUT);

  SPI.setModule(1);
  SPI.beginTransactionSlave(SPISettings(800000, MSBFIRST, SPI_MODE0, DATA_SIZE_16BIT));
}

void setup() {

  pinMode(pinLED, OUTPUT);
  pinMode(pinOUT, OUTPUT);
  pinMode(pins, INPUT_ANALOG);

  Serial.begin(115200);
  delay(100);

  SPI.dev()->regs->DR = 42069;
  setupSPI();

  bufr = 0;
  bufw = 0;
  buffers[0] = &buffer[0];
  buffers[1] = &buffer[maxSamples / 2];

  Timer3.setPeriod(samplePeriodus);
  Timer3.setMasterModeTrGo(TIMER_CR2_MMS_UPDATE);

  myADC.calibrate();
  myADC.setSampleRate(ADC_SMPR_1_5);
  myADC.setPins(&pins, 1);
  myADC.setDMA(buffer, maxSamples, (DMA_MINC_MODE | DMA_CIRC_MODE | DMA_HALF_TRNS | DMA_TRNS_CMPLT), DmaIRQ);
  myADC.setTrigger(ADC_EXT_EV_TIM3_TRGO);
  myADC.startConversion();
}

void loop() {

  if (bufr != bufw) {
    bufr = (bufr + 1) % 2;
  }

  uint8_t comState(SPI.read());
  uint16_t *staticBuffer = buffer;
  //Serial.println(comState);

  for (int i = 0; i < maxSamples; i++) {
    SPI.dev()->regs->DR = buffer[i];
    SPI.read();
    //SPI.dev()->regs->DR = 42069;
  }

  /*
    switch (comState) {
    case 0:

      break;

    case 1:
      for (int i = 0; i < maxSamples; i++) {
        SPI.dev()->regs->DR = buffer[i]-2500;
        SPI.read();
        SPI.dev()->regs->DR = 42069;
      }
      break;

    case 2:
      break;

    default:
      break;
    }*/
}
