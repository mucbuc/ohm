
#include <iostream>
#include <vector>

#include <lib/ohm/src/quemitter.h>
#include <tmp/src/test.h>

using namespace std;
using namespace om636;
template <template <class, class> class T>
void check_once_while_emit_recursive()
{
    typedef T<string, function<void()>> emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    emitter_type emitter;
    vector<listener_type> listeners;

    unsigned counter(0);

    listeners.push_back(emitter.once("on", [&]() {
        ++counter;
        emitter.emit("on");
    }));

    emitter.emit("on");

    ASSERT(counter == 1);

    FOOTER;
}

#include <lib/ohm/src/emitter.h>
#include <tmp/src/test.h>

template <class T, class U>
using QueuedEmitter = om636::control::Quemitter<T, U>;

int main()
{
    using namespace std;

    check_once_while_emit_recursive<om636::control::Emitter>();
    check_once_while_emit_recursive<QueuedEmitter>();

    return 0;
}
