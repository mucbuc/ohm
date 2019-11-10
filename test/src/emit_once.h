#include <tmp/src/test.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace om636;

template <template <class, class> class T>
void check_emit_once()
{
    typedef T<string, function<void(int)> > emitter_type;
    emitter_type e;

    unsigned counter(0);

    auto l(e.once("hello", [&](int) {
        ++counter;
    }));

    auto k(e.once("allo", [&](int) {
        ++counter;
    }));

    e.emit("hello", 0);
    e.emit("hello", 0);
    e.emit("allo", 9);
    e.emit("allo", 9);

    ASSERT(counter == 2);

    FOOTER;
}

