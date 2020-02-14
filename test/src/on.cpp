
#include <tmp/src/test.h>

#include <lib/ohm/src/emitter_impl.h>

using namespace std;
using namespace om636;
using namespace control;

int main()
{
    using namespace std;

    EmitterImpl<string> emitter;

    unsigned counter(0);
    auto listener { emitter.on("on", [&]() {
        ++counter;
    }) };

    emitter.interupt("on");
    emitter.interupt("on");
    emitter.interupt("on");
    emitter.interupt("on");

    ASSERT(counter == 4 && "on");
    return 0;
}
