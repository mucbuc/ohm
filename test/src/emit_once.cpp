#include <tmp/src/test.h>

#include <iostream>
#include <vector>
#include <lib/ohm/src/emitter.h>
#include <lib/ohm/src/quemitter.h>

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

template <class T, class U>
using QueuedEmitter = om636::control::Quemitter<T, U>;

int main()
{
    using namespace std;

    check_emit_once<om636::control::Emitter>();
    check_emit_once<QueuedEmitter>();

    return 0;
}
