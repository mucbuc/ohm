
#include <iostream>
#include <vector>

#include <tmp/src/test.h>

#include <lib/ohm/src/emitter_impl.h>

using namespace std;

int main()
{
    om636::control::EmitterImpl<string> e;
    size_t counter(0);

    auto p(e.once("e", [&]() {
        ++counter;
        e.interupt("e");
    }));

    e.interupt("e");

    ASSERT(counter == 1 && "emit while emit" );
    return 0;
}
