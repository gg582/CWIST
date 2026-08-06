# Tutorial 02: Routing & Path Parameters

CWIST의 동적 경로 파라미터(Dynamic Route Parameters) 사용법을 다룹니다.

## 주요 개념
- `/users/:id`와 같이 경로 변수 선언.
- `cwist_http_request_param(req, "id")`를 통해 URL 경로 파라미터를 추출.

## 빌드 및 실행

```bash
mkdir build && cd build
cmake ..
make
./tut02
```

`curl`로 테스트:
```bash
curl http://127.0.0.1:8081/users/42
```
