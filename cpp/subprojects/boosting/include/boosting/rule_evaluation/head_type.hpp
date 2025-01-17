/*
 * @author Michael Rapp (michael.rapp.ml@gmail.com)
 */
#pragma once

#include "boosting/losses/loss_example_wise.hpp"
#include "boosting/losses/loss_label_wise_sparse.hpp"
#include "boosting/math/blas.hpp"
#include "boosting/math/lapack.hpp"
#include "common/input/feature_matrix.hpp"
#include "common/input/label_matrix_row_wise.hpp"

namespace boosting {

    /**
     * Defines an interface for all classes that allow to configure the heads of the rules that should be induced by a
     * rule learner.
     */
    class IHeadConfig {
        public:

            virtual ~IHeadConfig() {};

            /**
             * Creates and returns a new object of type `IStatisticsProviderFactory` according to the specified
             * configuration.
             *
             * @param featureMatrix A reference to an object of type `IFeatureMatrix` that provides access to the
             *                      feature values of the training examples
             * @param labelMatrix   A reference to an object of type `IRowWiseLabelMatrix` that provides access to the
             *                      labels of the training examples
             * @param lossConfig    A reference to an object of type `ILabelWiseLossConfig` that specifies the
             *                      configuration of the loss function
             * @return              An unique pointer to an object of type `IStatisticsProviderFactory` that has been
             *                      created
             */
            virtual std::unique_ptr<IStatisticsProviderFactory> createStatisticsProviderFactory(
              const IFeatureMatrix& featureMatrix, const IRowWiseLabelMatrix& labelMatrix,
              const ILabelWiseLossConfig& lossConfig) const = 0;

            /**
             * Creates and returns a new object of type `IStatisticsProviderFactory` according to the specified
             * configuration.
             *
             * @param featureMatrix A reference to an object of type `IFeatureMatrix` that provides access to the
             *                      feature values of the training examples
             * @param labelMatrix   A reference to an object of type `IRowWiseLabelMatrix` that provides access to the
             *                      labels of the training examples
             * @param lossConfig    A reference to an object of type `ISparseLabelWiseLossConfig` that specifies the
             *                      configuration of the loss function
             * @return              An unique pointer to an object of type `IStatisticsProviderFactory` that has been
             *                      created
             */
            virtual std::unique_ptr<IStatisticsProviderFactory> createStatisticsProviderFactory(
              const IFeatureMatrix& featureMatrix, const IRowWiseLabelMatrix& labelMatrix,
              const ISparseLabelWiseLossConfig& lossConfig) const = 0;

            /**
             * Creates and returns a new object of type `IStatisticsProviderFactory` according to the specified
             * configuration.
             *
             * @param featureMatrix A reference to an object of type `IFeatureMatrix` that provides access to the
             *                      feature values of the training examples
             * @param labelMatrix   A reference to an object of type `IRowWiseLabelMatrix` that provides access to the
             *                      labels of the training examples
             * @param lossConfig    A reference to an object of type `IExampleWiseLossConfig` that specifies the
             *                      configuration of the loss function
             * @param blas          A reference to an object of type `Blas` that allows to execute BLAS routines
             * @param lapack        A reference to an object of type `Lapack` that allows to execute LAPACK routines
             * @return              An unique pointer to an object of type `IStatisticsProviderFactory` that has been
             *                      created
             */
            virtual std::unique_ptr<IStatisticsProviderFactory> createStatisticsProviderFactory(
              const IFeatureMatrix& featureMatrix, const IRowWiseLabelMatrix& labelMatrix,
              const IExampleWiseLossConfig& lossConfig, const Blas& blas, const Lapack& lapack) const = 0;

            /**
             * Returns, whether the heads of rules are partial, i.e., they predict for a subset of the available labels,
             * or not.
             *
             * @return True, if the heads of rules are partial, false otherwise
             */
            virtual bool isPartial() const = 0;

            /**
             * Returns whether the rule heads predict for a single label or not.
             *
             * @return True, if the rule heads predict for a single label, false otherwise
             */
            virtual bool isSingleLabel() const = 0;
    };

}
