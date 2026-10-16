#include "KingSystem/Sound/sndSound.h"
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Utils/InitTimeInfo.h"
#include "Game/Actor/actEnvSeEmitPoint.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Terrain/teraSystem.h"
#include <prim/seadScopedLock.h>
#include <aal/aalSpeakerBalanceUnifier.h>
#include "Game/gameUnkRttiPlaceholders.h"

// Address placeholder for the original kind-name text lookup; its enum type is not recovered.
const char* sub_7101029E34(u32 kind);

namespace ksys::snd {

// The TU's static initialiser is 0x710103ae20 (`_GLOBAL__sub_I_sndSoundMgr38.cpp`).
static util::InitTimeInfoEx sInitTimeInfo;

// NON_MATCHING: the compiler combines the adjacent flag and float initialization stores.
Unk_SoundMgr38_20::Unk_SoundMgr38_20() = default;

Unk_SoundMgr38_20::~Unk_SoundMgr38_20() {
    _8[0].clear();
    _8[1].clear();
}

void Unk_SoundMgr38_20::sub_7101029958(sead::Heap* heap) {
    _7a[0] = false;
    _7a[1] = false;
    _8[0].initOffset(0x850);
    _8[1].initOffset(0x850);
}

void Unk_SoundMgr38_20::sub_7101029970() {
    if (_78) {
        sub_71010299AC();
        sub_7101029AA0();
    }
}

void Unk_SoundMgr38_20::sub_71010299AC() {
    auto lock = sead::makeScopedLock(mCS);
    if (_8[0].size() == 0)
        return;
    sub_7101029D3C(&_8[0]);
    s32 index = 0;
    for (auto& point : _8[0]) {
        if (index <= 3)
            point.sub_7101029620(false);
        else
            point.sub_7101029620(true);
        ++index;
    }
    for (auto& point : _8[0])
        point.sub_71010296B0();
}

void Unk_SoundMgr38_20::sub_7101029AA0() {
    auto lock = sead::makeScopedLock(mCS);
    if (_8[1].size() == 0)
        return;
    sub_7101029D3C(&_8[1]);
    s32 index = 0;
    for (auto& point : _8[1]) {
        if (index <= 5)
            point.sub_7101029620(false);
        else
            point.sub_7101029620(true);
        ++index;
    }
    for (auto& point : _8[1])
        point.sub_71010296B0();
}

void Unk_SoundMgr38_20::sub_7101029B94() { _78 = true; }
void Unk_SoundMgr38_20::sub_7101029BA0() { _78 = false; }
void Unk_SoundMgr38_20::sub_7101029BA8() { _78 = false; }

bool Unk_SoundMgr38_20::sub_7101029BB0(uking::act::EnvSeEmitPoint* point) {
    if (!point)
        return false;
    u32 kind = 0;
    if (point->getName().findIndex(sub_7101029E34(0)) == -1) {
        kind = 1;
        if (point->getName().findIndex(sub_7101029E34(1)) == -1)
            return false;
    }
    point->_83c = kind;
    point->_84d = _7a[kind];
    auto lock = sead::makeScopedLock(mCS);
    _8[kind].pushBack(point);
    return true;
}

void Unk_SoundMgr38_20::sub_7101029C98(uking::act::EnvSeEmitPoint* point) {
    if (!point)
        return;
    const s32 kind = point->_83c;
    if (kind < 0 || kind >= 2)
        return;
    auto lock = sead::makeScopedLock(mCS);
    if (_8[kind].indexOf(point) >= 0) {
        point->_84d = 0;
        _8[kind].erase(point);
    }
}

// NON_MATCHING: the existing list API uses a different offset-negation instruction and address-load order.
void Unk_SoundMgr38_20::sub_7101029D3C(sead::OffsetList<uking::act::EnvSeEmitPoint>* points) {
    for (auto& point : *points)
        point.sub_7101029658();
    // The native insertion comparison includes unordered float values.
    points->insertionSort([](const uking::act::EnvSeEmitPoint* a,
                             const uking::act::EnvSeEmitPoint* b) {
        return !(a->_840 <= b->_840);
    });
}

// NON_MATCHING: our build inlines Unk_SoundMgr38_20::sub_7101029BA0 (same file); the original calls it, which
// suggests the _20 class is in another TU.
Unk_SoundMgr38::Unk_SoundMgr38() = default;

Unk_SoundMgr38::~Unk_SoundMgr38() {
    if (_8) {
        delete _8;
        _8 = nullptr;
    }
    if (_10) {
        delete _10;
        _10 = nullptr;
    }
    if (_18) {
        delete _18;
        _18 = nullptr;
    }
    if (_20) {
        delete _20;
        _20 = nullptr;
    }
    if (_80) {
        SoundMgr::instance()->_60->sub_7101059354(_80);
        if (_68)
            _68->setAssetInfoReader(nullptr);
        _80 = nullptr;
        _88 = 0;
    }
    if (_68) {
        _68->destroy();
        _68 = nullptr;
    }
    if (_28) {
        delete _28;
        _28 = nullptr;
    }
    if (_30) {
        delete _30;
        _30 = nullptr;
    }
    if (_38) {
        delete _38;
        _38 = nullptr;
    }
    if (_40) {
        delete _40;
        _40 = nullptr;
    }
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
    if (_50) {
        delete _50;
        _50 = nullptr;
    }
    if (_58) {
        delete _58;
        _58 = nullptr;
    }
    if (_60) {
        delete _60;
        _60 = nullptr;
    }
    _138 = nullptr;
}

// NON_MATCHING: our build inlines the Unk_SoundMgr38_20 constructor (defined above in this TU)
void Unk_SoundMgr38::init(sead::Heap* heap) {
    _8 = new (heap) Unk_SoundMgr38_8;
    _8->sub_710102C388(heap);
    _10 = new (heap) Unk_SoundMgr38_10;
    _10->sub_71010317B4(heap);
    _18 = new (heap) Unk_SoundMgr38_18;
    _18->sub_710102D9C0(heap);
    _20 = new (heap) Unk_SoundMgr38_20;
    _20->sub_7101029958(heap);
    _30 = new (heap) SpeakerBalanceUnifierMgr;
    _30->sub_71010276F0(heap);
    _38 = new (heap) Unk_SoundMgr38_38;
    _38->sub_710103A034(heap);
    _40 = new (heap) Unk_SoundMgr38_40;
    _40->sub_71012BE5F4(heap);
    _70 = false;
}

void Unk_SoundMgr38::sub_710102AEC4() {
    if (_70) {
        if (_8)
            _8->sub_710102C81C();
        if (_10)
            _10->sub_71010333F0();
        if (_18)
            _18->sub_710102EE60();
    }
    if (_20)
        _20->sub_7101029BA0();
    if (_28)
        _28->sub_710103920C();
    if (_30)
        _30->sub_7101027BF8();
    if (_68)
        _68->stopAllEvent(30);
    if (_38)
        _38->sub_710103A084();
    if (_40)
        _40->sub_71012BEC28();
    if (_50)
        _50->sub_7101036840();
    if (_58)
        _58->sub_71010289CC();
    if (_60)
        _60->sub_71012C17B4();
}

// NON_MATCHING: Unk_SoundMgr38_8::sub_710102C8F8 and Unk_SoundMgr38_20::sub_7101029BA8 are inlined in our build (other
// TUs in the original; same as sub_710102AEC4).
void Unk_SoundMgr38::sub_710102AF84() {
    if (_70) {
        if (_8)
            _8->sub_710102C8F8();
        if (_10)
            _10->sub_710103362C();
        if (_18)
            _18->sub_710102EFFC();
    }
    if (_20)
        _20->sub_7101029BA8();
    if (_28)
        _28->sub_710103937C();
    if (_30)
        _30->sub_7101027CE8();
    if (_38)
        _38->sub_710103A294();
    if (_40)
        _40->sub_71012BED18();
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
    if (_50) {
        _50->sub_7101036A68();
        delete _50;
        _50 = nullptr;
    }
    if (_58) {
        _58->sub_7101028690();
        delete _58;
        _58 = nullptr;
    }
    if (_60) {
        _60->sub_71012C167C();
        delete _60;
        _60 = nullptr;
    }
    if (_28) {
        _28->sub_710103937C();
        _28->sub_71010375CC();
        delete _28;
        _28 = nullptr;
    }
    if (_80) {
        SoundMgr::instance()->_60->sub_7101059354(_80);
        if (_68)
            _68->setAssetInfoReader(nullptr);
        _80 = nullptr;
        _88 = 0;
    }
    if (_68) {
        _68->destroy();
        _68 = nullptr;
    }
    _98 = 0;
    _a0 = 0;
    _138 = nullptr;
}

// NON_MATCHING: local vector and terrain-height stack layout differs.
void Unk_SoundMgr38::sub_710102B4B8() {
    sead::Vector3f position = sead::Vector3f::zero;
    f32 distance = 0.0f;
    if (ksys::act::ActorSystem::instance()->getPlayerPosition(&position) &&
        ksys::act::ActorSystem::instance()->getPlayer() &&
        ksys::act::ActorSystem::instance()->getPlayerLink()->m200()) {
        if (auto* placement = ksys::map::PlacementMgr::instance()) {
            if (auto* terrain = placement->mTeraSystem) {
                f32 height = 0.0f;
                const sead::Vector2f xz{position.x, position.z};
                if (ksys::tera::sub_71011094A0(&height, &xz, terrain, -1, 0))
                    distance = position.y - height;
            }
        }
    }
    _130 = distance;
}

Unk_SoundMgr38_28* Unk_SoundMgr38::sub_710102C104() const {
    return _28;
}

Unk_SoundMgr38_28* Unk_SoundMgr38::sub_710102C10C() const {
    if (_70)
        return nullptr;
    return _28;
}

void Unk_SoundMgr38::sub_710102B11C() {
    sub_710102AF84();
}

// NON_MATCHING: only the schedule (the original loads both vectors up front and keeps the six results in
// registers before the stores).
void Unk_SoundMgr38_8::sub_710102C594() {
    if (_68 && _18)
        sub_710102C5AC();
}

// NON_MATCHING: the original stores the zeroed position z before the vtable load (scheduling only).
Unk_71025018c0* Unk_SoundMgr38_8::sub_710102C924() {
    if (!mPositions.isBufferReady())
        return nullptr;
    auto lock = sead::makeScopedLock(mCS);
    auto* position = mPositions.emplaceBack();
    if (position)
        mUnifier->addUnifiable(position);
    return position;
}

void Unk_SoundMgr38_8::sub_710102C9E8(void* handle) {
    if (!handle || !mPositions.isBufferReady())
        return;
    auto* position = static_cast<Unk_71025018c0*>(handle);
    auto lock = sead::makeScopedLock(mCS);
    mUnifier->removeUnifiable(position);
    mPositions.erase(position);
}

void Unk_SoundMgr38_8::sub_710102C8F8() {
    mProcHandle.deleteProc();
    _18 = nullptr;
    _68 = false;
}

void Unk_SoundMgr38_28::sub_7101037ED8(const sead::Vector3f* pos, const sead::Vector3f* size) {
    const sead::Vector3f half = *size * 0.5f;
    mBoxMin = *pos - half;
    mBoxMax = half + *pos;
    mBoxCenter = *pos;
    mBoxSize = *size;
}

void Unk_SoundMgr38_28::sub_7101037F5C(u8 value) {
    _344 = value;
}

void Unk_SoundMgr38_28::sub_7101037F64(bool enabled) {
    _328 = enabled;
    if (!enabled) {
        _3c8 = nullptr;
        _3c0 = nullptr;
    }
}

void Unk_SoundMgr38_28::sub_7101037F7C(bool value) {
    _39c = value;
}

void Unk_710103AC60::start(s32 kind) {
    if (mActive)
        return;
    mType = kind == 1 ? DuckingMgr::DuckerType::cFieldRemainsFire : DuckingMgr::DuckerType::cFieldRemainsOrGanon;
    mActive = true;
}

void Unk_710103AC60::stop() {
    if (!mActive)
        return;
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(mType, false);
    mActive = false;
}

}  // namespace ksys::snd

Unk_7102501910::~Unk_7102501910() = default;

Unk_7102501980::~Unk_7102501980() = default;

Unk_7102501f10::~Unk_7102501f10() = default;
