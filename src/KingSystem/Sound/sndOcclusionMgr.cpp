#include "KingSystem/Sound/sndOcclusionMgr.h"
#include <resource/seadResource.h>
#include <aal/aalArbiter.h>
#include <aal/aalSystemAccessor.h>
#include "KingSystem/Sound/sndSound.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Sound/sndBarslistArchive.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::snd {

// Whole 1056A68 reads this writable float; native initial bits are 3e4ccccd.
KSYS_VISIBILITY_HIDDEN f32 sUnk_710250294C = 0.2f;

f32 OcclusionMgr::sub_7101056A4C() const {
    return _24 == 3 ? _20 : _1c;
}

// NON_MATCHING: the global float access has an extra GOT load and different register allocation.
f32 OcclusionMgr::sub_7101056A68() const {
    return _24 == 2 ? sUnk_710250294C : 0.0f;
}

void OcclusionMgr::sub_71010560D4(sead::Heap* heap) {}

void OcclusionMgr::sub_7101056868() {
    _74 = true;
    _7c = 2;
}

// NON_MATCHING: only the schedule of the constant stores (the original stores the vtable pointer and the pair at +0x20 after
// the first group of members).
OcclusionMgr::OcclusionMgr() = default;

OcclusionMgr::~OcclusionMgr() {
    if (_28) {
        delete _28;
        _28 = nullptr;
    }
    if (_30) {
        delete _30;
        _30 = nullptr;
    }
    if (_80) {
        delete _80;
        _80 = nullptr;
    }
}

}  // namespace ksys::snd

bool ResourceBars::parse_(u8* data, size_t size, sead::Heap* heap) {
    mAudioResource = aal::AudioResource::create(data, size, heap, sead::SafeString::cEmptyString);
    if (auto* manager = ksys::snd::SoundMgr::instance())
        manager->_60->sub_7101059450(mAudioResource);
    return true;
}

bool ResourceBars::readAssetInfo(aal::AssetInfo* info, const sead::SafeString& name, bool flag) {
    if (!mAudioResource)
        return false;
    return mAudioResource->readAssetInfo(info, name);
}

namespace ksys::snd {

// NON_MATCHING: the interface requires an explicit boolean at each virtual read; the native calls
// do not materialise it. The bounds checks and cast-cache accesses also schedule differently.
bool Unk_7102502950::readAssetInfo(aal::AssetInfo* info, const sead::SafeString& name, bool) {
    for (s64 i = 0; i < mHandles.size(); ++i) {
        auto* bars = sead::DynamicCast<ResourceBars>(mHandles[i].getResource());
        if (bars && bars->readAssetInfo(info, name, false))
            return true;
    }

    auto* manager = SoundMgr::instance()->_60;
    if (manager->_1408.isSuccess()) {
        auto* bars = sead::DynamicCast<ResourceBars>(manager->_1408.getResource());
        if (bars && bars->readAssetInfo(info, name, false))
            return true;
    }

    auto* slink = &SoundMgr::instance()->_60->mSlinkResources;
    for (s64 i = 0; i < slink->mHandles.size(); ++i) {
        auto* bars = sead::DynamicCast<ResourceBars>(slink->mHandles[i].getResource());
        if (bars && bars->readAssetInfo(info, name, false))
            return true;
    }

    if (manager->_1458.isSuccess()) {
        auto* bars = sead::DynamicCast<ResourceBars>(manager->_1458.getResource());
        if (bars && bars->readAssetInfo(info, name, false))
            return true;
    }
    if (manager->_14a8.isSuccess()) {
        auto* bars = sead::DynamicCast<ResourceBars>(manager->_14a8.getResource());
        if (bars && bars->readAssetInfo(info, name, false))
            return true;
    }
    if (manager->_15f8.isSuccess()) {
        auto* bars = sead::DynamicCast<ResourceBars>(manager->_15f8.getResource());
        if (bars && bars->readAssetInfo(info, name, false))
            return true;
    }
    if (manager->_1648.isSuccess()) {
        auto* bars = sead::DynamicCast<ResourceBars>(manager->_1648.getResource());
        if (bars && bars->readAssetInfo(info, name, false))
            return true;
    }
    return false;
}

// NON_MATCHING: the returned iterator copy is elided; the parse-state branches and loop registers differ.
bool Unk_7102502950::sub_7101057258(const sead::SafeString& name, sead::Heap*) {
    if (_18 & 3)
        return true;
    const auto iter = SoundMgr::instance()->_60->_15e8->getIter(name);
    if (!iter.isValid())
        return false;

    const s32 count = iter.getSize();
    s32 loaded = 0;
    s32 status = 2;
    for (s64 i = 0; i < count; ++i) {
        res::Handle& handle = mHandles[i];
        if (handle.isReadyOrNeedsParse()) {
            handle.parseResource(nullptr);
            if (!handle.isSuccess()) {
                status = 5;
                break;
            }
            auto* bars = sead::DynamicCast<ResourceBars>(handle.getResource());
            const char* filename;
            iter.tryGetStringByIndex(&filename, i);
            bars->sub_7101057588(filename);
        }
        loaded += handle.isSuccess();
    }
    if (status == 2 && loaded == count)
        status = 6;
    if (status == 5)
        _18 |= 2;
    else if (status == 6)
        _18 |= 1;
    else
        return false;
    return true;
}

}  // namespace ksys::snd

// NON_MATCHING: the inlined data-size result uses an extra move before the arbiter call.
// 0x71010571a4: allocates the handle array (`count` res::Handle objects).
void ksys::snd::Unk_7102502950::sub_71010571A4(s32 count, sead::Heap* heap) {
    if (count < 1)
        return;
    auto* handles = new (heap, 8, std::nothrow) res::Handle[count];
    if (!handles)
        return;
    mHandles = sead::Buffer<res::Handle>(count, handles);
}

ksys::snd::Unk_7102502950::~Unk_7102502950() {
    mHandles.freeBuffer();
}

ResourceBars::~ResourceBars() {
    if (mAudioResource) {
        if (auto* arbiter = aal::SystemAccessor::getArbiter()) {
            const void* data;
            u32 size;
            mAudioResource->getDataAndSize(&data, &size);
            arbiter->execOnDestroyWaveAsset(reinterpret_cast<u64>(data), size, true, true);
        }
        if (auto* manager = ksys::snd::SoundMgr::instance())
            manager->_60->sub_7101059454(mAudioResource);
        delete mAudioResource;
        mAudioResource = nullptr;
    }
}

void ResourceBars::sub_7101057588(const sead::SafeString& name) {
    mFileName.copy(name);
    mAudioResource->setFilename(&mFileName);
}

Unk_7102502b50::~Unk_7102502b50() = default;

namespace ksys::snd {

BarslistArchive::BarslistArchive() = default;

BarslistArchive::~BarslistArchive() {
    if (mIter)
        delete mIter;
}

// 4-byte tail call in the original.
void BarslistArchive::loadRes(sead::Heap* heap) {
    load(heap);
}

void BarslistArchive::load(sead::Heap* heap) {
    res::LoadRequest req;
    req.mRequester = "snd::BarslistArchive";
    req._22 = true;
    mHandle.load("Sound/ResourceList/BarslistInfo.byml", &req);

    auto* resource = sead::DynamicCast<sead::DirectResource>(mHandle.getResource());

    if (mIter)
        delete mIter;
    mIter = new (heap, 8) al::ByamlIter(resource->getRawData());
}

// NON_MATCHING: the original copy-constructs the returned iterator into the result slot instead of
// eliding the copy (20 bytes longer).
// 0x7101057520: the sub-iterator of the bars list at `key`.
al::ByamlIter BarslistArchive::getIter(const sead::SafeString& key) const {
    al::ByamlIter iter = mIter->getIterByKey(key.cstr());
    return iter;
}

// 0x7101057580: the entry count of `iter`.
s32 BarslistArchive::getSize(const al::ByamlIter& iter) const {
    return iter.getSize();
}

// 0x710105767c: the asset name at `index` in `iter`.
const char* BarslistArchive::getEntryName(const al::ByamlIter& iter, s32 index) const {
    const char* name;
    iter.tryGetStringByIndex(&name, index);
    return name;
}

}  // namespace ksys::snd
