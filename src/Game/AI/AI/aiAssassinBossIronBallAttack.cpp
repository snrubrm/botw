#include "Game/AI/AI/aiAssassinBossIronBallAttack.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

AssassinBossIronBallAttack::AssassinBossIronBallAttack(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AssassinBossIronBallAttack::~AssassinBossIronBallAttack() = default;

bool AssassinBossIronBallAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AssassinBossIronBallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71003189D4())
        changeChild("攻撃", params);
    else
        changeChild("準備完了待ち", params);
}

void AssassinBossIronBallAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinBossIronBallAttack::loadParams_() {
    getStaticParam(&mIronBallNum_s, "IronBallNum");
    getStaticParam(&mIronBallPartsName_s, "IronBallPartsName");
}

void AssassinBossIronBallAttack::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("準備完了待ち"))
            setFailed();
        else
            setFinished();
        return;
    }
    if (child->isChangeable() && sub_71003189D4() && !isCurrentChild("攻撃"))
        changeChild("攻撃");
}

bool AssassinBossIronBallAttack::sub_71003189D4() {
    bool done = true;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<32> name;
        ksys::act::ActorConstDataAccess accessor;
        for (int i = 0; i < *mIronBallNum_s; ++i) {
            name.format("%s%d", mIronBallPartsName_s.cstr(), i);
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
            if (accessor.sub_7100D10E6C(25) && !accessor.sub_7100D10E6C(24))
                return false;
            done = done && !accessor.sub_7100D10E6C(25);
        }
    }
    return !done;
}

}  // namespace uking::ai
