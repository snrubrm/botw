#include "Game/AI/AI/aiExplodeCheck.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

ExplodeCheck::ExplodeCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ExplodeCheck::~ExplodeCheck() = default;

bool ExplodeCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ExplodeCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* life = mActor->getLife();
    if (!life || *life >= 1) {
        auto* chemical = mActor->getChemicalStuff();
        if (!chemical || (chemical->_c0 != 4 && !(chemical->_b8 & 0x10))) {
            changeChild("通常", params);
            return;
        }
    }
    changeChild("爆発", params);
}

bool ExplodeCheck::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool ExplodeCheck::isFinished() const {
    return getCurrentChild()->isFinished();
}

void ExplodeCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ExplodeCheck::loadParams_() {}

bool ExplodeCheck::isChangeable() const {
    return isCurrentChild("通常") && getCurrentChild()->isChangeable();
}

void ExplodeCheck::calc_() {
    if (!isCurrentChild("通常"))
        return;
    auto* life = mActor->getLife();
    if (!life || *life >= 1) {
        auto* chemical = mActor->getChemicalStuff();
        if (!chemical || (chemical->_c0 != 4 && !(chemical->_b8 & 0x10)))
            return;
    }
    changeChild("爆発");
}

}  // namespace uking::ai
