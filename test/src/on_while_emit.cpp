
#include <iostream>
#include <vector>

#include <tmp/src/test.h>
#include <lib/ohm/src/quemitter.h>

using namespace std;
using namespace om636;
template <template <class, class> class T>
void check_on_while_emit()
{
    typedef T<string, function<void()> > emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    emitter_type emitter;
    vector<listener_type> listeners;

    unsigned counter(0);

    listeners.push_back(emitter.once("load", [&]() {
        listeners.push_back(emitter.on("on", [&]() {
            ++counter;
        }));

        emitter.emit("on");
    }));

    emitter.emit("load");
    emitter.emit("on");

    ASSERT(counter == 2);

    FOOTER;
}

template <class T, class U>
using QueuedEmitter = om636::control::Quemitter<T, U>;

int main()
{
    using namespace std;

    check_on_while_emit<om636::control::Emitter>();
    check_on_while_emit<QueuedEmitter>();

    return 0;
}
