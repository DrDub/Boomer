/*
 * @author Michael Rapp (michael.rapp.ml@gmail.com)
 */
#pragma once

#include "common/data/view_one_dimensional.hpp"

/**
 * Implements read-only access to the values that are stored in a pre-allocated C-contiguous array.
 *
 * @tparam T The type of the values
 */
template<typename T>
class MLRLCOMMON_API VectorConstView : public IOneDimensionalView {
    protected:

        /**
         * The number of elements in the view.
         */
        uint32 numElements_;

        /**
         * A pointer to the array that stores the values, the view provides access to.
         */
        T* array_;

    public:

        /**
         * @param numElements   The number of elements in the view
         * @param array         A pointer to a C-contiguous array of template type `T` that stores the values, the view
         *                      provides access to
         */
        VectorConstView(uint32 numElements, T* array);

        virtual ~VectorConstView() override {};

        /**
         * An iterator that provides read-only access to the elements in the view.
         */
        typedef const T* const_iterator;

        /**
         * Returns a `const_iterator` to the beginning of the view.
         *
         * @return A `const_iterator` to the beginning
         */
        const_iterator cbegin() const;

        /**
         * Returns a `const_iterator` to the end of the view.
         *
         * @return A `const_iterator` to the end
         */
        const_iterator cend() const;

        /**
         * Returns a const reference to the element at a specific position.
         *
         * @param pos   The position of the element
         * @return      A const reference to the specified element
         */
        const T& operator[](uint32 pos) const;

        /**
         * @see `IOneDimensionalView::getNumElements`
         */
        uint32 getNumElements() const override final;
};

/**
 * Implements read and write access to the values that are stored in a pre-allocated C-contiguous array.
 *
 * @tparam T The type of the values
 */
template<typename T>
class MLRLCOMMON_API VectorView : public VectorConstView<T> {
    public:

        /**
         * @param numElements   The number of elements in the view
         * @param array         A pointer to a C-contiguous array of template type `T` that stores the values, the view
         *                      provides access to
         */
        VectorView(uint32 numElements, T* array);

        virtual ~VectorView() override {};

        /**
         * An iterator that provides access to the elements in the view and allows to modify them.
         */
        typedef T* iterator;

        /**
         * Returns an `iterator` to the beginning of the view.
         *
         * @return An `iterator` to the beginning
         */
        iterator begin();

        /**
         * Returns an `iterator` to the end of the view.
         *
         * @return An `iterator` to the end
         */
        iterator end();

        /**
         * Returns a const reference to the element at a specific position.
         *
         * @param pos   The position of the element
         * @return      A const reference to the specified element
         */
        const T& operator[](uint32 pos) const;

        /**
         * Returns a reference to the element at a specific position.
         *
         * @param pos   The position of the element
         * @return      A reference to the specified element
         */
        T& operator[](uint32 pos);
};
