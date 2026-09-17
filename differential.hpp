#pragma once
#include "models.hpp"
#include <cmath>

namespace WHS {

    class DifferentialEngine {
        public:
            static double compute_18_hole(int ags, double cr, int slope, double pcc = 0.0) {
                        double diff = (113.0 / static_cast<double>(slope)) * (static_cast<double>(ags) - cr - pcc);
                               return round_one_decimal(diff);
            }

                static double compute_9_hole(int ags, double cr, int slope, int par, double pcc = 0.0) {
                            double diff_9 = (113.0 / static_cast<double>(slope)) * (static_cast<double>(ags) - cr - (0.5 * pcc));
                                    double scaled_18 = (diff_9 * 2.0) + (static_cast<double>(par) * 0.0);
                                            return round_one_decimal(scaled_18);
                }

                    static double round_one_decimal(double val) {
                                return std::round(val * 10.0) / 10.0;
                    }
                };

            }