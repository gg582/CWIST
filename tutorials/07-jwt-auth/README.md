# Tutorial 07: JWT Authentication

CWIST JWT 서명(`cwist_jwt_sign`) 모듈을 이용한 인증 토큰 생성 예제입니다.

## 빌드 및 실행

```bash
mkdir build && cd build
cmake ..
make
./tut07
```

`curl`로 테스트:
```bash
curl http://127.0.0.1:8086/token
```
