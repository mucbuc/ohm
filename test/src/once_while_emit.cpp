
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

    emitter_type emitter;
    vector<listener_type> listeners;

    unsigned counter(0);

    listeners.push_back(emitter.once("load", [&]() {
        listeners.push_back(emitter.once("on", [&]() {
            ++counter;
        }));

        emitter.interupt("on");
    }));

    emitter.interupt("load");
    emitter.interupt("on");

    ASSERT(counter == 1);

    return 0;
}
