
#include <iostream>
#include <vector>

#include <tmp/src/test.h>

#include <lib/ohm/src/emitter_impl.h>

int main()
{
 
    using namespace std;
    using namespace om636;
    using namespace control;

    typedef EmitterImpl<string> emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    static emitter_type emitter;
    static unsigned trap(0);
    static const string event("load");
    struct tester {
        static void trigger_trap()
        {
            ++trap;
        }
    };

    vector<listener_type> listeners;

    // test insert while traverse
    listeners.push_back(emitter.on(event, [&]() {
        listeners.push_back(emitter.on(event, tester::trigger_trap));
    }));
    emitter.interupt(event);
    listeners.front().reset();
    ASSERT(trap == 0)(trap);

    emitter.interupt(event);
    ASSERT(trap == 1);

    emitter.interupt(event);
    ASSERT(trap == 2 && "modify_while_traversau")(trap);

    return 0;
}
