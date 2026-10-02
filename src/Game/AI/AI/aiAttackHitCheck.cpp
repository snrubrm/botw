#include "Game/AI/AI/aiAttackHitCheck.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

AttackHitCheck::AttackHitCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AttackHitCheck::~AttackHitCheck() = default;

bool AttackHitCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AttackHitCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("オフ");
    mFlags.set(Flag::Changeable);
}

void AttackHitCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AttackHitCheck::loadParams_() {
    getStaticParam(&mAtkType_s, "AtkType");
}

void AttackHitCheck::calc_() {
    auto* actor = mActor;
    if (!sub_71007A2604(actor))
        return;

    s32 damage = -1;
    s32 field_50 = -1;
    if (auto* damage_mgr = sub_710072BA90(actor)) {
        damage = damage_mgr->getDamage();
        field_50 = damage_mgr->getField50();
    }

    switch (*mAtkType_s) {
    case 0:
        if (damage < 1 || field_50 != 4)
            return;
        break;
    case 1:
        break;
    default:
        return;
    }

    if (!isCurrentChild("オン"))
        changeChild("オン");
}

}  // namespace uking::ai
