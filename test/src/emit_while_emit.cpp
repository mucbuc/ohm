
#include <iostream>
#include <vector>

#include <tmp/src/test.h>

#include <lib/ohm/src/emitter_impl.h>

using namespace std;

int main()
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

    ASSERT(counter == 1 && "emit while emit" );
    return 0;
}
