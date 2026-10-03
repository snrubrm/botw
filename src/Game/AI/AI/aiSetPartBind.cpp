#include "Game/AI/AI/aiSetPartBind.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SetPartBind::SetPartBind(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SetPartBind::~SetPartBind() {
    ;
}

// NON_MATCHING: stack slots of the two BoneAccessKey locals (the original keeps them 8-byte aligned at sp+0x18 /
// sp+0; ours packs the 4-byte keys at sp+0x1c / sp+4); same as the BoneAccessKey temporaries of Unk_71025be918
void SetPartBind::sub_7100567E78() {
    auto* actor = mActor;
    if (!actor || !actor->getModel() || !actor->getASList())
        return;
    auto* as_list = actor->getASList();
    const auto base = actor->getModel()->searchBone(mBaseNodeName_s.cstr());
    const auto partial = actor->getModel()->searchBone(mPartialNodeName_s.cstr());
    if (!base.isValid() || !partial.isValid())
        return;
    as_list->sub_710115C9E0(0);
    as_list->mSlots[0].sub_7101165008(base, 0, true);
    as_list->mSlots[0].sub_7101165008(partial, 3, true);
    as_list->mSlots[0].sub_7101164E38(false);
    as_list->sub_710115C9E0(1);
    as_list->mSlots[1].sub_7101165008(base, 3, true);
    as_list->mSlots[1].sub_7101165008(partial, 0, true);
    as_list->mSlots[1].sub_7101164E38(false);
}

void SetPartBind::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100567E78();
    changeChild("行動", params);
}

void SetPartBind::calc_() {
    if (getCurrentChild()->isFinished()) {
        setFinished();
        return;
    }
    if (getCurrentChild()->isFailed())
        setFailed();
}

void SetPartBind::leave_() {
    auto* actor = mActor;
    if (actor && actor->getModel() && actor->getASList()) {
        actor->getASList()->sub_710115B01C(1, 0, true);
        actor->getASList()->sub_710115C11C();
        actor->getASList()->sub_710115BED4(true);
    }
}

void SetPartBind::loadParams_() {
    getStaticParam(&mBaseNodeName_s, "BaseNodeName");
    getStaticParam(&mPartialNodeName_s, "PartialNodeName");
}

}  // namespace uking::ai
