# Tutorial 06: DB Connection Pool

멀티스레드 환경에서 안전하게 DB 커넥션을 획득하고 반납하는 CWIST DB 커넥션 풀 사용법입니다.

## 빌드 및 실행

```bash
mkdir build && cd build
cmake ..
make
./tut06
```

`curl`로 테스트:
```bash
curl http://127.0.0.1:8085/pool
```
