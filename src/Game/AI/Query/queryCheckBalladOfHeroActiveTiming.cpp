#include "Game/AI/Query/queryCheckBalladOfHeroActiveTiming.h"
#include <evfl/Query.h>

// The adjacent original helper takes no arguments and returns query results 0, 1 or 2.
int getBalladOfHeroActiveTiming();

namespace uking::query {

CheckBalladOfHeroActiveTiming::CheckBalladOfHeroActiveTiming(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckBalladOfHeroActiveTiming::~CheckBalladOfHeroActiveTiming() = default;

int CheckBalladOfHeroActiveTiming::doQuery() {
    return getBalladOfHeroActiveTiming();
}

void CheckBalladOfHeroActiveTiming::loadParams(const evfl::QueryArg& arg) {}

void CheckBalladOfHeroActiveTiming::loadParams() {}

}  // namespace uking::query
