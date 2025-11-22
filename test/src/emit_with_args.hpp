#include <asserter/src/test.hpp>

#include <ohm/src/emitter_impl.hpp>

void test_emit_with_args()
{
    unsigned sum(0);
    auto f = [&](unsigned i, unsigned j) { sum += i * j; };

    om636::control::EmitterImpl<std::string, unsigned, unsigned> e;
    auto p(e.on("e", f));
    auto q(e.on("e", f));
    e.interupt("e", 7, 3);

    ASSERT(sum == 42);

    FOOTER;
}
