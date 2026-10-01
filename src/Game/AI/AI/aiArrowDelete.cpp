#include "Game/AI/AI/aiArrowDelete.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

ArrowDelete::ArrowDelete(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ArrowDelete::~ArrowDelete() = default;

bool ArrowDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ArrowDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getChemicalStuff();
    changeChild("ケミカル待機");
}

void ArrowDelete::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        changeChild("消滅");
    else
        child->isChangeable();
}

void ArrowDelete::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ArrowDelete::loadParams_() {}

}  // namespace uking::ai
