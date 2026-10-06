#include "Game/AI/AI/aiNpcMoveToAnchor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ai {

NpcMoveToAnchor::NpcMoveToAnchor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NpcMoveToAnchor::~NpcMoveToAnchor() {
    ;
}

bool NpcMoveToAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original loads the ASKeyName string top / first char before the InlineParamPack
// constructor loop but selects at the use; a `const char*` local before the pack moves the select too
void NpcMoveToAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* anchor = ksys::act::findLinkReferenceObj(mActor, mAnchorName_d, mAnchorUniqueName_d, nullptr);
    if (!anchor) {
        setFailed();
        return;
    }

    const sead::Vector3f translate = anchor->getTranslate();
    _78 = translate;
    _84 = anchor->getRotate();

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_78, "TargetPos", -1);
    pack.addString(mASKeyName_d.isEmpty() ? "Walk" : mASKeyName_d.getStringTop(), "DynASKeyName", -1);
    changeChild("移動", &pack);
}

void NpcMoveToAnchor::calc_() {
    if (isFinishedOrFailed()) {
        sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
        sub_7100738AA8(mActor, 0.0f);
        return;
    }

    if (isCurrentChild("移動")) {
        if (getCurrentChild()->isFinished()) {
            if (*mIsAlignmentAnchor_d) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(_78, "TargetPos", -1);
                changeChild("アンカー接近", &pack);
                return;
            }
            if (*mIsTurnToAnchorDir_d) {
                ksys::act::ai::InlineParamPack pack;
                const sead::Matrix34f& mtx = mActor->getMtx();
                pack.addVec3({mtx.m[0][3], mtx.m[1][3], mtx.m[2][3]}, "TargetPos", -1);
                pack.addVec3(_84, "TargetRot", -1);
                changeChild("振り向く", &pack);
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
            if (*mIsTurnToAnchorDir_d) {
                ksys::act::ai::InlineParamPack pack;
                const sead::Matrix34f& mtx = mActor->getMtx();
                pack.addVec3({mtx.m[0][3], mtx.m[1][3], mtx.m[2][3]}, "TargetPos", -1);
                pack.addVec3(_84, "TargetRot", -1);
                changeChild("振り向く", &pack);
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

void NpcMoveToAnchor::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NpcMoveToAnchor::loadParams_() {
    getDynamicParam(&mIsTurnToAnchorDir_d, "IsTurnToAnchorDir");
    getDynamicParam(&mIsAlignmentAnchor_d, "IsAlignmentAnchor");
    getDynamicParam(&mAnchorName_d, "AnchorName");
    getDynamicParam(&mAnchorUniqueName_d, "AnchorUniqueName");
    getDynamicParam(&mASKeyName_d, "ASKeyName");
}

}  // namespace uking::ai
