# TeamProject
# PJB in.
#
#
#
#
#
#
#
#
# Code Style.
#   카멜 표기법.            파스칼 표기법.          스네이크 표기법.
#       - int codeStyle;        - int CodeStyle;        - int code_style;
#
# 변수      : 카멜 표기법.
# 상수      : 대문자 스네이크 표기법.
# 글로벌 변수, 상수 : 대문자 스네이크 표기법.
# 매개 변수 : _가 붙은 카멜 표기법.
# 함수      : 파스칼 표기법.
# 클래스    : 파스칼 표기법. (+ 구조체, 공용체)
# 매크로    : 대문자 스네이크 표기법. (+ 열거형)(+ typedef)
#
#
#
# 클래스 내에서...
#   class A
# {
#   private:
#       변수
#   protected:
#       변수
#   public:
#       변수
#   private:
#       함수
#   protected:
#       함수
#   public:
#       함수
#   }
# (항목이 많다 싶으면)변수를 위에, 함수를 아래에.
# private, protected, public 순으로 정리.
#
# 함수 순서.
#   생성자, 소멸자.
#   오버라이딩하는 함수.
#   getter, setter.
#   나머지.
#
#   * 오버라이딩된 함수를 오버로딩하는 함수는 끼워넣음.
#   ex)
#       void Init(); <- 요게 오버라이딩된 함수면.
#       void Init(int _i); <- 이건 적당히 Init() 위, 아래에 위치.
#
#
#
# 괄호.
#   ~~()
#   {
#       ~~~
#   }
#
#   () 안이 길어질 떄.
#       if( i < 123
#           && j < 1234
#           && k < 12345 )
#       {
#           ~~~~
#           ~~~~
#       }
#   
#   
#   
#   열거형(클래스) 정의시.
#       맨 뒤에 (열거형 명)_NUM 추가.
#       해당 값으로 열거형의 유효한 멤버의 개수를 알 수 있음.
#       ex)
#           enum class IMAGE_LOAD_KIND
#           {
#           	LOAD_RESOURCE = 0,
#           	LOAD_FILE,
#           	LOAD_EMPTY,
#           	LOAD_END,
#           	IMAGE_LOAD_KIND_NUM
#           };
#           IMAGE_LOAD_KIND_NUM은 4로 유효한 멤버는 총 4개.
#
#
#
# 헤더.
#   https://del4u.tistory.com/29
#   stdafx -> cpp파일과 매칭되는 헤더 -> c <> -> c++ <> -> "" 순, 사전순으로 정렬.
#   ex)
#       //foo.cpp
#       #include "Stdafx/stdafx.h"
#
#       #include "foo.h"
#
#       #include <memory.h>
#       #include <stdlib.h>
#
#       #include <iostream>
#       #include <vector>
#
#       #include "myHeader.h"
#       #include "myHeader2.h"
#
#
#
# 주석.
#   한 줄 : //로 처리.
#   여러 줄 : /**/로 처리.
#   * 팁.
#       여러 줄 주석을
#       /*      (주석 처리된 상태)
#           ~~~
#       //*/
#       이렇게 해놓으면 위에 '/'만 더하고 빼서 주석을 처리, 해제 할 수 있다.
#       //*     (주석 해제된 상태)
#           ~~~
#       //*/
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#