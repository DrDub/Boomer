/*
 * @author Michael Rapp (mrapp@ke.tu-darmstadt.de)
 */
#pragma once

#include "common/input/feature_matrix_c_contiguous.hpp"
#include "common/input/feature_matrix_csr.hpp"
#include "common/model/rule_model.hpp"


/**
 * Defines an interface for all classes that allow to make predictions for given query examples using an existing
 * rule-based model.
 *
 * @tparam T The type of the values that are stored by the prediction matrix
 */
template<class T>
class IPredictor {

    public:

        virtual ~IPredictor() { };

        /**
         * Obtains predictions for all examples in a C-contiguous matrix, using a specific rule-based model, and writes
         * them to a given prediction matrix.
         *
         * @param featureMatrix     A reference to an object of type `CContiguousFeatureMatrix` that stores the feature
         *                          values of the examples
         * @param predictionMatrix  A reference to an object of type `CContiguousView`, the predictions should be
         *                          written to. May contain arbitrary values
         * @param model             A reference to an object of type `RuleModel` that should be used to obtain the
         *                          predictions
         */
        virtual void predict(const CContiguousFeatureMatrix& featureMatrix, CContiguousView<T>& predictionMatrix,
                             const RuleModel& model) const = 0;

        /**
         * Obtains predictions for all examples in a sparse CSR matrix, using a specific rule-based model, and writes
         * them to a given prediction matrix.
         *
         * @param featureMatrix     A reference to an object of type `CsrFeatureMatrix` that stores the feature values
         *                          of the examples
         * @param predictionMatrix  A reference to an object of type `CContiguousView`, the predictions should be
         *                          written to. May contain arbitrary values
         * @param model             A reference to an object of type `RuleModel` that should be used to obtain the
         *                          predictions
         */
        virtual void predict(const CsrFeatureMatrix& featureMatrix, CContiguousView<T>& predictionMatrix,
                             const RuleModel& model) const = 0;

};