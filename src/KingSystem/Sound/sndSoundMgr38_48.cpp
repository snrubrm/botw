#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
#include "KingSystem/Physics/System/physClosestPointQueryWithInfo.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"

namespace ksys::snd {

// TU 0x71010349dc..0x71010366e4 (static initialiser) in the original.

Unk_SoundMgr38_48::~Unk_SoundMgr38_48() {
    if (_1dc8.isActive())
        _1dc8.getEvent()->kill();
    if (_1da0) {
        SoundMgr::instance()->_60->sub_7101059354(_1da0);
        _1da0 = nullptr;
    }
    if (_1d98) {
        _1d98->destroy();
        _1d98 = nullptr;
    }
    if (mSphere) {
        delete mSphere;
        mSphere = nullptr;
    }
    _1a88.freeBuffer();
    _1a98.freeBuffer();
}

void Unk_SoundMgr38_48::sub_7101035A50() {
    _1e08.set(1);
    if (_1e08.isOff(2)) {
        sub_7101035888();
        _1dc0 = 1;
    }
}

// The empty name the reader is loaded with. The original keeps it in the TU's merged static block at
// 0x7102610840 + 0x30 (GlobalMerge, together with the InitTimeInfoEx and two constant pairs), so ours
// addresses a standalone symbol.
static const sead::SafeString sEmptyName;

// NON_MATCHING: the empty name's address is block + 0x30 in the original (GlobalMerge of the TU
// statics) and the original keeps &_1da0 in a saved register across the calls, so its frame is 0x10
// larger; ours addresses a standalone symbol and reloads the member. The calls and values are the same.
// 0x7101035888 (placeholder name): creates the empty-name user instance and its asset info reader and
// loads the bars file for it; releases both when either step fails.
void Unk_SoundMgr38_48::sub_7101035888() {
    auto* sound = SoundMgr::instance();
    auto* resource_mgr = sound->_60;
    sead::Heap* heap = sound->_198;

    _1d98 = sub_710105E3D0(sEmptyName.cstr(), heap, nullptr, nullptr, nullptr);
    if (_1d98) {
        _1da0 = new (resource_mgr->mHeap, 8) Unk_7102502950;
        if (_1da0 && resource_mgr->loadBars(sEmptyName, _1da0, heap, false, false, nullptr))
            return;
    }

    if (_1da0) {
        resource_mgr->sub_7101059354(_1da0);
        _1da0 = nullptr;
    }
    if (_1d98) {
        _1d98->destroy();
        _1d98 = nullptr;
    }
}

// NON_MATCHING: the empty name's address is block + 0x30 in the original (GlobalMerge of the TU
// statics); ours addresses a standalone symbol. The rest of the body matches.
// 0x71010359b0 (placeholder name): loads the asset info reader at _1da0 with an empty name and hands
// it to the user instance at _1d98 once it is ready; releases both when the load fails.
bool Unk_SoundMgr38_48::sub_71010359B0() {
    if (!_1da0 || (_1da0->_18 & 1))
        return true;

    if (!_1da0->sub_7101057258(sEmptyName, SoundMgr::instance()->_60->mHeap))
        return false;

    if (_1da0->_18 & 1) {
        if (!_1d98)
            return false;
        _1d98->setAssetInfoReader(_1da0);
    } else {
        if (_1da0) {
            SoundMgr::instance()->_60->sub_7101059354(_1da0);
            _1da0 = nullptr;
        }
        if (_1d98) {
            _1d98->destroy();
            _1d98 = nullptr;
        }
    }
    return true;
}

// NON_MATCHING: query and contact iterator stack layout and status loads differ.
bool Unk_SoundMgr38_48::sub_7101036530(bool* indoor, const sead::Vector3f& position) {
    static_assert(offsetof(Unk_SoundMgr38_48, mSphere) == 0x1e00);
    static_assert(offsetof(phys::ClosestPointQuery, _18) == 0x18);
    static_assert(offsetof(phys::ContactPoint, material_mask_b) == 0x48);
    phys::SphereBasedClosestPointQuery query(mSphere, position, 1, "GrudgeBaseSound InDoor", 1,
                                             phys::LowPriority::Yes);
    if (auto* info = query.getContactPointInfo()) {
        info->subscribeLayer(phys::ContactLayer::SensorInDoor);
        const bool result = query.execute(false);
        if (query._18 == 1) {
            *indoor = result;
            if (result) {
                for (auto it = info->begin(), end = info->end(); it != end; ++it) {
                    const u32 type = (it.getPoint()->material_mask_b.getRawData() >> 20) & 7;
                    if (type == 3 || type == 4) {
                        *indoor = false;
                        break;
                    }
                }
            }
        }
    }
    return query._18 == 1;
}

}  // namespace ksys::snd
