# Tutorial 03: JSON API Server

cJSON과 CWIST 응답 헤더를 조합하여 RESTful JSON API를 작성하는 방법입니다.

## 빌드 및 실행

```bash
mkdir build && cd build
cmake ..
make
./tut03
```

`curl`로 테스트:
```bash
curl -i http://127.0.0.1:8082/api/data
```
