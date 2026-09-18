# 1단계: 빌드 환경 (GCC 12)
FROM gcc:12 AS builder

WORKDIR /app
COPY . .

# 리눅스 환경에 맞게 컴파일
RUN g++ -std=c++17 main.cpp -o mock_server -pthread

# 2단계: 실행 환경 (GCC 12와 호환되는 최신 데비안 리눅스로 변경)
FROM debian:bookworm-slim

WORKDIR /app

# 빌드된 서버 파일과 필요한 폴더들 복사
COPY --from=builder /app/mock_server .
COPY --from=builder /app/public ./public
COPY --from=builder /app/questions ./questions

# 서버 실행
CMD ["./mock_server"]