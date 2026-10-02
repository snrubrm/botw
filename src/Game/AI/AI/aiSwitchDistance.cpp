#include "Game/AI/AI/aiSwitchDistance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

SwitchDistance::SwitchDistance(const InitArg& arg) : SwitchAI(arg) {}

SwitchDistance::~SwitchDistance() = default;

bool SwitchDistance::init_(sead::Heap* heap) {
    return SwitchAI::init_(heap);
}

void SwitchDistance::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchAI::enter_(params);
}

void SwitchDistance::leave_() {
    SwitchAI::leave_();
}

void SwitchDistance::loadParams_() {
    SwitchAI::loadParams_();
    getStaticParam(&mOnDis_s, "OnDis");
    getStaticParam(&mOffsetDis_s, "OffsetDis");
    getStaticParam(&mChangeSeq_s, "ChangeSeq");
}

void SwitchDistance::calc_() {
    SwitchAI::calc_();
}

bool SwitchDistance::m34() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f target = pos;
    if (sub_710072B8E4())
        target = getPlayerPosition();
    return (pos - target).length() <= *mOnDis_s;
}

// NON_MATCHING: `cbz` vs `tbz #0` on the combined child-state flag
bool SwitchDistance::m35() {
    auto* child = getCurrentChild();
    bool check = isCurrentChild("オフ");
    if (*mChangeSeq_s)
        check = false;
    if (isCurrentChild("オフ待機") && child->isChangeable())
        check = true;
    if (check) {
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        sead::Vector3f target = pos;
        if (sub_710072B8E4())
            target = getPlayerPosition();
        if ((pos - target).length() <= *mOnDis_s)
            return true;
    }
    return false;
}

// NON_MATCHING: `cbz` vs `tbz #0` on the combined child-state flag
bool SwitchDistance::m36() {
    auto* child = getCurrentChild();
    bool check = isCurrentChild("オン");
    if (*mChangeSeq_s)
        check = false;
    if (isCurrentChild("オン待機") && child->isChangeable())
        check = true;
    if (check) {
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        sead::Vector3f target = pos;
        if (sub_710072B8E4())
            target = getPlayerPosition();
        if ((pos - target).length() >= *mOnDis_s + *mOffsetDis_s)
            return true;
    }
    return false;
}

bool SwitchDistance::m37() {
    auto* child = getCurrentChild();
    return isCurrentChild("オン") && child->isFinished();
}

bool SwitchDistance::m38() {
    auto* child = getCurrentChild();
    return isCurrentChild("オフ") && child->isFinished();
}

}  // namespace uking::ai
