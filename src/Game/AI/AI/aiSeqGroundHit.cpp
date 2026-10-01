#include "Game/AI/AI/aiSeqGroundHit.h"

namespace uking::ai {

SeqGroundHit::SeqGroundHit(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqGroundHit::~SeqGroundHit() = default;

bool SeqGroundHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqGroundHit::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("空中", params);
}

void SeqGroundHit::calc_() {
    if (!isCurrentChild("空中"))
        return;

    auto* child = getCurrentChild();
    if (*mIsCheckChangeable_s && !child->isChangeable())
        return;

    if (sub_7100562078() || child->isFinished() || child->isFailed())
        changeChild("地上");
}

bool SeqGroundHit::isFailed() const {
    return ksys::act::ai::Ai::isFailed() ||
           (getCurrentChild()->isFailed() && (isCurrentChild("地上") || *mIsNoHitEnd_s));
}

bool SeqGroundHit::isFinished() const {
    return ksys::act::ai::Ai::isFinished() ||
           (getCurrentChild()->isFinished() && (isCurrentChild("地上") || *mIsNoHitEnd_s));
}

void SeqGroundHit::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqGroundHit::loadParams_() {
    getStaticParam(&mCheckType_s, "CheckType");
    getStaticParam(&mIsCheckChangeable_s, "IsCheckChangeable");
    getStaticParam(&mIsNoHitEnd_s, "IsNoHitEnd");
}

}  // namespace uking::ai
