#include "KingSystem/GameData/gdtSaveMgr.h"
#include <cstring>
#include <filedevice/seadFileDeviceMgr.h>
#include <thread/seadDelegateThread.h>
#include "KingSystem/GameData/gdtManager.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(SaveMgr)

bool SaveMgr::sub_7100E0402C(const sead::SafeString& path) {
    auto* device_mgr = sead::FileDeviceMgr::instance();
    if (!device_mgr)
        return false;

    sead::FileDevice* device;
    {
        const sead::SafeString mount(_80.cstr());
        device = device_mgr->findDevice(mount);
    }
    if (!device)
        return false;

    bool exists = false;
    device->tryIsExistFile(&exists, path);
    return exists;
}

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

bool SaveMgr::auto6(s32 idx) {
    if (_38 != 0)
        return false;

    _38 = 2;
    if (idx < 0 || idx >= _e00->_20->_4)
        idx = 0;
    _148 = idx;

    if (!gdt::Manager::instance())
        return false;

    _30->sendMessage(2, sead::MessageQueue::BlockType::NonBlocking);
    return true;
}

bool SaveMgr::x_0(s32 idx) {
    _f8 = false;
    if (!auto6(idx)) {
        _f8 = true;
        return false;
    }
    return true;
}

void SaveMgr::auto4() {
    std::memset(_e08, 0, _e10);
    _e14 = 0;
    _e18 = 0;
    _103c = -1;
    _11c8.clear();
    _e40 = 0;
    _e44 = 0;
    _e48 = 0;
    _3c = 0;
    _f98 = gdt::Manager::instance()->mFlagBuffer;
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
