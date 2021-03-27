#include "boosting/statistics/statistics_label_wise_provider.hpp"
#include "boosting/statistics/statistics_label_wise_dense.hpp"


namespace boosting {

    /**
     * Provides access to an object of type `ILabelWiseStatistics`.
     */
    class LabelWiseStatisticsProvider : public IStatisticsProvider {

        private:

            std::shared_ptr<ILabelWiseRuleEvaluationFactory> ruleEvaluationFactoryPtr_;

            std::unique_ptr<ILabelWiseStatistics> statisticsPtr_;

        public:

            /**
             * @param ruleEvaluationFactoryPtr  A shared pointer to an object of type `ILabelWiseRuleEvaluationFactory`
             *                                  to switch to when invoking the function `switchRuleEvaluation`
             * @param statisticsPtr             An unique pointer to an object of type `ILabelWiseStatistics` to provide
             *                                  access to
             */
            LabelWiseStatisticsProvider(std::shared_ptr<ILabelWiseRuleEvaluationFactory> ruleEvaluationFactoryPtr,
                                        std::unique_ptr<ILabelWiseStatistics> statisticsPtr)
                : ruleEvaluationFactoryPtr_(ruleEvaluationFactoryPtr), statisticsPtr_(std::move(statisticsPtr)) {

            }

            IStatistics& get() const override {
                return *statisticsPtr_;
            }

            void switchRuleEvaluation() override {
                statisticsPtr_->setRuleEvaluationFactory(ruleEvaluationFactoryPtr_);
            }

    };

    LabelWiseStatisticsProviderFactory::LabelWiseStatisticsProviderFactory(
            std::shared_ptr<ILabelWiseLoss> lossFunctionPtr,
            std::shared_ptr<ILabelWiseRuleEvaluationFactory> defaultRuleEvaluationFactoryPtr,
            std::shared_ptr<ILabelWiseRuleEvaluationFactory> ruleEvaluationFactoryPtr, uint32 numThreads)
        : lossFunctionPtr_(lossFunctionPtr), defaultRuleEvaluationFactoryPtr_(defaultRuleEvaluationFactoryPtr),
          ruleEvaluationFactoryPtr_(ruleEvaluationFactoryPtr), numThreads_(numThreads) {

    }

    std::unique_ptr<IStatisticsProvider> LabelWiseStatisticsProviderFactory::create(
            std::shared_ptr<IRandomAccessLabelMatrix> labelMatrixPtr) const {
        DenseLabelWiseStatisticsFactory statisticsFactory(lossFunctionPtr_, defaultRuleEvaluationFactoryPtr_,
                                                          labelMatrixPtr, numThreads_);
        return std::make_unique<LabelWiseStatisticsProvider>(ruleEvaluationFactoryPtr_, statisticsFactory.create());
    }

}