/* 	TUGAS Robotika
    aswin Saputra
    311221 000 6
    Nov 2023     */

/*
 * Pengukuran Jarak dengan sensor Ultrasonic dan memicu buzzer
 * pada jarak tertentu
 * Sistem ini bekerja mirip dengan sensor parkir mobil
 * dimana buzer akan mendeteksi dari jarak lebih dari 2m
 * dibawah 2 meter akan mempercepat dan memperbanyak durasi buzer
 * jika jarak dibawah 15 cm buzer akan berbunyi kontinyu
 */

// kalkulasi kecepatan suara m/s berdasarkan temperatur udara
#define SOUND_SPEED(air_temp) 331.3 + (0.606 * air_temp)

#define pingTrig 11
#define pongEcho 3
#define buzzPin 5

// menetapakan temperatur
#define AIR_TEMP 25

float soundSpeed = SOUND_SPEED(AIR_TEMP);

float Distance_Calc(uint8_t Pin_Trigger, uint8_t Pin_Echo)
{
    // membuat pulsa 10 micro second
    digitalWrite(Pin_Trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(Pin_Trigger, LOW);

    uint16_t durasi = pulseIn(Pin_Echo, HIGH); // hitung kalkulasi waktu durasi dalam us

    return float(durasi) / 20000.0 * soundSpeed; // hitung jarak dalam cm
}

void buzzer(uint8_t pin, int duration = 100)
{
    int tonefreq = 1760; // A 6th octave
    tone(pin, tonefreq, duration);
    // delay(Time_delay);
}

void setup()
{
    Serial.begin(9600);
    pinMode(pingTrig, OUTPUT);
    pinMode(pongEcho, INPUT);
    pinMode(buzzPin, OUTPUT);
}

void loop()
{
    float jarak = Distance_Calc(pingTrig, pongEcho);
    if (jarak >= 200)
    { // jika jarak lebih dari 200 cm maka akan ada beep
        buzzer(buzzPin);
        delay(1200);
    }
    else if (jarak >= 50 && jarak < 200)
    { // jika jarak  antara 50 -- 200 cm maka
      // akan beep yang semangkin cepat seiring jarak mendekat
        buzzer(buzzPin);
        delay((2 * (jarak / 10) * (jarak / 10)) + 350);
    }
    else if (jarak >= 15 && jarak <= 50)
    {
        buzzer(buzzPin);
        delay(((jarak * jarak) / 10) + 150);
    }
    else
    { // jika jarak  kurang dari 15 cm maka cuzer akan berbunyi kontinyu
        buzzer(buzzPin, 800);
        delay(100);
    }
    // print hasil pengukuran
    Serial.print(", Jarak: ");
    Serial.println(jarak);
}
