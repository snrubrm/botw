#include "Game/Actor/AI/aiNPCMoveToRailPoint.h"
#include "Game/Actor/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapRail.h"

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
