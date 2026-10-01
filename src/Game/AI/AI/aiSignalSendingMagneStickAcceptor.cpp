#include "Game/AI/AI/aiSignalSendingMagneStickAcceptor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::ai {

SignalSendingMagneStickAcceptor::SignalSendingMagneStickAcceptor(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SignalSendingMagneStickAcceptor::~SignalSendingMagneStickAcceptor() = default;

bool SignalSendingMagneStickAcceptor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SignalSendingMagneStickAcceptor::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("抜けた");
}

void SignalSendingMagneStickAcceptor::calc_() {
    if (!mActor)
        return;

    ksys::act::ActorConstDataAccess acc;
    sub_710056BD78(&acc);
    if (!acc.hasProc())
        return;

    bool linked = false;
    if (auto* obj = acc.getMapObject()) {
        auto* link_data = obj->getLinkData();
        if (link_data && link_data->findLinkWithType(ksys::map::MapLinkDefType::BasicSig))
            linked = link_data->mLinksOther.checkLink(ksys::map::MapLinkDefType::BasicSig, true);
    }

    if (isCurrentChild("抜けた")) {
        if (linked)
            changeChild("刺さった");
    } else if (!linked) {
        changeChild("抜けた");
    }
}

void SignalSendingMagneStickAcceptor::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SignalSendingMagneStickAcceptor::loadParams_() {
    getMapUnitParam(&mMagneStickMaxSearchDistance_m, "MagneStickMaxSearchDistance");
}

}  // namespace uking::ai
