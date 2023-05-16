#ifndef _TRACYSTL_ITERATOR_H_
#define _TRACYSTL_ITERATOR_H_
#include <cstddef>

namespace tracystl {

    // Iterator categories
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<class Category, class T, class Distance = ptrdiff_t,
             class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef Category    iterator_category;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
    };

    template<class Iterator>
    struct iterator_traits {
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
    };

    // Specialization for pointers
    template<class T>
    struct iterator_traits<T*> {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef std::size_t                 difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };

    template<class T>
    struct iterator_traits<const T*> {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef std::size_t                 difference_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
    };
}

#endif
