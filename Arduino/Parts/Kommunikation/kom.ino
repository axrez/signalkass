#define PARALLEL_0 32

void setup() {
  for(int i = 0; i < 1; i++) {
    pinMode(PARALLEL_0 + i, INPUT);
  }

  parallel_set_inputs(PARALLEL_0);
}

void loop() {
  parallel_read(PARALLEL_0);
}


void parallel_set_inputs(int pin) {
  REG_WRITE(GPIO_ENABLE_WITC_REG, 0xFF << pin);
}

uint8_t parallel_read(int pin) { 
  uint32_t input = REG_READ(GPIO_IN_REG);

  return (input >> pin);
}

