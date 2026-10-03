#include "Game/AI/AI/aiFirstSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

FirstSelect::FirstSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FirstSelect::~FirstSelect() = default;

bool FirstSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool FirstSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool FirstSelect::init_(sead::Heap* heap) {
    _40 = true;
    return true;
}

void FirstSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (testRootAiFlag(ksys::act::ai::RootAiFlag::_7) && *mResetFromDemo_s)
        _40 = true;

    if (_40)
        changeChild("初回", params);
    else
        changeChild("二回目以降", params);
    _40 = false;
}

void FirstSelect::calc_() {}

void FirstSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FirstSelect::loadParams_() {
    getStaticParam(&mResetFromDemo_s, "ResetFromDemo");
}

}  // namespace uking::ai
