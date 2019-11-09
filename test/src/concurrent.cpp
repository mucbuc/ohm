#include <string>

#include <tmp/src/test.h>

#include "emitter_fwd.h"
#include <lib/ohm/src/quemitter.h>

using namespace std;

void run_concurent_test();

int main()
{

    run_concurent_test();

    return 0;
}

template <typename T>
struct concurent_test_policy {
    static void pushed_event(T& e)
    {
        if (index == 0) {
            e.emit("hello", ++index);
        }
    }

    static bool locked_mutex(T& e)
    {
        if (index == 1) {
            e.emit("hello", ++index);
        }

        return true;
    }

    static void unlocked_mutex(T& e)
    {
        if (index == 2) {
            e.emit("hello", ++index);
        }
    }

    static unsigned index;
};

template <typename T>
unsigned concurent_test_policy<T>::index = 0;

void run_concurent_test()
{
    typedef om636::control::Quemitter<string, function<void(unsigned)>, concurent_test_policy> q_type;
    q_type e;

    unsigned counter = 0;
    q_type::listener_type a{ e.on("hello", [&counter](unsigned index) {
        ASSERT(counter == index);
        ++counter;
    }) };

    e.emit("hello", 0);

    ASSERT(counter == 4);

    FOOTER;
}
