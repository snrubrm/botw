#include "Game/AI/Action/actionSiteBossChemicalPlus.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

SiteBossChemicalPlus::SiteBossChemicalPlus(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

SiteBossChemicalPlus::~SiteBossChemicalPlus() = default;

bool SiteBossChemicalPlus::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void SiteBossChemicalPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    _60 = false;
    playAS(mChmicalPlusASName_s.cstr(), false, 0, 0, -1.0f);
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115B01C(3, 0, true);
    sub_71005DB41C(mActor);
}

void SiteBossChemicalPlus::leave_() {
    ActionWithPosAngReduce::leave_();
}

void SiteBossChemicalPlus::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mIsDeleteAllChildDevice_s, "IsDeleteAllChildDevice");
    getStaticParam(&mIsSetCanGuardArrowFlag_s, "IsSetCanGuardArrowFlag");
    getStaticParam(&mChemicalLoopASName_s, "ChemicalLoopASName");
    getStaticParam(&mChmicalPlusASName_s, "ChmicalPlusASName");
}

void SiteBossChemicalPlus::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
