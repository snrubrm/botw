#include "Game/AI/Query/queryBranchByGameOver.h"
#include <evfl/Query.h>
#include "Game/UI/uiUtils.h"

namespace uking::query {

BranchByGameOver::BranchByGameOver(const InitArg& arg) : ksys::act::ai::Query(arg) {}

BranchByGameOver::~BranchByGameOver() = default;

// NON_MATCHING: same mapping; the original reads an 8-entry table at 0x7101e7b190 behind an `index < 8`
// check (the compiler folds the explicit range check and the default into a 7-entry table).
int BranchByGameOver::doQuery() {
    const u32 type = ui::sub_7100A968B4();
    if (type >= 8)
        return 0;
    switch (type) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        return 1;
    case 6:
        return 2;
    default:
        return 0;
    }
}

void BranchByGameOver::loadParams(const evfl::QueryArg& arg) {}

void BranchByGameOver::loadParams() {}

}  // namespace uking::query
