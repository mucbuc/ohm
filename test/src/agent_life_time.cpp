#include <iostream>
#include <vector>

#include <tmp/src/test.h>
#include <lib/ohm/src/emitter_impl.h>

using namespace std;
using namespace om636;

int main()
{
    struct dummy_callback {
        dummy_callback()
        {
            ++instance_counter();
        }

        dummy_callback(const dummy_callback&)
            : dummy_callback()
        {
        }

        ~dummy_callback()
        {
            --instance_counter();
        }

        dummy_callback& operator=(const dummy_callback&) = default;

        static size_t& instance_counter()
        {
            static size_t counter(0);
            return counter;
        }
    };

    static string event("init");
    typedef om636::control::EmitterImpl<string, dummy_callback> emitter_type;
    typedef typename emitter_type::listener_type listener_type;
    emitter_type emitter;

    if (1) {
        auto listener(emitter.on(event, [](){}));
        emitter.removeListeners(event);

        // this reference is owned by the listener
        ASSERT(dummy_callback::instance_counter() == 1);
    }
    ASSERT(!dummy_callback::instance_counter());

    if (1) {
        auto listener(emitter.on(event, dummy_callback()));
        emitter.removeAllListeners();

        // this reference is owned by the listener
        ASSERT(dummy_callback::instance_counter() == 1);
    }
    ASSERT(!dummy_callback::instance_counter());

    if (1) {
        listener_type listener;
        if (1) {
            auto temp(emitter.on(event, dummy_callback()));
            ASSERT(dummy_callback::instance_counter() == 1);

            listener = temp;

            ASSERT(dummy_callback::instance_counter() == 1);
        }

        // this reference is owned by the emitter
        ASSERT(dummy_callback::instance_counter() == 1);
    }

    emitter.removeListeners(event);
    ASSERT(!dummy_callback::instance_counter());

    FOOTER;
}

template <class T, class U>
using QueuedEmitter = om636::control::Quemitter<T, U>;

int main()
{
    using namespace std;

    check_agent_life_time<om636::control::EmitterImpl>();
//    check_agent_life_time<QueuedEmitter>();

    return 0;
}
