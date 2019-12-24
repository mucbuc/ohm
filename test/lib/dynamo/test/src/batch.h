using namespace om636;
using namespace std;

typedef control::BatchImpl<> batch_type;

void check_traverse_with_arg()
{
    typedef control::BatchImpl<int> batch_type;

    unsigned test_passed(0);
    batch_type batch;

    auto p(batch.hook([&](int i) {
        ASSERT(i == 99);
        ++test_passed;
    }));

    batch.invoke(99);

    ASSERT(test_passed == 1);
    FOOTER;
}

void check_traverse_with_args()
{
    typedef control::BatchImpl<int, int> batch_type;

    unsigned test_passed(0);
    batch_type batch;

    auto p(batch.hook([&](int i, int j) {
        ASSERT(i == 99);
        ASSERT(j == 3);
        ++test_passed;
    }));

    batch.invoke(99, 3);

    ASSERT(test_passed == 1);
    FOOTER;
}

void check_traverse_while_traverse()
{
    batch_type batch;
    unsigned passed(0);

    auto p(batch.hook([&]() {
        ++passed;
        batch.invoke();
    }));

    batch.invoke();

    ASSERT(passed == 1);
    FOOTER;
}

void check_traverse()
{
    batch_type batch;
    unsigned passed(0);

    auto temp(batch.hook([&]() {
        ++passed;
    }));

    batch.invoke();
    batch.invoke();

    ASSERT(passed == 2);
    FOOTER;
}
