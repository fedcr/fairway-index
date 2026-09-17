#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace WHS {

    enum class RoundType {
            EIGHTEEN_HOLES,
                NINE_HOLES
    };

    struct CourseRtingData {
            std::string course_name;
            std::string tee_color;
            double course_rating;
            int slope_rating;
            int par;
            RoundType type;
    };

    struct RoundScore {
            std::string date;
            std::string course_id;
            int adjusted_gross_score;
            double course_rating_used;
            int slope_rating_used;
            int par_used;
            RoundType type;
            double pcc;
            double score_differential;
    };

}