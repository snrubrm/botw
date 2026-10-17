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

bool Unk_7102502978::readAssetInfo(aal::AssetInfo* info, const sead::SafeString& name, bool flag) {
    if (!mAudioResource)
        return false;
    return mAudioResource->readAssetInfo(info, name);
}

// NON_MATCHING: the inlined data-size result uses an extra move before the arbiter call.
Unk_7102502978::~Unk_7102502978() {
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

void Unk_7102502978::sub_7101057588(const sead::SafeString& name) {
    mFileName.copy(name);
    mAudioResource->setFilename(&mFileName);
}

// NON_MATCHING: placeholder destructor; the original (0x7101059518) also destroys members or bases
// this class does not declare yet.
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

}  // namespace ksys::snd
