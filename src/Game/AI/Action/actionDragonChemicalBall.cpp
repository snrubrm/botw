#include "Game/AI/Action/actionDragonChemicalBall.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

DragonChemicalBall::DragonChemicalBall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DragonChemicalBall::~DragonChemicalBall() = default;

bool DragonChemicalBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DragonChemicalBall::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        const sead::Matrix34f mtx = actor->getMtx();
        body->setTransform(mtx);
        body->setGravityFactor(*mGravity_s);
    }
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        const sead::Matrix34f mtx = actor->getMtx();
        body->setTransform(mtx);
        body->setScale(*mHitScale_s);
        sub_71007A2B64(body, nullptr);
        sub_71007A2EB0(body, actor, nullptr);
    }
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D91098(true);
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2c, true);
}

void DragonChemicalBall::leave_() {
    auto* actor = mActor;
    sub_71007A32E4(actor, nullptr);
    sub_71007A2E04(actor);
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D91098(false);
}

void DragonChemicalBall::loadParams_() {
    getStaticParam(&mLife_s, "Life");
    getStaticParam(&mHitScale_s, "HitScale");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mHomingPower_s, "HomingPower");
    getStaticParam(&mHomingDistance_s, "HomingDistance");
    getStaticParam(&mHomingTime_s, "HomingTime");
}

// NON_MATCHING: register assignment and load/scheduling order only — our (dx, dy, dz) land in
// s12/s11/s10 (the original's s11/s10/s12), cascading through the impulse fmuls, and our
// HomingPower-float/mMainBody loads sit on opposite sides of them. All calls, branches, constants
// and the sqrt/normalize/Timer shapes match.
void DragonChemicalBall::calc_() {
    ksys::Timer::update(&_50, 1.0f);
    if (f32(*mLife_s) < _50)
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    if (auto* manager = ksys::evt::Manager::instance()) {
        if (manager->hasActiveEvent() || manager->_1d3e0)
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    if (_54 < *mHomingTime_s) {
        const sead::Vector3f& player = getPlayerPosition();
        const auto& mtx = mActor->getMtx();
        const f32 mx = mtx.m[0][3];
        const f32 my = mtx.m[1][3];
        const f32 mz = mtx.m[2][3];
        const f32 px = player.x;
        const f32 py = player.y;
        f32 dx = px - mx;
        f32 dy = py - my;
        const f32 pz = player.z;
        f32 dz = pz - mz;
        const f32 dist_sq = dx * dx + dy * dy + dz * dz;
        if (dist_sq < *mHomingDistance_s * *mHomingDistance_s) {
            const f32 len = std::sqrt(dist_sq);
            if (len > 0.0f) {
                const f32 inv = 1.0f / len;
                dx *= inv;
                dy *= inv;
                dz *= inv;
            }
            const f32 power = *mHomingPower_s;
            const sead::Vector3f impulse(dist_sq * dx * power, dist_sq * dy * power,
                                         dist_sq * dz * power);
            mActor->getMainBody()->applyLinearImpulse(impulse);
            ksys::Timer::update(&_54, 1.0f);
        }
    }
}

}  // namespace uking::action
