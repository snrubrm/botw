#include "Game/Actor/AI/aiLynelRoot.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/Actor/aiUnk_PartsActorDelete.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

void Unk_7102406048::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) {
    if (mDamageManager->mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40))
        return;
    if (u32(*a5 - 3) > 25)
        return;
    auto* info = sead::DynamicCast<act::DamageCallbackInfo>(a6);
    if (info && (info->mFlags & 1))
        *a5 = 2;
}

LynelRoot::LynelRoot(const InitArg& arg) : EnemyRoot(arg) {}

LynelRoot::~LynelRoot() {
    if (auto* parts = mActor->m101()) {
        if (!mBreathActorName_s.isEmpty()) {
            deleteActorParts(parts, mBreathPartsKey0_s);
            deleteActorParts(parts, mBreathPartsKey1_s);
            deleteActorParts(parts, mBreathPartsKey2_s);
        }
        if (!mRoarFlameActorName_s.isEmpty())
            deleteActorParts(parts, mRoarFlamePartsKey_s);
    }
}

// NON_MATCHING: the original keeps three separate `return false` blocks and orders the SafeString temporaries of
// setAITreeVariable differently.
bool LynelRoot::init_(sead::Heap* heap) {
    if (!EnemyRoot::init_(heap))
        return false;

    auto* parts = mActor->m101();
    if (!parts)
        return false;

    if (!mBreathActorName_s.isEmpty()) {
        if (!parts->sub_7100D3CED8(mBreathPartsKey0_s, heap) ||
            !parts->sub_7100D3CED8(mBreathPartsKey1_s, heap) ||
            !parts->sub_7100D3CED8(mBreathPartsKey2_s, heap)) {
            return false;
        }

        ksys::act::InstParamPack pack;
        ksys::act::ActorCreator::setCreatePriorityState1(pack, mActor);
        const sead::SafeString* keys = &mBreathPartsKey0_s;
        for (s32 i = 0; i < 3; ++i) {
            auto* actor = ksys::act::ActorCreator::instance()->createActor(
                mBreathActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack,
                true, false);
            if (actor) {
                if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor)) {
                    bullet->_bd0._0.acquire(mActor, false);
                    bullet->sub_71000048BC(mActor);
                    bullet->sub_710000497C(mActor);
                    bullet->getRootAi()->getMapUnitParams().setAITreeVariable(
                        "IsReuseActor", ksys::AIDefParamType::Bool, true);
                }
                parts->sub_7100D3D108(keys[i], actor);
            } else if (!sub_71005D6D10()) {
                return false;
            }
        }
    }

    if (!mRoarFlameActorName_s.isEmpty()) {
        if (!parts->sub_7100D3CED8(mRoarFlamePartsKey_s, heap))
            return false;

        ksys::act::InstParamPack pack;
        ksys::act::ActorCreator::setCreatePriorityState1(pack, mActor);
        auto* actor = ksys::act::ActorCreator::instance()->createActor(
            mRoarFlameActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, true,
            false);
        if (actor) {
            if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor)) {
                bullet->_bd0._0.acquire(mActor, false);
                bullet->sub_71000048BC(mActor);
                bullet->sub_710000497C(mActor);
                bullet->getRootAi()->getMapUnitParams().setAITreeVariable(
                    "IsReuseActor", ksys::AIDefParamType::Bool, true);
                bullet->getRootAi()->getMapUnitParams().setAITreeVariable(
                    "ScaleTime", ksys::AIDefParamType::Float, 10.0f);
            }
            parts->sub_7100D3D108(mRoarFlamePartsKey_s, actor);
        } else if (!sub_71005D6D10()) {
            return false;
        }
    }

    _2c8.sub_710070F32C(heap, mActor, mStandBoneName_s);
    _2c8._10 = *mBoneStandAddRatio_s;
    *static_cast<Unk_71025afb58**>(mLynelBodyControlUnit_a) = &_2c8;
    *static_cast<Unk_71025c89e8**>(mLynelMoveParam_a) = &_278;
    return true;
}

// NON_MATCHING: the original reloads `mActor` at the top of each iteration of the weapon loop and once more after it;
// we load it once at the end of the loop body (loop rotation + load merging)
void LynelRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _2c8.sub_710070F350(mActor);
    sub_71005DDA44(mActor);
    ksys::act::disableAttClient(mActor, "HornAttackRide");
    ksys::act::disableAttClient(mActor, "Ride");
    if (mActor->getRootAi()->getI() != 5 && *mIsNearCreate_m)
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);

    const s32 count = sub_71005D7854(mActor);
    if (count >= 1) {
        s32 i = 0;
        do {
            sub_71005DB6D0(mActor, i);
            ++i;
        } while (i != count);
    }

    {
        auto* actor = mActor;
        if (auto* controller = actor->getCharacterController()) {
            if (auto* as_list = actor->getASList()) {
                sead::Vector3f velocity;
                if (!controller->sub_7100F5F234(&velocity))
                    velocity = sead::Vector3f::ey;
                as_list->sub_710115F024(velocity, 0);
            }
        }
    }
    if (auto* body = mActor->getMainBody())
        body->clearEntityMotionFlag10(false);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F631B8(true);
    sub_7100721670(&_4a0, mActor, "BodyFrontLeg");
    EnemyRoot::enter_(params);
}

// NON_MATCHING: the first riding-state enum temporary uses a different stack slot.
void LynelRoot::calc_() {
    sub_71003B5644();
    sub_710049AEA0();
    if (auto* as_list = mActor->getASList()) {
        if (auto* rideable = mActor->getHorseOptionsMaybe()) {
            const act::Rideable::Gear gear(rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b);
            as_list->x_6(10, 0, static_cast<f32>(int(gear)));
        }
    }
    {
        auto* actor = mActor;
        if (auto* controller = actor->getCharacterController()) {
            if (auto* as_list = actor->getASList()) {
                sead::Vector3f velocity;
                if (!controller->sub_7100F5F234(&velocity))
                    velocity = sead::Vector3f::ey;
                as_list->sub_710115F024(velocity, 0);
            }
        }
    }
    _2c8.sub_710070F400(mActor);
    if (sub_71005DB904(mActor, *mBowIdx_s)) {
        if (!_478.mDamageManager)
            setDamageCallbackTiming(mActor, 0, &_478);
    } else if (_478.mDamageManager) {
        sub_71005DA114(mActor, &_478);
    }
    if (!isCurrentChild("ロデオ") &&
        !mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::Alive)) {
        auto* rideable = mActor->getHorseOptionsMaybe();
        if (rideable &&
            int(act::Unk_7100e8b2b8::Unk8(rideable->act::Unk_7100e8b2b8::_8.load() & 0xff)) !=
                act::Unk_7100e8b2b8::Unk8::_0 &&
            (rideable->act::Unk_7100e8b2b8::_8.load() & 0xff) ==
                act::Unk_7100e8b2b8::Unk8::_1) {
            *mLynelAIFlags_a |= 1;
            changeChild("ロデオ");
            return;
        }
    }
    EnemyRoot::calc_();
    if (!isCurrentChild("ロデオ"))
        *mLynelAIFlags_a &= ~1;
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        child->isChangeable();  // The original makes this virtual call and discards its result.
}

void LynelRoot::sub_710049AEA0() {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;
    auto* weapons = mActor->getWeapons();
    if (!weapons)
        return;
    for (s32 i = 0; i < 6; ++i) {
        auto& entry = weapons->mWeapons[i];
        auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(entry.link.getProc(nullptr, mActor));
        if (weapon && !entry._10 && !weapon->isWeaponType4()) {
            as_list->goLimpFromHeadShotMaybe(0x2c, weapon->getProfile(), 0);
            return;
        }
    }
    as_list->goLimpFromHeadShotMaybe(0x2c, sead::SafeString::cEmptyString, 0);
}

void LynelRoot::leave_() {
    EnemyRoot::leave_();
    if (_478.mDamageManager)
        sub_71005DA114(mActor, &_478);
    _2c8.sub_710070F398(mActor);
}

void LynelRoot::m37() {
    if (mActor->getVelocity().y > 0) {
        if (auto* controller = mActor->getCharacterController()) {
            sead::Vector3f vel;
            controller->sub_7100F5F598(&vel);
            vel.y = 0;
            controller->sub_7100F5F6FC(vel);
        }
    }
    EnemyRoot::m37();
}

void LynelRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mBowIdx_s, "BowIdx");
    getStaticParam(&mBoneStandAddRatio_s, "BoneStandAddRatio");
    getStaticParam(&mRoarFlameActorName_s, "RoarFlameActorName");
    getStaticParam(&mRoarFlamePartsKey_s, "RoarFlamePartsKey");
    getStaticParam(&mBreathActorName_s, "BreathActorName");
    getStaticParam(&mBreathPartsKey0_s, "BreathPartsKey0");
    getStaticParam(&mBreathPartsKey1_s, "BreathPartsKey1");
    getStaticParam(&mBreathPartsKey2_s, "BreathPartsKey2");
    getStaticParam(&mStandBoneName_s, "StandBoneName");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
    getAITreeVariable(&mLynelAreaAlarmPoint_a, "LynelAreaAlarmPoint");
    getAITreeVariable(&mLynelBodyControlUnit_a, "LynelBodyControlUnit");
    getAITreeVariable(&mLynelMoveParam_a, "LynelMoveParam");
    _278.sub_710070F83C(this);
}

}  // namespace uking::ai
