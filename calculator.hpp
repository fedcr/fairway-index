#pragma once
#include "models.hpp"
#include "differential.hpp"
#include "handicap_table.hpp"
#include <vector>
#include <numeric>
#include <algorithm>

namespace WHS {

    struct HandicapResult {
            double handicap_index;
                double low_handicap_index;
                    bool soft_cap_applied;
                        bool hard_cap_applied;
                            size_t differentials_counted;
                                std::vector<size_t> used_differential_indices;
    };

    class IndexCalculator {
        public:
           static HandicapResult compute_index(std::vector<RoundScore>& history, double low_hcp_365d) {
                    HandicapResult res{};
                            res.low_handicap_index = low_hcp_365d;
                                    res.soft_cap_applied = false;
                                            res.hard_cap_applied = false;

                                                   size_t available = std::min<size_t>(history.size(), 20);
                                                           if (available < 3) {
                                                                        res.handicap_index = 54.0;
                                                                                    return res;
                                                           }

                                                                   auto [count_to_use, adj] = RulesTable::get_selection_rule(available);
                                                                           res.differentials_counted = count_to_use;

                                                                                   std::vector<std::pair<double, size_t>> indexed_diffs;
                                                                                           for (size_t i = 0; i < available; ++i) {
                                                                                                        indexed_diffs.push_back({history[i].score_differential, i});
                                                                                           }

                                                                                                   std::sort(index_diffs.begin(), indexed_diffs.end(), [](const auto& a, const auto& b) {
                                                                                                                return a.first < b.first;
           });
        
                double sum = 0.0;
                    for (size_t i = 0; i < count_to_use; ++i) {
                                    sum += indexed_diffs[i].first;
                                           res.used_differential_indices.push_back(indexed_diffs[i].second);
                    }
                
                        double raw_index = (sum / count_to_use) + adj;
                            double capped_index = raw_index;
                        
                                    if (low_hcp_365d >= 0.0 && available >= 20) {
                                                    if (raw_index > (low_hcp_365d + 3.0)) {
                                                                        res.soft_cap_applied = true;
                                                                                        double excess = raw_index - (low_hcp_365d + 3.0);
                                                                                                        capped_index = (low_hcp_365d + 3.0) + (excess * 0.5);
                                                    }
                                                                if (capped_index> (low_hcp_365d + 5.0)) {
                                                                                    res.hard_cap_applied = true;
                                                                                                    capped_index = low_hcp_365d + 5.0;
                                                                }
                                                            }

                                                                    res.handicap_index = std::clamp(DifferentialEngine::round_one_decimal(capped_index), -10.0, 54.0);
                                                                           return res;
                                                        }
                                                    };

}