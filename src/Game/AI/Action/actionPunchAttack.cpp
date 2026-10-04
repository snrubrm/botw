#include "Game/AI/Action/actionPunchAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include <prim/seadStringBuilder.h>

namespace uking::action {

PunchAttack::PunchAttack(const InitArg& arg) : ActionWithAS(arg) {}

PunchAttack::~PunchAttack() = default;

bool PunchAttack::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void PunchAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
    setDamageCallbackTiming(mActor, 4, &_a8);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void PunchAttack::leave_() {
    auto* actor = mActor;
    for (int i = 0; i < 3; ++i) {
        if (mAtkBodyName_s[i].isEmpty())
            break;
        sub_71007A2D7C(actor, mAtkBodyName_s[i]);
    }
    sub_71005DA114(mActor, &_a8);
    ActionWithPosAngReduce::leave_();
}

void PunchAttack::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mIsGuardPierce_s, "IsGuardPierce");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
    getStaticParam(&mIsIniviciblePierce_s, "IsIniviciblePierce");
    getStaticParam(&mIsImpulseLarge_s, "IsImpulseLarge");
    getStaticParam(&mIsHeavy_s, "IsHeavy");
    getStaticParam(&mIsHammer_s, "IsHammer");
    getStaticParam(&mASName_s, "ASName");
    sead::FixedStringBuilder<64> name;
    for (int i = 0; i < 3; ++i) {
        name.format("AtkBodyName%d", i + 1);
        getStaticParam(&mAtkBodyName_s[i], name.cstr());
    }
}

// NON_MATCHING: identical except the scheduler loads `*cNullChar` (w21) before the first name character
// instead of after it
void PunchAttack::calc_() {
    ActionWithAS::calc_();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0)) {
        sub_710022424C(&query);
    } else if (sub_71005DD74C(mActor, nullptr, 0, 0)) {
        if (!mAtkBodyName_s[0].isEmpty()) {
            auto* actor = mActor;
            sub_71007A2D7C(actor, mAtkBodyName_s[0]);
            if (!mAtkBodyName_s[1].isEmpty()) {
                sub_71007A2D7C(actor, mAtkBodyName_s[1]);
                if (!mAtkBodyName_s[2].isEmpty())
                    sub_71007A2D7C(actor, mAtkBodyName_s[2]);
            }
        }
    }
}

}  // namespace uking::action
