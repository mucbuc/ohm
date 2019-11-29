
#include <iostream>
#include <vector>
#include <tmp/src/test.h>
#include <lib/ohm/src/emitter_impl.h>

using namespace std;
using namespace om636;

template <template <class, class ...> class T>
void check_emit_with_arg()
{
    typedef T<string, int> emitter_type;
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

    e.interupt(event, 99);

    ASSERT(test_passed == 2);

    FOOTER;
}

//template <class T, class U>
//using QueuedEmitter = om636::control::Quemitter<T, U>;

int main()
{
    using namespace std;

    check_emit_with_arg<om636::control::EmitterImpl>();
    //check_emit_with_arg<QueuedEmitter>();

    return 0;
}
