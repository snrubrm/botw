#include "Game/Actor/AI/aiNPCMoveToRailPoint.h"
#include "Game/Actor/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapRail.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

NPCMoveToRailPoint::NPCMoveToRailPoint(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NPCMoveToRailPoint::~NPCMoveToRailPoint() {
    ;
}

bool NPCMoveToRailPoint::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCMoveToRailPoint::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::map::Rail* rail;
    if (mRailUniqueName_d.isEmpty())
        rail = sub_7100EEF264(mActor, 0);
    else
        rail = sub_7100EEF2F0(mActor, mRailUniqueName_d);

    if (!rail || *mRailPointIndex_d < 0 || *mRailPointIndex_d >= rail->getNumPoints()) {
        setFailed();
        return;
    }

    rail->calcTranslate(&_70, *mRailPointIndex_d);
    _7c = rail->getPointRotate(*mRailPointIndex_d);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_70, "TargetPos", -1);
    pack.addString(mASName_d, "DynASKeyName", -1);
    changeChild("移動", &pack);
}

// 0x71004d5b3c
void NPCMoveToRailPoint::calc_() {
    if (isFinished() || isFailed()) {
        sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
        sub_7100738AA8(mActor, 0.0f);
        return;
    }

    if (isCurrentChild("移動")) {
        if (getCurrentChild()->isFinished()) {
            if (*mIsAlignmentAnchor_d) {
                ksys::act::ai::InlineParamPack params;
                params.addVec3(_70, "TargetPos", -1);
                changeChild("アンカー接近", &params);
                return;
            }
            if (*mIsTurnToRailPointDir_d) {
                ksys::act::ai::InlineParamPack params;
                params.addVec3(mActor->getMtx().getTranslation(), "TargetPos", -1);
                params.addVec3(_7c, "TargetRot", -1);
                changeChild("振り向く", &params);
                return;
            }
            setFinished();
            return;
        }
    } else if (isCurrentChild("振り向く")) {
        if (getCurrentChild()->isFinished())
            setFinished();
        return;
    } else if (isCurrentChild("アンカー接近")) {
        if (getCurrentChild()->isFinished()) {
            if (*mIsTurnToRailPointDir_d) {
                ksys::act::ai::InlineParamPack params;
                params.addVec3(mActor->getMtx().getTranslation(), "TargetPos", -1);
                params.addVec3(_7c, "TargetRot", -1);
                changeChild("振り向く", &params);
            } else {
                setFinished();
            }
        }
    } else {
        return;
    }

    if (getCurrentChild()->isFailed())
        setFailed();
}

void NPCMoveToRailPoint::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCMoveToRailPoint::loadParams_() {
    getDynamicParam(&mRailPointIndex_d, "RailPointIndex");
    getDynamicParam(&mIsTurnToRailPointDir_d, "IsTurnToRailPointDir");
    getDynamicParam(&mIsAlignmentAnchor_d, "IsAlignmentAnchor");
    getDynamicParam(&mRailUniqueName_d, "RailUniqueName");
    getDynamicParam(&mASName_d, "ASName");
}

}  // namespace uking::ai
