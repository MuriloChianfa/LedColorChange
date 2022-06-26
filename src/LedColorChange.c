#include <IRremote.h>

// Porta do receiver
#define CONTROLL_PORT 2

// Portas do LED RGB
#define RED_PORT 3
#define BLUE_PORT 4
#define GREEN_PORT 5

// Hexadecimais dos botoes
#define BUTTON_0 0xFD30CF
#define BUTTON_1 0xFD08F7
#define BUTTON_2 0xFD8877
#define BUTTON_3 0xFD48B7
#define BUTTON_4 0xFD28D7
#define BUTTON_5 0xFDA857
#define BUTTON_6 0xFD6897

IRrecv controll(CONTROLL_PORT);
decode_results commands;

typedef struct {
    int red;
    int blue;
    int green;
} Color;

Color colors[7] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
};

enum ColorCode {
    red,
    blue,
    green,
    purple,
    cian,
    yellow,
    white
};

void changeLedColor(int colorCode)
{
    // Set the new color
    digitalWrite(RED_PORT, colors[colorCode].red);
    digitalWrite(BLUE_PORT, colors[colorCode].blue);
    digitalWrite(GREEN_PORT, colors[colorCode].green);
}

void dispatchButtonAction()
{
    if (!controll.decode(&commands))
    {
        return;
    }
  
    Serial.println(commands.value, HEX);

    switch (commands.value)
    {
        case BUTTON_0: changeLedColor(red); break;
        case BUTTON_1: changeLedColor(blue); break;
        case BUTTON_2: changeLedColor(green); break;
        case BUTTON_3: changeLedColor(purple); break;
        case BUTTON_4: changeLedColor(cian); break;
        case BUTTON_5: changeLedColor(yellow); break;
        case BUTTON_6: changeLedColor(white); break;
    }

    controll.resume();
}

void setup()
{
    Serial.begin(9600);
    controll.enableIRIn();
  
    pinMode(RED_PORT, OUTPUT);
    pinMode(BLUE_PORT, OUTPUT);
    pinMode(GREEN_PORT, OUTPUT);
  
    // Inicia com vermelho
    changeLedColor(red);
}

void loop()
{
    dispatchButtonAction();
    
    delay(500);
}

