#include "Game/AI/Action/actionEquipDisplayCreate.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

// 0x710070106c (CSV name; declared only, signature inferred from EquipDisplayCreate::enter_: the handle that
// receives the created actor, the owner's matrix and the equip stand slot). Source namespace unknown.
bool aiActionEquipDisplayCreateDoCreateActor(ksys::act::BaseProcHandle* handle,
                                             const sead::Matrix34f* mtx, s32 slot);

namespace uking::action {

EquipDisplayCreate::EquipDisplayCreate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EquipDisplayCreate::~EquipDisplayCreate() = default;

bool EquipDisplayCreate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EquipDisplayCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    _a8 = 2;
    if (_b0.isAllocatedOrFailed()) {
        _b0.deleteProc();
        _b0.deleteProcIfFailed();
    }
    if (aiActionEquipDisplayCreateDoCreateActor(&_b0, &mActor->getMtx(), *mEquipStandSlot_m)) {
        _a8 = 0;
        return;
    }
    setFailed();
}

void EquipDisplayCreate::leave_() {
    ksys::act::ai::Action::leave_();
}

void EquipDisplayCreate::loadParams_() {
    getStaticParam(&mDelayTimer_s, "DelayTimer");
    getStaticParam(&mSwordEquipNode_s, "SwordEquipNode");
    getStaticParam(&mLSwordEquipNode_s, "LSwordEquipNode");
    getStaticParam(&mSpearEquipNode_s, "SpearEquipNode");
    getStaticParam(&mBowEquipNode_s, "BowEquipNode");
    getStaticParam(&mShieldEquipNode_s, "ShieldEquipNode");
    getStaticParam(&mXLinkKey_s, "XLinkKey");
    getMapUnitParam(&mEquipStandSlot_m, "EquipStandSlot");
    getMapUnitParam(&mEquipStandNode_m, "EquipStandNode");
    getAITreeVariable(&mEquipDisplayChild_a, "EquipDisplayChild");
}

void EquipDisplayCreate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
