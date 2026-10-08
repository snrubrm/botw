#include "Game/AI/AI/aiIceMakerBlock.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/gameSceneSubsys14.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxRigidBody.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include <prim/seadStringUtil.h>
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"

namespace uking::ai {

// NON_MATCHING: the original branches `if (_148 > _144) lerp(...); else if (_148 < _144) lerp(...);` (identical calls,
// NaN-safe), ours folds the test into `!=`.
void IceMakerBlock::sub_7100447F20() {
    if (auto* as_list = mActor->getASList()) {
        ksys::as::ASList::Unk4 query;
        f32 value;
        if (as_list->x(0x2f, &query, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true) &&
            sead::StringUtil::tryParseF32(&value, query.name)) {
            _148 = value;
        }
    }
    if (_148 != _144)
        ksys::VFR::lerp(&_144, _148, 0.5f, 2.0f, 0.1f);
}

// NON_MATCHING: store/schedule order of the extents (the original stores extents.y first, between the multiplies)
void IceMakerBlock::sub_7100446FD8(const sead::Vector3f& scale) {
    auto* main_body = sead::DynamicCast<ksys::phys::BoxRigidBody>(mActor->getMainBody());
    if (!main_body)
        return;
    const f32 height = _138.y * scale.y;
    const sead::Vector3f extents(sead::Mathf::clampMin(_138.x * scale.x, 0.5f), height,
                                 sead::Mathf::clampMin(_138.z * scale.z, 0.5f));
    const sead::Vector3f translate(0, height * 0.5f, 0);
    main_body->setTranslate(translate);
    main_body->setExtents(extents);
    auto* water = sead::DynamicCast<ksys::phys::BoxRigidBody>(
        mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), "Water"));
    if (water) {
        water->setTranslate(translate);
        water->setExtents(extents);
    }
}

// NON_MATCHING: register allocation / join of the "no point other than Fall" exit; `goto next` out of the inner loop
// (continue of the body loop) matches
bool IceMakerBlock::sub_71004483E8() {
    for (s32 i = 0; i < 3; ++i) {
        auto* body = _88[i];
        if (!body)
            continue;
        auto* info = body->getContactPointInfo();
        if (!info)
            continue;
        if (info->getNumContactPoints() == 0 || info->begin().isEnd())
            return false;
        auto it = info->begin();
        const auto end = info->end();
        for (; it != end; ++it) {
            const ksys::phys::FloorCode floor = (*it)->material_mask_b.getFloorCode();
            if (int(floor) != ksys::phys::FloorCode::Fall)
                break;
        }
        if (it == end)
            return false;
    }
    return true;
}

IceMakerBlock::IceMakerBlock(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IceMakerBlock::~IceMakerBlock() {
    _78[0] = nullptr;
    _78[1] = nullptr;
    _88[0] = nullptr;
    _88[1] = nullptr;
    _88[2] = nullptr;
}

bool IceMakerBlock::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original loads mActor once before the string for the three loop calls (and
// reloads it for the first call); ours reloads it each time.
bool IceMakerBlock::sub_7100446B0C() {
    _88[0] = nullptr;
    _88[1] = nullptr;
    _88[2] = nullptr;
    sead::FixedSafeString<128> name;
    auto* water = mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), "Water");
    if (!water)
        return false;
    water->setFlag100000();
    for (s32 i = 0; i < 3; ++i) {
        name.format("Water_Break_%d", i);
        auto* body = mActor->findPhysicsBodyByName("Body", name.cstr());
        if (!body)
            return false;
        body->changeFlag100000(true);
        _88[i] = body;
    }
    return true;
}

void IceMakerBlock::enter_(ksys::act::ai::InlineParamPack* params) {
    setDamageCallbackTiming(mActor, 4, &_38);
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A2548()->cstr(), "NPCSensor"))
        body->addToWorld();
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A2548()->cstr(), "PlayerSensor"))
        body->addToWorld();
    _14c = 20.0f;
    _148 = 1.0f;
    _144 = 1.0f;
    _a4 = false;
    _a5 = true;
    _a6 = false;
    sub_7100446DA8();
}

void IceMakerBlock::sub_71004473A8() {
    _a4 = true;
    if (auto* as_list = mActor->getASList())
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163100, 1.0f);
    auto* body = mActor->getMainBody();
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FBA010(false);
    if (body) {
        body->setGravityFactor(1.0f);
        body->setFlag100000();
        body->setAngularVelocity(sead::Vector3f::zero);
        body->setLinearVelocity(sead::Vector3f::zero);
    }
    for (auto* rigid_body : _78) {
        if (rigid_body)
            rigid_body->removeFromWorld();
    }
}

bool IceMakerBlock::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x80000b6)
        mActor->sub_71011D0204(0x80);
    else if (message->getType() == 0x80000b7)
        mActor->sub_71011D0228(0x80);
    else if (message->getType() == 0x8000004)
        sub_71004473A8();
    else
        return false;
    return true;
}

void IceMakerBlock::sub_7100447C8C() {
    auto* body = mActor->findPhysicsBodyByName(sub_71007A2548()->cstr(), "PlayerSensor");
    if (body && body->getCollisionInfo()) {
        if (_a8 != (body->getCollisionInfo()->getCollidingBodies().size() != 0)) {
            const bool state = !_a8;
            _a8 = state;
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&_150._18.mLock);
                _150._18._0 = state;
            }
            _150.sub_710070DBB0(*GameSceneSubsys14::instance()->mTransceiver.getId(), true);
        }
    }
}

// NON_MATCHING: the original computes `&_150` for the sender call between the payload store and the
// lock release (ours materialises it before the lock)
void IceMakerBlock::leave_() {
    sub_71005DA114(mActor, &_38);
    for (auto* body : _78) {
        if (body && body->isAddedToWorld())
            body->removeFromWorld();
    }
    if (!isActorDeletedOrDeleting() && _a8) {
        _a8 = false;
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_150._18.mLock);
            _150._18._0 = false;
        }
        _150.sub_710070DBB0(*GameSceneSubsys14::instance()->mTransceiver.getId(), true);
    }
}

void IceMakerBlock::loadParams_() {
    getStaticParam(&mParams.mSubRigidStartOffset_s, "SubRigidStartOffset");
    getStaticParam(&mParams.mSubRigidEndOffset_s, "SubRigidEndOffset");
    getStaticParam(&mParams.mSubRigidExOffset_s, "SubRigidExOffset");
}

void Unk_71023fd228::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          dmg::DamageCallbackInfo* a6) {
    if (*a5 != 1)
        return;

    auto* damage_manager = sead::DynamicCast<dmg::DamageManager>(mDamageManager);
    ksys::act::ActorConstDataAccess accessor;
    if (damage_manager && ksys::act::acquireActor(damage_manager->m37(), &accessor) &&
        (accessor.hasTag(ksys::act::tags::CanBreakIceMakerBlock) ||
         accessor.hasTag(ksys::act::tags::AncientWeapon))) {
        *a1 = 1;
        *a5 = 34;
    }
}

}  // namespace uking::ai
