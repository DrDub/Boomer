/*
 * @author Michael Rapp (michael.rapp.ml@gmail.com)
 */
#pragma once

#include "boosting/data/statistic_vector_example_wise_dense.hpp"
#include "boosting/rule_evaluation/rule_evaluation.hpp"
#include "common/indices/index_vector_complete.hpp"
#include "common/indices/index_vector_partial.hpp"

#include <memory>

namespace boosting {

    /**
     * Defines an interface for all factories that allow to create instances of the type `IRuleEvaluation` that allow to
     * calculate the predictions of rules, based on the gradients and Hessians that have been calculated according to a
     * loss function that is applied example-wise.
     */
    class IExampleWiseRuleEvaluationFactory {
        public:

            virtual ~IExampleWiseRuleEvaluationFactory() {};

            /**
             * Creates and returns a new object of type `IRuleEvaluation` that allows to calculate the predictions of
             * rules that predict for all available labels, based on the gradients and Hessians that are stored by a `
             * DenseExampleWiseStatisticVector`.
             *
             * @param statisticVector   A reference to an object of type `DenseExampleWiseStatisticVector`. This vector
             *                          is only used to identify the function that is able to deal with this particular
             *                          type of vector via function overloading
             * @param indexVector       A reference to an object of type `CompleteIndexVector` that provides access to
             *                          the indices of the labels for which the rules may predict
             * @return                  An unique pointer to an object of type `IRuleEvaluation` that has been created
             */
            virtual std::unique_ptr<IRuleEvaluation<DenseExampleWiseStatisticVector>> create(
              const DenseExampleWiseStatisticVector& statisticVector, const CompleteIndexVector& indexVector) const = 0;

            /**
             * Creates and returns a new object of type `IRuleEvaluation` that allows to calculate the predictions of
             * rules that predict for a subset of the available labels, based on the gradients and Hessians that are
             * stored by a `DenseExampleWiseStatisticVector`.
             *
             * @param statisticVector   A reference to an object of type `DenseExampleWiseStatisticVector`. This vector
             *                          is only used to identify the function that is able to deal with this particular
             *                          type of vector via function overloading
             * @param indexVector       A reference to an object of type `PartialIndexVector` that provides access to
             *                          the indices of the labels for which the rules may predict
             * @return                  An unique pointer to an object of type `IRuleEvaluation` that has been created
             */
            virtual std::unique_ptr<IRuleEvaluation<DenseExampleWiseStatisticVector>> create(
              const DenseExampleWiseStatisticVector& statisticVector, const PartialIndexVector& indexVector) const = 0;
    };

}
