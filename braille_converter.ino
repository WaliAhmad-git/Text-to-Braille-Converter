const char* braille_alphabet[27] = {
  "100000", "101000", "110000", "110100", "100100", "111000", "111100",
  "101100", "011000", "011100", "100010", "101010", "110010", "110110",
  "100110", "111010", "111110", "101110", "011010", "011110", "100011",
  "101011", "011101", "110011", "110111", "100111", "000000"
};

const int pin1 = 6, pin2 = 7, pin3 = 8, pin4 = 9, pin5 = 10, pin6 = 11;
const int verf = 2;

// Verify this order matches dot1..dot6 wiring on your hardware
const int pins[6] = {pin1, pin4, pin2, pin5, pin3, pin6};

void setup() {
  Serial.begin(9600);
  Serial.println("Serial connection started");
  for (int i = 0; i < 6; i++) {
    pinMode(pins[i], OUTPUT);
  }
  pinMode(verf, OUTPUT);
}

void showOutput(const char* seq) {
  for (int i = 0; i < 6; i++) {
    digitalWrite(pins[i], seq[i] == '1' ? HIGH : LOW);
  }
  digitalWrite(verf, HIGH);
  delay(2000);

  for (int i = 0; i < 6; i++) {
    digitalWrite(pins[i], LOW);
  }
  digitalWrite(verf, LOW);
  Serial.println(seq);   // moved out of the loop, prints once
  delay(500);
}

int letterToIndex(char letter) {
  letter = toupper(letter);
  if (letter >= 'A' && letter <= 'Z') return letter - 'A';
  if (letter == ' ') return 26;
  return -1;
}

void loop() {
  if (Serial.available() > 0) {
    char ch = Serial.read();

    // Ignore line endings / control characters
    if (ch == '\n' || ch == '\r') return;

    int index = letterToIndex(ch);
    if (index != -1) {
      showOutput(braille_alphabet[index]);
    } else {
      Serial.print("Invalid character encountered: ");
      Serial.println(ch);
    }
  }
}
