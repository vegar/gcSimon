#include "game.h"

#define FONT_TITLE u8g2_font_9x15_tf
#define FONT_BODY u8g2_font_6x13_tf
#define FONT_HUGE u8g2_font_courB24_tf

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

void setupDisplay(uint8_t menu_select_pin, uint8_t menu_next_pin, uint8_t menu_prev_pin, uint8_t menu_up_pin = U8X8_PIN_NONE, uint8_t menu_down_pin = U8X8_PIN_NONE, uint8_t menu_home_pin = U8X8_PIN_NONE)
{
    u8g2.begin(menu_select_pin, menu_next_pin, menu_prev_pin, menu_up_pin);
}

void center(const char *s, uint8_t y)
{
  uint8_t i = u8g2.getStrWidth(s);

  u8g2.setCursor((128 - i) / 2, y);
  u8g2.print(s);
}

void center(const byte value)
{
  uint8_t x = u8g2.getStrWidth("8") * ((int)log10(value)+1);

  u8g2.setFontPosCenter();
  u8g2.setCursor((128 - x) / 2, 32);
  u8g2.print(value);
}

void print_title(){
  u8g2.firstPage();
  do {
    u8g2.setFont(FONT_TITLE);
    center("-= SiMoN =-", 12);

    u8g2.setFont(FONT_BODY);
    center("Push any button", 60);
  } while (u8g2.nextPage());
}

void print_winner()
{
  u8g2.firstPage();
  do {
    u8g2.setFont(FONT_HUGE);
    u8g2.setFontPosCenter();
    center("HURRA!", 32);
  } while (u8g2.nextPage());
}

void print_loser(byte reason)
{
  char *screens[2][2] = {
    {"Wrong", "move!"}, 
    {"Too", "slow!"}
  };
  
  u8g2.firstPage();
  do {
    u8g2.setFont(FONT_HUGE);
    u8g2.setFontPosCenter();
    if (reason == GAME_WRONG_MOVE) {
      center(screens[0][0], 32);  
    } else {
      center(screens[1][0], 32);  
    }    
  } while (u8g2.nextPage());

  delay(1000);
  u8g2.firstPage();
  do {
    u8g2.setFont(FONT_HUGE);
    u8g2.setFontPosCenter();
    if (reason == GAME_WRONG_MOVE) {
      center(screens[0][1], 32);  
    } else {
      center(screens[1][1], 32);  
    }    
  } while (u8g2.nextPage());
}

void printRound(byte gameRound)
{
  u8g2.firstPage();
  do {
    u8g2.setFont(FONT_TITLE);
    center("-Round-", 12);
    u8g2.setFont(FONT_HUGE);
    center(gameRound);
  } while (u8g2.nextPage());
}

void instructions_memory()
{

  u8g2.firstPage();
  do {
    u8g2.setFont(FONT_TITLE);
    center("-Instructions-", 12);
    u8g2.setFont(FONT_BODY);
    center("Repeat shown sequence", 30); 
  } while (u8g2.nextPage());
  
  delay(ENTRY_TIME_LIMIT);
  
  u8g2.firstPage();
  do {
    u8g2.setFont(FONT_TITLE);
    center("-Instructions-", 12);
    u8g2.setFont(FONT_BODY);
    center("Wait no longer than", 30); 
    center("3 sec", 45); 
  } while (u8g2.nextPage());
  
  delay(ENTRY_TIME_LIMIT);

  char buf[20];
  snprintf (buf, 20, "Manage %d rounds", ROUNDS_TO_WIN);

  u8g2.firstPage();
  do {
    u8g2.setFont(FONT_TITLE);
    center("-Instructions-", 12);
    u8g2.setFont(FONT_BODY);
    center(buf, 30); 
    center("in a row to win.", 45); 
  } while (u8g2.nextPage());

  delay(ENTRY_TIME_LIMIT);  
}

void render_screens(){
  print_winner();
  delay(1000);
  print_loser(GAME_TIMED_OUT);
  delay(1000);
  print_loser(GAME_WRONG_MOVE);
  delay(1000);
  printRound(1);
  delay(1000);
  instructions_memory();
  delay(1000);
}

