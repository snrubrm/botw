#include "Game/AI/AI/aiSignalSendingMagneStickAcceptor.h"
#include "KingSystem/ActorSystem/actActor.h"
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

// NON_MATCHING: the original never sets x0 for the 0x710056be7c call (it keeps whatever was in x0: `this` on the first
// iteration, the accessor dtor's return value afterwards) and so keeps `this` out of a callee-saved register; the helper's
// first parameter is unknown, ours passes `this`
// 0x710056bd78
void SignalSendingMagneStickAcceptor::sub_710056BD78(ksys::act::ActorConstDataAccess* acc) {
    f32 min_dist = *mMagneStickMaxSearchDistance_m;
    s32 index = 0;
    auto* actor = mActor;
    if (!actor)
        return;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    while (auto* object = sub_710056BE7C(actor, &index, nullptr)) {
        ksys::act::ActorConstDataAccess other;
        object->getActorWithAccessor(other);
        const sead::Vector3f other_pos = other.getActorMtx().getTranslation();
        const f32 dist = (other_pos - pos).length();
        if (dist < min_dist) {
            acc->acquireActor(other);
            min_dist = dist;
        }
        ++index;
    }
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
