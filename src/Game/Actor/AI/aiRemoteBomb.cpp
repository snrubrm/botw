#include "Game/Actor/AI/aiRemoteBomb.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

RemoteBomb::RemoteBomb(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemoteBomb::~RemoteBomb() = default;

bool RemoteBomb::init_(sead::Heap* heap) {
    _198 = nullptr;
    return true;
}

void RemoteBomb::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemoteBomb::leave_() {
    if (_198 && mActor->isDeletedOrDeleting())
        _198->sub_710067ED08(mActor, 0, false);
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->_14c = 1.0f;
}

void RemoteBomb::sub_710054FEF4() {
    _58.x();
    if (_198) {
        _198->sub_710067ED08(mActor, 0, false);
        _198->sub_710067ED08(mActor, 3, true);
    }
    ksys::act::disableAllAttClients(mActor);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    mActor->setFlag(ksys::act::Actor::ActorFlag::_1c, true);
    changeChild("爆発予約");
}

void RemoteBomb::sub_7100550260() {
    _58.x();
    if (_198) {
        _198->sub_710067ED08(mActor, 0, false);
        _198->sub_710067ED08(mActor, 3, true);
    }
    ksys::act::disableAllAttClients(mActor);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    changeChild("爆発");
}

void RemoteBomb::loadParams_() {
    getStaticParam(&mWindRatio_s, "WindRatio");
    getStaticParam(&mXLinkKey_s, "XLinkKey");
    getAITreeVariable(&mIsIgniteCarriedBomb_a, "IsIgniteCarriedBomb");
}

}  // namespace uking::ai
