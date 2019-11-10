#include <tmp/src/test.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace om636;

template <template <class, class> class T>
void check_emit_while_emit()
{
    typedef T<string, function<void()> > emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    size_t counter(0);

    emitter_type e;
    string event("e");
    listener_type p(e.once(event, [&]() {
        ++counter;
        e.emit(event);
    }));

    e.emit(event);

    ASSERT(counter == 1);

    FOOTER;
}
