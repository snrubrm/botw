#include "KingSystem/Graphics/gfxPrePassLightMgr.h"

namespace ksys::gfx {

u32 PrePassLightMgr::getDrawLightNum(s32 index) const {
    return mDrawLightNums[index];
}

}  // namespace ksys::gfx
