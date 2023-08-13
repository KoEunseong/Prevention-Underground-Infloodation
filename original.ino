#include <Servo.h>

const int sensorPin = A0;    // 아날로그 핀 번호 설정
const int servoPin = 8;      // 서보 모터 핀 번호 설정
const int servo2Pin = 9;      // 서보 모터 핀 번호 설정

Servo servo;
Servo servo2;// Servo 라이브러리를 이용한 객체 생성
float referenceVoltage = 5.0; // 아두이노의 참조 전압 (보드마다 다를 수 있음)
float waterLevel = 0.0;       // 수위 값 저장 변수
int mode = 0;
int i;
//0 평상시
//1 1래밸 재난
//2 2래밸 재난
void setup() {
  servo.attach(servoPin); // 서보 모터를 핀에 연결
  servo2.attach(servo2Pin);
  servo.write(180);  // 서보 모터에 각도 쓰기 ,내리기
  servo2.write(180);
  Serial.begin(9600);   
  //
}

void loop() {
  int sensorValue = analogRead(sensorPin); // 아날로그 값 읽기
  waterLevel = map(sensorValue, 0, 1023, 0, 100); // 아날로그 값을 0 ~ 100 범위로 매핑

  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println(" %");


  switch(mode)
  {
  case 0://평상시
    servo.write(180);
    delay(500);
    break;
  case 1://무릅이하
    servo.write(120);
    delay(500);
    break;
  case 2://무릅위 
    servo.write(180);
    delay(1000);
    servo2.write(0);
    delay(1000);
  }


   if( waterLevel > 50){
    mode = 2;
   }
   else if(waterLevel >30){
    mode = 1;
   }
   else{
    mode = 0;
   }
//  if( waterLevel > 40 ) {
////    isTrue = false;
//    servo.write(120);  // 서보 모터에 각도 쓰기 , 올리기
//    delay(5000);
//    servo.write(180);
//    delay(1000);
//    servo2.write(0);
//    
//    
//    
//  }
//  else {
//    servo.write(180);  // 서보 모터에 각도 쓰기 ,내리기
//  }

  //delay(1000);  // 1초 대기

  
  
}
