#include "Game/AI/AI/aiDoubtItemSubTargetSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actUnk_71002dccbc.h"

namespace uking::ai {

DoubtItemSubTargetSelect::DoubtItemSubTargetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DoubtItemSubTargetSelect::~DoubtItemSubTargetSelect() = default;

bool DoubtItemSubTargetSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool DoubtItemSubTargetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DoubtItemSubTargetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* unk = sub_71005D9D68(mActor);
    if (unk == nullptr || unk->sub_71002DCCBC(0x80))
        changeChild("なかった", params);
    else
        changeChild("あった", params);
}

void DoubtItemSubTargetSelect::calc_() {}

void DoubtItemSubTargetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DoubtItemSubTargetSelect::loadParams_() {}

bool DoubtItemSubTargetSelect::m34() {
    return getCurrentChild()->isFailed();
}

}  // namespace uking::ai
