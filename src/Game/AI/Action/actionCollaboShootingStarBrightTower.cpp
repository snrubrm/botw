#include "Game/AI/Action/actionCollaboShootingStarBrightTower.h"
#include <codec/seadHashCRC32.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

CollaboShootingStarBrightTower::CollaboShootingStarBrightTower(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CollaboShootingStarBrightTower::~CollaboShootingStarBrightTower() = default;

bool CollaboShootingStarBrightTower::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CollaboShootingStarBrightTower::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CollaboShootingStarBrightTower::leave_() {
    _28.fadeXLink();
}

void CollaboShootingStarBrightTower::loadParams_() {
    getAITreeVariable(&mCollaboShootingStarId_a, "CollaboShootingStarId");
    const sead::SafeString id = mCollaboShootingStarId_a->cstr();
    _48.name = id;
    _48.hash = sead::HashCRC32::calcStringHash(id.cstr());
}

void CollaboShootingStarBrightTower::calc_() {
    if (isFinished() || isFailed())
        return;
    ksys::world::ShootingStarAnchor* anchor =
        ksys::world::ShootingStarMgrEx::sub_71010D0464(_48);
    if (anchor != nullptr && !anchor->sub_71010D0734())
        setFailed();
    const sead::Vector3f& player_pos = getPlayerPosition();
    // NON_MATCHING: the original loads the actor matrix X/Z before the player position;
    // ours loads them in the opposite order. Values, branches and calls are identical.
    const f32 dx = player_pos.x - mActor->getMtx().m[0][3];
    const f32 dz = player_pos.z - mActor->getMtx().m[2][3];
    if (!((dx * dx + dz * dz) < 625.0f))
        return;
    setFinished();
}

}  // namespace uking::action
