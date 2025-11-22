
#include <asserter/src/test.hpp>

#include <ohm/src/emitter_impl.hpp>

using namespace std;
using namespace om636;
using namespace control;

void test_on()
{
    using namespace std;

    EmitterImpl<string> emitter;

    unsigned counter(0);
    auto listener{ emitter.on("on", [&]() {
        ++counter;
    }) };

    emitter.interupt("on");
    emitter.interupt("on");
    emitter.interupt("on");
    emitter.interupt("on");

    ASSERT(counter == 4);
    FOOTER;
}
