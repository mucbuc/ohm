#ifndef QUEMITTER_IMPL_H_INCLUDEGUARD_QMNEOIUOIUEN3242
#define QUEMITTER_IMPL_H_INCLUDEGUARD_QMNEOIUOIUEN3242

#include <lib/twice-size/src/queue.h>

#include "emitter_impl.h"
#include "interface.h"

namespace om636 {
namespace control {

    template <typename T>
    struct default_policy {
        static void pushed_event(const T&) {}
        static bool locked_mutex(const T&) { return true; }
        static void unlocked_mutex(const T&) {}
    };


    template <class T, template <typename> class P, typename ... U>
    class QuemitterImpl
        : private EmitterImpl<T, U ...>
	, public Quemitter<T, U ...>
    {
        typedef EmitterImpl<T, U ...> base_type;
    
    public:
        using typename base_type::event_type;
        using typename base_type::callback_type;
        using typename base_type::listener_type;
	using base_type::on;
	using base_type::once;
	using base_type::removeListeners;
	using base_type::removeAllListeners;
	using base_type::interupt;

        void emit(event_type, U ...) override;

    private:
        typedef P<QuemitterImpl<T, P, U ...> > fbp;
	typedef std::function<void()> function_type;
        typedef om636::queue<function_type> queue_type;
        typedef std::mutex mutex_type;

        void push_event(function_type);

        queue_type m_queue;
        mutex_type m_mutex;
    };

} //control
} // om636

#include "quemitter_impl.hxx"

#endif
