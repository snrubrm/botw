#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include <gfx/seadColor.h>
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectEffect.h"
#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Chemical/chmShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/XLink/xlinkChemicalEventState.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actReaction.h"

#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Chemical/chmChemical.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyBox.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyCylinder.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyCapsule.h"
#include "KingSystem/World/worldManager.h"
#include <thread/seadThread.h>

namespace ksys::act {

bool Unk_71024e6428::sub_7100E39BF0(bool force) {
    if (chm::Chemical::instance()->_84 & 1) {
        // The original discards this current-thread lookup result.
        sead::ThreadMgr::instance()->getCurrentThread();
        if (static_cast<const void*>(chm::Chemical::instance()) != this)
            chm::Chemical::instance()->_85 = 100;
    }
    if (_20)
        _20->fade();
    bool removed = true;
    for (const auto& entry : _278) {
        auto* body = entry.body;
        if (force)
            body->removeFromWorldImmediatelyAndResetLinks();
        else
            body->removeFromWorldAndResetLinks();
        removed &= !body->isAddedToWorld();
    }
    if (!removed)
        return false;
    return mChemical.sub_7100D8E87C();
}

Unk_71024e6428::~Unk_71024e6428() {
    if (chm::Chemical::instance()->_84 & 1) {
        // The original discards this lookup, then the full reset repeats its own watch notification.
        sead::ThreadMgr::instance()->getCurrentThread();
        if (static_cast<const void*>(chm::Chemical::instance()) != this)
            chm::Chemical::instance()->_85 = 100;
    }
    sub_7100E39BF0(false);
    for (auto& entry : _278) {
        auto* body = entry.body;
        if (body && entry.owns_body) {
            if (body->isAddedToWorld())
                body->removeFromWorldImmediatelyAndResetLinks();
            delete body;
            entry.body = nullptr;
        }
    }
    _278.freeBuffer();
    if (_20) {
        for (s32 i = 0; i < _20->mHandles.size(); ++i) {
            auto& handles = _20->mHandles[i];
            if (handles.mELink.isActive()) {
                auto* event = static_cast<xlink2::EventELink*>(handles.mELink.getEvent());
                if (auto* delayed = event->mDelayEmitParam._0xf8) {
                    delayed->mActor = nullptr;
                    delayed->mChemical = nullptr;
                }
            }
        }
        delete _20;
        _20 = nullptr;
    }
    world::Manager::instance()->getChemicalMgr()->sub_71010CBEAC(&mChemical);
}



void sub_7100E40448(sead::Vector3f* out, phys::RigidBody* body) {
    if (auto* sphere = sead::DynamicCast<phys::SphereRigidBody>(body)) {
        sphere->getTransformedTranslate(out);
        return;
    }
    if (auto* box = sead::DynamicCast<phys::BoxRigidBody>(body)) {
        box->getTransformedTranslate(out);
        return;
    }
    sead::Vector3f a;
    sead::Vector3f b;
    if (auto* cylinder = sead::DynamicCast<phys::CylinderRigidBody>(body)) {
        cylinder->transformVertices(&a, &b);
    } else if (auto* capsule = sead::DynamicCast<phys::CapsuleRigidBody>(body)) {
        capsule->transformVertices(&a, &b);
    } else {
        *out = body->getCenterOfMassInWorld();
        return;
    }
    *out = (a + b) * 0.5f;
}

// NON_MATCHING: virtual queries, scalar accumulations and branch layout are scheduled differently.
void Unk_71024e6428::sub_7100E3AE40(u32 unused) {
    _28c = 0;
    _294 = 0;
    if (!mActor) {
        _28c = 15.0f;
        _294 = _278(0).body->getVolume();
    } else {
        phys::RigidBody* body;
        if (auto* controller = mActor->getCharacterController()) {
            body = controller->sub_7100F61A34();
        } else {
            body = mActor->getMainBody();
            if (!body) {
                // Both native virtual attribute queries are called even when their results are unused.
                _18->isRigidAttribute3Set(_288);
                _18->isRigidAttribute9Set(_288);
            }
        }
        const f32 mass = body ? body->getMass() : 1.0f;
        const f32 volume = body ? body->getVolume() : 1.0f;
        if (_278.size() < 1) {
            _28c = mass;
            _294 = volume;
        } else {
            for (const auto& entry : _278) {
                auto* body = entry.body;
                if (!body)
                    continue;
                if (_18->isRigidAttribute3Set(_288))
                    _294 += body->getVolume();
                if (_18->isRigidAttribute9Set(_288))
                    _28c = mass;
            }
        }
        if (!_18->isRigidAttribute3Set(_288)) {
            if (_18->isRigidAttribute15Set(_288))
                _294 = volume;
            else
                _294 = _18->getRigidVolume(_288) * _298.x * _298.y * _298.z;
        }
        if (!_18->isRigidAttribute9Set(_288)) {
            if (_18->isRigidAttribute10Set(_288)) {
                _28c = mass * _294 / volume;
            } else {
                _28c = _18->getRigidMass(_288) * _298.x * _298.y * _298.z;
                _290 = _18->getRigidMass(_288);
            }
        }
        if (_294 == 0)
            _294 = _28c * 0.001f;
    }
    _290 = _28c;
    if (!_18->isRigidAttribute9Set(_288) && !_18->isRigidAttribute10Set(_288))
        _290 = _18->getRigidMass(_288);
    for (auto& entry : _278) {
        if (entry.body)
            entry.body->getAabbInLocal(&entry.aabb);
    }
}

// NON_MATCHING: body lookup branches and linked-body selection differ.
void Unk_71024e6428::sub_7100E3B144() {
    if (_278.size() < 1) {
        if (mActor)
            _2a4 = mActor->getMtx().getTranslation();
        else
            _2a4.set(0, 0, 0);
    } else {
        if (!_278(0).body) {
            _2a4 = sead::Vector3f::zero;
            return;
        }
        sead::Vector3f position;
        sub_7100E40448(&position, _278(0).body);
        _2a4 = position;
        if (mChemical._60 && Chemical::sub_7100D9CB54(mChemical._60, &mChemical) &&
            (chm::Chemical::instance()->_84 & 1)) {
            // The original discards this current-thread lookup result.
            sead::ThreadMgr::instance()->getCurrentThread();
            if (static_cast<const void*>(chm::Chemical::instance()) != this)
                chm::Chemical::instance()->_85 = 100;
        }
        if (_278.size() > 0 && _278(0).body) {
            auto* body = _278(0).body;
            if (auto* linked = body->getLinkedRigidBody())
                body = linked;
            _2b0 = body->getLinearVelocity();
            return;
        }
    }
    _2b0.set(0, 0, 0);
}

// NON_MATCHING: the compiler merges repeated property tests and uses different flag selects.
void Unk_71024e6428::sub_7100E3B3F4(Chemical* chemical) {
    const bool metamor = mActor && isMetamorBurnout(mActor);
    _2c4.setDirect(0xffffffff);
    _2c4.change(1, (chemical->mMaterial->attribute.ref() & 1) && !(chemical->_be & 1));
    if (!(chemical->mMaterial->attribute.ref() & 1) || (chemical->_be & 1))
        _2c4.reset(0x80000);
    _2c4.change(0x400, (chemical->mMaterial->attribute.ref() & 1) && !(chemical->_be & 1));
    _2c4.change(2, (chemical->mMaterial->attribute.ref() & 1) && !(chemical->_be & 1) && !metamor);
    _2c4.change(4, (chemical->mMaterial->attribute.ref() & 1) && !(chemical->_be & 1) && metamor);
    _2c4.change(0x40, chemical->mMaterial->attribute.ref() & 0x10);
    _2c4.change(0x80, chemical->mMaterial->attribute.ref() & 0x10);
    _2c4.change(8, (chemical->mMaterial->attribute.ref() & 8) && !(chemical->_be & 4));
    _2c4.change(0x800, (chemical->mMaterial->attribute.ref() & 8) && !(chemical->_be & 4));
    _2c4.change(0x1000, (chemical->mMaterial->attribute.ref() & 8) && !(chemical->_be & 4));
    _2c4.change(0x2000, (chemical->mMaterial->attribute.ref() & 8) && !(chemical->_be & 4));
    _2c4.change(0x4000, chemical->mMaterial->attribute.ref() & 0x8000);
    _2c4.change(0x10, chemical->mMaterial->attribute.ref() & 0x80040);
    _2c4.change(0x20, chemical->mMaterial->attribute.ref() & 0x80040);
    _2c4.change(0x8000, (chemical->mMaterial->attribute.ref() & 8) && !(chemical->_be & 4));
    _2c4.change(0x10000, (chemical->mMaterial->attribute.ref() & 8) && !(chemical->_be & 4));
    _2c4.change(0x20000, (chemical->mMaterial->attribute.ref() & 8) && !(chemical->_be & 4));
    _2c4.change(0x40000, (chemical->mMaterial->attribute.ref() & 8) && !(chemical->_be & 4));
    _2c4.change(0x100, chemical->mMaterial->attribute.ref() & 0x10000);
    _2c4.change(0x200, (chemical->mMaterial->attribute.ref() & 1) && !(chemical->_be & 1));
}

void sub_7100E3F3E8(phys::RigidBody* body, const Chemical* chemical, world::ChemicalMgr* manager) {
    if (chemical->mMaterial->attribute.ref() & 0x90040) {
        body->setSystemGroupHandler(nullptr);
        return;
    }
    if (!manager)
        manager = world::Manager::instance()->getChemicalMgrUnchecked();
    body->setSystemGroupHandler(manager->_a8);
}

namespace {
// The fallback name object at 0x71024e6418 is used when the chemical has no actor.
const sead::SafeString sFarObjName("FarObj");
}

// The body keeps the vtable store of the original, as in upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; }
// (commit 96101229).
Unk_71024e6560::~Unk_71024e6560() {
    ;
}

Unk_71024e6428::Unk_71024e6428()
    : mActor(nullptr),
      mPlacementXLink(nullptr),
      _18(nullptr),
      _20(nullptr),
      _28(nullptr),
      _30(0),
      _34(0),
      _36{},
      _37{},
      _38{},
      _3c(0),
      _288(0),
      _28c(0.0f),
      _290(0.0f),
      _294(0.0f),
      _298(sead::Vector3f::ones),
      _2bc(0),
      _2c0(0),
      _2c4(0),
      _2c8{},
      _2d4(0) {
    _2a4.set(0.0f, 0.0f, 0.0f);
    _2b0.set(0.0f, 0.0f, 0.0f);
}

// NON_MATCHING: the element constructor is defined in this translation unit, so clang inlines it into the
// new[] loop; the original calls it out of line at 0x7100e399c0.
void ActorChemicals::sub_7100E37990(s32 count, sead::Heap* heap) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    _80 = 0;
    if (count < 1)
        return;
    auto* elements = new (heap, 8, std::nothrow) Unk_71024e6428[count];
    if (elements)
        _70.setBuffer(count, elements);
}

// NON_MATCHING: the flag select uses the opposite condition and different temporary registers.
void Unk_71024e6428::sub_7100E3B708(const Unk_71024e6428& other) {
    if (other._30 & 0x800)
        _30 |= 0x800;
    else
        _30 &= ~0x800;
    _20->transferFrom(*other._20);
    for (s32 i = 0; i < _20->mHandles.size(); ++i) {
        auto& handles = _20->mHandles[i];
        if (!handles.mELink.isActive())
            continue;
        auto* event = static_cast<xlink2::EventELink*>(handles.mELink.getEvent());
        auto* delayed = event->mDelayEmitParam._0xf8;
        if (delayed) {
            delayed->mActor = mActor;
            delayed->mChemical = &mChemical;
            delayed->mFlags |= 8;
        }
    }
}

// NON_MATCHING: the two flag selects use different temporary registers and operation order.
void Unk_71024e6428::sub_7100E3AA34(sead::Heap* heap) {
    sub_7100E3AE40(0);
    if (mActor && _28c == 0.0f)
        _28c = 1.0f;
    mChemical.sub_7100D8EA50(heap);
    mChemical.sub_7100D8EABC(&_18->getShape(_288), this);
    if (mActor) {
        if (hasTag(mActor, 0x19f6c13a))
            mChemical._c |= 0x2000000;
        else
            mChemical._c &= ~0x2000000;
        if (hasTag(mActor, 0x2bc52291))
            mChemical._c |= 0x80000;
        else
            mChemical._c &= ~0x80000;
        if (mActor && isFarChemicalActorNameMaybe(mActor->getName()) &&
            map::PlacementMgr::instance() && map::PlacementMgr::instance()->mPlacementActors &&
            mActor->getMapObject()) {
            const auto* entry = mActor->getMapObject()->getActorData().mEffectEntry;
            mPlacementXLink = entry ? entry->mXLink : nullptr;
        }
    }
    const u32 count = _278.size();
    if (count) {
        auto* manager = _28;
        const auto* entries = _278.getBufferPtr();
        for (u32 i = 0; i < count; ++i) {
            sub_7100E3F3E8(entries[i].body, &mChemical, manager);
            entries[i].body->setContactPointInfo(manager->_af0);
        }
    }
    sub_7100E3B144();
    _20 = new (heap, 8) xlink::ChemicalEventState;
    sub_7100E3B3F4(&mChemical);
}

void Unk_71024e6428::sub_7100E3B6D8(phys::UserTag* tag) {
    for (auto& entry : _278) {
        if (entry.owns_body && entry.body)
            entry.body->setUserTag(tag);
    }
}

// NON_MATCHING: actor reloads, RTTI branches and end-sound temporary scheduling differ.
void Unk_71024e6428::sub_7100E3D4E8(u32 kind, bool emit_end) {
    if (!_20)
        return;

    auto& handles = _20->mHandles[kind];
    const u32 mask = 1u << kind;
    if (!(_20->mActiveMask & mask)) {
        if (!mActor || !handles.mELink.isActive() ||
            !sead::IsDerivedFrom<WeaponBase>(mActor) ||
            !static_cast<WeaponBase*>(mActor)->m188())
            return;
        handles.mELink.kill();
        handles.mELink.reset();
        return;
    }

    _20->mActiveMask &= ~mask;
    if (kind == 20)
        kind = _20->mKind;

    bool kill = false;
    if (kind != 15 && kind != 16 && mActor && sead::IsDerivedFrom<WeaponBase>(mActor)) {
        auto* weapon = static_cast<WeaponBase*>(mActor);
        if (weapon->m153() || ((kind == 19 || kind == 0) && weapon->m194())) {
            if (kind == 19 || kind == 0) {
                Unk_71012419b4 emitted;
                _20->sub_710122DE90(mActor, &emitted, nullptr, 10, false, false);
            }
            kill = true;
        }
        if ((kind == 0 || kind == 3 || kind == 14) && weapon->m188())
            kill = true;
    }
    if (kill) {
        handles.mELink.kill();
        handles.mELink.reset();
    } else {
        handles.mELink.fadeIfLoopEffect();
    }

    sead::Vector3f position;
    bool has_position = false;
    if (handles.mSLink.isActive()) {
        // The native call discards getPos's bool result and retains the handle validity instead.
        static_cast<xlink2::EventSLink*>(handles.mSLink.getEvent())->getPos(&position);
        has_position = true;
    }
    handles.mSLink.fadeIfLoopSound();

    if (!emit_end || !mActor || (_30 & 2))
        return;
    const char* name;
    switch (kind) {
    case 3:
        name = "Chemical_Electricity_End";
        break;
    case 12:
        name = "Chemical_ElectricWater_End";
        break;
    case 11:
        name = "Chemical_ElecConnect_End";
        break;
    default:
        return;
    }
    const int type = sub_7101240FE8(mActor);
    auto sound = eft::searchAndEmitSLink(
        type == 1 || type == 2 ? mActor : Reaction::instance()->_38, name, false);
    if (has_position)
        sound.setPosition(position);
}

// NON_MATCHING: the bit-mask load and loop-shift registers are allocated differently.
void Unk_71024e6428::sub_7100E39DF4() {
    for (u32 i = 0; i < 21; ++i) {
        if (_20 && ((_20->mActiveMask & (1u << i)) ||
                    (mActor && _20->mHandles[i].mELink.isActive())))
            sub_7100E3D4E8(i, false);
    }
}

// NON_MATCHING: the three slot tests share different branch tails and actor reloads.
void Unk_71024e6428::m34() {
    if (!_20)
        return;
    if ((_20->mActiveMask & 1) || (mActor && _20->mHandles[0].mELink.isActive()))
        sub_7100E3D4E8(0, false);
    if (!_20)
        return;
    if ((_20->mActiveMask & (1u << 19)) || (mActor && _20->mHandles[19].mELink.isActive()))
        sub_7100E3D4E8(19, false);
    if (_20 && (_20->mKind == 19 || _20->mKind == 0) &&
        ((_20->mActiveMask & (1u << 20)) || (mActor && _20->mHandles[20].mELink.isActive())))
        sub_7100E3D4E8(20, false);
}

Chemical* Unk_71024e6428::sub_7100E3B79C() const {
    if (mActor && mActor->m48())
        return mActor->m48()->getChemicalStuff();
    return nullptr;
}

void Unk_71024e6428::sub_7100E3E2E8() {
    _30 |= 0x2000;
    for (auto& entry : _278)
        entry.body->resetLinkedRigidBody();
}

// NON_MATCHING: translation-only fallback stores are scheduled in a different order.
void Unk_71024e6428::m4(sead::Matrix34f* out, Chemical* chemical) {
    if (_278.size() >= 1) {
        if (auto* body = _278[0].body) {
            body->getTransform(out);
            sead::Matrix34f offset;
            offset.makeT(body->getCenterOfMassInLocal());
            out->setMul(*out, offset);
        }
    } else if (mActor) {
        out->makeT(mActor->getMtx().getTranslation());
    } else {
        out->makeZero();
    }
}

const sead::Vector3f& Unk_71024e6428::m5() const {
    return _2a4;
}

const sead::Vector3f& Unk_71024e6428::m6() const {
    return _2b0;
}

const sead::SafeString& Unk_71024e6428::getName() const {
    return mActor ? mActor->getName() : sFarObjName;
}

bool Unk_71024e6428::m15(u32 a1) const {
    return _30 & 0x100;
}

bool Unk_71024e6428::m16() const {
    return _30 & 0x2;
}

bool Unk_71024e6428::m17() const {
    return mActor && mActor->getActorFlags2().isOn(Actor::ActorFlag2::_40);
}

bool Unk_71024e6428::m18() const {
    if (_278.size() < 1)
        return false;
    for (auto& entry : _278) {
        if (auto* body = entry.body) {
            if (!body->isAddedToWorld() && !body->isAddingBodyToWorld())
                return false;
        }
    }
    return true;
}

bool Unk_71024e6428::m19() const {
    return mActor && mActor->isSleep();
}

bool Unk_71024e6428::m20() const {
    for (const auto& entry : _278) {
        if (entry.body) {
            switch (entry.body->getContactLayer()) {
            case phys::ContactLayer::SensorHitOnlyInDoor:
            case phys::ContactLayer::SensorNoHit:
                return true;
            default:
                return false;
            }
        }
    }
    return true;
}

bool Unk_71024e6428::m21() const {
    return false;
}

f32 Unk_71024e6428::m23() const {
    return _28c;
}

f32 Unk_71024e6428::m24() const {
    return _290;
}

f32 Unk_71024e6428::m26() const {
    return _294;
}

void Unk_71024e6428::m27(f32 value) {
    _28c = value;
}

bool Unk_71024e6428::m22(u32 a1) const {
    return !(_30 & 0x30);
}

f32 Unk_71024e6428::m25() const {
    if (mActor) {
        if (auto* body = mActor->getMainBody())
            return body->getMass();
    }
    return 1.0f;
}

// NON_MATCHING: the original loads `mActor` before the virtual m5() call (the null test comes after it) and reloads it
// inside the branch
bool Unk_71024e6428::m28() {
    return sub_7100E41470(m5(), mActor ? mActor->getPhysics()->get188(0) : nullptr);
}

f32 Unk_71024e6428::m30(const void* a1) {
    f32 sum = 0;
    for (auto& entry : _278)
        sum += sub_7100E40B7C(entry.body, a1, &entry.aabb);
    return sum;
}

bool Unk_71024e6428::m31() {
    return !_18->isRigidAttribute16Set(_288);
}

bool Unk_71024e6428::m33() {
    if (mChemical._c0 == 2 && mActor) {
        if (mActor->getName() == "FireWoodFromBundle") {
            mChemical.sub_7100D90B78();
            return true;
        }
    }
    return false;
}

// NON_MATCHING: the original loads `_288` before the slot of the virtual call (scheduling only)
bool Unk_71024e6428::m36() {
    if ((_30 & 0x10000) || !(_3c & 0x1))
        return true;
    if (!_18->isRigidAttribute6Or14Set(_288) && !(_3c & 0x100000))
        return true;
    return _30 & 0x8000;
}

ActorChemicals::ActorChemicals() = default;

// NON_MATCHING: the loop-end element count is widened before addition.
void ActorChemicals::init2(Unk_7101265a6c* state) {
    const auto lock = sead::makeScopedLock(mCS);
    for (int i = 0; i < _58.size() + _80; ++i) {
        if (auto* element = getElement_(i))
            element->mChemical._68 = state;
    }
}

Unk_71024e6428* ActorChemicals::sub_7100E3718C(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    if (_58.size() + _80 < 1)
        return nullptr;
    if (idx < _58.size())
        return &_58[idx];
    return &_70[idx - _58.size()];
}

Unk_71024e6428* ActorChemicals::sub_7100E37FA8(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    if (_58.size() + _80 < 1)
        return nullptr;
    if (idx < _58.size())
        return &_58[idx];
    return &_70[idx - _58.size()];
}

// NON_MATCHING: the original's null path skips the conversion (branch target only)
Chemical* ActorChemicals::sub_7100E37788(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    auto* element = getElement_(idx);
    if (!element)
        return nullptr;
    return &element->mChemical;
}

// NON_MATCHING: the original's null path skips the conversion (branch target only)
Chemical* ActorChemicals::getStuff(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    auto* element = getElement_(idx);
    if (!element)
        return nullptr;
    return &element->mChemical;
}

// NON_MATCHING: inlined getStuff null-path branch and loop sum width differ.
void ActorChemicals::sub_7100E37CE4() {
    const auto lock = sead::makeScopedLock(mCS);
    for (s32 i = 0; i < _58.size() + _80; ++i) {
        const auto* element = sub_7100E3718C(i);
        if (!element || !element->_18)
            continue;
        const auto* root = element->_18;
        const u32 index = element->_288;
        if (root->rigidHasBurnOutTime(index)) {
            const f32 time = root->getRigidBurnOutTime(index);
            getStuff(i)->sub_7100D91390(time);
        }
    }
}

// 0x7100e39458: true when an element whose rigid has attribute 4 set has chemical state 3; false
// as soon as such an element is in another state.
// NON_MATCHING: the original looks the element up twice (the second getStuff result is only tested
// for null) and tests the first pointer before the second lookup; our clang merges the two inlined
// lookups and folds the Chemical offset into the state read.
bool ActorChemicals::sub_7100E39458() {
    const auto lock = sead::makeScopedLock(mCS);
    if (_58.size() < 1 || _58.size() + _80 < 1)
        return false;

    bool found = false;
    s32 i = 0;
    do {
        const auto* element = getElement_(i);
        if (!element)
            continue;
        if (!getStuff(i))
            continue;
        if (!element->_18->isRigidAttribute4Set(element->_288))
            continue;
        if (element->mChemical._c0 != 3)
            return false;
        found = true;
    } while (++i < _58.size() + _80);
    return found;
}

Chemical* ActorChemicals::sub_7100E380FC(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    if (idx < 0 || idx >= _70.size())
        return nullptr;
    return &_70[idx].mChemical;
}

Chemical* ActorChemicals::sub_7100E3816C(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    if (idx < 0 || idx >= _70.size())
        return nullptr;
    return &_70[idx].mChemical;
}

// NON_MATCHING: same as getStuff (the null path of the inlined element lookup branches to a different unlock)
Chemical* ActorChemicals::sub_7100E381DC(const sead::SafeString& name) {
    const auto lock = sead::makeScopedLock(mCS);
    const s32 idx = sub_7100E382C4(name);
    if (idx == -1)
        return nullptr;
    return getStuff(idx);
}

// NON_MATCHING: the ordinary loop omits the original callback result flags and uses a wider end-count sum.
s32 ActorChemicals::sub_7100E382C4(const sead::SafeString& name) {
    const auto lock = sead::makeScopedLock(mCS);
    for (s32 i = 0; i < _58.size() + _80; ++i) {
        if (auto* element = getElement_(i)) {
            if (element->mChemical.mShape->getName() == name)
                return i;
        }
    }
    return -1;
}

// NON_MATCHING: the original keeps the null check of the element and loads the body count without sign extension
bool ActorChemicals::sub_7100E384C4(const phys::RigidBody* body, int idx) {
    if (idx < 0 || idx >= _58.size() + _80)
        return false;
    Unk_71024e6428* element;
    if (idx < _58.size())
        element = &_58[idx];
    else
        element = &_70[idx - _58.size()];
    if (!element)
        return false;
    for (s32 i = 0; i < element->_278.size(); ++i) {
        if (element->_278[i].body == body)
            return true;
    }
    return false;
}

// NON_MATCHING: existing getStuff null conversion, loop count width and register allocation differ.
void ActorChemicals::sub_7100E38588(u32 value) {
    const auto lock = sead::makeScopedLock(mCS);
    _68 = value;
    for (s32 i = 0; i < _58.size() + _80; ++i) {
        auto* element = getElement_(i);
        if (element) {
            if (auto* chemical = getStuff(i)) {
                if (!_50->isRigidAttribute13Set(element->_288))
                    chemical->sub_7100D8EAB4(value);
            }
        }
    }
}

// NON_MATCHING: same as getStuff (the original's null path of the inlined element lookup unlocks once and shares the
// outer unlock; the loop counters also use other registers)
void ActorChemicals::sub_7100E39614(bool on) {
    const auto lock = sead::makeScopedLock(mCS);
    for (s32 i = 0; i < _58.size() + _80; ++i) {
        if (auto* chemical = getStuff(i))
            chemical->sub_7100D91098(on);
    }
}

// NON_MATCHING: body iteration and event-slot traversal are scheduled differently.
void Unk_71024e6428::m10() {
    for (const auto& entry : _278) {
        auto* body = entry.body;
        if (body && entry.owns_body &&
            (body->isAddedToWorld() || !body->isRemovingBodyFromWorld()))
            body->removeFromWorld();
    }
    for (u32 i = 0; i < 21; ++i) {
        if (_20 && ((_20->mActiveMask & (1u << i)) ||
                    (mActor && _20->mHandles[i].mELink.isActive())))
            sub_7100E3D4E8(i, false);
    }
    _2d4 = 0;
    _38 = 0;
}

// NON_MATCHING: color construction and body traversal are scheduled differently.
void Unk_71024e6428::m11() {
    for (const auto& entry : _278) {
        auto* body = entry.body;
        if (!body || body->getContactLayer() == phys::ContactLayer::SensorNoHit ||
            !body->isAddedToWorld())
            continue;
        sead::Color4f color(0, 0, 0, 1);
        sead::Color4f overlay(0.5f, 0.5f, 0.5f, 0.1f);
        if (mChemical._b8 & 4)
            color = sead::Color4f(1, mChemical._1b8 > 0 ? 0.7f : 0, 0, 1);
        else if (mChemical._1b8 > 0)
            color = sead::Color4f(1, 1, 0, 1);
        if (mChemical._bc & 0x300)
            overlay = sead::Color4f(1, 1, 1, 1);
        body->setColor(color, &overlay, true);
    }
}

// NON_MATCHING: debug-name temporaries and formatting branches differ.
void Unk_71024e6428::m14(sead::BufferedSafeString* out) const {
    if (!mActor) {
        out->appendWithFormat("(FarObj)");
        return;
    }
    const s32 count = _278.size();
    const char* actor_name = mActor->getName().cstr();
    if (count > 0) {
        const auto& entry = _278[0];
        const char* set_name = entry.body_set ? entry.body_set->getName().cstr() : "(null)";
        const sead::SafeString body_name = entry.original_body ?
            entry.original_body->getHkBodyName() : sead::SafeString("(null)");
        out->appendWithFormat("%s (%d: %s, %s) %s", actor_name, count, set_name,
                              body_name.cstr(), entry.owns_body ? "[Chm剛体生成]" : "");
    } else {
        out->appendWithFormat("%s (no rigid)", actor_name);
    }
}

// NON_MATCHING: runtime casts, parent tests and radius-reset loops differ.
void Unk_71024e6428::m32(bool on) {
    if (!on || !mActor || !sead::IsDerivedFrom<WeaponBase>(mActor))
        return;
    auto* weapon = static_cast<WeaponBase*>(mActor);
    if (!weapon->hasParentActor())
        return;
    if ((mChemical._c & 0x40) && weapon->hasParentActor()) {
        for (const auto& entry : _278) {
            if (auto* capsule = sead::DynamicCast<phys::CapsuleRigidBody>(entry.body))
                capsule->setRadius(mChemical._60->sub_7100D9A19C());
            else if (auto* sphere = sead::DynamicCast<phys::SphereRigidBody>(entry.body))
                sphere->setRadius(mChemical._60->sub_7100D9A19C());
        }
    } else {
        for (const auto& entry : _278) {
            if (auto* capsule = sead::DynamicCast<phys::CapsuleRigidBody>(entry.body))
                capsule->setRadius(entry.original_radius);
            else if (auto* sphere = sead::DynamicCast<phys::SphereRigidBody>(entry.body))
                sphere->setRadius(entry.original_radius);
        }
    }
}

bool Unk_71024e6428::m35() {
    return mActor && (mActor->getName() == "Weapon_Lsword_035" ||
                      mActor->getName() == "Weapon_Spear_035" ||
                      mActor->getName() == "Weapon_Sword_035");
}

void Unk_71024e6428::m7() {
    if (_30 & 2)
        _30 |= 4;
    if (mActor && mActor->sub_71011D8F44()) {
        _30 |= 2;
        if (mChemical._60->sub_7100D9D520())
            mActor->sub_71011D8F44();  // The native callback discards this second result.
    } else {
        _30 &= ~2u;
    }
    sub_7100E3B87C();
    sub_7100E3B144();
    _2bc = -1;
    sub_7100E3BE78();
}

// NON_MATCHING: stationary counters and sensor-layer loops are scheduled differently.
void Unk_71024e6428::sub_7100E3BE78() {
    if (_30 & 0x10)
        _30 |= 0x20;
    else
        _30 &= ~0x20u;
    u8 stationary_frames = _37;
    if (_2b0.equals(sead::Vector3f::zero, 0.05f)) {
        if (stationary_frames != 0xff)
            ++stationary_frames;
    } else {
        stationary_frames = 0;
    }
    _37 = stationary_frames;
    if (mChemical._60 && !(mChemical._60->_c8 & 0x180000) && _38 != 0xff)
        ++_38;
    auto* placement = map::PlacementMgr::instance();
    if (placement && !placement->isStaticCompoundReady(m5(), false))
        _38 = 0;
    if (stationary_frames < 11 || _38 < 11) {
        if (!(_30 & 0x10))
            return;
        for (s32 i = 0; i < _278.size(); ++i) {
            _278[i].body->clearSensorReceiverIgnoredLayer();
            _278[i].body->setMotionFlag(phys::RigidBody::MotionFlag::_20000);
        }
        _30 &= ~0x10u;
    } else {
        if (_30 & 0x10)
            return;
        for (s32 i = 0; i < _278.size(); ++i)
            _278[i].body->setSensorReceiverIgnoredLayer(phys::ContactLayer::SensorInDoor);
        _30 |= 0x10;
    }
}

f32 sub_7100E40698(phys::RigidBody* body) {
    if (auto* sphere = sead::DynamicCast<phys::SphereRigidBody>(body))
        return sphere->getRadius();
    if (auto* cylinder = sead::DynamicCast<phys::CylinderRigidBody>(body))
        return cylinder->getRadius();
    if (auto* capsule = sead::DynamicCast<phys::CapsuleRigidBody>(body))
        return capsule->getRadius();
    return 1.0f;
}

// NON_MATCHING: link synchronization, watch notifications and world-transition scheduling differ.
void Unk_71024e6428::sub_7100E3B87C() {
    _30 &= ~0x100u;
    if (!mActor) {
        const f32 previous_mass = _28c;
        const f32 previous_volume = _294;
        sub_7100E3AE40(0);
        if (previous_mass != _28c || previous_volume != _294)
            mChemical.sub_7100D97578();
        return;
    }
    if (_30 & 0x2000) {
        for (const auto& entry : _278) {
            auto* body = entry.body;
            if (!body || !entry.owns_body)
                continue;
            auto* original = entry.original_body;
            if (original->hasFlag(phys::RigidBody::Flag::_4)) {
                body->removeFromWorldAndResetLinks();
            } else if (!(_30 & 0x1000)) {
                const bool original_added = original->isAddedToWorld();
                const bool body_added = body->isAddedToWorld();
                if (!original_added) {
                    if (body_added || body->isAddingBodyToWorld())
                        body->removeFromWorld();
                } else if (!body_added && !body->isAddingBodyToWorld()) {
                    body->addToWorld();
                }
            }
        }
        return;
    }
    for (const auto& entry : _278) {
        auto* body = entry.body;
        if (body) {
            auto* original = entry.original_body;
            auto* linked = body->getLinkedRigidBody();
            if (entry.owns_body) {
                if (!linked) {
                    if (!original->isAddedToWorld() || !body->isAddedToWorld() ||
                        mActor->getPhysics()->getFlags().isOn(phys::InstanceSet::Flag::_8)) {
                        if (mChemical._60 && Chemical::sub_7100D9CB54(mChemical._60, &mChemical) &&
                            (chm::Chemical::instance()->_84 & 1)) {
                            sead::ThreadMgr::instance()->getCurrentThread();
                            if (static_cast<const void*>(chm::Chemical::instance()) != this)
                                chm::Chemical::instance()->_85 = 100;
                        }
                        const sead::Matrix34f transform = original->getTransform();
                        body->setTransform(transform, phys::PropagateToLinkedMotions{true});
                        _30 |= 0x100;
                    } else {
                        if (mChemical._60 && Chemical::sub_7100D9CB54(mChemical._60, &mChemical) &&
                            (chm::Chemical::instance()->_84 & 1)) {
                            sead::ThreadMgr::instance()->getCurrentThread();
                            if (static_cast<const void*>(chm::Chemical::instance()) != this)
                                chm::Chemical::instance()->_85 = 100;
                        }
                        const sead::Matrix34f transform = original->getTransform();
                        body->changePositionAndRotation(transform, 1.1920929e-07f);
                    }
                } else if (!body->isAddedToWorld()) {
                    if (mChemical._60 && Chemical::sub_7100D9CB54(mChemical._60, &mChemical) &&
                        (chm::Chemical::instance()->_84 & 1)) {
                        sead::ThreadMgr::instance()->getCurrentThread();
                        if (static_cast<const void*>(chm::Chemical::instance()) != this)
                            chm::Chemical::instance()->_85 = 100;
                    }
                    const sead::Matrix34f transform = body->getLinkedRigidBody()->getTransform();
                    body->setTransform(transform, phys::PropagateToLinkedMotions{true});
                    _30 |= 0x100;
                }
                body->setScale(original->getScale() / entry.original_scale);
                if (original->hasFlag(phys::RigidBody::Flag::_4)) {
                    body->removeFromWorldAndResetLinks();
                } else if (!(_30 & 0x1000)) {
                    const bool original_added = original->isAddedToWorld();
                    const bool body_added = body->isAddedToWorld();
                    if (!original_added) {
                        if (body_added || body->isAddingBodyToWorld()) {
                            if (mChemical._60 && Chemical::sub_7100D9CB54(mChemical._60, &mChemical) &&
                                (chm::Chemical::instance()->_84 & 1)) {
                                sead::ThreadMgr::instance()->getCurrentThread();
                                if (static_cast<const void*>(chm::Chemical::instance()) != this)
                                    chm::Chemical::instance()->_85 = 100;
                            }
                            body->removeFromWorld();
                        }
                    } else if (!body_added && !body->isAddingBodyToWorld()) {
                        if (mChemical._60 && Chemical::sub_7100D9CB54(mChemical._60, &mChemical) &&
                            (chm::Chemical::instance()->_84 & 1)) {
                            sead::ThreadMgr::instance()->getCurrentThread();
                            if (static_cast<const void*>(chm::Chemical::instance()) != this)
                                chm::Chemical::instance()->_85 = 100;
                        }
                        body->addToWorld();
                    }
                }
                continue;
            }
        }
        auto* tag = sead::DynamicCast<PhysicsUserTag>(body->getUserTag());
        auto* actor = tag ? tag->getActor(nullptr, nullptr) : nullptr;
        if (!actor)
            continue;
        if (actor->getPhysics() &&
            actor->getPhysics()->getFlags().isOn(phys::InstanceSet::Flag::_8))
            _30 |= 0x100;
        auto* controller = actor->getCharacterController();
        if (controller && !entry._19) {
            if (!controller->sub_7100F61A34()->isAddedToWorld()) {
                if (body->getLinkedRigidBody())
                    body->resetLinkedRigidBody();
                const bool propagate = actor->getPhysics()->getFlags().isOn(phys::InstanceSet::Flag::_8);
                const sead::Matrix34f transform = controller->sub_7100F61A34()->getTransform();
                if (!propagate)
                    body->changePositionAndRotation(transform, 1.1920929e-07f);
                else
                    body->setTransform(transform, phys::PropagateToLinkedMotions{true});
            } else {
                body->setLinkedRigidBody(controller->sub_7100F61A34());
            }
        }
    }
    if (_298 != mActor->getScale()) {
        _298 = mActor->getScale();
        sub_7100E3AE40(0);
        mChemical.sub_7100D97578();
    }
}

}  // namespace ksys::act

namespace ksys::xlink {

ChemicalEventState::ChemicalEventState() = default;

}  // namespace ksys::xlink
