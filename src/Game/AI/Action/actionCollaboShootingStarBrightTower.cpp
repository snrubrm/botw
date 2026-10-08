#include "Game/AI/Action/actionCollaboShootingStarBrightTower.h"
#include <codec/seadHashCRC32.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

CollaboShootingStarBrightTower::CollaboShootingStarBrightTower(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CollaboShootingStarBrightTower::~CollaboShootingStarBrightTower() = default;

bool CollaboShootingStarBrightTower::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CollaboShootingStarBrightTower::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* anchor = ksys::world::ShootingStarMgrEx::sub_71010D0464(_48);
    if (!anchor)
        return;

    anchor->sub_71010D0734();
    anchor->sub_71010D07A4();
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    mActor->getXLink()->_cc.resetBit(19);
    const sead::Vector3f pos = anchor->_48;
    xlinkSearchAndEmit(mActor, "BrightTower_01", 2, &_28);
    _28.sub_71012419B4(pos);
    mActor->getMainBody()->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
    mActor->getMainBody()->setAngularVelocity(sead::Vector3f::zero);
    mActor->getMainBody()->setLinearVelocity(sead::Vector3f::zero);
    mActor->getMainBody()->setGravityFactor(0.0f);
    mActor->getMainBody()->setPosition(pos);
    mActor->getLodState()->mFlags10.set(0x40);
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
