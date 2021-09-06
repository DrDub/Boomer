/*
 * @author Michael Rapp (mrapp@ke.tu-darmstadt.de)
 */
#pragma once

#include "boosting/rule_evaluation/rule_evaluation_label_wise.hpp"
#include "boosting/data/statistic_vector_dense_label_wise.hpp"


namespace boosting {

    /**
     * Allows to create instances of the class `LabelWiseSingleLabelRuleEvaluationFactory`.
     */
    class LabelWiseSingleLabelRuleEvaluationFactory final : public ILabelWiseRuleEvaluationFactory {

        private:

            float64 l2RegularizationWeight_;

        public:

            /**
             * @param l2RegularizationWeight The weight of the L2 regularization that is applied for calculating the
             *                               scores to be predicted by rules
             */
            LabelWiseSingleLabelRuleEvaluationFactory(float64 l2RegularizationWeight);

            std::unique_ptr<IRuleEvaluation<DenseLabelWiseStatisticVector>> createDense(
                const CompleteIndexVector& indexVector) const override;

            std::unique_ptr<IRuleEvaluation<DenseLabelWiseStatisticVector>> createDense(
                const PartialIndexVector& indexVector) const override;

    };

}