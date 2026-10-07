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

}  // namespace ksys::gfx
