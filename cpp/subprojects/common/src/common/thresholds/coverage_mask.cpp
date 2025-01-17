#include "common/thresholds/coverage_mask.hpp"

#include "common/data/arrays.hpp"
#include "common/rule_refinement/prediction.hpp"
#include "common/thresholds/thresholds_subset.hpp"

CoverageMask::CoverageMask(uint32 numElements)
    : array_(new uint32[numElements] {0}), numElements_(numElements), indicatorValue_(0) {}

CoverageMask::CoverageMask(const CoverageMask& coverageMask)
    : array_(new uint32[coverageMask.numElements_]), numElements_(coverageMask.numElements_),
      indicatorValue_(coverageMask.indicatorValue_) {
    copyArray(coverageMask.array_, array_, numElements_);
}

CoverageMask::~CoverageMask() {
    delete[] array_;
}

CoverageMask::iterator CoverageMask::begin() {
    return array_;
}

CoverageMask::iterator CoverageMask::end() {
    return &array_[numElements_];
}

CoverageMask::const_iterator CoverageMask::cbegin() const {
    return array_;
}

CoverageMask::const_iterator CoverageMask::cend() const {
    return &array_[numElements_];
}

uint32 CoverageMask::getNumElements() const {
    return numElements_;
}

uint32 CoverageMask::getIndicatorValue() const {
    return indicatorValue_;
}

void CoverageMask::setIndicatorValue(uint32 indicatorValue) {
    indicatorValue_ = indicatorValue;
}

void CoverageMask::reset() {
    indicatorValue_ = 0;
    setArrayToZeros(array_, numElements_);
}

bool CoverageMask::isCovered(uint32 pos) const {
    return array_[pos] == indicatorValue_;
}

std::unique_ptr<ICoverageState> CoverageMask::copy() const {
    return std::make_unique<CoverageMask>(*this);
}

Quality CoverageMask::evaluateOutOfSample(const IThresholdsSubset& thresholdsSubset, const SinglePartition& partition,
                                          const AbstractPrediction& head) const {
    return thresholdsSubset.evaluateOutOfSample(partition, *this, head);
}

Quality CoverageMask::evaluateOutOfSample(const IThresholdsSubset& thresholdsSubset, BiPartition& partition,
                                          const AbstractPrediction& head) const {
    return thresholdsSubset.evaluateOutOfSample(partition, *this, head);
}

void CoverageMask::recalculatePrediction(const IThresholdsSubset& thresholdsSubset, const SinglePartition& partition,
                                         AbstractPrediction& head) const {
    thresholdsSubset.recalculatePrediction(partition, *this, head);
}

void CoverageMask::recalculatePrediction(const IThresholdsSubset& thresholdsSubset, BiPartition& partition,
                                         AbstractPrediction& head) const {
    thresholdsSubset.recalculatePrediction(partition, *this, head);
}
