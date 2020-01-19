#pragma once

namespace om636 {
namespace twice_size {

    template <class T>
    struct Circuit {
        typedef T value_type;

        virtual ~Circuit() = default;
        virtual void push(value_type&&) = 0;
        virtual bool check_pop(value_type&) = 0;
        virtual void wait_pop(value_type&) = 0;
    };

} // twice_size
} // om636

