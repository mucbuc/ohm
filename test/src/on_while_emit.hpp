
#include <iostream>
#include <vector>

#include <lib/asserter/src/test.hpp>

#include <lib/ohm/src/emitter_impl.hpp>

void test_on_while_emit()
{
    using namespace std;
    using namespace om636;
    using namespace control;
    typedef EmitterImpl<string> emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    emitter_type emitter;
    vector<listener_type> listeners;

    unsigned counter(0);

    listeners.push_back(emitter.on("load", [&]() {
        listeners.push_back(emitter.on("on", [&]() {
            ++counter;
        }));

        emitter.interupt("on");
    }));

    emitter.interupt("load");
    emitter.interupt("on");

    ASSERT(counter == 2);

    FOOTER;
}
