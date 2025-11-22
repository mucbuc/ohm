#include <iostream>
#include <vector>

#include <asserter/src/test.hpp>

#include <ohm/src/emitter_impl.hpp>

void test_dispatch_logic()
{
    using namespace std;
    using namespace om636;
    using namespace control;

    typedef EmitterImpl<string> emitter_type;
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
    emitter.on(event, tester::trigger_trap);
    emitter.interupt(event);
    ASSERT(trap == 0);

    // check on
    listeners.push_back(emitter.on(event, tester::trigger_trap));
    emitter.interupt(event);
    ASSERT(trap == 1);
    emitter.interupt(event);
    ASSERT(trap == 2);

    // check duplicate
    listeners.push_back(emitter.on(event, tester::trigger_trap));
    emitter.interupt(event);
    ASSERT(trap == 4);
    
    FOOTER;
}
