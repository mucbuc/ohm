#include <tmp/src/test.h>

#include "emitter.h"
#include "emitter_fwd.h"

template <template <class, class> class T>
void test_emitter()
{
    check_dispatch_logic<T>();
    check_agent_life_time<T>();
    check_modify_while_traversal<T>();
    check_emit_while_emit<T>();
    check_emit_with_args<T>();
    check_emit_once<T>();
    check_on<T>();
    check_on_while_emit<T>();
    check_once_while_emit<T>();
    check_once_while_emit_recursive<T>();
}

template<class T, class U>
using QE = om636::control::Quemitter<T, U>;

int main()
{
    using namespace std;

    test_emitter<om636::control::Emitter>();
    cout << "om636::control::Emitter passed" << endl
         << endl;
    
    test_emitter<QE>();
    cout << "om636::control::Quemitter passed" << endl
         << endl;
    return 0;
}
