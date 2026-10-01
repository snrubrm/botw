#include "Game/AI/AI/aiEnterFromResetSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

EnterFromResetSelect::EnterFromResetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnterFromResetSelect::~EnterFromResetSelect() = default;

bool EnterFromResetSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EnterFromResetSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool EnterFromResetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnterFromResetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->getRootAi()->getI() == 5)
        changeChild("通常", params);
    else
        changeChild("初期状態", params);
}

void EnterFromResetSelect::calc_() {}

void EnterFromResetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnterFromResetSelect::loadParams_() {}

}  // namespace uking::ai
