/*
 An example analogue meter using a ILI9341 TFT LCD screen

 Needs Font 2 (also Font 4 if using large scale label)

 Make sure all the display driver and pin connections are correct by
 editing the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
 
Updated by Bodmer for variable meter size
 */

// Define meter size as 1 for tft.rotation(0) or 1.3333 for tft.rotation(1)
#define M_SIZE 1.3333
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#define FMB9 &FreeMonoBold9pt7b
#define FMB12 &FreeMonoBold12pt7b

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

#define TFT_GREY 0x5AEB
//VU meter
float Udb2Vrms[231][2] = {{-16.0, 122}, {-15.9, 124}, {-15.8, 125}, {-15.7, 127}, {-15.6, 128}, {-15.5, 130}, {-15.4, 131}, {-15.3, 133}, {-15.2, 134}, {-15.1, 136}, {-15.0, 137}, {-14.9, 139}, {-14.8, 140}, {-14.7, 142}, {-14.6, 144}, {-14.5, 145}, {-14.4, 147}, {-14.3, 149}, {-14.2, 151}, {-14.1, 152}, {-14.0, 154}, {-13.9, 156}, {-13.8, 158}, {-13.7, 159}, {-13.6, 161}, {-13.5, 163}, {-13.4, 165}, {-13.3, 167}, {-13.2, 169}, {-13.1, 171}, {-13.0, 173}, {-12.9, 175}, {-12.8, 177}, {-12.7, 179}, {-12.6, 181}, {-12.5, 183}, {-12.4, 185}, {-12.3, 187}, {-12.2, 190}, {-12.1, 192}, {-12.0, 194}, {-11.9, 196}, {-11.8, 199}, {-11.7, 201}, {-11.6, 203}, {-11.5, 206}, {-11.4, 208}, {-11.3, 210}, {-11.2, 213}, {-11.1, 215}, {-11.0, 218}, {-10.9, 220}, {-10.8, 223}, {-10.7, 225}, {-10.6, 228}, {-10.5, 231}, {-10.4, 233}, {-10.3, 236}, {-10.2, 239}, {-10.1, 242}, {-10.0, 244}, {-9.9, 247}, {-9.8, 250}, {-9.7, 253}, {-9.6, 256}, {-9.5, 259}, {-9.4, 262}, {-9.3, 265}, {-9.2, 268}, {-9.1, 271}, {-9.0, 274}, {-8.9, 278}, {-8.8, 281}, {-8.7, 284}, {-8.6, 287}, {-8.5, 291}, {-8.4, 294}, {-8.3, 297}, {-8.2, 301}, {-8.1, 304}, {-8.0, 308}, {-7.9, 311}, {-7.8, 315}, {-7.7, 319}, {-7.6, 322}, {-7.5, 326}, {-7.4, 330}, {-7.3, 334}, {-7.2, 338}, {-7.1, 342}, {-7.0, 345}, {-6.9, 350}, {-6.8, 354}, {-6.7, 358}, {-6.6, 362}, {-6.5, 366}, {-6.4, 370}, {-6.3, 375}, {-6.2, 379}, {-6.1, 383}, {-6.0, 388}, {-5.9, 392}, {-5.8, 397}, {-5.7, 401}, {-5.6, 406}, {-5.5, 411}, {-5.4, 415}, {-5.3, 420}, {-5.2, 425}, {-5.1, 430}, {-5.0, 435}, {-4.9, 440}, {-4.8, 445}, {-4.7, 450}, {-4.6, 456}, {-4.5, 461}, {-4.4, 466}, {-4.3, 472}, {-4.2, 477}, {-4.1, 483}, {-4.0, 488}, {-3.9, 494}, {-3.8, 500}, {-3.7, 505}, {-3.6, 511}, {-3.5, 517}, {-3.4, 523}, {-3.3, 529}, {-3.2, 535}, {-3.1, 542}, {-3.0, 548}, {-2.9, 554}, {-2.8, 561}, {-2.7, 567}, {-2.6, 574}, {-2.5, 580}, {-2.4, 587}, {-2.3, 594}, {-2.2, 601}, {-2.1, 608}, {-2.0, 615}, {-1.9, 622}, {-1.8, 629}, {-1.7, 636}, {-1.6, 644}, {-1.5, 651}, {-1.4, 659}, {-1.3, 666}, {-1.2, 674}, {-1.1, 682}, {-1.0, 690}, {-0.9, 698}, {-0.8, 706}, {-0.7, 714}, {-0.6, 722}, {-0.5, 731}, {-0.4, 739}, {-0.3, 748}, {-0.2, 756}, {-0.1, 765}, {-0.0, 774}, {0.1, 783}, {0.2, 792}, {0.3, 801}, {0.4, 811}, {0.5, 820}, {0.6, 829}, {0.7, 839}, {0.8, 849}, {0.9, 859}, {1.0, 869}, {1.1, 879}, {1.2, 889}, {1.3, 899}, {1.4, 910}, {1.5, 920}, {1.6, 931}, {1.7, 942}, {1.8, 952}, {1.9, 963}, {2.0, 975}, {2.1, 986}, {2.2, 997}, {2.3, 1009}, {2.4, 1021}, {2.5, 1032}, {2.6, 1044}, {2.7, 1057}, {2.8, 1069}, {2.9, 1081}, {3.0, 1094}, {3.1, 1106}, {3.2, 1119}, {3.3, 1132}, {3.4, 1145}, {3.5, 1158}, {3.6, 1172}, {3.7, 1185}, {3.8, 1199}, {3.9, 1213}, {4.0, 1227}, {4.1, 1241}, {4.2, 1256}, {4.3, 1270}, {4.4, 1285}, {4.5, 1300}, {4.6, 1315}, {4.7, 1330}, {4.8, 1346}, {4.9, 1361}, {5.0, 1377}, {5.1, 1393}, {5.2, 1409}, {5.3, 1425}, {5.4, 1442}, {5.5, 1459}, {5.6, 1475}, {5.7, 1493}, {5.8, 1510}, {5.9, 1527}, {6.0, 1545}, {6.1, 1563}, {6.2, 1581}, {6.3, 1599}, {6.4, 1618}, {6.5, 1637}, {6.6, 1656}, {6.7, 1675}, {6.8, 1694}, {6.9, 1714}, {7.0, 1734}};
int vu2angle[24][2] = {{-20, -35}, {-19, -34}, {-18, -33}, {-17, 32}, {-16, -32}, {-15, -30}, {-14, -29}, {-13, -28}, {-12, -26}, {-11, -24}, {-10, -22}, {-9, -20}, {-8, -18}, {-7, -15}, {-6, -12}, {-5, -8}, {-4, -4}, {-3, 0}, {-2, 5}, {-1, 11}, {0, 17}, {1, 24}, {2, 32}, {3,41}};
float percent[21][3]={{0, 0.000, -41}, {5, 0.061, -38}, {10, 0.123, -35}, {15, 0.184, -32}, {20, 0.246, -29}, {25, 0.307, -26}, {30, 0.368, -23}, {35, 0.430, -20}, {40, 0.491, -18}, {45, 0.552, -15}, {50, 0.614, -12}, {55, 0.675, -9}, {60, 0.737, -6}, {65, 0.798, -3}, {70, 0.859, 0}, {75, 0.921, 3}, {80, 0.982, 5}, {85, 1.044, 8}, {90, 1.105, 11}, {95, 1.166, 14}, {100, 1.228, 17}};
int vu_tick[13][2] = {{-20, -35},{-10, -22},{-7, -15}, {-6, -12}, {-5, -8}, {-4, -4}, {-3, 0}, {-2, 5}, {-1, 11}, {0, 17}, {1, 24}, {2, 32}, {3,41}};
int vu_angle[11] = {-35, -22, -15, -8, 0, 5, 11, 17, 24, 32, 41};
char* vu_label[11] = {"20", "10", "7", "5", "3", "2", "1", "0", "1", "2", "3"};

int percent_tick[11] = {-41, -35, -29, -24, -18, -12, -6, 0, 5, 11, 17};
int percent_angle[6] = {-41, -29, -18, -6, 5, 17};
char* percent_label[6] = {"0", "20", "40", "60", "80", "100"};

float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = M_SIZE*120, osy = M_SIZE*120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update

int old_analog =  -999; // Value last displayed
float radian = 0.0174532925;
int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = { -1, -1, -1, -1, -1, -1};
int d = 0;
//width, height
int w = 320;int h = 240;
//origial point
int ox = 160; int oy = 160;
float prev_vu_angle = 0;
float now_vu_angle = 0;
float now_udb = 0;
float prev_udb = 0;

float prev_ppm_angle = 0;
float now_ppm_angle = 0;
void clearBoard()
{
  tft.fillRect(0, 0, w, h, TFT_GREY);
  tft.fillRect(5, 3, (w - 10), (h-6), TFT_WHITE);
}
void setup(void) {
  tft.init();
  tft.setRotation(1);
  Serial.begin(115200); // For debug
  tft.fillScreen(TFT_BLACK);
  updateTime = millis(); // Next update time
  analogReadResolution(12);
  clearBoard();
  //Test the meters
  analogMeter();
  vuNeedle(now_udb, now_vu_angle, 0);
  delay(2000);
  clearBoard();
  
  PeakProgramMeter();
  peakNeedle(4, now_ppm_angle,0);
  delay(2000);
  clearBoard();
  
  horizontal_bar(0.0, 10, 40, w - 20, 40);
  horizontal_bar(0.0, 10, h - 80, w - 20, 40);
  delay(2000);
  clearBoard();
  vertical_bar(0.0, 40, 10, 40, h - 20);
  vertical_bar(0.0, w - 80, 10, 40, h - 20);
}

void loop() {
  int analogValue = analogRead(2);
  int analogVolts = analogReadMilliVolts(2);
  Serial.printf("ADC analog value = %d, MilliVolts = %d\n",analogValue, analogVolts);
  for (int i = 0; i < 231; i++){
    if(analogVolts <= Udb2Vrms[i][1]){
      now_udb = Udb2Vrms[i][0];
      break;
    }
  }
  if(analogVolts > Udb2Vrms[230][1]){
    now_udb = Udb2Vrms[230][0] + 1; //get dDB
  }
  if(analogVolts < Udb2Vrms[0][1]){
    now_udb = Udb2Vrms[0][0] - 1;
  }
  for (int i = 0; i < 24; i++){
    if ( now_udb  < float((vu2angle[i][0] + 4))){
      now_vu_angle = (vu2angle[i][1] + vu2angle[i-1][1]) / 2;
      break;
    }
    if(now_udb  == float((vu2angle[i][0] + 4))){
      now_vu_angle = vu2angle[i][1];
      break;
    }
  }
  //vuNeedle(now_udb, now_vu_angle, 0);
  //peakNeedle(4, now_ppm_angle,0);
  prev_vu_angle = now_vu_angle;
  prev_ppm_angle = now_ppm_angle;
  delay(300);
  if (now_vu_angle > 41){
    now_vu_angle = -41;
  }
}


// #########################################################################
//  Draw the analogue meter on the screen
// #########################################################################
void analogMeter()
{
  // Meter outline
  float x0, y0, x1, y1, x2, y2, x3, y3;
  float cx0, cy0, cx1, cy1;
  
  //draw the VU tick
  for (int i = 0; i < 13; i++)
  {
    if(i < 10){
      x0 = ox + 130 * cos((vu_tick[i][1] - 90) * radian);  
      y0 = oy+ 130 * sin((vu_tick[i][1] - 90) * radian);
      if(i == 3 || i == 5){
        x1 = ox + 135 * cos((vu_tick[i][1] - 90) * radian);  
        y1 = oy + 135 * sin((vu_tick[i][1] - 90) * radian);
      }
      else{
        x1 = ox + 140 * cos((vu_tick[i][1] - 90) * radian);  
        y1 = oy + 140 * sin((vu_tick[i][1] - 90) * radian);
      }
      tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
      
    }
    else if (i > 9 && i < 12){
      x0 = ox + 130 * cos((vu_tick[i][1] - 90) * radian);  
      y0 = oy+ 130 * sin((vu_tick[i][1] - 90) * radian);
      x1 = ox + 140 * cos((vu_tick[i][1] - 90) * radian);  
      y1 = oy + 140 * sin((vu_tick[i][1] - 90) * radian);
      tft.drawLine(x0, y0, x1, y1, TFT_RED);
      //x1 = ox + 125 * cos((vu_tick[i][1] - 90) * radian);  
      //y1 = oy + 125 * sin((vu_tick[i][1] - 90) * radian);
      //x2 = ox + 125 * cos((vu_tick[i + 1][1] - 90) * radian);  
      //y2 = oy+ 125 * sin((vu_tick[i + 1][1] - 90) * radian);
      //x3 = ox + 130 * cos((vu_tick[i + 1][1] - 90) * radian);  
      //y3 = oy + 130 * sin((vu_tick[i + 1][1] - 90) * radian);
      
    }
    else if (i == 12){
      x0 = ox + 125 * cos((vu_tick[i][1] - 90) * radian);  
      y0 = oy+ 125 * sin((vu_tick[i][1] - 90) * radian);
      x1 = ox + 140 * cos((vu_tick[i][1] - 90) * radian);  
      y1 = oy + 140 * sin((vu_tick[i][1] - 90) * radian);
      tft.drawLine(x0, y0, x1, y1, TFT_RED);  
    }
  }
  //draw the arc
 
  for (int i = -41; i <42; i++ )
  {
      // Now draw the arc of the scale
    x0 = ox + 130 * cos((i - 90) * radian);  
    y0 = oy+ 130 * sin((i - 90) * radian);
    x1 = ox + 130 * cos((i + 1 - 90) * radian);  
    y1 = oy + 130 * sin((i + 1 - 90) * radian);
    x2 = ox + 125 * cos((i - 90) * radian);  
    y2 = oy+ 125 * sin((i - 90) * radian);
    x3 = ox + 125 * cos((i + 1 - 90) * radian);  
    y3 = oy + 125 * sin((i + 1 - 90) * radian);
    // Draw scale arc, don't draw the last part
    if (i == -41){
       tft.setFreeFont(FMB12);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawCentreString("-", x0 - 12, y0, 2);
    }
    if (i < 17){
      tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
      tft.drawLine(x2, y2, x3, y3, TFT_BLACK);
    }
    else if (i >= 17 && i < 41){
      tft.drawLine(x0, y0, x1, y1, TFT_RED);
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_RED);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_RED);
    }
    if (i == 41){
       tft.setFreeFont(FMB12);
      tft.setTextColor(TFT_RED, TFT_WHITE);
      tft.drawCentreString("+", x0 + 12, y0, 2);
    }
  }
  //draw the percentage tick
  for(int i = 0; i < 11; i++){
    x0 = ox + 120 * cos((percent_tick[i] - 90) * radian);  
    y0 = oy+ 120 * sin((percent_tick[i] - 90) * radian);
    x1 = ox + 125 * cos((percent_tick[i] - 90) * radian);  
    y1 = oy + 125 * sin((percent_tick[i] - 90) * radian);
    tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
  }
  tft.setFreeFont(FMB9);
  // draw the label of VU
  for(int i = 0; i < 11; i++){
    x0 = ox + 140 * cos((vu_angle[i] - 90) * radian);  
    y0 = oy+ 140 * sin((vu_angle[i] - 90) * radian);
    x1 = ox + 125 * cos((percent_angle[i] - 90) * radian);  
    y1 = oy+ 125 * sin((percent_angle[i] - 90) * radian);
    if(i > 7){
      tft.setTextColor(TFT_RED, TFT_WHITE);
      tft.drawCentreString(vu_label[i], x0, y0 - 12, 2);
    } else{
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawCentreString(vu_label[i], x0, y0 - 12, 2);    
    }
    //draw percentage label
    if(i < 6){
      tft.drawCentreString(percent_label[i], x1 + 3, y1 + 6, 2);  
    }
  }
}

// #########################################################################
// Update needle position
// This function is blocking while needle moves, time depends on ms_delay
// 10ms minimises needle flicker if text is drawn within needle sweep area
// Smaller values OK if text not in sweep area, zero for instant movement but
// does not look realistic... (note: 100 increments for full scale deflection)
// #########################################################################
void vuNeedle(float dDB, float value, byte ms_delay)
{
  float x0 = 0, y0 = 0;
  tft.fillRect(5, (oy - 40), 80, 37, TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  char buf[12]; dtostrf(dDB, 4, 1, buf);
  char unit[4] = "dBu";
  strcat(buf, unit);
  tft.drawRightString(buf, 60, (oy  - 40), 2);

  if (value < -42) value = -42; // Limit value to emulate needle end stops
  if (value > 42) value = 42;

  x0 = ox + 100 * cos((prev_vu_angle - 90) * radian);  
  y0 = oy+ 100 * sin((prev_vu_angle - 90) * radian);
  tft.drawLine(ox, oy, x0, y0, TFT_WHITE);
  
  x0 = ox + 100 * cos((value - 90) * radian);  
  y0 = oy+ 100 * sin((value - 90) * radian);
  tft.drawLine(ox, oy, x0, y0, TFT_BLACK);
  delay(ms_delay);
}

void horizontal_bar(float db, int ox, int oy, int w, int h)
{
  int interval = w / 24;
  for (int i = 0; i < 24; i++){
    if (i < 16){
      tft.fillRect((ox + i * interval), oy, (interval - 2) , h, TFT_GREEN);  
    } else if(i > 15 && i < 20){
      tft.fillRect((ox + i * interval), oy, (interval - 2), h, TFT_YELLOW);  
    } else if (i > 19){
      tft.fillRect((ox + i * interval), oy, (interval - 2), h, TFT_RED);  
    }
  }
}

void vertical_bar(float db, int xx, int yy, int w, int h)
{
  int interval = h / 24;
  for (int i = 24; i > 0; i--){
    if (i > 8){
      tft.fillRect(xx, (yy + i * interval), w , (interval - 2), TFT_GREEN);  
    } else if(i < 9 && i > 4){
      tft.fillRect(xx, (yy + i * interval), w, (interval - 2), TFT_YELLOW);  
    } else if (i < 5){
      tft.fillRect(xx, (yy + i * interval), w, (interval - 2), TFT_RED);  
    }
  }
}

void PeakProgramMeter()
{
   float x0, y0, x1, y1;
   uint8_t k = 0;
  //draw the VU tick
  for (int i = -60; i < 61; i+=15)
  {
    if(i < 60){
      x0 = ox + 130 * cos((i - 90) * radian);
      y0 = oy + 130 * sin((i - 90) * radian);
      x1 = ox + 140 * cos((i - 90) * radian);  
      y1 = oy + 140 * sin((i - 90) * radian);
      tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
      if (k > 0){
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.drawCentreString(String(k), x1, y1 - 12, 2); 
      }
      k = k + 1;
    }
    else if(i == 60){
      x0 = ox + 130 * cos((i - 5 - 90) * radian);  
      y0 = oy + 130 * sin((i - 5 - 90) * radian);
      x1 = ox + 140 * cos((i - 5 - 90) * radian);  
      y1 = oy + 140 * sin((i- 5   - 90) * radian);
      tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
    }
  }
}

void peakNeedle(float dDB, float angle, byte ms_delay)
{
  float x0 = 0, y0 = 0;
  tft.fillRect(5, (oy - 40), 80, 37, TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  char buf[12]; dtostrf(dDB, 4, 1, buf);
  char unit[4] = "dBu";
  strcat(buf, unit);
  tft.drawRightString(buf, 60, (oy  - 40), 2);

  if (angle < -60) angle = -65; // Limit value to emulate needle end stops
  if (angle > 60) angle = 65;

  x0 = ox + 120 * cos((prev_ppm_angle - 90) * radian);  
  y0 = oy+ 120 * sin((prev_ppm_angle - 90) * radian);
  tft.drawLine(ox, oy, x0, y0, TFT_WHITE);
  
  x0 = ox + 100 * cos((angle - 90) * radian);  
  y0 = oy+ 100 * sin((angle - 90) * radian);
  tft.drawLine(ox, oy, x0, y0, TFT_BLACK);
  delay(ms_delay);
}
