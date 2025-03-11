# IOCP를 이용한 채팅 서버 구축

## 개요

이 프로젝트는 IOCP를 이용하여 비동기 소켓 통신을 구현한 채팅 서버입니다. 서버는 클라이언트의 접속을 받아들이고, 클라이언트 간의 메시지를 주고받을 수 있습니다. 클라이언트는 서버에 접속하여 로그인하고, 채팅방에 입장하여 메시지를 전송할 수 있습니다.

## 주요 기능
 - 	사용자 인증 및 관리
 - 	채팅방 생성 및 관리
 - 	실시간 메시지 전송
 -	에러 코드 관리

## 요구 사항

## 설치

## 실행 방법

### 1. 서버 실행

- `ChatServer` 프로젝트를 빌드하고 실행하여 서버를 시작합니다.
- `"Define.h"`에서 서버의 포트, 최대 인원 수, 버퍼 사이즈 등을 설정할 수 있습니다.
- 서버가 설정한 포트에서 클라이언트의 접속을 기다립니다.

- ### 2. 클라이언트 실행

- `ChatClient` 프로젝트를 빌드하고 실행합니다.
- 클라이언트에서 접속할 서버의 **IP**와 **Port**를 입력하고 "접속하기" 버튼을 클릭하여 서버에 접속합니다.
- "접속 끊기" 버튼을 클릭하여 서버와의 연결을 종료할 수 있습니다.
- 사용자는 **사용자 이름**을 입력하고 "로그인" 버튼을 클릭하여 서버에 로그인합니다.
- **채팅방 번호**를 입력하고 "Enter" 버튼을 클릭하여 원하는 채팅방에 입장합니다.
- 메시지를 입력 후 "chat" 버튼을 클릭하여 메시지를 전송하고, 다른 클라이언트로부터 오는 메시지를 실시간으로 확인합니다.
- "Leave" 버튼을 클릭하여 채팅방에서 퇴장할 수 있습니다.
- 
## 동작 방식

이 프로젝트는 서버와 클라이언트 간의 메시지 전송을 관리하는 방식으로 동작합니다. 주요 흐름은 다음과 같습니다:

1. **서버**는 IOCP를 이용하여 클라이언트의 접속을 받아들이고, 클라이언트 간의 메시지를 주고받을 수 있습니다.
2. **클라이언트**는 사용자가 로그인하고 채팅방에 입장한 후, 다른 클라이언트와 메시지를 주고받을 수 있습니다.
3. **서버 접속**: 클라이언트는 접속할 서버의 IP와 Port를 입력하고 서버에 접속합니다.
4. **로그인**: 사용자는 자신의 이름을 입력하여 서버에 로그인합니다.
5. **채팅방 입장**: 로그인 후 사용자는 특정 채팅방에 입장할 수 있습니다.
6. **메시지 전송**: 사용자가 채팅방에 메시지를 전송하면, 서버는 해당 채팅방에 있는 모든 사용자에게 메시지를 브로드캐스트합니다.
7. **브로드캐스팅**: 서버는 같은 채팅방에 있는 클라이언트들에게만 메시지를 전달합니다.
8. **채팅방 퇴장**: 사용자가 채팅방에서 퇴장하면 남은 사용자에게 퇴장 메시지를 알립니다.

### 동작 흐름

1. **서버 시작**:
   - 서버는 지정된 IP 주소(`127.0.0.1`)와 포트(`65535`)에서 클라이언트의 연결을 기다립니다.
   - 서버는 클라이언트의 연결을 받아들이고, 클라이언트의 요청을 처리합니다.

2. **클라이언트 로그인**:
   - 클라이언트가 서버에 연결한 후, 로그인 창에서 사용자 이름을 입력하면 서버에 `"Login"` 패킷을 전송합니다.
   - 서버는 해당 사용자 이름을 확인하고, 로그인 성공 또는 실패 메시지를 클라이언트에 전달합니다.

3. **채팅방 입장**:
   - 로그인 성공 후, 클라이언트는 `"RoomEnter"` 패킷을 통해 원하는 채팅방에 입장합니다.
   - 서버는 해당 클라이언트를 채팅방에 추가하고, 입장 성공 메시지를 클라이언트에게 전달합니다.
   - 서버는 각 채팅방에 참여한 클라이언트를 추적하고, 동일 채팅방에 있는 모든 클라이언트에게 패킷을 전달합니다.

4. **메시지 전송 및 수신**:
   - 클라이언트가 메시지를 입력하고 `"Message"` 패킷을 서버로 전송하면, 서버는 해당 채팅방에 있는 모든 사용자에게 메시지를 브로드캐스트합니다.
   - 클라이언트는 서버로부터 받은 메시지를 실시간으로 화면에 표시합니다.

5. **채팅방 퇴장**:
   - 사용자가 `"RoomLeave"` 패킷을 서버로 전송하면 해당 채팅방에서 퇴장합니다.
   - 사용자가 퇴장하면 서버는 동일 채팅방에 있는 다른 클라이언트들에게 퇴장한 사용자 정보를 브로드캐스트합니다.

6. **세션 종료**:
   - 사용자가 연결을 종료하면, 서버는 해당 클라이언트의 세션을 종료하고, 연결된 다른 클라이언트들에게 종료 패킷을 전송합니다.