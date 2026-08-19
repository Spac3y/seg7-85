#define DATA_PIN   0   // PB0 - SER   (DS)
#define CLOCK_PIN  1   // PB2 - SRCLK (SHCP)  ← moved from PB1
#define RESET_PIN  2   // PB4 - SRCLR (MR)    ← moved from PB3
#define LATCH_PIN  3   // PB3 - RCLK  (STCP)  ← moved from PB2

// ATtiny85 Timer1: 8-bit, prescaler /16384
// 8MHz / 16384 / 162 ≈ 3 Hz scroll rate
#define TIMER1_TOP 162

const size_t segLen = 7;
const size_t digitsLen = 4;

const char keys[] = {'I', 'L', 'O', 'V', 'E', 'Y', 'U', 'H',' ', '-'};
const uint8_t values[] = { 0b0000110, 0b0001110, 0b1111110, 0b0111110, 0b1001111, 0b0110011, 0b0111110, 0b0110111, 0b0000000, 0b0000001 };
const uint8_t MAP_SIZE =  10;


const char message[] = "I LOVE YOU   ";
const uint16_t length = sizeof(message)/sizeof(message[0]);

volatile unsigned ind = 0;
volatile char buffer[4] = { ' ', ' ', ' ', ' ' };
                            /* 3    2    1    0*/
volatile bool doShift = false;

uint8_t getMapValue(char key) {
  for(uint8_t i = 0; i < MAP_SIZE; i++) 
    if(keys[i] == key)
      return values[i];
  return 0;
}

void resetShiftRegister() {
  digitalWrite(RESET_PIN, LOW);
  delayMicroseconds(1);
  digitalWrite(RESET_PIN, HIGH);
}

void latchOutput() {
  digitalWrite(LATCH_PIN, HIGH);
  delayMicroseconds(1);
  digitalWrite(LATCH_PIN, LOW);
}

uint16_t combineData(uint8_t data, uint8_t poz) {
  poz = ~(1 << poz);
  uint16_t rez = ((uint16_t)(data & 0x7F) << 4) | (poz & 0x0F);
  return rez;
}

void writeShiftRegister(uint8_t data, uint8_t poz) {
  // 1. Clear shift register before writing
  resetShiftRegister();

  uint16_t value = combineData(data, poz);

  // 2. Clock out 11 bits, MSB first
  for (int8_t bit = 0; bit < 11; bit++) {
    digitalWrite(DATA_PIN,  (value >> bit) & 0x01);
    digitalWrite(CLOCK_PIN, HIGH);
    delayMicroseconds(1);
    digitalWrite(CLOCK_PIN, LOW);
  }

  // 3. Transfer shift register → output latches
  latchOutput();
}

void displayBuffer() {
  for (unsigned i = 0; i < 4; i++) {
    writeShiftRegister(getMapValue(buffer[i]), 3-i);
    delay(2);
  }
}

void shiftLetter(char letter) {
  for (unsigned i = 1; i < 4; i++) {
    buffer[i - 1] = buffer[i];
  }
  buffer[3] = letter;
}

ISR(TIMER1_COMPA_vect) {
  doShift = true;
}

void startAnimation() {
  const unsigned time = 125;

  for(short i = 0; i < 7; i++) {
    uint8_t data = ~(1 << i) & 0x7F;
    for(short j = 0; j < 4; j++) {
      writeShiftRegister(data, j);
      delay(2);
    }
    delay(time);
  }

  for(short i = 0; i < 3; i++) {
    for(short j = 0; j < 4; j++) {
      writeShiftRegister(getMapValue('-'), j);
      delay(2);
    }
    delay(time);

    for(short j = 0; j < 4; j++) {
      writeShiftRegister(getMapValue(' '), j);
      delay(2);
    }
  }
}

void setup() {

  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);

  resetShiftRegister();

  // startAnimation();

  cli();
  TCCR1 = 0;
  GTCCR = 0;
  TCNT1 = 0;
  OCR1C = TIMER1_TOP;             // TOP for CTC mode
  OCR1A = TIMER1_TOP;             // compare match A = fire ISR at TOP
  TCCR1 |= (1 << CTC1);          // CTC mode (clear on OCR1C match)
  TCCR1 |= 0x0F;                  // prescaler /16384 (CS13:CS10 = 1111)
  TIMSK |= (1 << OCIE1A);         // enable compare match A interrupt
  sei();
}

void loop() {
  if(doShift) {
    doShift = false;
    shiftLetter(message[ind]);
    ind = (ind+1) % length;
  }
  displayBuffer();
}
