#include "emitter_fwd.h"
#include "emitter.h"

int main()
{
    check_dispatch_logic();
    check_agent_life_time();
    check_modify_while_traversal();
    check_emit_while_emit();
    check_emit_with_args();
    check_emit_once();
    check_on();
    check_on_while_emit();
    check_once_while_emit();
    return 0;
}
