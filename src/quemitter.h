#ifndef QUEMITTER_H_INCLUDEGUARD_QMNEOIUOIUEN3242
#define QUEMITTER_H_INCLUDEGUARD_QMNEOIUOIUEN3242

#include <lib/ohm/src/emitter.h>
#include <lib/twice-size/src/queue.h>

namespace om636 {
namespace control {

    template <typename T, typename ... U>
    class Quemitter
        : public Emitter<T, U> {

        typedef Emitter<T, U> base_type;
    
    public:
        using typename base_type::event_type;
        using typename base_type::callback_type;
        using typename base_type::listener_type;

        virtual ~Quemitter() = default;
        virtual void emit(event_type, U ...) = 0;
    };
} //control
} // om636

#include "quemitter.hxx"

#endif
