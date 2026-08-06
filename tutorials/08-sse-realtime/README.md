# Tutorial 08: Server-Sent Events (SSE)

CWIST SSE (`cwist_sse_send`) 모듈을 이용한 단방향 실시간 이벤트 스트리밍 구성법입니다.

## 빌드 및 실행

```bash
mkdir build && cd build
cmake ..
make
./tut08
```

`curl`로 테스트:
```bash
curl -N http://127.0.0.1:8087/events
```
