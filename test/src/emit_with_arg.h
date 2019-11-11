#include <tmp/src/test.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace om636;

template <template <class, class> class T>
void check_emit_with_arg()
{
    typedef T<string, function<void(int)> > emitter_type;
    typedef typename emitter_type::listener_type listener_type;
    emitter_type e;

    unsigned test_passed(0);
    string event("e");

    listener_type p(e.once(event, [&](int i) {
        ASSERT(i == 99);
        ++test_passed;
    }));

    listener_type q(e.on(event, [&](int i) {
        ASSERT(i == 99);
        ++test_passed;
    }));

    e.emit(event, 99);

    ASSERT(test_passed == 2);

    FOOTER;
}

#include <tmp/src/test.h>
#include <lib/ohm/src/emitter.h>

template <class T, class U>
using QueuedEmitter = om636::control::Quemitter<T, U>;

int main()
{
    using namespace std;

    test_emitter<om636::control::Emitter>();
    test_emitter<QueuedEmitter>();

    return 0;
}
