#include <tmp/src/test.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace om636;

template <template <class, class> class T>
void check_on()
{
    typedef T<string, function<void()> > emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    emitter_type emitter;
    vector<listener_type> listeners;

    unsigned counter(0);

    listeners.push_back(emitter.on("on", [&]() {
        ++counter;
    }));

    emitter.emit("on");
    emitter.emit("on");
    emitter.emit("on");
    emitter.emit("on");

    ASSERT(counter == 4);

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
