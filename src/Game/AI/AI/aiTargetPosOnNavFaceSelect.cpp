#include "Game/AI/AI/aiTargetPosOnNavFaceSelect.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetPosOnNavFaceSelect::TargetPosOnNavFaceSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetPosOnNavFaceSelect::~TargetPosOnNavFaceSelect() = default;

bool TargetPosOnNavFaceSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetPosOnNavFaceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    if (sub_710072E304(*mTargetPos_d, *mSearchRadius_s))
        changeChild("ナビメッシュ上", &pack);
    else
        changeChild("ナビメッシュ外", &pack);
}

void TargetPosOnNavFaceSelect::calc_() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void TargetPosOnNavFaceSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetPosOnNavFaceSelect::loadParams_() {
    getStaticParam(&mSearchRadius_s, "SearchRadius");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
