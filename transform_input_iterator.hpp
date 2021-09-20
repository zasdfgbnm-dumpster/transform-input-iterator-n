#pragma once

#include <iterator>
#include <iostream>
#include <tuple>

template <
    typename ValueType,
    typename ConversionOp,
    typename OffsetT = ptrdiff_t,
    typename ...InputIteratorTs>
class TransformInputIteratorN
{
public:

    // Required iterator traits
    typedef TransformInputIteratorN             self_type;              ///< My own type
    typedef OffsetT                             difference_type;        ///< Type to express the result of subtracting one iterator from another
    typedef ValueType                           value_type;             ///< The type of the element the iterator can point to
    typedef ValueType*                          pointer;                ///< The type of a pointer to an element the iterator can point to
    typedef ValueType                           reference;              ///< The type of a reference to an element the iterator can point to

    typedef std::random_access_iterator_tag     iterator_category;      ///< The iterator category

private:

    ConversionOp    conversion_op;
    std::tuple<InputIteratorTs...>  input_itrs;
    static constexpr auto tuple_size = std::tuple_size<decltype(input_itrs)>::value;

    // Helper functions
    template<typename ...Whatever>
    void noop(Whatever...) {}

    template<std::size_t ...I>
    void plus_plus(std::index_sequence<I...>) {
        noop((std::get<I>(input_itrs)++)...);
    }

    template<typename Distance, std::size_t ...I>
    void plus_eq(Distance d, std::index_sequence<I...>) {
        noop((std::get<I>(input_itrs) += d)...);
    }

    template<std::size_t ...I>
    void minus_minus(std::index_sequence<I...>) {
        noop((std::get<I>(input_itrs)--)...);
    }

    template<typename Distance, std::size_t ...I>
    void minus_eq(Distance d, std::index_sequence<I...>) {
        noop((std::get<I>(input_itrs) -= d)...);
    }

    template<std::size_t ...I>
    reference apply(std::index_sequence<I...>) const {
        return conversion_op(*std::get<I>(input_itrs)...);
    }

public:

    /// Constructor
    TransformInputIteratorN(
        InputIteratorTs...  input_itrs,         ///< Input iterators to wrap
        ConversionOp        conversion_op)      ///< Conversion functor to wrap
    :
        conversion_op(conversion_op),
        input_itrs(input_itrs...)
    {}

    /// Postfix increment
    self_type operator++(int)
    {
        self_type retval = *this;
        plus_plus(std::make_index_sequence<tuple_size>());
        return retval;
    }

    /// Prefix increment
    self_type operator++()
    {
        plus_plus(input_itrs, std::make_index_sequence<tuple_size>());
        return *this;
    }

    /// Postfix decrement
    self_type operator--(int)
    {
        self_type retval = *this;
        minus_minus(std::make_index_sequence<tuple_size>());
        return retval;
    }

    /// Prefix decrement
    self_type operator--()
    {
        minus_minus(input_itrs, std::make_index_sequence<tuple_size>());
        return *this;
    }

    /// Indirection
    reference operator*() const
    {
        return apply(std::make_index_sequence<tuple_size>());
    }

    /// Addition
    template <typename Distance>
    self_type operator+(Distance n) const
    {
        self_type result = *this;
        result.plus_eq(n, std::make_index_sequence<tuple_size>());
        return result;
    }

    /// Addition assignment
    template <typename Distance>
    self_type& operator+=(Distance n)
    {
        plus_eq(n, std::make_index_sequence<tuple_size>());
        return *this;
    }

    /// Subtraction
    template <typename Distance>
    self_type operator-(Distance n) const
    {
        self_type result = *this;
        result.minus_eq(n, std::make_index_sequence<tuple_size>());
        return result;
    }

    /// Subtraction assignment
    template <typename Distance>
    self_type& operator-=(Distance n)
    {
        minus_eq(n, std::make_index_sequence<tuple_size>());
        return *this;
    }

    /// Distance
    difference_type operator-(self_type other) const
    {
        return std::get<0>(input_itrs) - std::get<0>(other.input_itrs);
    }

    /// Array subscript
    template <typename Distance>
    reference operator[](Distance n) const
    {
        return *(*this + n);
    }

    /// Structure dereference
    pointer operator->()
    {
        return &apply(std::make_index_sequence<tuple_size>());
    }

    /// Equal to
    bool operator==(const self_type& rhs)
    {
        return (std::get<0>(input_itrs) == std::get<0>(rhs.input_itrs));
    }

    /// Not equal to
    bool operator!=(const self_type& rhs)
    {
        return (std::get<0>(input_itrs) != std::get<0>(rhs.input_itrs));
    }

    /// ostream operator
    friend std::ostream& operator<<(std::ostream& os, const self_type& /* itr */)
    {
        return os;
    }
};
