#include <iostream>
#include <cstdlib> // getenv 사용을 위해 추가
#include "httplib.h"
#include "QuestionDB.h"

// 윈도우 환경일 경우에만 windows.h 포함
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
// 윈도우 환경일 경우에만 콘솔 인코딩 설정
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    httplib::Server svr;

    // 1. API 엔드포인트
    svr.Get("/api/start-test", [](const httplib::Request& req, httplib::Response& res) {
        std::string json_data = QuestionDB::get_mock_test_json("./questions");
        res.set_content(json_data, "application/json");
    });

    // 2. 정적 파일 라우팅
    svr.set_mount_point("/", "./public");
    svr.set_mount_point("/questions", "./questions");

    // 3. Render.com 동적 포트 할당 처리
    int port = 8080; // 기본 포트 (로컬 테스트용)
    const char* port_env = std::getenv("PORT");
    if (port_env != nullptr) {
        port = std::stoi(port_env);
    }

    std::cout << "웹 서버가 실행되었습니다. 포트: " << port << "\n";
    std::cout << "종료하려면 Ctrl+C 를 누르세요.\n";
    
    // 0.0.0.0 으로 열어야 외부(Render)에서 접속 가능
    svr.listen("0.0.0.0", port);

    return 0;
}