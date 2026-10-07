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

void SaveMgr::loadFlagValuesFromTriggerParam(gdt::TriggerParam* buffer) {
    _f98 = buffer;
    const s32 count = _e00->getFiles().size();
    for (s32 i = 0; i < count; ++i) {
        auto* file = _e00->getFiles()[i];
        const sead::Delegate1<SaveMgr, res::GameSaveData::Flag&> delegate(
            this, &SaveMgr::invokedLoadFlagValueFromTriggerParam);
        file->forEachFlag(delegate);
    }
    _f98 = nullptr;
}

void SaveMgr::invokedLoadFlagValueFromTriggerParam(res::GameSaveData::Flag& flag) {
    if (!gdt::Manager::instance())
        return;
    auto* buffer = _f98;
    if (!buffer)
        return;
    const u32 hash = flag.kv.name_hash;
    {
        s32 index = 0;
        flag.kv.value = -1;
        flag._8 = 0;
        if (buffer->getBoolFlagAndIdx(&index, hash)) {
            flag.type = gdt::FlagType::Bool;
            flag.kv.value = index;
            return;
        }
    }
    {
        s32 index = 0;
        flag.kv.value = -1;
        flag._8 = 0;
        if (buffer->getS32FlagAndIdx(&index, hash)) {
            flag.type = gdt::FlagType::S32;
            flag.kv.value = index;
            return;
        }
    }
    {
        s32 index = 0;
        flag.kv.value = -1;
        flag._8 = 0;
        if (buffer->getF32FlagAndIdx(&index, hash)) {
            flag.type = gdt::FlagType::F32;
            flag.kv.value = index;
            return;
        }
    }
    {
        s32 index = 0;
        flag.kv.value = -1;
        flag._8 = 0;
        if (buffer->getStrFlagAndIdx(&index, hash)) {
            flag.type = gdt::FlagType::String;
            flag.kv.value = index;
            return;
        }
    }
    {
        s32 index = 0;
        flag.kv.value = -1;
        flag._8 = 0;
        if (buffer->getStr64FlagAndIdx(&index, hash)) {
            flag.type = gdt::FlagType::String64;
            flag.kv.value = index;
            return;
        }
    }
    {
        s32 index = 0;
        flag.kv.value = -1;
        flag._8 = 0;
        if (buffer->getStr256FlagAndIdx(&index, hash)) {
            flag.type = gdt::FlagType::String256;
            flag.kv.value = index;
            return;
        }
    }
    {
        s32 index = 0;
        flag.kv.value = -1;
        flag._8 = 0;
        if (buffer->getVec2fFlagAndIdx(&index, hash)) {
            flag.type = gdt::FlagType::Vector2f;
            flag.kv.value = index;
            return;
        }
    }
    {
        s32 index = 0;
        flag.kv.value = -1;
        flag._8 = 0;
        if (buffer->getVec3fFlagAndIdx(&index, hash)) {
            flag.type = gdt::FlagType::Vector3f;
            flag.kv.value = index;
            return;
        }
    }
    {
        s32 index = 0;
        flag.kv.value = -1;
        flag._8 = 0;
        if (buffer->getVec4fFlagAndIdx(&index, hash)) {
            flag.type = gdt::FlagType::Vector4f;
            flag.kv.value = index;
            return;
        }
    }
    {
        s32 size = 0;
        if (buffer->getBoolArraySizeByHash(&size, hash)) {
            s32 index = 0;
            flag.kv.value = -1;
            flag._8 = 0;
            if (buffer->getBoolFlagAndIdx(&index, hash, 0)) {
                flag.type = gdt::FlagType::BoolArray;
                flag.kv.value = index;
                return;
            }
        }
    }
    {
        s32 size = 0;
        if (buffer->getS32ArraySizeByHash(&size, hash)) {
            s32 index = 0;
            flag.kv.value = -1;
            flag._8 = 0;
            if (buffer->getS32FlagAndIdx(&index, hash, 0)) {
                flag.type = gdt::FlagType::S32Array;
                flag.kv.value = index;
                return;
            }
        }
    }
    {
        s32 size = 0;
        if (buffer->getF32ArraySizeByHash(&size, hash)) {
            s32 index = 0;
            flag.kv.value = -1;
            flag._8 = 0;
            if (buffer->getF32FlagAndIdx(&index, hash, 0)) {
                flag.type = gdt::FlagType::F32Array;
                flag.kv.value = index;
                return;
            }
        }
    }
    {
        s32 size = 0;
        if (buffer->getStrArraySizeByHash(&size, hash)) {
            s32 index = 0;
            flag.kv.value = -1;
            flag._8 = 0;
            if (buffer->getStrFlagAndIdx(&index, hash, 0)) {
                flag.type = gdt::FlagType::StringArray;
                flag.kv.value = index;
                return;
            }
        }
    }
    {
        s32 size = 0;
        if (buffer->getStr64ArraySizeByHash(&size, hash)) {
            s32 index = 0;
            flag.kv.value = -1;
            flag._8 = 0;
            if (buffer->getStr64FlagAndIdx(&index, hash, 0)) {
                flag.type = gdt::FlagType::String64Array;
                flag.kv.value = index;
                return;
            }
        }
    }
    {
        s32 size = 0;
        if (buffer->getStr256ArraySizeByHash(&size, hash)) {
            s32 index = 0;
            flag.kv.value = -1;
            flag._8 = 0;
            if (buffer->getStr256FlagAndIdx(&index, hash, 0)) {
                flag.type = gdt::FlagType::String256Array;
                flag.kv.value = index;
                return;
            }
        }
    }
    {
        s32 size = 0;
        if (buffer->getVec2fArraySizeByHash(&size, hash)) {
            s32 index = 0;
            flag.kv.value = -1;
            flag._8 = 0;
            if (buffer->getVec2fFlagAndIdx(&index, hash, 0)) {
                flag.type = gdt::FlagType::Vector2fArray;
                flag.kv.value = index;
                return;
            }
        }
    }
    {
        s32 size = 0;
        if (buffer->getVec3fArraySizeByHash(&size, hash)) {
            s32 index = 0;
            flag.kv.value = -1;
            flag._8 = 0;
            if (buffer->getVec3fFlagAndIdx(&index, hash, 0)) {
                flag.type = gdt::FlagType::Vector3fArray;
                flag.kv.value = index;
                return;
            }
        }
    }
    {
        s32 size = 0;
        if (buffer->getVec4fArraySizeByHash(&size, hash)) {
            s32 index = 0;
            flag.kv.value = -1;
            flag._8 = 0;
            if (buffer->getVec4fFlagAndIdx(&index, hash, 0)) {
                flag.type = gdt::FlagType::Vector4fArray;
                flag.kv.value = index;
                return;
            }
        }
    }
}

void SaveMgr::auto3() {
    _140 &= ~0x100;
}

bool SaveMgr::someCheck() const {
    return _e40 >= _e00->getFiles().size();
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
    if (idx < 0 || idx >= _e00->mSaveInfo->directory_num)
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
    const u32 count = _e00->getFiles().size();
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

void SaveMgr::x_5(u32 value) {
    if (_103c >= 1)
        *reinterpret_cast<u32*>(&_e08[_103c]) = value;
}

}  // namespace ksys
