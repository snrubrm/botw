#include "Game/Actor/AI/aiVacuumEnemyRoot.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

VacuumEnemyRoot::VacuumEnemyRoot(const InitArg& arg) : EnemyRoot(arg) {}

VacuumEnemyRoot::~VacuumEnemyRoot() {
    auto* child = mActor->getConnectedCalcChild();
    if (child && child->isSleep())
        child->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

bool VacuumEnemyRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void VacuumEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void VacuumEnemyRoot::calc_() {
    EnemyRoot::calc_();
}

void VacuumEnemyRoot::leave_() {
    EnemyRoot::leave_();
}

void VacuumEnemyRoot::loadParams_() {
    EnemyRoot::loadParams_();
}

}  // namespace uking::ai
