#include "../include/models.hpp"
#include "../include/differential.hpp"
#include "../include/calculator.hpp"
#include <iostream>
#include <fstream>

void export_state_to_json(const std::vector<WHS::RoundScore>& score, const WHS::HandicapResult& res, const std::string& path) {
        std::ofstream out(path);
            out << "{\n  \"handicapIndex\": " << res.handicap_index << ",\n";
            out << "  \"lowIndex\": " << res.low_handicap_index << ",\n";
            out << "  \"softCap\": " << (res.soft_cap_applied ? "true" : "false") << ",\n";
            out << "  \"hardCap\": " << (res.hard_cap_applied ? "true" : "false") << ",\n";
            out << "  \"rounds\": [\n";
            for (size_t i = 0; i < score.size(); ++i) {
                        const auto& r = score[i];        bool used = std::find(res.used_differential_indices.begin(), res.used_differential_indices.end(), i) != res.used_differential_indices.end();
                                out << "    {\"date\":\"" << r.date << "\",\"ags\":" << r.adjusted_gross_score 
                                        << ","diff\":" << r.score_differential << ",\"used\":" << (used ? "true" : "false") << "}"
                                                << (i + 1 < scores.size() ? ",\n" : "\n");
}
    out << "  ]\n}\n";
}

int main() {
        std::vector<WHS::RoundScore> history;
            // Dati sintetici di tst: 20 score completi
                std::vector<int> raw_gross = {82, 85, 79, 88, 91, 84, 80, 83, 86, 82, 78, 85, 87, 83, 81, 84, 86, 80, 82, 83};
                    for (size_t i = 0; i < raw_gross.size(); ++i) {
                                WHS::RoundScore s;
                                        s.date = "2026-0" + std::to_string((i % 9) + 1) + "-15";
                                                s.adjusted_gross_score = raw_gross[i];
                                                        s.course_rating_used = 71.8;
                                                                s.slope_rating_used = 128;
                                                                        s.par_used = 72;
                                                                                s.type = WHS::RoundType::EIGHTEEN_HOLES;
                                                                                        s.pcc = 0.0;
                                                                                                s.score_differential = WHS::DifferentialEngine::compute_18_hole(s.adjusted_gross_score, s.course_rating_used, s.slope_rating_used);
                                                                                                        history.push_back(s);
                    }

                        auto result = WHS::IndexCalculator::compute_index(history, 8.5);

                            std::cout << "==========================================\n";
                                std::cout << "   FAIRWAYINDEX - WHS ENGINE OUTPUT        \n";
                                    std::cout << "===========================================\n";
                                        std::cout << "Handicap Index Calcolato : " << result.handicap_index << "\n"
                                            std::cout << "Differenziali Utilizzati : " << result.differentials_counted << " su " << history.size() << "\n";
                                                std::cout << "Soft Cap Attivo          : " << (result.soft_cap_applied ? "SI" : "NO") << "\n";
                                                    std::cout << "Hard Cap Attivo         : " << (result.hard_cap_applied ? "SI" : "NO") << "\n";
                                                        std::cout << "===========================================\n";

                                                            export_state_to_json(history, result, "web/handicap_data.json");
                                                            std::cout << "[+] Dati esportati con successo in 'web/andicap_data.json'\n";
                                                            return 0;
}