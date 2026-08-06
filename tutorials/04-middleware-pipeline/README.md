# Tutorial 04: Middleware Pipeline

CWIST 애플리케이션 미들웨어 체인(`cwist_app_use`) 구성 방법과 요청 체인 가공 예제입니다.

## 빌드 및 실행

```bash
mkdir build && cd build
cmake ..
make
./tut04
```

`curl`로 테스트:
```bash
curl http://127.0.0.1:8083/dashboard
```
