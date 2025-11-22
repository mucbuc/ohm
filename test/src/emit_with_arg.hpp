#include <asserter/src/test.hpp>

#include <ohm/src/emitter_impl.hpp>

void test_emit_with_arg()
{
    unsigned sum(0);
    auto f = [&](unsigned i) { sum += i; };

    om636::control::EmitterImpl<std::string, unsigned> e;
    auto p(e.on("e", f));
    auto q(e.on("e", f));
    e.interupt("e", 7);

    ASSERT(sum == 14);

    FOOTER;
}
