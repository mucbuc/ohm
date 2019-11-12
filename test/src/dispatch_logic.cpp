#include <iostream>
#include <vector>
#include <tmp/src/test.h>
#include <lib/ohm/src/quemitter.h>

using namespace std;
using namespace om636;
/////////////////////////////////////////////////////////////////
template <template <class, class> class T>
void check_dispatch_logic()
{
    typedef T<string, function<void()> > emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    static unsigned trap(0);
    struct tester {
        static void trigger_trap()
        {
            ++trap;
        }
    };

    emitter_type emitter;
    vector<listener_type> listeners;
    string event("calculate answer to L.U. and E.");

    trap = 0;

    // check dead agent
    emitter.once(event, tester::trigger_trap);
    emitter.emit(event);
    ASSERT(trap == 0);

    // check once
    listeners.push_back(emitter.once(event, tester::trigger_trap));
    emitter.emit(event);
    ASSERT(trap == 1);
    emitter.emit(event);
    ASSERT(trap == 1);

    // check on
    listeners.push_back(emitter.on(event, tester::trigger_trap));
    emitter.emit(event);
    ASSERT(trap == 2);
    emitter.emit(event);
    ASSERT(trap == 3);

    // check duplicate
    listeners.push_back(emitter.on(event, tester::trigger_trap));
    emitter.emit(event);
    ASSERT(trap == 5);

    FOOTER;
}

template <class T, class U>
using QueuedEmitter = om636::control::Quemitter<T, U>;

int main()
{
    using namespace std;

    check_dispatch_logic<om636::control::Emitter>();
    check_dispatch_logic<QueuedEmitter>();

    return 0;
}
