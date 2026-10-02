#include "Game/AI/AI/aiBalloonPlantNormal.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

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

void BalloonPlantNormal::sub_710032782C() {
    if (_50.isAllocatedOrFailed())
        _50.deleteProc();

    ksys::act::InstParamPack pack;
    pack->addPosition(mActor->getMtx().getTranslation() + sead::Vector3f(0, 0, 0));
    pack->addScale(sead::Vector3f(1.0f, *mRopeLength_s, 1.0f));
    ksys::act::ActorCreator::instance()->requestCreateActor(
        mRopeActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_50,
        &pack, nullptr, 2);
}

}  // namespace uking::ai
