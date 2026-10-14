#include "Game/Actor/AI/aiSignalSendingMagneStickAcceptor.h"
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

// 0x710056bd78
void SignalSendingMagneStickAcceptor::sub_710056BD78(ksys::act::ActorLinkConstDataAccess* acc) {
    f32 min_dist = *mMagneStickMaxSearchDistance_m;
    s32 index = 0;
    auto* actor = mActor;
    if (!actor)
        return;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    while (auto* object = sub_710056BE7C(actor, &index, nullptr)) {
        ksys::act::ActorLinkConstDataAccess other;
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

// NON_MATCHING: the original keeps `index != nullptr` in a register of its own and counts the loop in 32 bits
// (`i != num`); ours tests the pointer and uses a 64-bit counter
ksys::map::Object* SignalSendingMagneStickAcceptor::sub_710056BE7C(
    ksys::act::Actor* actor, s32* index,
    sead::IDelegate1R<const ksys::act::ActorLinkConstDataAccess&, bool>* filter) {
    if (!actor) {
        if (index)
            *index = -1;
        return nullptr;
    }

    ksys::act::ActorLinkConstDataAccess acc(actor);
    s32 start = 0;
    if (index) {
        start = sead::Mathi::max(*index, 0);
        *index = -1;
    }

    auto* link_data = acc.getMapObjectLinkData();
    if (!link_data)
        return nullptr;

    const s32 num = link_data->mObjects.size();
    auto* objects = link_data->mObjects.getBufferPtr();
    for (s32 i = start; i < num; ++i) {
        if (!objects[i])
            continue;
        ksys::act::ActorLinkConstDataAccess other;
        objects[i]->getActorWithAccessor(other);
        if (!other.hasProc())
            continue;
        if (filter && !(*filter)(other))
            continue;
        if (index)
            *index = i;
        return objects[i];
    }
    return nullptr;
}

void SignalSendingMagneStickAcceptor::calc_() {
    if (!mActor)
        return;

    ksys::act::ActorLinkConstDataAccess acc;
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
