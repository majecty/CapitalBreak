
이 파일은 메인 화면에 보일 README 파일 입니다.

this file is READFILE which be shown in main screen

# File  상세

## lua file
* Configuration.lua

컴파일 하지 않고도 이 파일만 바꾸면
상수 값들이 바뀝니다.

간단한 게임 옵션들 설정할 수 있습니다.

이자 율 등등..

## header file들
* Constants.h   

코드에서 사용되는 상수들(문자열, Enum들) 선언

* common.h

일반적으로 자주 쓰이는 헤더파일들 모음

* GlobalFunctions.h

코드 전반적으로 쓰이는 함수들 선언

* Configuration.h

내부적으로 Configuration.lua 와 연동되는 선언들
과 이미지 위치들 등

* global.h

글로벌 변수들 선언

## cpp 파일들
* main.cpp 

맨 처음 시작되는 함수인 main이 들어있다.
전체 프로그램의 초기화와 이벤트 처리 등 담당

* Scene.cpp / GameScene.cpp

각 장면들은 각각의 Scene을 가진다.

맨 첫 화면은 StartScene
게임 화면은 GameScene
엔딩 화면은 GoodEndScene BadEndScene
크레딧 화면은 CreditScene

각각의 화면은
화면을 그리는 일과
이벤트 처리
게임 로직 처리
등 매우 중요한 일을 한다.

