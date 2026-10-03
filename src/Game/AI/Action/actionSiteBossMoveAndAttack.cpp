#include "Game/AI/Action/actionSiteBossMoveAndAttack.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossMoveAndAttack::SiteBossMoveAndAttack(const InitArg& arg) : SiteBossMove(arg) {}

SiteBossMoveAndAttack::~SiteBossMoveAndAttack() = default;

bool SiteBossMoveAndAttack::init_(sead::Heap* heap) {
    return SiteBossMove::init_(heap);
}

void SiteBossMoveAndAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossMove::enter_(params);
    if (auto* boss = sead::DynamicCast<uking::act::SiteBoss>(mActor)) {
        if (!boss->_1560.sub_710066C074())
            setFailed();
    }
}

void SiteBossMoveAndAttack::leave_() {
    SiteBossMove::leave_();
}

void SiteBossMoveAndAttack::loadParams_() {
    SiteBossMove::loadParams_();
}

void SiteBossMoveAndAttack::calc_() {
    SiteBossMove::calc_();
}

}  // namespace uking::action
