#include "Game/Actor/Behavior/behaviorLynelGearAttackCollision.h"
#include <limits>
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::behavior {

LynelGearAttackCollision::LynelGearAttackCollision(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
LynelGearAttackCollision::~LynelGearAttackCollision() {
    ;
}

bool LynelGearAttackCollision::m6(sead::Heap* heap) {
    return true;
}

void LynelGearAttackCollision::m9() {}

void LynelGearAttackCollision::loadParams() {
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mDamageScaleGear0_s, "DamageScaleGear0");
    getStaticParam(&mDamageScaleGear1_s, "DamageScaleGear1");
    getStaticParam(&mDamageScaleGear2_s, "DamageScaleGear2");
    getStaticParam(&mDamageScaleGear3_s, "DamageScaleGear3");
    getStaticParam(&mDamageScaleGearTop_s, "DamageScaleGearTop");
    getStaticParam(&mIsGuardPierce_s, "IsGuardPierce");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
    getStaticParam(&mIsIniviciblePierce_s, "IsIniviciblePierce");
    getStaticParam(&mAttackRigidName_s, "AttackRigidName");
}

void LynelGearAttackCollision::m8() {
    _80.rate = -1.0f;
    _8c = 0;
    _90 = 0;
    _80.value = 20.0f;
    _80.previous_value = 20.0f;
}

// NON_MATCHING: shared slow-time setup and gear selection differ from the native duplicated paths.
void LynelGearAttackCollision::m7() {
    const bool slow = isSlowTimeMaybe();
    if (auto* rideable = mActor->getHorseOptionsMaybe()) {
        const act::Rideable::Gear gear(rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b);
        if (slow && !(_90 & 1)) {
            sub_71007A2D7C(mActor, mAttackRigidName_s);
            _90 &= ~2;
            if (auto* controller = mActor->getCharacterController())
                controller->sub_7100F62DD0(0.0f);
            if (auto* body = mActor->getMainBody())
                body->setColImpulseScale(0.0f);
        } else if (!slow && (_90 & 1)) {
            if (auto* controller = mActor->getCharacterController())
                controller->sub_7100F62DD0(1.0f);
            if (auto* body = mActor->getMainBody())
                body->setColImpulseScale(1.0f);
        }
        f32 scale = 0.0f;
        switch (gear) {
        case act::Rideable::Gear::_0:
            scale = *mDamageScaleGear0_s;
            break;
        case act::Rideable::Gear::_1:
            scale = *mDamageScaleGear1_s;
            break;
        case act::Rideable::Gear::_2:
            scale = *mDamageScaleGear2_s;
            break;
        case act::Rideable::Gear::_3:
            scale = *mDamageScaleGear3_s;
            break;
        case act::Rideable::Gear::_4:
            scale = *mDamageScaleGearTop_s;
            break;
        default:
            break;
        }
        if (slow) {
            if (!(scale > 0.0f))
                _80.reset(20.0f);
        } else {
            if (scale > 0.0f) {
                if (_90 & 2) {
                    if (u32(gear) != _8c)
                        sub_710062BAE0(gear);
                } else if (!(_80.value <= std::numeric_limits<f32>::epsilon())) {
                    // Unordered timer values follow the native update path.
                    _80.update();
                } else {
                    sub_71007A2C30(mActor, mAttackRigidName_s, nullptr);
                    sub_710062BAE0(gear);
                    _90 |= 2;
                }
            } else if (_90 & 2) {
                sub_71007A2D7C(mActor, mAttackRigidName_s);
                _90 &= ~2;
                _80.reset(20.0f);
            }
            _8c = u32(gear);
        }
    }
    if (slow)
        _90 |= 1;
    else
        _90 &= ~1;
}

// NON_MATCHING: by-value gear spill timing and parameter value selection differ.
void LynelGearAttackCollision::sub_710062BAE0(act::Rideable::Gear gear) {
    auto* sensor = getActorAttackSensor(mActor);
    u32 flags = 0;
    switch (*mAttackIntensity_s) {
    case 1:
        flags = 1;
        break;
    case 2:
        flags = 2;
        break;
    case 3:
        flags = 4;
        break;
    default:
        break;
    }
    if (*mIsGuardPierce_s)
        flags |= 8;
    if (*mIsIniviciblePierce_s)
        flags |= 0x40;
    if (*mIsForceGuardBreak_s)
        flags |= 0x100;
    f32 scale = 0.0f;
    switch (gear) {
        case act::Rideable::Gear::_0:
            scale = *mDamageScaleGear0_s;
            break;
        case act::Rideable::Gear::_1:
            scale = *mDamageScaleGear1_s;
            break;
        case act::Rideable::Gear::_2:
            scale = *mDamageScaleGear2_s;
            break;
        case act::Rideable::Gear::_3:
            scale = *mDamageScaleGear3_s;
            break;
        case act::Rideable::Gear::_4:
            scale = *mDamageScaleGearTop_s;
            break;
        default:
            break;
        }
    const s32 power = static_cast<ksys::act::PlayerOrEnemy*>(mActor)->getEnemyAtkPower();
    const s32 scaled_power = static_cast<s32>(scale * static_cast<f32>(power > 1 ? power : 1));
    const auto* attack = mActor->getParam()->getRes().mGParamList->getAttack();
    sensor->activateAttackSensor(0x2000, flags, scaled_power, attack->mImpulse.ref(), 0.0f,
                                 attack->mGuardBreakPower.ref(), 1, -1, false, 1, -1);
}

}  // namespace uking::behavior
