#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <aal/aalShape.h>
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleShape.h"
#include <math/seadMatrix.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemicalUserTag.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/System/VFR.h"

Unk_710250c530::Unk_710250c530() = default;

Unk_710250c530::~Unk_710250c530() {
    if (_10) {
        if (_10->isAddedToWorld())
            _10->removeFromWorldImmediately(nullptr);
        delete _10;
        _10 = nullptr;
    }
}

Unk_710250c698::Unk_710250c698() = default;

Unk_710250c698::~Unk_710250c698() {
    if (_18) {
        if (_18->isAddedToWorld())
            _18->removeFromWorldImmediately(nullptr);
        delete _18;
        _18 = nullptr;
    }
}

Unk_710250c6b8::~Unk_710250c6b8() {
    if (_10) {
        if (_10->isAddedToWorld())
            _10->removeFromWorldImmediately(nullptr);
        delete _10;
        _10 = nullptr;
    }
    if (_50) {
        _50->destroy();
        _50 = nullptr;
    }
}

// NON_MATCHING: endpoint stores and parameter assignment scheduling differ.
void Unk_710250c6b8::sub_71010C6304(sead::Heap* heap) {
    ksys::phys::CapsuleParam param;
    param.vertex_a = sead::Vector3f::zero;
    param.vertex_b = sead::Vector3f::ey;
    param.radius = 4.0f;
    param.contact_layer = ksys::phys::ContactLayer::SensorChemicalElement;
    param.name = "Tornado";
    param.motion_type = ksys::phys::MotionType::Keyframed;
    _10 = ksys::phys::CapsuleRigidBody::make(&param, heap);
    if (_10) {
        _50 = aal::ShapeCapsule::create("Updraft", heap);
        if (_50) {
            _50->mFlags.resetBit(aal::Shape::KeepPosition);
            _50->mFlags.resetBit(aal::Shape::KeepRotation);
        }
    }
}

// NON_MATCHING: the entry constructor inlines into allocation; loop registers differ.
void Unk_71010cb1f0::sub_71010CB1F0(s32 count, sead::Heap* heap) {
    entries.tryAllocBuffer(count, heap, 8);
    free.allocBuffer(count, heap, 8);
    used.allocBuffer(count, heap, 8);
    for (auto& entry : entries)
        free.pushBack(&entry);
}

f32 Unk_710250c880::getVolumeOccupancy() const {
    return 1.0f;
}

f32 Unk_710250c880::getElementOcclusion() const {
    return 1.0f;
}

const ksys::chm::IShape& Unk_710250c8b0::getShape(int idx) const {
    return _8;
}

// The original keeps the vtable store that an empty destructor would drop: `{ ; }` as in upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
Unk_710250cac8::~Unk_710250cac8() {
    ;
}

namespace ksys::world {

// NON_MATCHING: placeholder; the original destructor (0x71010ca33c) frees the pools and phys handlers first.
ChemicalMgr::~ChemicalMgr() = default;

// The three overriders of Unk_710250cac8 are inline in the original: the vtable group at +0x20 has copies of
// their bodies (0x71010cc0e8, 0x71010cc1a8, 0x71010cc244) instead of branches to them.
inline void ChemicalMgr::m3(const sead::Vector3f* pos) {
    act::ActorConstDataAccess accessor;
    act::acquireActor(&_d88, &accessor);
    sead::Matrix34f mtx = sead::Matrix34f::ident;
    mtx.setTranslation(*pos);
    accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
}

inline void ChemicalMgr::m4() {
    _b10 = 0;
}

inline void* ChemicalMgr::m2(void* arg) {
    if (!_ae8)
        return nullptr;
    Unk_ChemicalMgrM2Arg m2_arg{arg, _ae8};
    return sub_71010CBF7C(_ae8, &m2_arg);
}

void ChemicalMgr::initBeforeStageGen() {
    sead::ScopedLock<sead::CriticalSection> lock(&mChemicalPairLock);
    _cf8.sub_71010C9B48();
    _ae8->sub_7100D9AA84();
    mChemicalPairs.clear();
    sub_71010CB39C();
}

void ChemicalMgr::unload2() {
    sead::ScopedLock<sead::CriticalSection> lock(&mChemicalPairLock);
    act::ActorConstDataAccess accessor;
    act::acquireActor(&_d88, &accessor);
    if (accessor.isStateCalc())
        accessor.sleep(act::BaseProc::SleepWakeReason::_0);
    _cf8.sub_71010C9CFC();
    mChemicalPairs.clear();
    if (_ae8) {
        auto* terrain = ksys::tera::Terrain::instance();
        if (terrain && terrain->isGrassEnabled())
            ksys::tera::sub_71011501C8(terrain->sub_710114DE4C());
        sub_71010CB39C();
        _ae8->sub_7100D9AAE4();
    }
}


void ChemicalMgr::sub_71010CC5AC() {
    _cf8.sub_71010C9438();
}

bool ChemicalMgr::x_4() const {
    return _b10 < 10;
}

void ChemicalMgr::x_5(ksys::act::Actor* actor) {
    _cf8.sub_71010C9D00(actor);
}

void ChemicalMgr::x_7(ksys::act::Actor* actor) {
    _cf8.sub_71010C9E48(actor);
}

Unk_710250c698* ChemicalMgr::x_8() {
    sead::ScopedLock<sead::CriticalSection> lock(&_c10.lock);
    auto* entry = _c10.free.popBack();
    if (entry)
        _c10.used.pushBack(entry);
    return entry;
}

// NON_MATCHING: indexOf uses a signed count loop rather than the original pointer countdown.
bool ChemicalMgr::x_9(Unk_710250c698* entry) {
    entry->_8 &= ~1u;
    sead::ScopedLock<sead::CriticalSection> lock(&_c10.lock);
    const s32 index = _c10.used.indexOf(entry);
    if (index >= 0) {
        _c10.used.erase(index);
        _c10.free.pushBack(entry);
    }
    return true;
}

void ChemicalMgr::sub_71010CBDCC(act::Chemical* first, act::Chemical* second, s32 type) {
    sead::ScopedLock<sead::CriticalSection> lock(&mChemicalPairLock);
    if (mChemicalPairs.isFull())
        return;
    // Original pair types are stored and compared as bytes, including the input truncation.
    const u8 pair_type = type;
    for (const auto& pair : mChemicalPairs) {
        if (pair.first == first && pair.second == second && pair.type == pair_type)
            return;
    }
    auto* pair = mChemicalPairs.emplaceBack();
    pair->type = pair_type;
    pair->first = first;
    pair->second = second;
}

// NON_MATCHING: iterator advancement uses the entry pointer rather than the node pointer.
void ChemicalMgr::sub_71010CBEAC(act::Chemical* chemical) {
    sead::ScopedLock<sead::CriticalSection> lock(&mChemicalPairLock);
    for (auto it = mChemicalPairs.begin(); it != mChemicalPairs.end();) {
        auto* pair = &*it;
        ++it;
        if (pair->first == chemical || pair->second == chemical)
            mChemicalPairs.erase(pair);
    }
}

void ChemicalMgr::sub_71010CE760() {
    sub_71010CE7DC(VFR::instance() ? VFR::instance()->getDeltaFrame() : 1.0f);
}

// NON_MATCHING: the queued pair value is copied before the counter increment, and iterator
// advancement uses the entry pointer rather than the native node pointer.
void ChemicalMgr::sub_71010CE7DC(f32 delta_frame) {
    sead::ScopedLock<sead::CriticalSection> lock(&mChemicalPairLock);
    for (const auto pair : mChemicalPairs) {
        ++_d9c;
        if (_b14.isOn(0x100000)) {
            pair.first->sub_7100D9155C();
            pair.second->sub_7100D9155C();
            pair.first->_18->getName().cstr();
            pair.second->_18->getName().cstr();
        }
        if (pair.type == 4) {
            if (pair.first->_1e8)
                pair.first->_1e8->sub_7100D8D3F4(pair.second, true, true, false, delta_frame,
                                               sead::Vector3f::zero, sead::Vector3f::ex);
            if (pair.second->_1e8)
                pair.second->_1e8->sub_7100D8D3F4(pair.first, true, true, false, delta_frame,
                                                sead::Vector3f::zero, sead::Vector3f::ex);
        }
    }
    mChemicalPairs.clear();
}

act::ActorChemicals* sub_71010CE968(const phys::UserTag* tag) {
    if (sead::IsDerivedFrom<act::PhysicsUserTag>(tag)) {
        auto* actor = static_cast<const act::PhysicsUserTag*>(tag)->getActor(nullptr, nullptr);
        if (actor && actor->getChemicalContainer())
            return actor->getChemicalContainer();
    } else if (sead::IsDerivedFrom<ChemicalUserTag>(tag)) {
        return static_cast<const ChemicalUserTag*>(tag)->mActorChemicals;
    }
    return nullptr;
}

}  // namespace ksys::world
