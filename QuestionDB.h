#ifndef QUESTION_DB_H
#define QUESTION_DB_H

#include <string>
#include <vector>
#include <filesystem>
#include <random>
#include <map>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

class QuestionDB {
public:
    static std::string get_mock_test_json(const std::string& pool_dir) {
        std::map<std::string, std::vector<std::string>> subject_pools;

        // 1. 디렉토리 스캔
        if (fs::exists(pool_dir)) {
            for (const auto& entry : fs::directory_iterator(pool_dir)) {
                if (entry.path().extension() == ".png") {
                    std::string filename = entry.path().filename().string();
                    if (filename.length() >= 15 && filename.find("_Q.png") != std::string::npos) {
                        std::string subject = filename.substr(0, 2);
                        subject_pools[subject].push_back(filename);
                    }
                }
            }
        }

        // 2. 랜덤 추출 및 JSON 문자열 조립
        std::random_device rd;
        std::mt19937 gen(rd());
        std::stringstream json_arr;
        json_arr << "[";
        bool is_first = true;

        for (int i = 0; i <= 9; ++i) {
            std::stringstream subj_ss;
            subj_ss << std::setw(2) << std::setfill('0') << i;
            std::string subject = subj_ss.str();

            if (!subject_pools[subject].empty()) {
                std::uniform_int_distribution<> dist(0, subject_pools[subject].size() - 1);
                std::string chosen_q = subject_pools[subject][dist(gen)];
                
                std::string chosen_a = chosen_q;
                size_t pos = chosen_a.rfind("_Q.png");
                if (pos != std::string::npos) {
                    chosen_a.replace(pos, 6, "_A.png");
                }

                if (!is_first) json_arr << ",";
                json_arr << "{\"q\": \"/questions/" << chosen_q << "\", "
                         << "\"a\": \"/questions/" << chosen_a << "\"}";
                is_first = false;
            }
        }
        json_arr << "]";
        
        return json_arr.str();
    }
};

#endif