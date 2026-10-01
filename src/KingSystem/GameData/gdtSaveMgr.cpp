#include "KingSystem/GameData/gdtSaveMgr.h"
#include <cstring>

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(SaveMgr)

void SaveMgr::auto3() {
    _140 &= ~0x100;
}

bool SaveMgr::someCheck() const {
    return _e40 >= _e00->_28;
}

bool SaveMgr::auto0() {
    if (_38 != 0)
        return false;
    if (!_f80)
        return false;
    std::memset(_f80, 0, _e10);
    return true;
}

}  // namespace ksys
