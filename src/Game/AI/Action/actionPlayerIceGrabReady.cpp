#include "Game/AI/Action/actionPlayerIceGrabReady.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::action {

PlayerIceGrabReady::PlayerIceGrabReady(const InitArg& arg) : PlayerAction(arg) {}

PlayerIceGrabReady::~PlayerIceGrabReady() = default;

// NON_MATCHING: scheduling only (the original keeps the connected-child pointer in a register for the
// `_17f0` store and orders the translation stores differently)
void PlayerIceGrabReady::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20);
    static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
    static_cast<ksys::act::Player*>(mActor)->m228(false);

    bool had_connected_child = false;
    if (mActor->getConnectedCalcChild()) {
        mActor->resetConnectedCalcChild(false);
        had_connected_child = true;
    }
    static_cast<ksys::act::Player*>(mActor)->_17f0 = had_connected_child;

    if (_20.isAllocatedOrFailed())
        _20.deleteProc();

    ksys::act::InstParamPack pack;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const sead::Vector3f pos = player->_1770;
    sead::Matrix34f mtx = player->_1b18;
    mtx.setTranslation(pos.x, pos.y + 2.0f, pos.z);
    pack->addMatrix(mtx);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "IceBlock", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_20, &pack, nullptr,
        1);
}

void PlayerIceGrabReady::leave_() {}

void PlayerIceGrabReady::calc_() {
    PlayerAction::calc_();
}

bool PlayerIceGrabReady::isChangeable() const {
    return false;
}

}  // namespace uking::action
