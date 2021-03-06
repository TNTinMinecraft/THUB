/*
 * by:TNTinMinecraft
 * 2021_4_5
 */

#include <Adafruit_Fingerprint.h>
#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g( U8G_I2C_OPT_NONE );

String    ID;
volatile int  error0;

String NAME = "mianban";//设备名称
String SITE = "bedroom";//设备位置

/**********定义I/O**********/

int in1 = 4;    //密码开关1
int in2 = 5;    //密码开关2
int in3 = 6;    //密码开关3
int in4 = 7;    //全黑
int in5 = 8;    //电脑开关
int in6 = 9;    //床下灯
int in7 = 13;   //锁in
int out3 = 12;  //锁led
int out2 = 11;  //data.led

int io1 = 0;

int io2 = 0;
int io3 = 0;

int cp  = 0;
int old_cp  = 0;
int cpled = 0;

#if defined(__AVR__) || defined(ESP8266)
SoftwareSerial mySerial( 2, 3 );
#else
#define mySerial Serial1
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint( &mySerial );

/**********UI**********/

const uint8_t bitmap_1[]   U8G_PROGMEM = {
  0x80, 0x00, 0x00, 0x83, 0x1B, 0x18, 0xA4, 0xA4, 0xA4, 0xD4, 0xA4, 0xBC, 0x94, 0xA4, 0xA0, 0x93,
  0x24, 0x9C
};

const uint8_t bitmap_2[]   U8G_PROGMEM = {
  0x30, 0x48, 0x40, 0xFC, 0x84, 0x84, 0xFC
};

const uint8_t light[]   U8G_PROGMEM = {
  0x65, 0x82, 0x00, 0x91, 0x82, 0x00, 0x95, 0xCA, 0x01, 0xE5, 0x96, 0x00, 0x85, 0x92, 0x00, 0x95,
  0x92, 0x00, 0x65, 0x92, 0x00
};

const uint8_t computer[]   U8G_PROGMEM = {
  0xC6, 0x28, 0x27, 0x01, 0x29, 0x55, 0x29, 0x01, 0x21, 0x55, 0x29, 0x01, 0x21, 0x55, 0x27, 0x01,
  0x21, 0x55, 0x21, 0x01, 0x29, 0x55, 0x21, 0x01, 0xC6, 0x54, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x80, 0x98, 0x00, 0x00, 0x80, 0xA4, 0x02, 0x00, 0xC0, 0xA5, 0x05, 0x00, 0x80, 0xBC, 0x00, 0x00,
  0x80, 0x84, 0x00, 0x00, 0x80, 0x84, 0x00, 0x00, 0x80, 0xB8, 0x00, 0x00
};

const uint8_t Clock[]   U8G_PROGMEM = {
  0x00, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0xFC, 0xFF, 0xFF,
  0x03, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x3E, 0x00, 0xC0, 0x07, 0x00, 0x00, 0x1E,
  0x00, 0x80, 0x07, 0x00, 0x00, 0x1E, 0x00, 0x80, 0x07, 0x00, 0x00, 0x1E, 0x00, 0x80, 0x07, 0x00,
  0x00, 0x1E, 0x00, 0x80, 0x07, 0x00, 0x00, 0x1E, 0x00, 0x80, 0x07, 0x00, 0x00, 0x1E, 0x00, 0x80,
  0x07, 0x00, 0x00, 0x1E, 0x00, 0x80, 0x07, 0x00, 0x00, 0x1E, 0x00, 0x80, 0x07, 0x00, 0x00, 0x1E,
  0x00, 0x80, 0x07, 0x00, 0x00, 0x1E, 0x00, 0x80, 0x07, 0x00, 0x00, 0x1E, 0x00, 0x80, 0x07, 0x00,
  0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0xFF,
  0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xFC, 0xFF,
  0xFF, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x03,
  0xFC, 0xFF, 0x9F, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0x9F, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0x9F, 0xFF,
  0xFF, 0x03, 0xFC, 0xFF, 0x0F, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0x0F, 0xFF, 0xFF, 0x03, 0xFC, 0xFF,
  0x0F, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0x0F, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0x0F, 0xFF, 0xFF, 0x03,
  0xFC, 0xFF, 0x0F, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0xFF,
  0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xFC, 0xFF,
  0xFF, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x03,
  0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00,
  0x00, 0x00, 0x1C, 0x00, 0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x04, 0x00, 0x00, 0x00, 0x10, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x04, 0xE0, 0x03, 0x3E, 0x10, 0x1E, 0x04, 0x30, 0x06, 0x43,
  0x10, 0x02, 0x04, 0x18, 0x8C, 0x41, 0x10, 0x01, 0x04, 0x08, 0x88, 0x40, 0x90, 0x00, 0x04, 0x08,
  0x88, 0x00, 0xD0, 0x01, 0x04, 0x0A, 0x88, 0x00, 0x30, 0x01, 0x04, 0x1A, 0x8C, 0x01, 0x10, 0x02,
  0x04, 0x33, 0x06, 0x43, 0x10, 0x06, 0xFF, 0xE3, 0x03, 0x3E, 0x7C, 0x1E
};

const uint8_t Clear[]   U8G_PROGMEM = {
  0x00
};

void setup()
{
  Serial.begin( 9600 );
  Serial.println( "THUB." + NAME + SITE + ".noline" + ".D" );//上线
  error0 = 0;//解锁
  finger.begin( 57600 );
  pinMode( in1, INPUT );
  pinMode( in2, INPUT );
  pinMode( in3, INPUT );
  pinMode( in4, INPUT );
  pinMode( in5, INPUT );
  pinMode( in6, INPUT );
  pinMode( in7, INPUT );
  pinMode( out3, OUTPUT );

  digitalWrite( out3, LOW );
  /**********加载动画**********/
  for ( int i = 1; i < 95; i = i + 7 )
  {
    u8g.firstPage();
    do
    {
      u8g.drawBox( 10, 35, i, 10 );
      u8g.setFont( u8g_font_osb18 );
      u8g.drawStr( 0, 25, "LOADING" );
    }
    while ( u8g.nextPage() );
  }
  u8g.firstPage();
  do
  {
    u8g.drawXBMP( 0, 0, 1, 1, Clear );
  }
  while ( u8g.nextPage() );
}


void loop()
{
  if ( digitalRead( in7 ) == 1 )
  {
    if ( io2 == 0 )
    {
      for ( int i = 1; i < 47; i = i + 6 )
      {
        u8g.firstPage();
        do
        {
          u8g.drawBox( 10, 35, i, 10 );
          u8g.setFont( u8g_font_osb18 );
          u8g.drawStr( 0, 25, "Testing" );
        }
        while ( u8g.nextPage() );
      }
      getFingerprintID();//指纹
      for ( int i = 47; i < 95; i = i + 6 )
      {
        u8g.firstPage();
        do
        {
          u8g.drawBox( 10, 35, i, 10 );
          u8g.setFont( u8g_font_osb18 );
          u8g.drawStr( 0, 25, "Testing" );
        }
        while ( u8g.nextPage() );
      }
      io2 = 1;
      io3 = 1;
    }
    if ( error0 == 1 )//指纹通过
    {
      if ( digitalRead( in1 ) == 1 && (digitalRead( in2 ) == 0 && digitalRead( in3 ) == 1) )//密码
      {
        /**********密码通过**********/
        digitalWrite( out3, HIGH );
        ui();
        cp_io();
        io();
      } else {
        /**********密码未通过**********/
        digitalWrite( out3, LOW );
        u8g.firstPage();
        do
        {
          if ( digitalRead( in1 ) == 1 )
          {
            u8g.drawBox( 27, 16, 10, 33 );
          } else {
            u8g.drawFrame( 27, 16, 10, 33 );
          }
          if ( digitalRead( in2 ) == 1 )
          {
            u8g.drawBox( 59, 16, 10, 33 );
          } else {
            u8g.drawFrame( 59, 16, 10, 33 );
          }
          if ( digitalRead( in3 ) == 1 )
          {
            u8g.drawBox( 91, 16, 10, 33 );
          } else {
            u8g.drawFrame( 91, 16, 10, 33 );
          }
        }
        while ( u8g.nextPage() );
      }
    } else {
      /**********指纹未通过**********/
      u8g.firstPage();
      do
      {
        u8g.setFont( u8g_font_fub14 );
        u8g.drawStr( 0, 25, "NO" );
      }
      while ( u8g.nextPage() );
    }
  } else {
    if ( io3 == 1 )
    {
      u8g.firstPage();
      do
      {
        u8g.drawXBMP( 40, 3, 45, 58, Clock );
      }
      while ( u8g.nextPage() );
      io2 = 0;
      io3 = 0;
      error0  = 0;
      //Serial.println( "lock" );
      delay( 1000 );
      u8g.firstPage();
      do
      {
        u8g.drawXBMP( 0, 0, 1, 1, Clear );
      }
      while ( u8g.nextPage() );
    }
  }
}

/**********绘制函数**********/
uint8_t ui()
{
  u8g.firstPage();
  do
  {
    u8g.drawBitmapP( 8, 2, 3, 6, bitmap_1 );
    u8g.drawBitmapP( 114, 1, 1, 7, bitmap_2 );
    u8g.drawLine( 4, 9, 123, 9 );

    if ( digitalRead( in4 ) == 0 )
    {
      u8g.drawCircle( 103, 4, 3 );
    } else {
      u8g.drawDisc( 103, 4, 3 );
    }

    if ( digitalRead( in6 ) == 0 )
    {
      u8g.drawCircle( 90, 42, 21 );
    } else {
      u8g.drawDisc( 90, 42, 21 );
    }

    if ( cpled == 0 )
    {
      u8g.drawCircle( 40, 42, 21 );
    } else {
      u8g.drawDisc( 40, 42, 21 );
    }

    u8g.drawXBMP( 28, 35, 32, 15, computer );
    u8g.drawXBMP( 82, 37, 24, 7, light );
  }
  while ( u8g.nextPage() );
}

/**********I/O函数**********/
uint8_t io()
{
  if ( io1 != digitalRead( in4 ) + digitalRead( in6 ) + cpled )
  {
    Serial.println( "THUB." + NAME + SITE + ".stop" + ".D" );//申请总线
    if ( digitalRead( in4 ) == 1 )
    {
      Serial.println( "THUB." + NAME + SITE + ".qh.1" + ".D" );
    } else {
      Serial.println( "THUB." + NAME + SITE + ".qh.0" + ".D" );
    }

    if ( digitalRead( in6 ) == 1 )
    {
      Serial.println( "THUB." + NAME + SITE + ".xd.1" + ".D" );
    } else {
      Serial.println( "THUB." + NAME + SITE + ".xd.0" + ".D" );
    }

    if ( cpled == 1 )
    {
      Serial.println( "THUB." + NAME + SITE + ".dn.1" + ".D" );
    } else {
      Serial.println( "THUB." + NAME + SITE + ".dn.0" + ".D" );
    }
    io1 = digitalRead( in4 ) + digitalRead( in6 ) + cpled;
    Serial.println( "THUB." + NAME + SITE + ".fr" + ".D" );//释放总线
  }
}


uint8_t cp_io()
{
  cp = digitalRead( in5 );
  if ( (cp == HIGH) && (old_cp == LOW) )
  {
    cpled = 1 - cpled;
  }
  old_cp = cp;
}

/**********指纹检测I/O函数**********/
uint8_t getFingerprintID()
{
  uint8_t p = finger.getImage();
  switch ( p )
  {
  case FINGERPRINT_OK:
    break;
  case FINGERPRINT_NOFINGER:
    return(p);
  case FINGERPRINT_PACKETRECIEVEERR:
    return(p);
  case FINGERPRINT_IMAGEFAIL:
    return(p);
  default:
    return(p);
  }
  p = finger.image2Tz();
  switch ( p )
  {
  case FINGERPRINT_OK:
    break;
  }
  p = finger.fingerSearch();
  if ( p == FINGERPRINT_OK )
  {
    error0 = 1;
  } else if ( p == FINGERPRINT_PACKETRECIEVEERR )
  {
    return(p);
  } else if ( p == FINGERPRINT_NOTFOUND )
  {
    return(p);
  } else {
    return(p);
  }

  return(finger.fingerID);
}
