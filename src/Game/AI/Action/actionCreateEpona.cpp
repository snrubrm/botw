#include "Game/AI/Action/actionCreateEpona.h"
#include "KingSystem/Physics/System/physHavokAI.h"

namespace uking::action {

CreateEpona::CreateEpona(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CreateEpona::~CreateEpona() {
    leave_();
}

bool CreateEpona::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateEpona::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CreateEpona::leave_() {
    if (_198.isAllocatedOrFailed())
        _198.deleteProc();
    if (_1a8)
        ksys::phys::HavokAI::instance()->destroyQuery(_1a8);
}

void CreateEpona::loadParams_() {
    getStaticParam(&mAreaSearchCharacterRadius_s, "AreaSearchCharacterRadius");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mAreaSearchRadius_s, "AreaSearchRadius");
    getStaticParam(&mCreateStartRate_s, "CreateStartRate");
}

void CreateEpona::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
