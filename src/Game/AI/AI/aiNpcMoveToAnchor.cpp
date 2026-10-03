#include "Game/AI/AI/aiNpcMoveToAnchor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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
