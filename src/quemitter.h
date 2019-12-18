#ifndef QUEMITTER_H_INCLUDEGUARD_QMNEOIUOIUEN3242
#define QUEMITTER_H_INCLUDEGUARD_QMNEOIUOIUEN3242

#include <lib/ohm/src/emitter.h>
#include <lib/twice-size/src/queue.h>

namespace om636 {
namespace control {

    template <typename T>
    struct default_policy {
        static void pushed_event(const T&) {}
        static bool locked_mutex(const T&) { return true; }
        static void unlocked_mutex(const T&) {}
    };

    template <typename T, typename U, template <typename> class P = default_policy>
    class Quemitter
        : public Emitter<T, U> {

        typedef P<Quemitter<T, U, P>> fbp;

    public:
        typedef Emitter<T, U> base_type;
        using typename base_type::callback_type;
        using typename base_type::event_type;
        using typename base_type::listener_type;

        Quemitter() = default;
        virtual ~Quemitter() = default;
        Quemitter(const Quemitter&) = delete;
        Quemitter& operator=(const Quemitter&) = delete;

        template <class... V>
        void emit(event_type, V...);

    private:
        typedef std::function<void()> function_type;
        typedef om636::queue<function_type> queue_type;
        typedef std::mutex mutex_type;

        void push_event(function_type);

        queue_type m_queue;
        mutex_type m_mutex;
    };
} //control
} // om636

#include "quemitter.hxx"

#endif
