#include "Game/AI/AI/aiGolemPartRoot.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

GolemPartRoot::GolemPartRoot(const InitArg& arg) : ReuseBulletPartsRoot(arg) {}

GolemPartRoot::~GolemPartRoot() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_c8, &accessor);
    if (accessor.hasProc() && accessor.isStateSleep())
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

bool GolemPartRoot::init_(sead::Heap* heap) {
    return ReuseBulletPartsRoot::init_(heap);
}

void GolemPartRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ReuseBulletPartsRoot::enter_(params);
}

void GolemPartRoot::calc_() {
    ReuseBulletPartsRoot::calc_();
}

void GolemPartRoot::leave_() {
    ReuseBulletPartsRoot::leave_();
}

void GolemPartRoot::loadParams_() {
    ReuseBulletPartsRoot::loadParams_();
    getStaticParam(&mChemFieldScale_s, "ChemFieldScale");
    getStaticParam(&mNormalAS_s, "NormalAS");
    getStaticParam(&mActiveAS_s, "ActiveAS");
    getAITreeVariable(&mGolemPartInitialIceMagic_a, "GolemPartInitialIceMagic");
    getAITreeVariable(&mGolemPartInitialBurn_a, "GolemPartInitialBurn");
}

}  // namespace uking::ai
