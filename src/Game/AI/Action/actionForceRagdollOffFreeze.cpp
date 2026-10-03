#include "Game/AI/Action/actionForceRagdollOffFreeze.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForceRagdollOffFreeze::ForceRagdollOffFreeze(const InitArg& arg) : Freeze(arg) {}

ForceRagdollOffFreeze::~ForceRagdollOffFreeze() = default;

bool ForceRagdollOffFreeze::init_(sead::Heap* heap) {
    if (!Freeze::init_(heap))
        return false;
    _80.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    setupCRBOffsetUnit(_80);
    return true;
}

void ForceRagdollOffFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor))
        actor->sub_71006DD92C(false);
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115F5C0(0.0f, 0, 0);
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_80._0))
        unit->_8.mHandle._68 = sead::Matrix34f::ident;
}

void ForceRagdollOffFreeze::leave_() {
    Freeze::leave_();
}

void ForceRagdollOffFreeze::loadParams_() {
    Freeze::loadParams_();
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void ForceRagdollOffFreeze::calc_() {
    Freeze::calc_();
}

}  // namespace uking::action
