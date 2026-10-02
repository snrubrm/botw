#include "Game/AI/AI/aiBalloonPlantNormal.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

BalloonPlantNormal::BalloonPlantNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BalloonPlantNormal::~BalloonPlantNormal() = default;

bool BalloonPlantNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BalloonPlantNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710032782C();
    _60.copy("Body");
    ksys::act::disableAllAttClients(mActor);
    _c4 = false;
    _b8.set(sead::Vector3f::zero);
    _60.clear();
    _c8 = 0;
    changeChild("準備待機");
}

void BalloonPlantNormal::leave_() {
    if (_50.hasProcCreationFailed())
        _50.deleteProcIfFailed();
    if (_50.isAllocatedOrFailed())
        _50.deleteProc();
}

void BalloonPlantNormal::loadParams_() {
    getStaticParam(&mRopeLength_s, "RopeLength");
    getStaticParam(&mRopeActorName_s, "RopeActorName");
}

}  // namespace uking::ai
