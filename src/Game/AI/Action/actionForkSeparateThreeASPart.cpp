#include "Game/AI/Action/actionForkSeparateThreeASPart.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "gsys/gsysModelAccessKey.h"
#include "gsys/gsysModel.h"

namespace uking::action {

ForkSeparateThreeASPart::ForkSeparateThreeASPart(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSeparateThreeASPart::~ForkSeparateThreeASPart() = default;

bool ForkSeparateThreeASPart::init_(sead::Heap* heap) {
    _88[0].getKey().bone_index = -1;
    _88[0].getKey().model_unit_index = -1;
    _88[1].getKey().bone_index = -1;
    _88[1].getKey().model_unit_index = -1;
    _50.getKey().reset();
    if (auto* model = mActor->getModel()) {
        _50.search(model, mRootNode_s);
        _88[0].search(model, mSlot1StartNode_s);
        _88[1].search(model, mSlot2StartNode_s);
    }
    return true;
}

// NON_MATCHING: the compiler unrolls the two-slot loop.
void ForkSeparateThreeASPart::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_50.isValid()) {
        auto* list = mActor->getASList();
        list->sub_710115C9E0(0);
        list->mSlots[0].sub_7101165008(_50.getKey(), 0, true);
        list->mSlots[0].sub_7101165008(_88[0].getKey(), 3, true);
        list->mSlots[0].sub_7101165008(_88[1].getKey(), 3, true);
        list->mSlots[0].sub_7101164E38(false);
    }
    for (s32 slot = 1; slot < 3; ++slot) {
        auto* list = mActor->getASList();
        list->sub_710115C9E0(slot);
        list->mSlots[slot].sub_7101165008(_50.getKey(), 3, true);
        if (_88[0].isValid())
            list->mSlots[slot].sub_7101165008(_88[0].getKey(), slot == 1 ? 0 : 3, true);
        if (_88[1].isValid())
            list->mSlots[slot].sub_7101165008(_88[1].getKey(), slot == 2 ? 0 : 3, true);
        list->mSlots[slot].sub_7101164E38(false);
    }
    mFlags.set(Flag::Changeable);
}

void ForkSeparateThreeASPart::leave_() {
    mActor->getASList()->sub_710115B01C(1, 0, true);
    mActor->getASList()->sub_710115B01C(2, 0, true);
    mActor->getASList()->sub_710115C11C();
}

void ForkSeparateThreeASPart::loadParams_() {
    getStaticParam(&mRootNode_s, "RootNode");
    getStaticParam(&mSlot1StartNode_s, "Slot1StartNode");
    getStaticParam(&mSlot2StartNode_s, "Slot2StartNode");
}

void ForkSeparateThreeASPart::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
