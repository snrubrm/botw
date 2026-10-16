#include "KingSystem/Graphics/gfxForestRenderer.h"
#include <gsys/gsysModelUnit.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/System/StageInfo.h"

namespace ksys::gfx {

// NON_MATCHING: only the schedule of the two GOT loads (the original loads both addresses first, then both bytes).
// `sIsFinalTrial` is the byte at 0x2606855 (StageInfo statics are consecutive from 0x2606848).
bool ForestRenderer::x_9() {
    if (_54 >= 5 && _220 != 0) {
        const bool stage = StageInfo::sIsNotDebugStageAndNotDungeon | StageInfo::sIsFinalTrial;
        return _54 != 6 && stage;
    }
    return false;
}

// NON_MATCHING: the original copies this to x8 and sets the false result in w0 before the state 6 test.
bool ForestRenderer::stopped() {
    if (_54 >= 5 && _220 != 0) {
        const bool stage = StageInfo::sIsNotDebugStageAndNotDungeon | StageInfo::sIsFinalTrial;
        if (stage)
            return _54 == 6 && (_50 & 1) != 0 && _60 > 3;
    }
    return true;
}

void ForestRenderer::sub_7100F03B68() {
    for (auto& entry : mEntries) {
        for (auto& item : entry.mItems)
            item._c.set(2);
    }
}

void ForestRenderer::x_1() {
    for (auto& entry : mEntries) {
        for (auto& record : entry.mRecords)
            record._4.reset(4);
        for (auto& item : entry.mItems)
            item._c.set(2);
    }
}

void ForestRenderer::sub_710F06904(map::PlacementMgr* mgr, bool a) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& entry : mUnitEntries) {
        if (!entry.mModelUnit)
            continue;
        auto* draw_array = entry.mModelUnit->getDrawArray();
        const u32 num = draw_array->_18;
        for (u32 i = 0; i < num; ++i)
            draw_array->flushUBO(i);
    }
}

s32 ForestRenderer::x_7(const sead::Vector3f& vec) {
    if (_54 >= 5) {
        u32 index = 0;
        for (auto& entry : mEntries) {
            const s32 item = entry.sub_7100F0663C(vec);
            if (item != -1)
                return item | index;
            index += 0x10000;
        }
    }
    return -1;
}

}  // namespace ksys::gfx
