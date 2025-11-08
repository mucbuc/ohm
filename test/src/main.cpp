#include <functional>
#include <iostream>

#include <lib/asserter/src/test.hpp>
#include <lib/dynamo/src/impl/batch.hpp>

#include "concurrent.hpp"
#include "dispatch_logic.hpp"
#include "emit_once.hpp"
#include "emit_while_emit.hpp"
#include "emit_with_arg.hpp"
#include "emit_with_args.hpp"
#include "modify_while_traversal.hpp"
#include "on.hpp"
#include "on_while_emit.hpp"
#include "once_while_emit.hpp"
#include "once_while_emit_recursive.hpp"


int main(int argc, const char* argv[])
{
    run_concurent_test();
    test_dispatch_logic();
    test_emit_once();
    test_emit_while_emit();
    test_emit_with_arg();
    test_emit_with_args();
    test_modify_while_traversal();
    test_on();
    test_on_while_emit();
    test_once_while_emit();
    test_once_while_emit_recursive();

    return 0;
}
