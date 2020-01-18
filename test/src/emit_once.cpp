#include <tmp/src/test.h>

#include <iostream>
#include <lib/ohm/src/emitter_impl.h>

using namespace std;
using namespace om636;
using namespace control;

int main()
{
    typedef EmitterImpl<string, int> emitter_type;
    emitter_type e;

    unsigned counter(0);

    auto l(e.once("hello", [&](int) {
        ++counter;
    }));

    auto k(e.once("allo", [&](int) {
        ++counter;
    }));

    e.interupt("hello", 0);
    e.interupt("hello", 0);
    e.interupt("allo", 9);
    e.interupt("allo", 9);

    ASSERT(counter == 2 && "emit once");

    return 0;
}
