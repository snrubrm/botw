#include "KingSystem/GameData/gdtSaveMgr.h"
#include <cstring>
#include <thread/seadDelegateThread.h>
#include "KingSystem/GameData/gdtManager.h"

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

void SaveMgr::auto5() {
    const u32 count = _e00->_28;
    if (_e40 != count) {
        if (x_6(_e40)) {
            ++_e40;
            _e44 = 0;
        }
        if (_e40 != count)
            return;
    }
    _e14 = 0;
    std::memset(_14c, 0xff, sizeof(_14c));
}

bool SaveMgr::enableGdtMgrChangeOnlyMode(s32 x) {
    if (_38 != 0)
        return false;

    _38 = 1;
    _148 = x;

    auto* gdm = gdt::Manager::instance();
    if (!gdm)
        return false;

    gdm->mBitFlags.set(gdt::Manager::BitFlag::_1);
    gdm->mParam.setChangeOnlyOnce(true);
    gdm->mParamBypassPerm.setChangeOnlyOnce(true);
    _30->sendMessage(1, sead::MessageQueue::BlockType::NonBlocking);
    return true;
}

}  // namespace ksys
