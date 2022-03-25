#include "bst.h"
#include "list.h"
#include "testing_module.hpp"

int main() {
    auto my_list = test::initial_data<linked_list, int>();
    test::test_run([&]() { my_list.add_at_begin(util::random<int>(0, 10000)); },
                   util::timer<util::precision_us>{});
    return 0;
}