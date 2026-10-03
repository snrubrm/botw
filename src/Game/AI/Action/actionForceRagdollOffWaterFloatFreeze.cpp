#include "Game/AI/Action/actionForceRagdollOffWaterFloatFreeze.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForceRagdollOffWaterFloatFreeze::ForceRagdollOffWaterFloatFreeze(const InitArg& arg)
    : WaterFloatFreeze(arg) {}

ForceRagdollOffWaterFloatFreeze::~ForceRagdollOffWaterFloatFreeze() = default;

bool ForceRagdollOffWaterFloatFreeze::init_(sead::Heap* heap) {
    if (!WaterFloatFreeze::init_(heap))
        return false;
    _80.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    setupCRBOffsetUnit(_80);
    return true;
}

void ForceRagdollOffWaterFloatFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatFreeze::enter_(params);
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor))
        actor->sub_71006DD92C(false);
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115F5C0(0.0f, 0, 0);
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_80._0))
        unit->_8.mHandle._68 = sead::Matrix34f::ident;
}

void ForceRagdollOffWaterFloatFreeze::loadParams_() {
    WaterFloatFreeze::loadParams_();
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

}  // namespace uking::action
