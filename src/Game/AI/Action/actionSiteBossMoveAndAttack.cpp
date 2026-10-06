#include "Game/AI/Action/actionSiteBossMoveAndAttack.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
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
    if (mActor->getASList()->x(71, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        if (auto* boss = sead::DynamicCast<uking::act::SiteBoss>(mActor)) {
            if (boss->_1560.sub_710066C074())
                boss->_1560.sub_710066C738(m32(), 0.8f, 0.4f);
        }
    }
}

}  // namespace uking::action
