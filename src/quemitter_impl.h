#ifndef QUEMITTER_IMPL_H_INCLUDEGUARD_QMNEOIUOIUEN3242
#define QUEMITTER_IMPL_H_INCLUDEGUARD_QMNEOIUOIUEN3242

#include <lib/twice-size/src/queue.h>

#include "emitter_impl.h"

namespace om636 {
namespace control {

    template <class T, template <typename> class P, typename ... U>
    class QuemitterImpl
        : public EmitterImpl<T, ... U> {

        typedef EmitterImpl<T, ... U> base_type;
    
    public:
        using typename base_type::event_type;
        using typename base_type::callback_type;
        using typename base_type::listener_type;

        virtual ~QuemitterImpl() = default;
        virtual void emit(event_type, U ...) = 0;
    };
} //control
} // om636

#include "quemitter_impl.hxx"

#endif
