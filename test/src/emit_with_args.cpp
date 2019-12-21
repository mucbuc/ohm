#include <tmp/src/test.h>

#include <lib/ohm/src/emitter_impl.h>

int main()
{
    unsigned sum(0);
    auto f = [&](unsigned i, unsigned j) { sum += i * j; };

    om636::control::EmitterImpl<std::string, unsigned, unsigned> e;
    auto p(e.once("e", f));
    auto q(e.on("e", f));
    e.interupt("e", 7, 3);

    ASSERT(sum == 42 && "emit with args");

    return 0;
}
