# Tutorial 01: Hello World Server

CWIST 웹 프레임워크를 사용한 가장 기본적인 HTTP 서버 예제입니다.

## 주요 개념
1. `cwist_app_create()`: CWIST 애플리케이션 인스턴스를 생성합니다.
2. `cwist_app_get(app, path, handler)`: GET 요청에 대한 핸들러를 등록합니다.
3. `cwist_app_listen(app, port)`: 서버를 지정한 포트로 수용하고 이벤트 루프를 실행합니다.

## 빌드 및 실행

```bash
# CMake를 이용한 빌드
mkdir build && cd build
cmake ..
make
./tut01
```

`curl`로 테스트:
```bash
curl http://127.0.0.1:8080/
```
