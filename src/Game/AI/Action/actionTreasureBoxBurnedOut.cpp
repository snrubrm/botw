#include "Game/AI/Action/actionTreasureBoxBurnedOut.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

TreasureBoxBurnedOut::TreasureBoxBurnedOut(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TreasureBoxBurnedOut::~TreasureBoxBurnedOut() = default;

bool TreasureBoxBurnedOut::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TreasureBoxBurnedOut::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TreasureBoxBurnedOut::leave_() {
    _20.deleteProc();
}

void TreasureBoxBurnedOut::loadParams_() {
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
    getAITreeVariable(&mDropActorName_a, "DropActorName");
    getAITreeVariable(&mSharpWeaponAddParam_a, "SharpWeaponAddParam");
}

// NON_MATCHING: the address of _30 is computed before the releaseAndWakeProc call in the original.
void TreasureBoxBurnedOut::calc_() {
    if (_20.isAllocatedOrFailed()) {
        if (_20.isProcReady()) {
            auto* proc = _20.releaseAndWakeProc();
            _30.acquire(sead::DynamicCast<ksys::act::Actor>(proc), false);
        } else if (_20.hasProcCreationFailed()) {
            _20.deleteProcIfFailed();
            spawnDropActor();
        }
    } else {
        auto* actor = mActor;
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000);
        actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

}  // namespace uking::action
