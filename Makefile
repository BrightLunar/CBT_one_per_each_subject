# 컴파일러 및 플래그 설정
CXX = g++
CXXFLAGS = -std=c++17 -Wall -D_WIN32_WINNT=0x0A00
LDFLAGS = -lws2_32

# 실행 파일 이름 (윈도우 환경이므로 .exe 추가)
TARGET = mock_server.exe

# 소스 및 헤더 파일
SRCS = main.cpp
HEADERS = QuestionDB.h httplib.h

# 기본 실행 대상
all: $(TARGET)

# 실행 파일 빌드 규칙
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)
	@echo "빌드가 완료되었습니다. 실행 파일: $(TARGET)"

# 서버 실행 (make run)
run: $(TARGET)
	@echo "웹 서버를 시작합니다..."
	./$(TARGET)

# 빌드된 파일 삭제 (make clean)
clean:
	del $(TARGET)
	@echo "실행 파일이 삭제되었습니다."