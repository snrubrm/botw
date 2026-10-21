#include "Game/Actor/Query/queryBranchByGameOver.h"
#include <evfl/Query.h>
#include "Game/UI/uiUtils.h"

namespace uking::query {

BranchByGameOver::BranchByGameOver(const InitArg& arg) : ksys::act::ai::Query(arg) {}

BranchByGameOver::~BranchByGameOver() = default;

namespace {
const s32 sBranchTable[8] = {1, 1, 1, 1, 1, 1, 2, 0};
}  // namespace

// NON_MATCHING: the table lookup and block layout match; the range check is `cmp #7; b.hi` in ours
// instead of the original's equivalent `cmp #8; b.hs`.
int BranchByGameOver::doQuery() {
    const s32 type = ui::sub_7100A968B4();
    return u32(type) < 8 ? sBranchTable[type] : 0;
}

void BranchByGameOver::loadParams(const evfl::QueryArg& arg) {}

void BranchByGameOver::loadParams() {}

}  // namespace uking::query
