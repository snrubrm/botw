#include "KingSystem/GameData/gdtSaveMgr.h"
#include <cstring>
#include <codec/seadHashCRC32.h>
#include <prim/seadEndian.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <filedevice/nin/seadNinSaveFileDeviceNin.h>
#include <resource/seadResource.h>
#include <thread/seadDelegateThread.h>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Resource/resResourceArchive.h"
#include "KingSystem/System/UIGlue.h"

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

// NON_MATCHING: The path strings and load request have different stack slots.
bool SaveMgr::loadSaveFile(u32 idx) {
    if (!_e00->mSaveInfo)
        return false;
    const s32 directory_count = _e00->mSaveInfo->directory_num;
    auto* file = _e00->mFiles[idx];
    sead::FormatFixedSafeString<256> name("%s", file->info->name.cstr());
    if (directory_count >= 2 && !file->info->is_common_at_same_account)
        name.format("%d/%s", _148, file->info->name.cstr());
    sead::FormatFixedSafeString<256> path("%s/%s", _10b0.cstr(), name.cstr());
    res::LoadRequest request;
    request.mRequester = "ukingSaveMgr";
    request.mPath = path;
    request._26 = false;
    request.mPackHandle = nullptr;
    request._22 = true;
    return mLoadHandle.load(path, &request, nullptr) != nullptr;
}

// NON_MATCHING: enum flag temporaries use different stack slots and byte-order branches differ.
void SaveMgr::x_3(const res::GameSaveData::File* file) {
    _f90 = 0;
    u32 revision;
    std::memcpy(&revision, _e08 + _e14, sizeof(revision));
    if (_1058.isOnBit(Flag1058(Flag1058::_2))) {
        if (revision <= 0xffff || (revision & 0xffff) == 0)
            _1058.changeBit(Flag1058(Flag1058::_1), revision > 0xffff);
    } else if (_1058.isOnBit(Flag1058(Flag1058::_0))) {
        _1058.setBit(Flag1058(Flag1058::_1));
    }
    if (_1058.isOnBit(Flag1058(Flag1058::_1)))
        revision = sead::Endian::swapU32(revision);
    _e14 += 4;
    _e18 -= 4;
    if (_e00->mSaveInfo->revision != revision)
        _f90 = 1;
    if (!file->info->is_common_at_same_account) {
        if (s32(revision) < 0x24e3)
            _1059 = 0;
        else if (s32(revision) < 0x24ef)
            _1059 = 1;
        else if (s32(revision) <= 0x3ef9)
            _1059 = 2;
        else
            _1059 = 3;
        _1058.changeBit(Flag1058(Flag1058::_4), s32(revision) < 0x36de);
    }
    std::memcpy(&_f88, _e08 + _e14, sizeof(_f88));
    if (_1058.isOnBit(Flag1058(Flag1058::_1)))
        _f88 = sead::Endian::swapU32(_f88);
    _e14 += 4;
    _e18 -= 4;
    if (auto* manager = gdt::Manager::instance()) {
        if (_f90 != 1 && manager->getParam().get().getBuffer1()->mResourceFlags != _f88)
            _f90 = 1;
    }
    // The original converts this byte even though its result is unused.
    if (_1058.isOnBit(Flag1058(Flag1058::_1)))
        sead::Endian::swapU8(_e08[_e14]);
    _e14 += 4;
    _e18 -= 4;
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

// NON_MATCHING: stack arrays, string insertion and grouped flag loops differ.
void SaveMgr::loadSavedataformat(const sead::SafeString& path, sead::Heap* heap) {
    static_assert(sizeof(sead::ArchiveFileDevice) == 0x88);
    static_assert(offsetof(SaveMgr, mSaveDataDevice) == 0xd78);
    static_assert(offsetof(SaveMgr, mSaveDataHandles) == 0x378);
    static_assert(offsetof(SaveMgr, _e00) == 0xe00);
    res::LoadRequest archive_request;
    archive_request.mRequester = "SaveMgr";
    archive_request._26 = false;
    auto* archive = sead::DynamicCast<res::Archive>(
        mSaveDataArcHandle.load(path, &archive_request, nullptr));
    if (!archive)
        return;
    mSaveDataDevice.mArchive = archive;
    sead::DirectoryHandle directory;
    // The open result is discarded; native code tests the handle's current device.
    mSaveDataDevice.tryOpenDirectory(&directory, "");
    if (!directory.getDevice())
        return;
    sead::DirectoryEntry entry;
    sead::FixedSafeString<256> names[32];
    res::GameSaveData* resources[32]{};
    s32 count = 0;
    while (directory.read(&entry, 1) != 0) {
        if (entry.is_directory)
            continue;
        {
            res::LoadRequest request;
            request.mRequester = "SaveMgr";
            request._24 = true;
            request._26 = false;
            request.mFileDevice = &mSaveDataDevice;
            auto* resource = sead::DynamicCast<res::GameSaveData>(
                mSaveDataHandles[count].load(entry.name, &request, nullptr));
            if (resource) {
                resources[count] = resource;
                names[count] = entry.name;
            }
            for (s32 i = 0; i < count; ++i) {
                if (names[i] > entry.name) {
                    for (s32 j = count; j > i; --j) {
                        resources[j] = resources[j - 1];
                        names[j] = names[j - 1];
                    }
                    resources[i] = resource;
                    names[i] = entry.name;
                    break;
                }
            }
        }  // The per-file request is destroyed before the capacity-exit read.
        if (++count >= 32) {
            // The native capacity exit still reads one more entry and discards its count.
            directory.read(&entry, 1);
            break;
        }
    }
    _e00 = new (heap, 8) res::GameSaveData;
    if (!_e00)
        return;
    u32 hashes[32]{};
    s32 flag_counts[32]{};
    s32 unique_count = 0;
    for (s32 i = 0; i < count; ++i) {
        auto* file = resources[i]->mFiles[0];
        const u32 hash = sead::HashCRC32::calcStringHash(file->info->name.cstr());
        for (s32 j = 0; j < 32; ++j) {
            if (hashes[j] == 0) {
                hashes[j] = hash;
                flag_counts[j] = file->flags.size();
                ++unique_count;
                break;
            }
            if (hashes[j] == hash) {
                flag_counts[j] += file->flags.size();
                break;
            }
        }
    }
    _e00->allocFiles(unique_count, heap);
    for (s32 i = 0; i < unique_count; ++i) {
        _e00->addFile(hashes[i], heap);
        _e00->allocFlags(hashes[i], flag_counts[i], heap);
    }
    for (s32 i = 0; i < count; ++i)
        _e00->copyFrom(*resources[i], heap);
    _e00->sortFlags();
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

// NON_MATCHING: the byte-order enum flag temporaries and branch scheduling differ.
bool SaveMgr::x_1(s32 index, const sead::SafeString& path, bool a, bool byte_swap) {
    _142 = _140;
    _140 = (_140 & 0x100) | (a ? 0x204 : 0x200);
    _105a = !a;
    if (byte_swap)
        _1058.setBit(Flag1058(Flag1058::_1));
    else
        _1058.resetBit(Flag1058(Flag1058::_1));
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

// NON_MATCHING: reverse search and shared scalar/array write branches differ.
void SaveMgr::x_8(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records) {
    for (const auto& record : records) {
        s32 file_index = _e00->getFiles().size();
        s32 flag_index = -1;
        while (file_index > 0) {
            --file_index;
            flag_index = _e00->getFiles()[file_index]->findFlagIndex(record.name_hash);
            if (flag_index >= 0)
                break;
        }
        if (flag_index < 0)
            continue;
        const auto& entry = _e00->getFiles().unsafeAt(file_index)->flags[flag_index];
        if (entry.kv.value < 0)
            continue;
        u32 offset = entry._8;
        gdt::FlagT<bool>* flag;
        const s16 sub_index = record.sub_index;
        if (sub_index < 0) {
            flag = _f98->getBoolFlag(entry.kv.value);
        } else {
            flag = _f98->getBoolFlag(entry.kv.value, sub_index);
            offset += sub_index * 8;
        }
        if (!flag || offset + 4 >= _e10)
            continue;
        const u32 hash = flag->getHash();
        std::memcpy(_e08 + offset, &hash, sizeof(hash));
        if (offset + 8 < _e10) {
            const u32 value = flag->getValue();
            std::memcpy(_e08 + (offset + 4), &value, sizeof(value));
        }
    }
}

// NON_MATCHING: reverse search and shared scalar/array write branches differ.
void SaveMgr::x_11(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records) {
    for (const auto& record : records) {
        s32 file_index = _e00->getFiles().size();
        s32 flag_index = -1;
        while (file_index > 0) {
            --file_index;
            flag_index = _e00->getFiles()[file_index]->findFlagIndex(record.name_hash);
            if (flag_index >= 0)
                break;
        }
        if (flag_index < 0)
            continue;
        const auto& entry = _e00->getFiles().unsafeAt(file_index)->flags[flag_index];
        if (entry.kv.value < 0)
            continue;
        u32 offset = entry._8;
        gdt::FlagT<s32>* flag;
        const s16 sub_index = record.sub_index;
        if (sub_index < 0) {
            flag = _f98->getS32Flag(entry.kv.value);
        } else {
            flag = _f98->getS32Flag(entry.kv.value, sub_index);
            offset += sub_index * 8;
        }
        if (!flag || offset + 4 >= _e10)
            continue;
        const u32 hash = flag->getHash();
        std::memcpy(_e08 + offset, &hash, sizeof(hash));
        if (offset + 8 < _e10) {
            const s32 value = flag->getValueRef();
            std::memcpy(_e08 + (offset + 4), &value, sizeof(value));
        }
    }
}

// NON_MATCHING: reverse search and shared scalar/array write branches differ.
void SaveMgr::x_12(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records) {
    for (const auto& record : records) {
        s32 file_index = _e00->getFiles().size();
        s32 flag_index = -1;
        while (file_index > 0) {
            --file_index;
            flag_index = _e00->getFiles()[file_index]->findFlagIndex(record.name_hash);
            if (flag_index >= 0)
                break;
        }
        if (flag_index < 0)
            continue;
        const auto& entry = _e00->getFiles().unsafeAt(file_index)->flags[flag_index];
        if (entry.kv.value < 0)
            continue;
        u32 offset = entry._8;
        gdt::FlagT<f32>* flag;
        const s16 sub_index = record.sub_index;
        if (sub_index < 0) {
            flag = _f98->getF32Flag(entry.kv.value);
        } else {
            flag = _f98->getF32Flag(entry.kv.value, sub_index);
            offset += sub_index * 8;
        }
        if (!flag || offset + 4 >= _e10)
            continue;
        const u32 hash = flag->getHash();
        std::memcpy(_e08 + offset, &hash, sizeof(hash));
        if (offset + 8 < _e10) {
            const f32 value = flag->getValueRef();
            std::memcpy(_e08 + (offset + 4), &value, sizeof(value));
        }
    }
}

bool SaveMgr::sub_7100E081E4(const res::GameSaveData::Flag&,
                                 const gdt::FlagT<sead::FixedSafeString<32>>* flag,
                                 u32 size, u32 offset) {
    constexpr u32 word_size = sizeof(u32);
    const u32 length = flag->getValueRef().calcLength();
    for (u32 i = 0; i < size; i += word_size) {
        const u32 value_offset = offset + word_size;
        if (value_offset >= _e10)
            return false;
        const u32 hash = flag->getHash();
        std::memcpy(_e08 + offset, &hash, sizeof(hash));
        offset += 2 * word_size;
        if (offset >= _e10)
            return false;
        if (length < i) {
            std::memset(_e08 + value_offset, 0, word_size);
        } else if (length < i + word_size) {
            std::memset(_e08 + value_offset, 0, word_size);
            std::memcpy(_e08 + value_offset, flag->getValueRef().cstr() + i, length - i);
        } else {
            std::memcpy(_e08 + value_offset, flag->getValueRef().cstr() + i, word_size);
        }
    }
    return true;
}

bool SaveMgr::sub_7100E083AC(const res::GameSaveData::Flag&,
                                 const gdt::FlagT<sead::FixedSafeString<64>>* flag,
                                 u32 size, u32 offset) {
    constexpr u32 word_size = sizeof(u32);
    const u32 length = flag->getValueRef().calcLength();
    for (u32 i = 0; i < size; i += word_size) {
        const u32 value_offset = offset + word_size;
        if (value_offset >= _e10)
            return false;
        const u32 hash = flag->getHash();
        std::memcpy(_e08 + offset, &hash, sizeof(hash));
        offset += 2 * word_size;
        if (offset >= _e10)
            return false;
        if (length < i) {
            std::memset(_e08 + value_offset, 0, word_size);
        } else if (length < i + word_size) {
            std::memset(_e08 + value_offset, 0, word_size);
            std::memcpy(_e08 + value_offset, flag->getValueRef().cstr() + i, length - i);
        } else {
            std::memcpy(_e08 + value_offset, flag->getValueRef().cstr() + i, word_size);
        }
    }
    return true;
}

bool SaveMgr::sub_7100E08574(const res::GameSaveData::Flag&,
                                 const gdt::FlagT<sead::FixedSafeString<256>>* flag,
                                 u32 size, u32 offset) {
    constexpr u32 word_size = sizeof(u32);
    const u32 length = flag->getValueRef().calcLength();
    for (u32 i = 0; i < size; i += word_size) {
        const u32 value_offset = offset + word_size;
        if (value_offset >= _e10)
            return false;
        const u32 hash = flag->getHash();
        std::memcpy(_e08 + offset, &hash, sizeof(hash));
        offset += 2 * word_size;
        if (offset >= _e10)
            return false;
        if (length < i) {
            std::memset(_e08 + value_offset, 0, word_size);
        } else if (length < i + word_size) {
            std::memset(_e08 + value_offset, 0, word_size);
            std::memcpy(_e08 + value_offset, flag->getValueRef().cstr() + i, length - i);
        } else {
            std::memcpy(_e08 + value_offset, flag->getValueRef().cstr() + i, word_size);
        }
    }
    return true;
}

// NON_MATCHING: reverse search and scalar/array call branches are scheduled differently.
void SaveMgr::x_13(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records) {
    for (const auto& record : records) {
        s32 file_index = _e00->getFiles().size();
        s32 flag_index = -1;
        while (file_index > 0) {
            --file_index;
            flag_index = _e00->getFiles()[file_index]->findFlagIndex(record.name_hash);
            if (flag_index >= 0)
                break;
        }
        if (flag_index < 0)
            continue;
        const auto& entry = _e00->getFiles().unsafeAt(file_index)->flags[flag_index];
        if (entry.kv.value < 0)
            continue;
        u32 offset = entry._8;
        const s16 sub_index = record.sub_index;
        const gdt::FlagT<sead::FixedSafeString<32>>* flag;
        if (sub_index < 0) {
            flag = _f98->getStrFlag(entry.kv.value);
        } else {
            flag = _f98->getStrFlag(entry.kv.value, sub_index);
            offset += sub_index * 64;
        }
        if (flag)
            sub_7100E081E4(entry, flag, 32, offset);
    }
}

// NON_MATCHING: reverse search and scalar/array call branches are scheduled differently.
void SaveMgr::x_14(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records) {
    for (const auto& record : records) {
        s32 file_index = _e00->getFiles().size();
        s32 flag_index = -1;
        while (file_index > 0) {
            --file_index;
            flag_index = _e00->getFiles()[file_index]->findFlagIndex(record.name_hash);
            if (flag_index >= 0)
                break;
        }
        if (flag_index < 0)
            continue;
        const auto& entry = _e00->getFiles().unsafeAt(file_index)->flags[flag_index];
        if (entry.kv.value < 0)
            continue;
        u32 offset = entry._8;
        const s16 sub_index = record.sub_index;
        const gdt::FlagT<sead::FixedSafeString<64>>* flag;
        if (sub_index < 0) {
            flag = _f98->getStr64Flag(entry.kv.value);
            if (!flag)
                continue;
            flag = _f98->getStr64Flag(entry.kv.value);
            sub_7100E083AC(entry, flag, 64, offset);
            continue;
        } else {
            flag = _f98->getStr64Flag(entry.kv.value, sub_index);
            offset += sub_index * 128;
        }
        if (flag)
            sub_7100E083AC(entry, flag, 64, offset);
    }
}

// NON_MATCHING: reverse search and scalar/array call branches are scheduled differently.
void SaveMgr::x_15(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records) {
    for (const auto& record : records) {
        s32 file_index = _e00->getFiles().size();
        s32 flag_index = -1;
        while (file_index > 0) {
            --file_index;
            flag_index = _e00->getFiles()[file_index]->findFlagIndex(record.name_hash);
            if (flag_index >= 0)
                break;
        }
        if (flag_index < 0)
            continue;
        const auto& entry = _e00->getFiles().unsafeAt(file_index)->flags[flag_index];
        if (entry.kv.value < 0)
            continue;
        u32 offset = entry._8;
        const s16 sub_index = record.sub_index;
        const gdt::FlagT<sead::FixedSafeString<256>>* flag;
        if (sub_index < 0) {
            flag = _f98->getStr256Flag(entry.kv.value);
        } else {
            flag = _f98->getStr256Flag(entry.kv.value, sub_index);
            offset += sub_index * 512;
        }
        if (flag)
            sub_7100E08574(entry, flag, 256, offset);
    }
}

// NON_MATCHING: reverse search and shared scalar/array component-write branches differ.
void SaveMgr::x_16(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records) {
    for (const auto& record : records) {
        s32 file_index = _e00->getFiles().size();
        s32 flag_index = -1;
        while (file_index > 0) {
            --file_index;
            flag_index = _e00->getFiles()[file_index]->findFlagIndex(record.name_hash);
            if (flag_index >= 0)
                break;
        }
        if (flag_index < 0)
            continue;
        const auto& entry = _e00->getFiles().unsafeAt(file_index)->flags[flag_index];
        if (entry.kv.value < 0)
            continue;
        u32 offset = entry._8;
        const s16 sub_index = record.sub_index;
        const gdt::FlagT<sead::Vector2f>* flag;
        if (sub_index < 0) {
            flag = _f98->getVec2fFlag(entry.kv.value);
        } else {
            flag = _f98->getVec2fFlag(entry.kv.value, sub_index);
            offset += sub_index * 16;
        }
        if (!flag)
            continue;
        if (offset + 4 >= _e10)
            continue;
        const u32 hash_x = flag->getHash();
        std::memcpy(_e08 + offset, &hash_x, sizeof(hash_x));
        if (offset + 8 >= _e10)
            continue;
        const f32 value_x = flag->getValueRef().x;
        std::memcpy(_e08 + (offset + 4), &value_x, sizeof(value_x));
        if (offset + 12 >= _e10)
            continue;
        const u32 hash_y = flag->getHash();
        std::memcpy(_e08 + (offset + 8), &hash_y, sizeof(hash_y));
        if (offset + 16 >= _e10)
            continue;
        const f32 value_y = flag->getValueRef().y;
        std::memcpy(_e08 + (offset + 12), &value_y, sizeof(value_y));
    }
}

// NON_MATCHING: reverse search and shared scalar/array component-write branches differ.
void SaveMgr::x_17(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records) {
    for (const auto& record : records) {
        s32 file_index = _e00->getFiles().size();
        s32 flag_index = -1;
        while (file_index > 0) {
            --file_index;
            flag_index = _e00->getFiles()[file_index]->findFlagIndex(record.name_hash);
            if (flag_index >= 0)
                break;
        }
        if (flag_index < 0)
            continue;
        const auto& entry = _e00->getFiles().unsafeAt(file_index)->flags[flag_index];
        if (entry.kv.value < 0)
            continue;
        u32 offset = entry._8;
        const s16 sub_index = record.sub_index;
        const gdt::FlagT<sead::Vector3f>* flag;
        if (sub_index < 0) {
            flag = _f98->getVec3fFlag(entry.kv.value);
        } else {
            flag = _f98->getVec3fFlag(entry.kv.value, sub_index);
            offset += sub_index * 24;
        }
        if (!flag)
            continue;
        if (offset + 4 >= _e10)
            continue;
        const u32 hash_x = flag->getHash();
        std::memcpy(_e08 + offset, &hash_x, sizeof(hash_x));
        if (offset + 8 >= _e10)
            continue;
        const f32 value_x = flag->getValueRef().x;
        std::memcpy(_e08 + (offset + 4), &value_x, sizeof(value_x));
        if (offset + 12 >= _e10)
            continue;
        const u32 hash_y = flag->getHash();
        std::memcpy(_e08 + (offset + 8), &hash_y, sizeof(hash_y));
        if (offset + 16 >= _e10)
            continue;
        const f32 value_y = flag->getValueRef().y;
        std::memcpy(_e08 + (offset + 12), &value_y, sizeof(value_y));
        if (offset + 20 >= _e10)
            continue;
        const u32 hash_z = flag->getHash();
        std::memcpy(_e08 + (offset + 16), &hash_z, sizeof(hash_z));
        if (offset + 24 >= _e10)
            continue;
        const f32 value_z = flag->getValueRef().z;
        std::memcpy(_e08 + (offset + 20), &value_z, sizeof(value_z));
    }
}

// NON_MATCHING: reverse search and shared scalar/array component-write branches differ.
void SaveMgr::sub_7100E07E3C(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records) {
    for (const auto& record : records) {
        s32 file_index = _e00->getFiles().size();
        s32 flag_index = -1;
        while (file_index > 0) {
            --file_index;
            flag_index = _e00->getFiles()[file_index]->findFlagIndex(record.name_hash);
            if (flag_index >= 0)
                break;
        }
        if (flag_index < 0)
            continue;
        const auto& entry = _e00->getFiles().unsafeAt(file_index)->flags[flag_index];
        if (entry.kv.value < 0)
            continue;
        u32 offset = entry._8;
        const s16 sub_index = record.sub_index;
        const gdt::FlagT<sead::Vector4f>* flag;
        if (sub_index < 0) {
            flag = _f98->getVec4fFlag(entry.kv.value);
        } else {
            flag = _f98->getVec4fFlag(entry.kv.value, sub_index);
            offset += sub_index * 32;
        }
        if (!flag)
            continue;
        if (offset + 4 >= _e10)
            continue;
        const u32 hash_x = flag->getHash();
        std::memcpy(_e08 + offset, &hash_x, sizeof(hash_x));
        if (offset + 8 >= _e10)
            continue;
        const f32 value_x = flag->getValueRef().x;
        std::memcpy(_e08 + (offset + 4), &value_x, sizeof(value_x));
        if (offset + 12 >= _e10)
            continue;
        const u32 hash_y = flag->getHash();
        std::memcpy(_e08 + (offset + 8), &hash_y, sizeof(hash_y));
        if (offset + 16 >= _e10)
            continue;
        const f32 value_y = flag->getValueRef().y;
        std::memcpy(_e08 + (offset + 12), &value_y, sizeof(value_y));
        if (offset + 20 >= _e10)
            continue;
        const u32 hash_z = flag->getHash();
        std::memcpy(_e08 + (offset + 16), &hash_z, sizeof(hash_z));
        if (offset + 24 >= _e10)
            continue;
        const f32 value_z = flag->getValueRef().z;
        std::memcpy(_e08 + (offset + 20), &value_z, sizeof(value_z));
        if (offset + 28 >= _e10)
            continue;
        const u32 hash_w = flag->getHash();
        std::memcpy(_e08 + (offset + 24), &hash_w, sizeof(hash_w));
        if (offset + 32 >= _e10)
            continue;
        const f32 value_w = flag->getValueRef().w;
        std::memcpy(_e08 + (offset + 28), &value_w, sizeof(value_w));
    }
}

// NON_MATCHING: the ResetEvent store order and the `1 << 1` mask materialisation differ (ours builds
// the mask directly); the callback list walk is otherwise the same.
bool SaveMgr::x_10() {
    if (_38)
        return false;

    if (auto* manager = gdt::Manager::instance())
        manager->mFlagBuffer->copyChangedFlags(*manager->mRetryBuffer, true, false, false);

    auto* manager = gdt::Manager::instance();
    gdt::Manager::ResetEvent event;
    event.param = _f98;
    if (manager) {
        manager->mBitFlags.reset(gdt::Manager::BitFlag::RequestResetAllFlagsToInitial);
        manager->copyParamToParam1();
        manager->mParamBypassPerm.setChangeOnlyOnce(false);
        manager->mParam.setChangeOnlyOnce(false);
        manager->mBitFlags.reset(gdt::Manager::BitFlag::_1);
    }

    auto it = mCallbacks2.begin();
    if (it != mCallbacks2.end()) {
        do {
            auto* callback = *it;
            if (callback->mDelegate)
                (*callback->mDelegate)(&event);
            ++it;
        } while (it != mCallbacks2.end());
    }

    _38 = 0;
    for (s32& value : _14c)
        value = -1;
    _1058.resetBit(Flag1058(Flag1058::_1));
    return true;
}

// NON_MATCHING: header copies, delegate stack placement and file record updates differ.
bool SaveMgr::x_6(u32 idx) {
    static_assert(sizeof(Unk3) == 0xc);
    if (_e44 == 0) {
        _e48 = _e14;
        const u32 revision = _e00->mSaveInfo->revision;
        const u32 build_machine = _e00->mSaveInfo->is_build_machine;
        const u32 resource_flags = gdt::Manager::instance()->getParam().get().getBuffer1()->mResourceFlags;
        std::memcpy(_e08 + _e14, &revision, sizeof(revision));
        std::memcpy(_e08 + _e14 + 4, &resource_flags, sizeof(resource_flags));
        std::memcpy(_e08 + _e14 + 8, &build_machine, sizeof(build_machine));
        _e14 += 12;
    }
    auto* file = _e00->mFiles[idx];
    const s32 flag_count = file->flags.size();
    const s32 end = s32(_e44) + 0x1800;
    const sead::Delegate1<SaveMgr, res::GameSaveData::Flag&> delegate(this, &SaveMgr::invoked);
    file->forEachFlag(delegate, s32(_e44), sead::Mathi::min(end, flag_count));
    if (end < flag_count) {
        _e44 += 0x1800;
        return false;
    }
    if (file->info->is_save_secure_code) {
        const u32 secure_code = 0xffffffff;
        std::memcpy(_e08 + _e14, &secure_code, sizeof(secure_code));
        _e14 += 4;
    }
    if (_3c == 3)
        return true;
    auto* record = _11c8.emplaceBack();
    record->file_index = idx;
    record->data_size = _e14 - _e48;
    const u32 padding = 0x20 - (_e14 & 0x1f);
    record->padding_size = padding;
    _e14 += padding;
    return true;
}

// NON_MATCHING: callback traversal and filename comparison loops differ.
void SaveMgr::sub_7100E0670C(const sead::SafeString& name) {
    static_assert(offsetof(gdt::Manager, mFlagBuffer) == 0xc00);
    _f98 = gdt::Manager::instance()->mFlagBuffer;
    gdt::Manager::ResetEvent event;
    event.param = _f98;
    auto it = mCallbacks2.begin();
    while (it != mCallbacks2.end()) {
        auto* callback = *it;
        ++it;  // The native walk retains the next node before invoking the callback.
        if (callback->mDelegate)
            (*callback->mDelegate)(&event);
    }
    for (s32 i = 0; i < _e00->getFiles().size(); ++i) {
        auto* file = _e00->mFiles[i];
        if (file->info->name == name) {
            const sead::Delegate1<SaveMgr, const res::GameSaveData::Flag&> delegate(this, &SaveMgr::x_9);
            _e00->mFiles[i]->forEachFlag(delegate);
            return;
        }
    }
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

namespace ksys {

// NON_MATCHING: write-status branches fold to a conditional selection and handle loads move.
void SaveMgr::sub_7100E0BC7C() {
    _3c = 4;
    if (!sead::FileDeviceMgr::instance()) {
        _38 = 0;
        _3c = 3;
        return;
    }
    if (!sub_7100E05560(_80, _1d0, 1, true)) {
        _3c = 3;
        if (mFileHandle.getDevice()) {
            if ((_140 & 0x10) && _100->isAvailable())
                _100->tryFlush(&mFileHandle);
            mFileHandle.tryClose();
        }
        return;
    }
    if (mFileHandle.getDevice()) {
        const u32 size = _e28;
        u32 written = 0;
        if (mFileHandle.tryWrite(&written, _e2c ? static_cast<const u8*>(_e30) : _e08, size) &&
            written == size) {
            _3c = 0;
        } else {
            _3c = 3;
        }
    } else {
        _3c = 3;
    }
    if (mFileHandle.getDevice()) {
        if ((_140 & 0x10) && _100->isAvailable())
            _100->tryFlush(&mFileHandle);
        if (!mFileHandle.tryClose())
            _3c = 3;
    }
}

bool SaveMgr::sub_7100E0C688() {
    if (_105a) {
        auto* resource = sead::DynamicCast<sead::DirectResource>(mLoadHandle.getResource());
        if (resource) {
            const u32 size = resource->getRawSize();
            if (size <= _e10) {
                _e18 = size;
                std::memcpy(_e08, resource->getRawData(), size);
                _e14 = 0;
                mLoadHandle.requestUnload();
                return true;
            }
        }
    } else if (mFileHandle.getDevice()) {
        u32 size = 0;
        if (!mFileHandle.tryGetFileSize(&size))
            return false;
        if (size && mFileHandle.tryRead(&_e18, _e08 + _e14, size)) {
            _e14 = 0;
            return true;
        }
    }
    return false;
}


// NON_MATCHING: same size and logic; only the callback loop's block order / registers differ (the original
// loads the next node before the delegate call, we load it after).
// NON_MATCHING: same size and logic; the callback loop's rotation differs as in SaveMgrThreadCmd2/3.
// 0x7100e05d30 (CSV unnamed; placeholder name): commits the save device once per request and then tells the
// third callback list, resets the retry indices and clears the state bytes.
void SaveMgr::sub_7100E05D30() {
    if (!_f8) {
        _f8 = true;
    } else if (_3c == 0) {
        if (auto* device_mgr = sead::FileDeviceMgr::instance()) {
            if ((~_140 & 3) != 0 && (_b8 & 3) != 0) {
                auto* device = static_cast<sead::NinSaveFileDevice*>(device_mgr->findDevice(_c0));
                if (!device->tryCommit())
                    _3c = 3;
            }
        }
    }

    gdt::Manager::ResetEvent event;
    event.param = _f98;
    for (auto it = mCallbacks3.begin(); it != mCallbacks3.end(); ++it) {
        auto* callback = *it;
        if (callback->mDelegate)
            (*callback->mDelegate)(&event);
    }

    for (s32& value : _14c)
        value = -1;
    _e2c = false;
    _38 = 0;
}

// NON_MATCHING: same logic; the 0x140 flag updates come out with a different operand order and one extra
// u16 mask, and the 0x140 constant is kept in a callee-saved register (324 vs 304 bytes).
// 0x7100e04df4 (CSV SaveMgrThreadCmd2; placeholder name): the save thread step that copies the save buffer
// out and advances the 0x140 flag word.
void SaveMgr::SaveMgrThreadCmd2() {
    if (_105b) {
        _3c = 0;
        if (_f80)
            memcpy(_f80, _e08, _e10);
        _f8 = false;
        return sub_7100E05D30();
    }

    _140 &= ~8u;
    if ((_140 & 0x140) == 0x140)
        _140 |= 0x80;

    sub_7100E05E2C();

    if ((_140 & 0x140) == 0x140)
        _140 &= ~0x80u;

    if ((_140 & 0x11) == 0x11) {
        if (!(_140 & 2)) {
            _140 &= ~1u;
            sub_7100E05E2C();
            _140 |= 1u;
        }
        if ((_140 & 0x140) == 0x100) {
            _140 |= 0x80;
            sub_7100E05E2C();
            _140 &= ~0x80u;
        }
    }

    sub_7100E05D30();

    if (_140 & 8) {
        _140 &= ~8u;
        _100 = nullptr;
    }
    if (_140 & 0x200) {
        _105a = false;
        _10b0.clear();
        _140 = _142;
    }
}

// 0x7100e04f24 (CSV SaveMgrThreadCmd3; placeholder name): flushes the pending flag buffer and runs the
// save state machine (the 0x140 flag word) before reloading the flag buffer.
void SaveMgr::SaveMgrThreadCmd3() {
    if (_105b) {
        _f8 = false;
        return sub_7100E05D30();
    }

    auto* manager = gdt::Manager::instance();
    if (!manager)
        return;

    _f98 = manager->mFlagBuffer1;
    gdt::Manager::ResetEvent event;
    event.param = _f98;
    auto it = mCallbacks2.begin();
    if (it != mCallbacks2.end()) {
        do {
            auto* callback = *it;
            if (callback->mDelegate)
                (*callback->mDelegate)(&event);
            ++it;
        } while (it != mCallbacks2.end());
    }

    sub_7100E0BC7C();

    if ((_140 & 0x11) == 0x11) {
        if (!(_140 & 2)) {
            _140 &= ~1u;
            sub_7100E0BC7C();
            _140 |= 1u;
        }
        if ((_140 & 0x140) == 0x100) {
            _140 |= 0x80;
            sub_7100E0BC7C();
            _140 &= ~0x80;
        }
    }

    sub_7100E05D30();

    if (_140 & 0x200) {
        _105a = false;
        _10b0.clear();
        _140 = _142;
    }
}

// 0x7100e03d48 (CSV SaveMgrThread; placeholder name): the SaveMgr delegate thread entry, which
// dispatches on the command number passed by the caller of the save thread.
void SaveMgr::SaveMgrThread(void* arg, s64 cmd) {
    switch (cmd) {
    case 1:
        SaveMgrThreadCmd1();
        return;
    case 2:
        SaveMgrThreadCmd2();
        return;
    case 3:
        SaveMgrThreadCmd3();
        return;
    case 4:
        if (auto* callback = ui::sUnk_7102606a98Handler)
            callback();
        return;
    }
}

// NON_MATCHING: bounds checks and repeated virtual value queries are scheduled differently.
bool SaveMgr::sub_7100E0AE0C(const res::GameSaveData::Flag& entry, gdt::TriggerParam* buffer) {
    const s32 index = entry.kv.value;
    if (index >= buffer->mVector2fFlags.size() || index < 0)
        return false;
    const auto* value = buffer->getVec2fFlag(index);
    if (!value)
        return false;
    const u32 offset = entry._8;
    bool success = false;
    do {
        if (offset + 4 >= _e10)
            break;
        const u32 hash0 = value->getHash();
        std::memcpy(_e08 + (offset + 0), &hash0, sizeof(hash0));
        if (offset + 8 >= _e10)
            break;
        const f32 component0 = value->getValueRef().x;
        std::memcpy(_e08 + (offset + 4), &component0, sizeof(component0));
        if (offset + 12 >= _e10)
            break;
        const u32 hash1 = value->getHash();
        std::memcpy(_e08 + (offset + 8), &hash1, sizeof(hash1));
        if (offset + 16 >= _e10)
            break;
        const f32 component1 = value->getValueRef().y;
        std::memcpy(_e08 + (offset + 12), &component1, sizeof(component1));
        success = true;
    } while (false);
    if (!success)
        _3c = 3;
    else if (_3c == 4)
        _3c = 0;
    return true;
}

// NON_MATCHING: bounds checks and repeated virtual value queries are scheduled differently.
bool SaveMgr::sub_7100E0AF38(const res::GameSaveData::Flag& entry, gdt::TriggerParam* buffer) {
    const s32 index = entry.kv.value;
    if (index >= buffer->mVector3fFlags.size() || index < 0)
        return false;
    const auto* value = buffer->getVec3fFlag(index);
    if (!value)
        return false;
    const u32 offset = entry._8;
    bool success = false;
    do {
        if (offset + 4 >= _e10)
            break;
        const u32 hash0 = value->getHash();
        std::memcpy(_e08 + (offset + 0), &hash0, sizeof(hash0));
        if (offset + 8 >= _e10)
            break;
        const f32 component0 = value->getValueRef().x;
        std::memcpy(_e08 + (offset + 4), &component0, sizeof(component0));
        if (offset + 12 >= _e10)
            break;
        const u32 hash1 = value->getHash();
        std::memcpy(_e08 + (offset + 8), &hash1, sizeof(hash1));
        if (offset + 16 >= _e10)
            break;
        const f32 component1 = value->getValueRef().y;
        std::memcpy(_e08 + (offset + 12), &component1, sizeof(component1));
        if (offset + 20 >= _e10)
            break;
        const u32 hash2 = value->getHash();
        std::memcpy(_e08 + (offset + 16), &hash2, sizeof(hash2));
        if (offset + 24 >= _e10)
            break;
        const f32 component2 = value->getValueRef().z;
        std::memcpy(_e08 + (offset + 20), &component2, sizeof(component2));
        success = true;
    } while (false);
    if (!success)
        _3c = 3;
    else if (_3c == 4)
        _3c = 0;
    return true;
}

// NON_MATCHING: bounds checks and repeated virtual value queries are scheduled differently.
bool SaveMgr::sub_7100E0B0B8(const res::GameSaveData::Flag& entry, gdt::TriggerParam* buffer) {
    const s32 index = entry.kv.value;
    if (index >= buffer->mVector4fFlags.size() || index < 0)
        return false;
    const auto* value = buffer->getVec4fFlag(index);
    if (!value)
        return false;
    const u32 offset = entry._8;
    bool success = false;
    do {
        if (offset + 4 >= _e10)
            break;
        const u32 hash0 = value->getHash();
        std::memcpy(_e08 + (offset + 0), &hash0, sizeof(hash0));
        if (offset + 8 >= _e10)
            break;
        const f32 component0 = value->getValueRef().x;
        std::memcpy(_e08 + (offset + 4), &component0, sizeof(component0));
        if (offset + 12 >= _e10)
            break;
        const u32 hash1 = value->getHash();
        std::memcpy(_e08 + (offset + 8), &hash1, sizeof(hash1));
        if (offset + 16 >= _e10)
            break;
        const f32 component1 = value->getValueRef().y;
        std::memcpy(_e08 + (offset + 12), &component1, sizeof(component1));
        if (offset + 20 >= _e10)
            break;
        const u32 hash2 = value->getHash();
        std::memcpy(_e08 + (offset + 16), &hash2, sizeof(hash2));
        if (offset + 24 >= _e10)
            break;
        const f32 component2 = value->getValueRef().z;
        std::memcpy(_e08 + (offset + 20), &component2, sizeof(component2));
        if (offset + 28 >= _e10)
            break;
        const u32 hash3 = value->getHash();
        std::memcpy(_e08 + (offset + 24), &hash3, sizeof(hash3));
        if (offset + 32 >= _e10)
            break;
        const f32 component3 = value->getValueRef().w;
        std::memcpy(_e08 + (offset + 28), &component3, sizeof(component3));
        success = true;
    } while (false);
    if (!success)
        _3c = 3;
    else if (_3c == 4)
        _3c = 0;
    return true;
}

// NON_MATCHING: bounds checks and repeated virtual value queries are scheduled differently.
bool SaveMgr::sub_7100E0B28C(const res::GameSaveData::Flag& entry, gdt::TriggerParam* buffer, u32 hash) {
    s32 count = 0;
    const bool found = buffer->getBoolArraySizeByHash(&count, hash);
    if (count == 0 || !found)
        return false;
    const s32 index = entry.kv.value;
    if (index >= buffer->mBoolArrayFlags.size() || index < 0)
        return false;
    if (count > 0) {
        u32 base = entry._8;
        auto* value = buffer->getBoolFlag(index, 0);
        u32 element_offset = 0;
        s32 next = 1;
        while (value) {
            const u32 offset = base + element_offset;
            bool success = false;
            do {
                if (offset + 4 >= _e10)
                    break;
                const u32 hash0 = value->getHash();
                std::memcpy(_e08 + (offset + 0), &hash0, sizeof(hash0));
                if (offset + 8 >= _e10)
                    break;
                const u32 component0 = u32(value->getValue());
                std::memcpy(_e08 + (offset + 4), &component0, sizeof(component0));
                success = true;
            } while (false);
            if (!success)
                _3c = 3;
            else if (_3c == 4)
                _3c = 0;
            if (count <= next)
                break;
            base = entry._8;
            value = buffer->getBoolFlag(entry.kv.value, next);
            element_offset += 8;
            ++next;
        }
    }
    return true;
}

// NON_MATCHING: bounds checks and repeated virtual value queries are scheduled differently.
bool SaveMgr::sub_7100E0B3E0(const res::GameSaveData::Flag& entry, gdt::TriggerParam* buffer, u32 hash) {
    s32 count = 0;
    const bool found = buffer->getS32ArraySizeByHash(&count, hash);
    if (count == 0 || !found)
        return false;
    const s32 index = entry.kv.value;
    if (index >= buffer->mS32ArrayFlags.size() || index < 0)
        return false;
    if (count > 0) {
        u32 base = entry._8;
        auto* value = buffer->getS32Flag(index, 0);
        u32 element_offset = 0;
        s32 next = 1;
        while (value) {
            const u32 offset = base + element_offset;
            bool success = false;
            do {
                if (offset + 4 >= _e10)
                    break;
                const u32 hash0 = value->getHash();
                std::memcpy(_e08 + (offset + 0), &hash0, sizeof(hash0));
                if (offset + 8 >= _e10)
                    break;
                const s32 component0 = value->getValueRef();
                std::memcpy(_e08 + (offset + 4), &component0, sizeof(component0));
                success = true;
            } while (false);
            if (!success)
                _3c = 3;
            else if (_3c == 4)
                _3c = 0;
            if (count <= next)
                break;
            base = entry._8;
            value = buffer->getS32Flag(entry.kv.value, next);
            element_offset += 8;
            ++next;
        }
    }
    return true;
}

// NON_MATCHING: bounds checks and repeated virtual value queries are scheduled differently.
bool SaveMgr::sub_7100E0B534(const res::GameSaveData::Flag& entry, gdt::TriggerParam* buffer, u32 hash) {
    s32 count = 0;
    const bool found = buffer->getF32ArraySizeByHash(&count, hash);
    if (count == 0 || !found)
        return false;
    const s32 index = entry.kv.value;
    if (index >= buffer->mF32ArrayFlags.size() || index < 0)
        return false;
    if (count > 0) {
        u32 base = entry._8;
        auto* value = buffer->getF32Flag(index, 0);
        u32 element_offset = 0;
        s32 next = 1;
        while (value) {
            const u32 offset = base + element_offset;
            bool success = false;
            do {
                if (offset + 4 >= _e10)
                    break;
                const u32 hash0 = value->getHash();
                std::memcpy(_e08 + (offset + 0), &hash0, sizeof(hash0));
                if (offset + 8 >= _e10)
                    break;
                const f32 component0 = value->getValueRef();
                std::memcpy(_e08 + (offset + 4), &component0, sizeof(component0));
                success = true;
            } while (false);
            if (!success)
                _3c = 3;
            else if (_3c == 4)
                _3c = 0;
            if (count <= next)
                break;
            base = entry._8;
            value = buffer->getF32Flag(entry.kv.value, next);
            element_offset += 8;
            ++next;
        }
    }
    return true;
}

// NON_MATCHING: bounds checks and repeated virtual value queries are scheduled differently.
bool SaveMgr::sub_7100E0B688(const res::GameSaveData::Flag& entry, gdt::TriggerParam* buffer, u32 hash) {
    s32 count = 0;
    const bool found = buffer->getVec2fArraySizeByHash(&count, hash);
    if (count == 0 || !found)
        return false;
    const s32 index = entry.kv.value;
    if (index >= buffer->mVector2fArrayFlags.size() || index < 0)
        return false;
    if (count > 0) {
        u32 base = entry._8;
        const auto* value = buffer->getVec2fFlag(index, 0);
        u32 element_offset = 0;
        s32 next = 1;
        while (value) {
            const u32 offset = base + element_offset;
            bool success = false;
            do {
                if (offset + 4 >= _e10)
                    break;
                const u32 hash0 = value->getHash();
                std::memcpy(_e08 + (offset + 0), &hash0, sizeof(hash0));
                if (offset + 8 >= _e10)
                    break;
                const f32 component0 = value->getValueRef().x;
                std::memcpy(_e08 + (offset + 4), &component0, sizeof(component0));
                if (offset + 12 >= _e10)
                    break;
                const u32 hash1 = value->getHash();
                std::memcpy(_e08 + (offset + 8), &hash1, sizeof(hash1));
                if (offset + 16 >= _e10)
                    break;
                const f32 component1 = value->getValueRef().y;
                std::memcpy(_e08 + (offset + 12), &component1, sizeof(component1));
                success = true;
            } while (false);
            if (!success)
                _3c = 3;
            else if (_3c == 4)
                _3c = 0;
            if (count <= next)
                break;
            base = entry._8;
            value = buffer->getVec2fFlag(entry.kv.value, next);
            element_offset += 16;
            ++next;
        }
    }
    return true;
}

// NON_MATCHING: bounds checks and repeated virtual value queries are scheduled differently.
bool SaveMgr::sub_7100E0B830(const res::GameSaveData::Flag& entry, gdt::TriggerParam* buffer, u32 hash) {
    s32 count = 0;
    const bool found = buffer->getVec3fArraySizeByHash(&count, hash);
    if (count == 0 || !found)
        return false;
    const s32 index = entry.kv.value;
    if (index >= buffer->mVector3fArrayFlags.size() || index < 0)
        return false;
    if (count > 0) {
        u32 base = entry._8;
        const auto* value = buffer->getVec3fFlag(index, 0);
        u32 element_offset = 0;
        s32 next = 1;
        while (value) {
            const u32 offset = base + element_offset;
            bool success = false;
            do {
                if (offset + 4 >= _e10)
                    break;
                const u32 hash0 = value->getHash();
                std::memcpy(_e08 + (offset + 0), &hash0, sizeof(hash0));
                if (offset + 8 >= _e10)
                    break;
                const f32 component0 = value->getValueRef().x;
                std::memcpy(_e08 + (offset + 4), &component0, sizeof(component0));
                if (offset + 12 >= _e10)
                    break;
                const u32 hash1 = value->getHash();
                std::memcpy(_e08 + (offset + 8), &hash1, sizeof(hash1));
                if (offset + 16 >= _e10)
                    break;
                const f32 component1 = value->getValueRef().y;
                std::memcpy(_e08 + (offset + 12), &component1, sizeof(component1));
                if (offset + 20 >= _e10)
                    break;
                const u32 hash2 = value->getHash();
                std::memcpy(_e08 + (offset + 16), &hash2, sizeof(hash2));
                if (offset + 24 >= _e10)
                    break;
                const f32 component2 = value->getValueRef().z;
                std::memcpy(_e08 + (offset + 20), &component2, sizeof(component2));
                success = true;
            } while (false);
            if (!success)
                _3c = 3;
            else if (_3c == 4)
                _3c = 0;
            if (count <= next)
                break;
            base = entry._8;
            value = buffer->getVec3fFlag(entry.kv.value, next);
            element_offset += 24;
            ++next;
        }
    }
    return true;
}

// NON_MATCHING: bounds checks and repeated virtual value queries are scheduled differently.
bool SaveMgr::sub_7100E0BA2C(const res::GameSaveData::Flag& entry, gdt::TriggerParam* buffer, u32 hash) {
    s32 count = 0;
    const bool found = buffer->getVec4fArraySizeByHash(&count, hash);
    if (count == 0 || !found)
        return false;
    const s32 index = entry.kv.value;
    if (index >= buffer->mVector4fArrayFlags.size() || index < 0)
        return false;
    if (count > 0) {
        u32 base = entry._8;
        const auto* value = buffer->getVec4fFlag(index, 0);
        u32 element_offset = 0;
        s32 next = 1;
        while (value) {
            const u32 offset = base + element_offset;
            bool success = false;
            do {
                if (offset + 4 >= _e10)
                    break;
                const u32 hash0 = value->getHash();
                std::memcpy(_e08 + (offset + 0), &hash0, sizeof(hash0));
                if (offset + 8 >= _e10)
                    break;
                const f32 component0 = value->getValueRef().x;
                std::memcpy(_e08 + (offset + 4), &component0, sizeof(component0));
                if (offset + 12 >= _e10)
                    break;
                const u32 hash1 = value->getHash();
                std::memcpy(_e08 + (offset + 8), &hash1, sizeof(hash1));
                if (offset + 16 >= _e10)
                    break;
                const f32 component1 = value->getValueRef().y;
                std::memcpy(_e08 + (offset + 12), &component1, sizeof(component1));
                if (offset + 20 >= _e10)
                    break;
                const u32 hash2 = value->getHash();
                std::memcpy(_e08 + (offset + 16), &hash2, sizeof(hash2));
                if (offset + 24 >= _e10)
                    break;
                const f32 component2 = value->getValueRef().z;
                std::memcpy(_e08 + (offset + 20), &component2, sizeof(component2));
                if (offset + 28 >= _e10)
                    break;
                const u32 hash3 = value->getHash();
                std::memcpy(_e08 + (offset + 24), &hash3, sizeof(hash3));
                if (offset + 32 >= _e10)
                    break;
                const f32 component3 = value->getValueRef().w;
                std::memcpy(_e08 + (offset + 28), &component3, sizeof(component3));
                success = true;
            } while (false);
            if (!success)
                _3c = 3;
            else if (_3c == 4)
                _3c = 0;
            if (count <= next)
                break;
            base = entry._8;
            value = buffer->getVec4fFlag(entry.kv.value, next);
            element_offset += 32;
            ++next;
        }
    }
    return true;
}

// NON_MATCHING: typed dispatch and array serialization loops are scheduled differently.
void SaveMgr::x_9(const res::GameSaveData::Flag& entry) {
    if (_3c == 3 || !gdt::Manager::instance() || !_f98)
        return;
    auto* buffer = _f98;
    const u32 hash = entry.kv.name_hash;
    switch (entry.type) {
    case gdt::FlagType::Bool: {
        const s32 index = entry.kv.value;
        if (index >= buffer->mBoolFlags.size() || index < 0)
            return;
        auto* value = buffer->getBoolFlag(index);
        if (!value)
            return;
        const u32 offset = entry._8;
        bool success = false;
        do {
            if (offset + 4 >= _e10)
                break;
            const u32 hash0 = value->getHash();
            std::memcpy(_e08 + (offset + 0), &hash0, sizeof(hash0));
            if (offset + 8 >= _e10)
                break;
            const u32 component0 = u32(value->getValue());
            std::memcpy(_e08 + (offset + 4), &component0, sizeof(component0));
            success = true;
        } while (false);
        if (!success)
            _3c = 3;
        else if (_3c == 4)
            _3c = 0;
        return;
    }
    case gdt::FlagType::S32: {
        const s32 index = entry.kv.value;
        if (index >= buffer->mS32Flags.size() || index < 0)
            return;
        auto* value = buffer->getS32Flag(index);
        if (!value)
            return;
        const u32 offset = entry._8;
        bool success = false;
        do {
            if (offset + 4 >= _e10)
                break;
            const u32 hash0 = value->getHash();
            std::memcpy(_e08 + (offset + 0), &hash0, sizeof(hash0));
            if (offset + 8 >= _e10)
                break;
            const s32 component0 = value->getValueRef();
            std::memcpy(_e08 + (offset + 4), &component0, sizeof(component0));
            success = true;
        } while (false);
        if (!success)
            _3c = 3;
        else if (_3c == 4)
            _3c = 0;
        return;
    }
    case gdt::FlagType::F32: {
        const s32 index = entry.kv.value;
        if (index >= buffer->mF32Flags.size() || index < 0)
            return;
        auto* value = buffer->getF32Flag(index);
        if (!value)
            return;
        const u32 offset = entry._8;
        bool success = false;
        do {
            if (offset + 4 >= _e10)
                break;
            const u32 hash0 = value->getHash();
            std::memcpy(_e08 + (offset + 0), &hash0, sizeof(hash0));
            if (offset + 8 >= _e10)
                break;
            const f32 component0 = value->getValueRef();
            std::memcpy(_e08 + (offset + 4), &component0, sizeof(component0));
            success = true;
        } while (false);
        if (!success)
            _3c = 3;
        else if (_3c == 4)
            _3c = 0;
        return;
    }
    case gdt::FlagType::String: {
        const s32 index = entry.kv.value;
        if (index >= buffer->mStringFlags.size() || index < 0)
            return;
        const auto* value = buffer->getStrFlag(index);
        if (!value)
            return;
        if (!sub_7100E081E4(entry, value, 32, entry._8))
            _3c = 3;
        else if (_3c == 4)
            _3c = 0;
        return;
    }
    case gdt::FlagType::String64: {
        const s32 index = entry.kv.value;
        if (index >= buffer->mString64Flags.size() || index < 0)
            return;
        const auto* value = buffer->getStr64Flag(index);
        if (!value)
            return;
        if (!sub_7100E083AC(entry, value, 64, entry._8))
            _3c = 3;
        else if (_3c == 4)
            _3c = 0;
        return;
    }
    case gdt::FlagType::String256: {
        const s32 index = entry.kv.value;
        if (index >= buffer->mString256Flags.size() || index < 0)
            return;
        const auto* value = buffer->getStr256Flag(index);
        if (!value)
            return;
        if (!sub_7100E08574(entry, value, 256, entry._8))
            _3c = 3;
        else if (_3c == 4)
            _3c = 0;
        return;
    }
    case gdt::FlagType::Vector2f:
        sub_7100E0AE0C(entry, buffer);
        return;
    case gdt::FlagType::Vector3f:
        sub_7100E0AF38(entry, buffer);
        return;
    case gdt::FlagType::Vector4f:
        sub_7100E0B0B8(entry, buffer);
        return;
    case gdt::FlagType::BoolArray:
        sub_7100E0B28C(entry, buffer, hash);
        return;
    case gdt::FlagType::S32Array:
        sub_7100E0B3E0(entry, buffer, hash);
        return;
    case gdt::FlagType::F32Array:
        sub_7100E0B534(entry, buffer, hash);
        return;
    case gdt::FlagType::StringArray: {
        s32 count = 0;
        const bool found = buffer->getStrArraySizeByHash(&count, hash);
        if (count == 0 || !found)
            return;
        const s32 index = entry.kv.value;
        if (index >= buffer->mStringArrayFlags.size() || index < 0 || count <= 0)
            return;
        u32 base = entry._8;
        const auto* value = buffer->getStrFlag(index, 0);
        u32 offset = 0;
        s32 next = 1;
        while (value) {
            if (!sub_7100E081E4(entry, value, 32, base + offset))
                _3c = 3;
            else if (_3c == 4)
                _3c = 0;
            if (count <= next)
                return;
            base = entry._8;
            value = buffer->getStrFlag(entry.kv.value, next);
            offset += 64;
            ++next;
        }
        return;
    }
    case gdt::FlagType::String64Array: {
        s32 count = 0;
        const bool found = buffer->getStr64ArraySizeByHash(&count, hash);
        if (count == 0 || !found)
            return;
        const s32 index = entry.kv.value;
        if (index >= buffer->mString64ArrayFlags.size() || index < 0 || count <= 0)
            return;
        u32 base = entry._8;
        const auto* value = buffer->getStr64Flag(index, 0);
        u32 offset = 0;
        s32 next = 1;
        while (value) {
            if (!sub_7100E083AC(entry, value, 64, base + offset))
                _3c = 3;
            else if (_3c == 4)
                _3c = 0;
            if (count <= next)
                return;
            base = entry._8;
            value = buffer->getStr64Flag(entry.kv.value, next);
            offset += 128;
            ++next;
        }
        return;
    }
    case gdt::FlagType::String256Array: {
        s32 count = 0;
        const bool found = buffer->getStr256ArraySizeByHash(&count, hash);
        if (count == 0 || !found)
            return;
        const s32 index = entry.kv.value;
        if (index >= buffer->mString256ArrayFlags.size() || index < 0 || count <= 0)
            return;
        u32 base = entry._8;
        const auto* value = buffer->getStr256Flag(index, 0);
        u32 offset = 0;
        s32 next = 1;
        while (value) {
            if (!sub_7100E08574(entry, value, 256, base + offset))
                _3c = 3;
            else if (_3c == 4)
                _3c = 0;
            if (count <= next)
                return;
            base = entry._8;
            value = buffer->getStr256Flag(entry.kv.value, next);
            offset += 512;
            ++next;
        }
        return;
    }
    case gdt::FlagType::Vector2fArray:
        sub_7100E0B688(entry, buffer, hash);
        return;
    case gdt::FlagType::Vector3fArray:
        sub_7100E0B830(entry, buffer, hash);
        return;
    case gdt::FlagType::Vector4fArray:
        sub_7100E0BA2C(entry, buffer, hash);
        return;
    default:
        return;
    }
}

}  // namespace ksys
