#include <tmp/src/test.h>

#include "emitter.h"
#include "emitter_fwd.h"

template <class T, class U>
using QueuedEmitter = om636::control::Quemitter<T, U>;

int main()
{
    using namespace std;

    test_emitter<QueuedEmitter>();

    return 0;
}
