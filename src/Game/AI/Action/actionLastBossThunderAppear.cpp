#include "Game/AI/Action/actionLastBossThunderAppear.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"

namespace uking::action {

LastBossThunderAppear::LastBossThunderAppear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossThunderAppear::~LastBossThunderAppear() = default;

bool LastBossThunderAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossThunderAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = ksys::Timer(*mAppearTime_s, *mAppearTime_s);
    u32 attack_attr;
    if (auto* chemical = mActor->getChemicalStuff()) {
        chemical->sub_7100D91098(true);
        chemical->sub_7100D90FF0(false);
        if (chemical->_c0 == 2) {
            attack_attr = 0x202;
        } else {
            const u32 attribute = chemical->mMaterial->attribute.ref();
            if (attribute & 0x8000) {
                attack_attr = 0x401;
            } else if ((((0x108 & ~attribute) == 0) && !(chemical->_be & 4)) ||
                       chemical->_1b8 > 0.0f) {
                chemical->sub_7100D90AF4(true);
                attack_attr = 0x80a;
            } else {
                attack_attr = 2;
            }
        }
    } else {
        attack_attr = 2;
    }
    sub_71007A2C30(mActor, "AtkCommon", &mActor->getMtx());
    getActorAttackSensor(mActor)->activateAttackSensor(0x10, attack_attr, *mAttackPower_m, 100, 0.0f,
                                                       0, 1, -1, false, *mAtMinDamage_m,
                                                       *mAttackPowerForPlayer_m);
    if (auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent())) {
        if (auto* unk = parent->m128()) {
            if (!unk->m2()) {
                mActor->sendMessage(*parent->getMesTransceiverId(), ksys::MessageType(0x8000004),
                                    nullptr, true);
                mActor->resetConnectedCalcParent(false);
            }
        }
    }
}

void LastBossThunderAppear::leave_() {
    sub_71007A2D7C(mActor, "AtkCommon");
}

void LastBossThunderAppear::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAppearTime_s, "AppearTime");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
}

void LastBossThunderAppear::calc_() {
    if (hasAttackInfo(mActor))
        sub_71007A2D7C(mActor, "AtkCommon");
    _48.update();
    if (!(_48.value <= sead::Mathf::epsilon()))
        return;
    if (auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent())) {
        if (auto* unk = parent->m128()) {
            if (!unk->m2()) {
                mActor->sendMessage(*parent->getMesTransceiverId(), ksys::MessageType(0x8000004),
                                    nullptr, true);
            }
        }
        mActor->resetConnectedCalcParent(false);
    }
    setFinished();
}

}  // namespace uking::action
