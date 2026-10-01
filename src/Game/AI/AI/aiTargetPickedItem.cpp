#include "Game/AI/AI/aiTargetPickedItem.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetPickedItem::TargetPickedItem(const InitArg& arg) : CommonPickedItem(arg) {}

TargetPickedItem::~TargetPickedItem() = default;

bool TargetPickedItem::init_(sead::Heap* heap) {
    return CommonPickedItem::init_(heap);
}

void TargetPickedItem::enter_(ksys::act::ai::InlineParamPack* params) {
    CommonPickedItem::enter_(params);
}

void TargetPickedItem::calc_() {
    CommonPickedItem::calc_();
    if (isCurrentChild("通常"))
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void TargetPickedItem::leave_() {
    CommonPickedItem::leave_();
}

void TargetPickedItem::loadParams_() {
    CommonPickedItem::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool TargetPickedItem::isChangeable() const {
    return ksys::act::ai::Ai::isChangeable() && !_88._30;
}

void TargetPickedItem::m38() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("通常", &params);
}

}  // namespace uking::ai
