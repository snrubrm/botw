#include "KingSystem/Graphics/gfxForestRenderer.h"
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

}  // namespace ksys::gfx
