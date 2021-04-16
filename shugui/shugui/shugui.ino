int a = 13;
int b = 12;
int c = 11;
int d = 10;
int e = 9;
int f = 8;
int g = 7;
int h = 6;
int i = 5;
int j = 4;
int k = 3;

String indate="";
String val="";

String NAME = "shugui";

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(h, OUTPUT);
  pinMode(i, OUTPUT);
  pinMode(j, OUTPUT);
  pinMode(k, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("THUB." + NAME + ".uol");
  
  of();
}

void loop() {
   while(Serial.available()>0)
  {
    indate+=char(Serial.read());
    delay(2);
    if(Serial.available()<=0)
     {
        Serial.println(indate);
     }
  }
  if(indate.length()>0)
  {
     val=indate;
     if(val=="THUB."+NAME+".oon")
      {
        oon();
        Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".of")
      {
         of();
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".upp")
      {
         upp();
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".up")
      {
         up();
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".OK?")
      {
         Serial.println("THUB."+NAME+".OK");
      }

      
      else if(val=="THUB."+NAME+".a.h")
      {
         digitalWrite(a,HIGH);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".a.l")
      {
         digitalWrite(a,LOW);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".b.h")
      {
         digitalWrite(b,HIGH);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".b.l")
      {
         digitalWrite(b,LOW);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".c.h")
      {
         digitalWrite(c,HIGH);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".c.l")
      {
         digitalWrite(c,LOW);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".d.h")
      {
         digitalWrite(d,HIGH);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".d.l")
      {
         digitalWrite(d,LOW);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".e.h")
      {
         digitalWrite(e,HIGH);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".e.l")
      {
         digitalWrite(e,LOW);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".f.h")
      {
         digitalWrite(f,HIGH);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".f.l")
      {
         digitalWrite(f,LOW);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".g.h")
      {
         digitalWrite(g,HIGH);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".g.l")
      {
         digitalWrite(g,LOW);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".h.h")
      {
         digitalWrite(h,HIGH);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".h.l")
      {
         digitalWrite(h,LOW);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".i.h")
      {
         digitalWrite(i,HIGH);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".i.l")
      {
         digitalWrite(i,LOW);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".j.h")
      {
         digitalWrite(j,HIGH);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".j.l")
      {
         digitalWrite(j,LOW);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".k.h")
      {
         digitalWrite(k,HIGH);
         Serial.println("OK");
      }
      else if(val=="THUB."+NAME+".k.l")
      {
         digitalWrite(k,LOW);
         Serial.println("OK");
      }
      
      
      else
      {
          Serial.println("THUB."+NAME+".error");
      }
    }   
    indate="";
}

uint8_t oon() {
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(h,HIGH);
  digitalWrite(i,HIGH);
  digitalWrite(j,HIGH);
  digitalWrite(k,HIGH);
}

uint8_t of() {
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,LOW);
  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
  digitalWrite(h,LOW);
  digitalWrite(i,LOW);
  digitalWrite(j,LOW);
  digitalWrite(k,LOW);
}

uint8_t upp() {
  digitalWrite(a,HIGH);
  delay(10);
  digitalWrite(b,HIGH);
  delay(10);
  digitalWrite(c,HIGH);
  delay(10);
  digitalWrite(d,HIGH);
  delay(10);
  digitalWrite(e,HIGH);
  delay(10);
  digitalWrite(f,HIGH);
  delay(10);
  digitalWrite(g,HIGH);
  delay(10);
  digitalWrite(h,HIGH);
  delay(10);
  digitalWrite(i,HIGH);
  delay(10);
  digitalWrite(j,HIGH);
  delay(10);
  digitalWrite(k,HIGH);
}

uint8_t up() {
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  delay(10);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  delay(10);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  delay(10);
  digitalWrite(g,HIGH);
  digitalWrite(h,HIGH);
  delay(10);
  digitalWrite(i,HIGH);
  digitalWrite(j,HIGH);
  delay(10);
  digitalWrite(k,HIGH);
}
