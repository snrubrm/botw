#include "Game/gameWolfLinkMgr.h"
#include <limits>
#include "Game/Actor/actWolfLink.h"

namespace uking {

bool WolfLinkMgr::sub_7100682CB4() const {
    return _60 == 2 && _80 && (_80->_1698 & 0x4000);
}

sead::Vector3f WolfLinkMgr::sub_71006831BC() const {
    if (_28.hasProc() && _80)
        return _80->getMtx().getTranslation();
    const f32 nan = std::numeric_limits<f32>::quiet_NaN();
    return {nan, nan, nan};
}

bool WolfLinkMgr::sub_710068367C() {
    if (_60 == 1)
        return false;
    return _28.hasProc();
}

bool WolfLinkMgr::sub_7100683698() {
    if (_60 == 1)
        return false;
    return !_28.hasProc();
}

}  // namespace uking
