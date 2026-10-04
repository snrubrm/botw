#include "Game/AI/Action/actionRequestCreateHCIModel.h"

#include "Game/gameHorseColorInfoMgr.h"

namespace uking::action {

RequestCreateHCIModel::RequestCreateHCIModel(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RequestCreateHCIModel::~RequestCreateHCIModel() = default;

bool RequestCreateHCIModel::oneShot_() {
    if (auto* mgr = HorseColorInfoMgr::instance())
        mgr->sub_710094D018();
    return true;
}

bool RequestCreateHCIModel::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RequestCreateHCIModel::loadParams_() {}

}  // namespace uking::action
