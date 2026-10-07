#include "KingSystem/GameData/gdtSaveMgr.h"
#include <cstring>
#include <filedevice/seadFileDeviceMgr.h>
#include <thread/seadDelegateThread.h>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys {

static sead::FixedSafeString<16> sUnk_7102601F08("../SaveData/");
static sead::FixedSafeString<16> sUnk_7102601F30("GameData/");
static sead::FixedSafeString<16> sUnk_7102601F58("bgsvdata");
static sead::FixedSafeString<16> sUnk_7102601F80("sarc");
static sead::FixedSafeString<32> sUnk_7102601FA8("セーブテスト");
static sead::FixedSafeString<32> sUnk_7102601FE0("ロードテスト");
static sead::FixedSafeString<16> sUnk_7102602018("_finish_copy");

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

void SaveMgr::unloadResources() {
    for (s32 i = 0; i < mSaveDataHandles.size(); ++i)
        mSaveDataHandles[i].requestUnload();
    mSaveDataArcHandle.requestUnload();
}

void SaveMgr::registerGameSavedataFactoryAndLoad() {
    auto* factory = new (mHeap, 8) res::EntryFactory<res::GameSaveData>(1.0f, 0x300000);
    res::registerEntryFactory(factory, sUnk_7102601F58);
    sead::FixedSafeString<1024> path;
    const char* prefix = sUnk_7102601F30.cstr();
    const char* extension = sUnk_7102601F80.cstr();
    path.format("%s%s.%s", prefix, "savedataformat", extension);
    loadSavedataformat(path, mHeap);
    std::memset(_14c, 0xff, sizeof(_14c));
    unloadResources();
    mHeap->adjust();
}

u32 SaveMgr::sub_7100E0F578() const {
    const s32 revision = _e00->mSaveInfo->revision;
    if (revision < 9443)
        return 0;
    if (revision < 9455)
        return 1;
    if (revision < 16122)
        return 2;
    return 3;
}

// NON_MATCHING: guard checks and return branches are scheduled differently.
bool SaveMgr::saveAlbumPicture(const sead::SafeString& path, void* data, s32 size,
                               u32 capacity) {
    if (size == 0 || _38 != 0 || size > s32(capacity) || capacity >= _e10)
        return false;
    _38 = 2;
    _e2c = true;
    std::memset(_e30, 0, s32(capacity));
    std::memcpy(_e30, data, size);
    _e28 = capacity;
    _1d0.copy(path);
    _30->sendMessage(3, sead::MessageQueue::BlockType::NonBlocking);
    return true;
}

// NON_MATCHING: guard checks and return branches are scheduled differently.
bool SaveMgr::sub_7100E044A8(const sead::SafeString& path, void* data, u32 size,
                               u32 capacity) {
    if (size == 0 || _38 != 0 || s32(size) > s32(capacity) || capacity >= _e10)
        return false;
    _38 = 2;
    _e2c = true;
    std::memset(_e30, 0, s32(capacity));
    std::memcpy(_e30, data, s32(size));
    _e28 = capacity;
    _1d0.copy(path);
    _30->sendMessage(3, sead::MessageQueue::BlockType::NonBlocking);
    return true;
}

// NON_MATCHING: guard checks and return branches are scheduled differently.
bool SaveMgr::sub_7100E0461C(const sead::SafeString& path, void* data, s32 size,
                               u32 capacity) {
    _f8 = false;
    if (size == 0 || _38 != 0 || size > s32(capacity) || capacity >= _e10) {
        _f8 = true;
        return false;
    }
    _38 = 2;
    _e2c = true;
    std::memset(_e30, 0, s32(capacity));
    std::memcpy(_e30, data, size);
    _e28 = capacity;
    _1d0.copy(path);
    _30->sendMessage(3, sead::MessageQueue::BlockType::NonBlocking);
    return true;
}

// NON_MATCHING: the library string comparison expands the byte loop.
bool SaveMgr::sub_7100E041D0(s32 index, const sead::SafeString& file_name) {
    if (_38 != 0)
        return false;

    const s32 count = _e00->getFiles().size();
    for (s32 i = 0; i < count; ++i) {
        if (_e00->getFiles().unsafeAt(i)->info->name != file_name)
            continue;

        _14c[0] = i;
        if (_38 != 0)
            return false;
        _38 = 2;
        if (index < 0 || index >= _e00->mSaveInfo->directory_num)
            index = 0;
        _148 = index;
        auto* manager = gdt::Manager::instance();
        if (!manager)
            return false;
        _30->sendMessage(2, sead::MessageQueue::BlockType::NonBlocking);
        return true;
    }
    return false;
}

// NON_MATCHING: the library string comparison expands the byte loop.
bool SaveMgr::sub_7100E04810(s32 index, const sead::SafeString& file_name) {
    if (_38 != 0)
        return false;

    const s32 count = _e00->getFiles().size();
    for (s32 i = 0; i < count; ++i) {
        if (_e00->getFiles().unsafeAt(i)->info->name != file_name)
            continue;

        _14c[0] = i;
        if (_38 != 0)
            return false;
        _38 = 1;
        _148 = index;
        auto* manager = gdt::Manager::instance();
        if (!manager)
            return false;
        manager->mBitFlags.set(gdt::Manager::BitFlag::_1);
        manager->mParam.setChangeOnlyOnce(true);
        manager->mParamBypassPerm.setChangeOnlyOnce(true);
        _30->sendMessage(1, sead::MessageQueue::BlockType::NonBlocking);
        return true;
    }
    return false;
}

// NON_MATCHING: size and buffer argument copies and stores are scheduled differently.
bool SaveMgr::x(const sead::SafeString& path, void* buffer, u32 size) {
    if (_38 != 0)
        return false;
    const char* mount = _80.cstr();
    sead::FormatFixedSafeString<256> full_path("%s://%s", mount, path.cstr());
    _e60.copy(full_path);
    _e58 = size;
    _e50 = buffer;
    _e4c = true;
    _f78 = 4;
    _38 = 1;
    _30->sendMessage(1, sead::MessageQueue::BlockType::NonBlocking);
    return true;
}

// NON_MATCHING: byte-order flag operations fold the original temporary flag-index storage.
bool SaveMgr::x_1(s32 index, const sead::SafeString& path, bool a, bool byte_swap) {
    _142 = _140;
    _140 = (_140 & 0x100) | (a ? 0x204 : 0x200);
    _105a = !a;
    if (byte_swap)
        _1058 |= 2;
    else
        _1058 &= ~2;
    _10b0.copy(path);
    if (_38 != 0)
        return false;
    _38 = 1;
    _148 = index;
    auto* manager = gdt::Manager::instance();
    if (!manager)
        return false;
    manager->mBitFlags.set(gdt::Manager::BitFlag::_1);
    manager->mParam.setChangeOnlyOnce(true);
    manager->mParamBypassPerm.setChangeOnlyOnce(true);
    _30->sendMessage(1, sead::MessageQueue::BlockType::NonBlocking);
    return true;
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

void SaveMgr::x_7() {
    _f98 = gdt::Manager::instance()->mFlagBuffer;
    x_8(_f98->mCopiedBoolFlags);
    x_11(_f98->mCopiedS32Flags);
    x_12(_f98->mCopiedF32Flags);
    x_13(_f98->mCopiedStringFlags);
    x_14(_f98->mCopiedString64Flags);
    x_15(_f98->mCopiedString256Flags);
    x_16(_f98->mCopiedVector2fFlags);
    x_17(_f98->mCopiedVector3fFlags);
    sub_7100E07E3C(_f98->mCopiedVector4fFlags);
}

// NON_MATCHING: redundant bounds checks and loop index scheduling differ.
void SaveMgr::someCheck_0(gdt::FlagT<bool>* flag) {
    if (!flag)
        return;
    const s32 count = _e00->getFiles().size();
    for (s32 i = 0; i < count; ++i) {
        const s32 flag_index = _e00->getFiles()[i]->findFlagIndex(flag->getHash());
        if (flag_index < 0)
            continue;
        const u32 offset = _e00->getFiles()[i]->flags[flag_index]._8;
        if (offset + 4 < _e10) {
            const u32 hash = flag->getHash();
            std::memcpy(_e08 + offset, &hash, sizeof(hash));
            if (offset + 8 < _e10) {
                const u32 value = flag->getValue();
                std::memcpy(_e08 + (offset + 4), &value, sizeof(value));
            }
        }
        return;
    }
}

// NON_MATCHING: redundant bounds checks and loop index scheduling differ.
void SaveMgr::someStuff(gdt::FlagT<s32>* flag) {
    if (!flag)
        return;
    for (s32 i = _e00->getFiles().size(); i > 0;) {
        --i;
        const s32 flag_index = _e00->getFiles()[i]->findFlagIndex(flag->getHash());
        if (flag_index < 0)
            continue;
        const u32 offset = _e00->getFiles()[i]->flags[flag_index]._8;
        if (offset + 4 < _e10) {
            const u32 hash = flag->getHash();
            std::memcpy(_e08 + offset, &hash, sizeof(hash));
            if (offset + 8 < _e10) {
                const s32 value = flag->getValueRef();
                std::memcpy(_e08 + (offset + 4), &value, sizeof(value));
            }
        }
        return;
    }
}

void SaveMgr::x_5(u32 value) {
    if (_103c >= 1)
        *reinterpret_cast<u32*>(&_e08[_103c]) = value;
}

}  // namespace ksys
