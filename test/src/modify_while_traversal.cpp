
#include <iostream>
#include <vector>

#include <lib/ohm/src/quemitter.h>
#include <tmp/src/test.h>

using namespace std;
using namespace om636;
/////////////////////////////////////////////////////////////////
template <template <class, class> class T>
void check_modify_while_traversal()
{
    typedef T<string, function<void()>> emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    static emitter_type emitter;
    static unsigned trap(0);
    static const string event("load");
    struct tester {
        static void trigger_trap()
        {
            ++trap;
        }

        static void remove()
        {
            ++trap;
            emitter.removeListeners(event);
        }

        static void removeAll()
        {
            ++trap;
            emitter.removeAllListeners();
        }
    };

    vector<listener_type> listeners;

    // test remove while traverse
    listeners.push_back(emitter.on(event, tester::remove));
    listeners.push_back(emitter.on(event, tester::remove));
    listeners.push_back(emitter.once(event, tester::remove));
    emitter.emit(event);
    ASSERT(trap == 1);

    // test removeAll while traverse
    listeners.push_back(emitter.on(event, tester::removeAll));
    listeners.push_back(emitter.on(event, tester::removeAll));
    listeners.push_back(emitter.once(event, tester::removeAll));
    emitter.emit(event);
    ASSERT(trap == 2);

    // test insert while traverse
    listeners.push_back(emitter.once(event, [&]() {
        listeners.push_back(emitter.on(event, tester::trigger_trap));
        listeners.push_back(emitter.once(event, tester::trigger_trap));
    }));
    emitter.emit(event);
    ASSERT(trap == 2);

    emitter.emit(event);
    ASSERT(trap == 4);

    emitter.emit(event);
    ASSERT(trap == 5);

    FOOTER;
}

template <class T, class U>
using QueuedEmitter = om636::control::Quemitter<T, U>;

int main()
{
    using namespace std;

    check_modify_while_traversal<om636::control::Emitter>();
    check_modify_while_traversal<QueuedEmitter>();

    return 0;
}
