#include "seco/head_refinement/lift_function_peak.hpp"
#include <cmath>


namespace seco {

    PeakLiftFunction::PeakLiftFunction(uint32 numLabels, uint32 peakLabel, float64 maxLift, float64 curvature)
        : numLabels_(numLabels), peakLabel_(peakLabel), maxLift_(maxLift), exponent_(1.0 / curvature) {

    }

    float64 PeakLiftFunction::calculateLift(uint32 numLabels) const {
        float64 normalization;

        if (numLabels < peakLabel_) {
            normalization = ((float64) numLabels - 1) / ((float64) peakLabel_ - 1);
        } else if (numLabels > peakLabel_) {
            normalization = ((float64) numLabels - (float64) numLabels_)
                            / ((float64) numLabels_ - (float64) peakLabel_);
        } else {
            return maxLift_;
        }

        return 1 + pow(normalization, exponent_) * (maxLift_ - 1);
    }

    float64 PeakLiftFunction::getMaxLift() const {
        return maxLift_;
    }

}