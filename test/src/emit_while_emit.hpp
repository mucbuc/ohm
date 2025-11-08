
#include <iostream>
#include <vector>

#include <lib/asserter/src/test.hpp>

#include <lib/ohm/src/emitter_impl.hpp>

using namespace std;

void test_emit_while_emit()
{
    typedef om636::control::EmitterImpl<string> emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    emitter_type e;
    size_t counter(0);

    listener_type p(e.on("e", [&]() {
        p.reset();
        ++counter;
        e.interupt("e");
    }));

    e.interupt("e");

    ASSERT(counter == 1);

    FOOTER;
}
