/*
 * @author Michael Rapp (michael.rapp.ml@gmail.com)
 */
#pragma once

#include "common/thresholds/thresholds.hpp"

/**
 * A factory that allows to create instances of the type `ExactThresholds`.
 */
class ExactThresholdsFactory final : public IThresholdsFactory {
    private:

        const uint32 numThreads_;

    public:

        /**
         * @param numThreads The number of CPU threads to be used to update statistics in parallel. Must be at least 1
         */
        ExactThresholdsFactory(uint32 numThreads);

        std::unique_ptr<IThresholds> create(const IColumnWiseFeatureMatrix& featureMatrix,
                                            const IFeatureInfo& featureInfo,
                                            IStatisticsProvider& statisticsProvider) const override;
};
