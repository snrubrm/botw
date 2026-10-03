#include "Game/AI/AI/aiAssassinBossLastAttack.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

AssassinBossLastAttack::AssassinBossLastAttack(const InitArg& arg)
    : AssassinBossIronBallAttack(arg) {}

AssassinBossLastAttack::~AssassinBossLastAttack() = default;

bool AssassinBossLastAttack::init_(sead::Heap* heap) {
    return AssassinBossIronBallAttack::init_(heap);
}

void AssassinBossLastAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_7100318F5C())
        changeChild("攻撃失敗", params);
    else if (sub_71003189D4())
        changeChild("攻撃予兆", params);
    else
        changeChild("準備完了待ち", params);
}

void AssassinBossLastAttack::calc_() {
    auto* child = getCurrentChild();
    if ((isCurrentChild("準備完了待ち") || isCurrentChild("攻撃予兆")) && sub_7100318F5C()) {
        changeChild("攻撃失敗");
        return;
    }

    if (isCurrentChild("攻撃")) {
        AssassinBossIronBallAttack::calc_();
        return;
    }

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("準備完了待ち"))
            setFailed();
        else
            changeChild("攻撃");
        return;
    }

    if (child->isChangeable() && isCurrentChild("準備完了待ち") && sub_71003189D4())
        changeChild("攻撃予兆");
}

bool AssassinBossLastAttack::sub_7100318F5C() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<32> name;
        ksys::act::ActorConstDataAccess accessor;
        for (int i = 0; i < *mIronBallNum_s; ++i) {
            name.format("%s%d", mIronBallPartsName_s.cstr(), i);
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
            if (accessor.sub_7100D13BB8())
                return true;
        }
    }
    return false;
}

void AssassinBossLastAttack::leave_() {
    AssassinBossIronBallAttack::leave_();
}

void AssassinBossLastAttack::loadParams_() {
    AssassinBossIronBallAttack::loadParams_();
}

}  // namespace uking::ai
