#include "Game/gameWolfLinkMgr.h"

namespace uking {

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
