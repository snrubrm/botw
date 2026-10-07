#include "KingSystem/World/worldWindMgr.h"

namespace ksys::world {

// NON_MATCHING: the Vector3 assignment copies components separately instead of the original word/pair copy.
void WindMgr::sub_71010EEBE4(sead::Vector3f* out, const sead::Vector3f* position) {
    if (!(_28 & 8)) {
        sub_71010EEA98(out, position);
        return;
    }
    *out = _34;
}

nn::gfx::ResTextureData* WindMgr::sub_71010EEEE8() {
    if (!(_28 & 0x40))
        return &_20->_1b8;
    return &_98;
}

f32 WindMgr::sub_71010EEF48() const {
    return _20->_8;
}

}  // namespace ksys::world
