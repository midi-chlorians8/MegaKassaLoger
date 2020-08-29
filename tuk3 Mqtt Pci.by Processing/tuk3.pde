// This example sketch connects to shiftr.io
// and sends a message on every keystroke.
//
// After starting the sketch you can find the
// client here: https://shiftr.io/try.
//
// Note: If you're running the sketch via the
// Android Mode you need to set the INTERNET
// permission in Android > Sketch Permissions.
//
// by JoÃ«l GÃ¤hwiler
// https://github.com/256dpi/processing-mqtt

import mqtt.*;

MQTTClient client;

void setup() {
  size(400,200);
  client = new MQTTClient(this);
 //  client.connect("tcp://localhost:1883");
  client.connect("tcp://178.163.226.73:1883");
  client.subscribe("test/temp");
  // client.unsubscribe("/example");
  /*
  for (int i=0;i <=1; i++)
  {
    client.publish("15/mod", "s1");
   delay(2000);  
 }
 */
   
//  client.publish("15/mod", "s3 1");
}

void draw() {
 //   client.publish("15/mod", "s7");
 //   delay(2000);
}



void messageReceived(String topic, byte[] payload) {
  println("new message: " + topic + " - " + new String(payload));
}

void keyPressed() {
  
  if (key == '9' ) {   println("s9 " ); client.publish("15/mod", "s9");  }
  
  if (key == '8' ) {   println("s8 " ); client.publish("15/mod", "s8");  }
  
//  if (key == '7' ) {   println("s7 " ); client.publish("15/mod", "s7");  }
  
// else if (key == '6')  {  println("s6 " ); client.publish("15/mod", "s6");  }
  else if (key == '5')  {  println("s5 " ); client.publish("15/mod", "s5");  } 
  else if (key == 'z'||key == 'я')  {  println("s5 1" ); client.publish("15/mod", "s5 1");  }
  else if (key == 'x'||key == 'ч')  {  println("s5 2" ); client.publish("15/mod", "s5 2");  }
  else if (key == 'c'||key == 'с')  {  println("s5 3" ); client.publish("15/mod", "s5 3");  }

  
  else if (key == '1')  {  println("s1 " ); client.publish("15/mod", "s1");  }
 
  else if (key == 'q' ||key == 'й' )
  {     
      println("q OgranSkorost OFF s3 1" );client.publish("15/mod", "s3 1");
  }
        else if (key == 'w'||key == 'ц')
  {
      println("w OgranSkorost ON s3 2" );  client.publish("15/mod", "s3 2");
  }
  
  
  
    else if (key == 'i' ||key == 'ш' )
  {     
      println("Справка по кнопкам:" );
      println("Кнопка 1 - MQTT s1   - Включает режим 1" );
      println("========" );
      println("Кнопка q - MQTT s3 1 - Включает OgranSkorost OFF" );
      println("Кнопка w - MQTT s3 2 - Включает OgranSkorost ON" );
      println("========" );
      println("Кнопка 5 - MQTT s5   - Включает режим 5 poff()" );
      println("Кнопка z - MQTT s5 1 - Включает режим 5 c параметром 1" );
      println("Кнопка x - MQTT s5 2 - Включает режим 5 c параметром 2" );
      println("Кнопка с - MQTT s5 3 - Включает режим 5 c параметром 3" );
      println("========" );
      println("Кнопка 8 - MQTT s8   - Включает функцию посигналить" );
      println("========" );
      println("Кнопка 9 - MQTT s9   - Включает режим угон" );
      
  }
}
