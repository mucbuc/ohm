#include <iostream>
#include <tmp/src/test.h>
#include <lib/ohm/src/index.h>

int main()
{
    using namespace om636::control;
    using namespace std;

    auto e = make_emitter<string, int>();
    auto l = e->on("run", [](int v) {
        cout << "run " << v << endl;
    });
    e->interupt("run", 322);
    return 0;
}
