#include "Game/AI/AI/aiPriestBossAfterImageRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::ai {

PriestBossAfterImageRoot::PriestBossAfterImageRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossAfterImageRoot::~PriestBossAfterImageRoot() = default;

bool PriestBossAfterImageRoot::init_(sead::Heap* heap) {
    _38 = false;
    return true;
}

void PriestBossAfterImageRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = false;
    mActor->getXLink()->toggle(true);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    changeChild("通常");
}

void PriestBossAfterImageRoot::calc_() {
    if (isSlowTimeMaybe() || _38) {
        auto* xlink = mActor->getXLink();
        if (!xlink->_73)
            xlink->setMask(1);
        if (!mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_20))
            mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
        _38 = true;
    }
}

void PriestBossAfterImageRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossAfterImageRoot::loadParams_() {}

}  // namespace uking::ai
