#pragma once
#include <cstddef>
#include <algorithm>

namespace WHS {

    struct ScaleEntry {
            size_t total_scores;
            size_t differentials_used;
            double adjustment;
    };

    class RulesTable {
        public:
            static std::pair<size_t, double> get_selection_rule(size_t n_scores) {
                        if (n_scores < 3) return {0, 0.0};
                                if (n_scores == 3) return {1, -2.0};
                                        if (n_scores == 4) return {1, -1.0};
                                                if (n_scores == 5) return {1, 0.0};
                                                        if (n_scores == 6) return {2, -1.0};
                                                                if (n_scores <= 8) return {2, 0.0};
                                                                        if (n_scores <= 11) return {3, 0.0};
                                                                                if (n_scores <= 14) return {4, 0.0};
                                                                                        if (n_scores <= 16) return {5, 0.0};
                                                                                                if (n_scores <= 18) return {6, 0.0};
                                                                                                        if (n_scores == 19) return {7, 0.0};
                                                                                                               return {8, 0.0}; // 20 score: media degli 8 migliori
            }
        };

    }