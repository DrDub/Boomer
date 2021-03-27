/*
 * @author Michael Rapp (mrapp@ke.tu-darmstadt.de)
 */
#pragma once

#include "common/sampling/instance_sampling.hpp"


/**
 * Implements bootstrap aggregating (bagging) for selecting a subset of the available training examples with
 * replacement.
 */
class Bagging final : public IInstanceSubSampling {

    private:

        float32 sampleSize_;

    public:

        /**
         * @param sampleSize The fraction of examples to be included in the sample (e.g. a value of 0.6 corresponds to
         *                   60 % of the available examples). Must be in (0, 1]
         */
        Bagging(float32 sampleSize);

        std::unique_ptr<IWeightVector> subSample(const SinglePartition& partition, RNG& rng) const override;

        std::unique_ptr<IWeightVector> subSample(const BiPartition& partition, RNG& rng) const override;

};
