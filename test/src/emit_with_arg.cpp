
#include <tmp/src/test.h>
#include <lib/ohm/src/emitter_impl.h>
#include <lib/ohm/src/quemitter_impl.h>

using namespace std;
using namespace om636;

template <template <class, class ...> class T>
void check_emit_with_arg()
{
    T<string, int> e;

    unsigned counter(0);
    string event("e");

    auto p(e.once(event, [&](int i) {
        ASSERT(i == 99);
        ++counter;
    }));

    auto q(e.on(event, [&](int i) {
        ASSERT(i == 99);
        ++counter;
    }));

    e.interupt(event, 99);

    ASSERT(counter == 2);

    FOOTER;
}

template <class T, class ... U>
using QueuedEmitter = om636::control::QuemitterImpl<T, om636::control::default_policy, U ...>;

int main()
{
    using namespace std;

    check_emit_with_arg<om636::control::EmitterImpl>();
    check_emit_with_arg<QueuedEmitter>();

    return 0;
}
