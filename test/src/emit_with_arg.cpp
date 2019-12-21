#include <tmp/src/test.h>

#include <lib/ohm/src/emitter_impl.h>

int main()
{
    unsigned sum(0);
    auto f = [&](unsigned i) { sum += i; };

    om636::control::EmitterImpl<std::string, unsigned> e;
    auto p(e.once("e", f));
    auto q(e.on("e", f));
    e.interupt("e", 7);

    ASSERT(sum == 14 && "emit with arg");

    return 0;
}
