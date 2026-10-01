#include "Game/AI/AI/aiInitFromInCarryBoxSelect.h"

namespace uking::ai {

InitFromInCarryBoxSelect::InitFromInCarryBoxSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InitFromInCarryBoxSelect::~InitFromInCarryBoxSelect() = default;

bool InitFromInCarryBoxSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool InitFromInCarryBoxSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool InitFromInCarryBoxSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InitFromInCarryBoxSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsInitFromCarryBox_a) {
        if (*mIsResetInCarryBoxFlag_s)
            *mIsInitFromCarryBox_a = false;
        changeChild("抱持あり");
    } else {
        changeChild("抱持なし");
    }
}

void InitFromInCarryBoxSelect::calc_() {}

void InitFromInCarryBoxSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InitFromInCarryBoxSelect::loadParams_() {
    getStaticParam(&mIsResetInCarryBoxFlag_s, "IsResetInCarryBoxFlag");
    getAITreeVariable(&mIsInitFromCarryBox_a, "IsInitFromCarryBox");
}

}  // namespace uking::ai
