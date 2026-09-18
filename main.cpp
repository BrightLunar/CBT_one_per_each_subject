#include <iostream>
#include "httplib.h"
#include "QuestionDB.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    httplib::Server svr;

    // 1. API 엔드포인트: 랜덤 생성된 문제 목록을 JSON으로 반환
    svr.Get("/api/start-test", [](const httplib::Request& req, httplib::Response& res) {
        std::string json_data = QuestionDB::get_mock_test_json("./questions");
        res.set_content(json_data, "application/json");
    });

    // 2. 정적 파일 라우팅
    // ./public 폴더 안의 index.html을 기본 화면으로 제공
    svr.set_mount_point("/", "./public");
    
    // 브라우저가 이미지 파일에 접근할 수 있도록 권한 부여
    svr.set_mount_point("/questions", "./questions");

    std::cout << "웹 서버가 실행되었습니다. 브라우저에서 http://localhost:8080 으로 접속하세요.\n";
    std::cout << "종료하려면 Ctrl+C 를 누르세요.\n";
    
    svr.listen("0.0.0.0", 8080);

    return 0;
}