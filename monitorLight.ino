#include <FastLED.h>  // Подключаем библиотеку
#define NUM_LEDS 118  // Указываем количество светодиодов на ленте
#define PIN 13        // Указываем пин для подключения ленты

const int buttonPin = 12; // Подключена кнопка, подает логическую "1", константа buttonPin

CRGB leds[NUM_LEDS];     // Массив, где хранятся цвета каждого светодиода
uint8_t hue = 0;
int hue_m;              // Hue переменный регулятор
int sat_m;              // Saturation переменный регулятор
int val_m;              // Value переменный регулятор

void setup()
{
FastLED.addLeds <WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);  // Основные настройки для адресной ленты
FastLED.setBrightness(255);                                                         // Задать яркость
pinMode(buttonPin, INPUT);                                                          // Режим работы цифрового входа D12
}

void loop()
{

hue_m = analogRead (A0);                // Читаем состояние аналогового входа А0, записываем в переменную hue_m
hue_m = map(hue_m, 0, 1023, 0, 255);    // Преобразуем пропорционально из 0-1023 в 0-255

sat_m = analogRead (A1);                // Читаем состояние аналогового входа А1, записываем в переменную sat_m
sat_m = map(sat_m, 0, 1023, 0, 255);    // Преобразуем пропорционально из 0-1023 в 0-255

val_m = analogRead (A2);                // Читаем состояние аналогового входа А2, записываем в переменную val_m
val_m = map(val_m, 0, 1023, 0, 255);    // Преобразуем пропорционально из 0-1023 в 0-255
 
int buttonState = digitalRead(buttonPin);   // Объявляем переменную buttonState

if(buttonState == HIGH)                     // Если значение buttonState = высокое
{
for (int i = 0; i < NUM_LEDS; i++)
{
leds[i] = CHSV(hue, sat_m, val_m);
}
EVERY_N_MILLISECONDS(60){hue++;}
}
else                                        // Если не выполняется условие buttonState = высокое
{
for (int i = 0; i < NUM_LEDS; i++)
{
leds[i] = CHSV(hue_m, sat_m, val_m);
}
}
FastLED.show();
}
