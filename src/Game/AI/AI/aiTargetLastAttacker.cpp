#include "Game/AI/AI/aiTargetLastAttacker.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetLastAttacker::TargetLastAttacker(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetLastAttacker::~TargetLastAttacker() = default;

bool TargetLastAttacker::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetLastAttacker::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy)
        pack.addActor(enemy->_e08._0, "TargetActor", -1);
    else
        pack.addActor(ksys::act::getDummyBaseProcLink(), "TargetActor", -1);
    changeChild("行動", &pack);
}

void TargetLastAttacker::calc_() {
    if (*mOnEnterOnly_s)
        return;

    ksys::act::ai::InlineParamPack pack;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy)
        getCurrentChild()->setDynamicParam(enemy->_e08._0, "TargetActor");
    else
        getCurrentChild()->setDynamicParam(ksys::act::getDummyBaseProcLink(), "TargetActor");
}

void TargetLastAttacker::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetLastAttacker::loadParams_() {
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
}

}  // namespace uking::ai
