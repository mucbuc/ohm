#include <tmp/src/test.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace om636;
template <template <class, class> class T>
void check_once_while_emit()
{
    typedef T<string, function<void()> > emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    emitter_type emitter;
    vector<listener_type> listeners;

    unsigned counter(0);

    listeners.push_back(emitter.once("load", [&]() {
        listeners.push_back(emitter.once("on", [&]() {
            ++counter;
        }));

        emitter.emit("on");
    }));

    emitter.emit("load");
    emitter.emit("on");

    ASSERT(counter == 1);

    FOOTER;
}
