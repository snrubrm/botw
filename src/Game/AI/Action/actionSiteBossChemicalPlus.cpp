#include "Game/AI/Action/actionSiteBossChemicalPlus.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

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
    if (!_60)
        sub_7100257F80();
    sub_71005DB434(mActor);
}

void SiteBossChemicalPlus::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mIsDeleteAllChildDevice_s, "IsDeleteAllChildDevice");
    getStaticParam(&mIsSetCanGuardArrowFlag_s, "IsSetCanGuardArrowFlag");
    getStaticParam(&mChemicalLoopASName_s, "ChemicalLoopASName");
    getStaticParam(&mChmicalPlusASName_s, "ChmicalPlusASName");
}

// NON_MATCHING: the kind test (1 / 5 / 9) is lowered by the original as a rebased bit test (`sub 1; cmp 8; lsr 0x111`), ours
// as `cmp 9; 1 << kind & 0x222` (switch and an or-chain give the same)
void SiteBossChemicalPlus::sub_7100257F80() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->x_1(true, *mIsSetCanGuardArrowFlag_s, false);
        if (*mIsDeleteAllChildDevice_s)
            boss->_1560.sub_710066CD7C(0);
        if (boss->_1534 == 1 || boss->_1534 == 5 || boss->_1534 == 9)
            act::SiteBoss::sub_71002D355C(boss, mActor, "WearFlame");
        act::SiteBoss::x_2(boss, mActor);
        if (!mChemicalLoopASName_s.isEmpty())
            playAS("Chemical_Loop", false, 3, 0, -1.0f);
        boss->_14c8._30.reset(0x400);
    }
}

void SiteBossChemicalPlus::calc_() {
    ActionWithPosAngReduce::calc_();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD780(mActor, 81, &query, 0, 0)) {
        _60 = true;
        sub_7100257F80();
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
