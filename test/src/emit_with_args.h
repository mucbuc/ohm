#include <tmp/src/test.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace om636;

template <template <class, class> class T>
void check_emit_with_args()
{
    typedef T<string, function<void(int, int)> > emitter_type;
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
