#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "pins.h"
#include "oled.h"
#include "pid_conf.h"
extern volatile float VL_result; 
extern volatile PIDCTROL PID;

Adafruit_SSD1306 display(128, 64, &Wire, -1);



// 主页面
INTERFACE front_page = {
    .top_x = 46,
    .top_y = 8,
    .top_text = "PID",
    .first_text_x = TEXT_X,
    .first_text_y=17,
    .first_text = "STANCE:",
    .second_text_x = TEXT_X,
    .second_text_y = 27,
    .second_text = "SET POINT:",
    .third_text_x = TEXT_X,
    .third_text_y = 37,
    .third_text = "KP:",
    .fourth_text_x = TEXT_X,
    .fourth_text_y = 47,
    .fourth_text = "PID OUTPUT:"
};

void displayout(const char *pt, int x, int y) {
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(x, y);
    display.print(pt);
}


void display_battery() {
    int points[][2] = {
        {4, -1}, {3, 0}, {2, 1}, {1, 2}, {0, 3},
        {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3},
        {5, 3}, {4, 4}, {3, 5}, {2, 6}, {1, 7}
    };

    for (int i = 0; i < sizeof(points) / sizeof(points[0]); ++i) {
        displayout(".", points[i][0], points[i][1]);
    }
   // display.display();
}

void display_bar() {
    displayout("PID...", 45, 39);
    for (int x = 10; x < 100; x++) {
        for (int y = 28; y < 40; y++) {
            displayout(".", x, y);
        }
        if (x % 2 == 0) {
            DELAY_MS(22); // Delay to simulate loading
            display.display();
        }
    }
}
void dispaly_num(float num, int x, int y) {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.print(num);
}

void display_speed(INTERFACE *menu) {
    displayout(menu->top_text,menu->top_x,menu->top_y);
    displayout(menu->first_text, menu->first_text_x, menu->first_text_y);
    displayout(menu->second_text, menu->second_text_x, menu->second_text_y);
    displayout(menu->third_text, menu->third_text_x, menu->third_text_y);
    displayout(menu->fourth_text, menu->fourth_text_x, menu->fourth_text_y);
   dispaly_num(VL_result/10, 80, 17);
    displayout("CM",110,27);
    displayout("CM",110,17);
    dispaly_num(PID.Setpoint, 80, 27);
    dispaly_num(PID.kp, 80, 37);
    dispaly_num(PID.Output, 80, 47);
}

void init_screen() {
  //Wire.begin(SDA_PIN,SCL_PIN);
 if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C 是I2C地址
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // 如果初始化失败，停留在这里
  }
    Serial.println(F("SSD1306 initialized"));
        display.clearDisplay();
    display.display();
      display_bar();
        display_battery();
        DELAY_MS(500); // Delay to show the battery and bar initialization
        //initialized = true;
        Serial.println("2");
    display.clearDisplay();
   display.display();
}
void screen_loop() {
  Serial.println("screen");
    display.clearDisplay();
    display_speed(&front_page);
    display_battery();
    display.display();
    Serial.println("clear");
    DELAY_MS(100);
  }
