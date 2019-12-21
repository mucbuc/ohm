
#include <iostream>
#include <lib/ohm/src/quemitter.h>
#include <tmp/src/test.h>
#include <vector>

using namespace std;
using namespace om636;

template <template <class, class> class T>
void check_emit_with_args()
{
    typedef T<string, function<void(int, int)>> emitter_type;
    typedef typename emitter_type::listener_type listener_type;
    emitter_type e;

    unsigned test_passed(0);
    string event("e");

    listener_type p(e.once(event, [&](int i, int j) {
        ASSERT(i == 99);
        ASSERT(j == 3);
        ++test_passed;
    }));

    listener_type q(e.on(event, [&](int i, int j) {
        ASSERT(i == 99);
        ASSERT(j == 3);
        ++test_passed;
    }));

    e.emit(event, 99, 3);

    ASSERT(test_passed == 2);

    FOOTER;
}

template <class T, class U>
using QueuedEmitter = om636::control::Quemitter<T, U>;

int main()
{
    using namespace std;

    check_emit_with_args<om636::control::Emitter>();
    check_emit_with_args<QueuedEmitter>();

    return 0;
}
