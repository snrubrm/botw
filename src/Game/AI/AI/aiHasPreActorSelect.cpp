#include "Game/AI/AI/aiHasPreActorSelect.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HasPreActorSelect::HasPreActorSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HasPreActorSelect::~HasPreActorSelect() = default;

bool HasPreActorSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool HasPreActorSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool HasPreActorSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HasPreActorSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->getMapObject())
        changeChild("存在する", params);
    else
        changeChild("存在しない", params);
}

void HasPreActorSelect::calc_() {}

void HasPreActorSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HasPreActorSelect::loadParams_() {}

}  // namespace uking::ai
