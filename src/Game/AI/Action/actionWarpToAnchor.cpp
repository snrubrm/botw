#include "Game/AI/Action/actionWarpToAnchor.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

WarpToAnchor::WarpToAnchor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToAnchor::~WarpToAnchor() = default;

bool WarpToAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToAnchor::loadParams_() {
    getDynamicParam(&mDirectionY_d, "DirectionY");
    getDynamicParam(&mDestinationY_d, "DestinationY");
    getDynamicParam(&mDestinationZ_d, "DestinationZ");
    getDynamicParam(&mDestinationX_d, "DestinationX");
}

bool WarpToAnchor::oneShot_() {
    if (!mActor)
        return false;

    _70.set(mActor->getScale());
    m32();
    mActor->setMtx(_40, false, true);
    if (auto* npc = sead::DynamicCast<uking::act::NPC>(mActor)) {
        npc->_10a4 = _40.m[1][3];
        npc->_fe8 |= 2;
    }
    return true;
}

void WarpToAnchor::m32() {
    const sead::Vector3f translation(*mDestinationX_d, *mDestinationY_d, *mDestinationZ_d);
    const sead::Vector3f rotation(0, sead::Mathf::deg2rad(*mDirectionY_d), 0);
    _40.makeSRT(_70, rotation, translation);
}

}  // namespace uking::action
