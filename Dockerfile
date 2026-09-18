# 1단계: 빌드 환경 (GCC 사용)
FROM gcc:12 AS builder

WORKDIR /app
COPY . .

# 리눅스 환경에 맞게 컴파일 (ws2_32 대신 pthread 사용)
RUN g++ -std=c++17 main.cpp -o mock_server -pthread

# 2단계: 실행 환경 (가벼운 데비안 리눅스로 전환)
FROM debian:bullseye-slim

WORKDIR /app

# 빌드된 서버 파일과 필요한 폴더들 복사
COPY --from=builder /app/mock_server .
COPY --from=builder /app/public ./public
COPY --from=builder /app/questions ./questions

# 서버 실행
CMD ["./mock_server"]