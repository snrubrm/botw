#include "Game/Actor/AI/aiTreasureBoxRoot.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyMotionEntity.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "Game/gameSceneSubsysMisc.h"

namespace uking::ai {

TreasureBoxRoot::TreasureBoxRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TreasureBoxRoot::~TreasureBoxRoot() = default;

bool TreasureBoxRoot::init_(sead::Heap* heap) {
    if (*mIsInGround_m)
        _79 = false;
    return true;
}

void TreasureBoxRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* map = actor->getMapObject();
    const bool linked = actor->checkLinkBasicSig();
    const bool used = actor->isWaitRevivalForUsed();
    const bool revival = map && map->checkRevivalFlag(ksys::map::ActorData::Flag::RevivalEnable);
    if (auto* body = actor->getMainBody())
        body->getMotionType();
    if (!*mIsInGround_m) {
        enter_init();
        return;
    }
    if (linked || used || revival || _79)
        enter_init();
    else
        sub_71005CEA88();
}

void TreasureBoxRoot::enter_init() {
    auto* actor = mActor;
    auto* physics = actor->getPhysics();
    if (physics) {
        if (*mIsInGround_m)
            physics->sub_7100FBADDC();
        if (actor->getName().findIndex("Iron") != -1 ||
            actor->getName().findIndex("Wood") != -1 ||
            actor->getName().findIndex("Sandworm") != -1) {
            if (auto* body = physics->findRigidBody("Cover"))
                body->changeMotionType(ksys::phys::MotionType::Dynamic);
        }
    }
    _78 = true;
    _79 = true;
    sub_71005DD1CC(actor, true, 0.0f, 1.0f);
    changeChild("地上", nullptr);
}

void TreasureBoxRoot::sub_71005CEA88() {
    auto* actor = mActor;
    ksys::act::disableAllAttClients(actor);
    if (actor->getPhysics()) {
        if (auto* set = actor->getRigidBodyByName("Body")) {
            for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i)
                set->getRigidBody(i)->changeMotionType(ksys::phys::MotionType::Keyframed);
        }
    }
    _78 = false;
    _79 = false;
    _7a = sub_71005DD1CC(actor, false, 1.0f, 1.0f);
    if (!_7a)
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    changeChild("地中", nullptr);
}

// NON_MATCHING: vector temporary stack slots, copy scheduling and multiplication order differ.
void TreasureBoxRoot::calc_() {
    auto* actor = mActor;
    if (isCurrentChild("地中") && !_7a) {
        _7a = sub_71005DD1CC(actor, true, 1.0f, 1.0f);
        if (_7a)
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    }
    bool inactive = true;
    if (auto* state = actor->m128())
        inactive = !state->m2();
    auto* scene = GameSceneSubsys5::instance();
    if ((!scene || !scene->sub_7100905BEC() || inactive) && !_79)
        return;
    if (!isCurrentChild("地中"))
        return;
    if (scene)
        scene->sub_7100905C70();
    _79 = true;
    sead::Vector3f position;
    actor->getMtx().getTranslation(position);
    sead::Vector3f normal = sead::Vector3f::zero;
    const bool hit = sub_71005CEDD4(&position, &normal, true, *mInGroundOffsetY_s, *mInGroundScale_s);
    if (!_78) {
        Unk_71012419b4 effect;
        xlinkSearchAndEmit(actor, "DigOut", 2, &effect);
        effect.sub_71012419B4(position);
        _78 = true;
    }
    normal = sead::Vector3f::ey;
    normal *= *mJumpPower_s;
    if (auto* body = actor->getMainBody()) {
        if (hit) {
            sead::Vector3f target;
            actor->getMtx().getTranslation(target);
            target += normal;
            body->changePosition(target, static_cast<ksys::phys::KeepAngularVelocity>(false));
            if (*mDebugDraw_s) {
                sead::Vector3f center;
                actor->getMtx().getTranslation(center);
                body->getCenterOfMassInWorld(&center);
            }
        } else {
            enter_init();
        }
    }
}

// NON_MATCHING: common direction selection and ray setup replace the native two branch copies.
bool TreasureBoxRoot::sub_71005CEDD4(sead::Vector3f* position, sead::Vector3f* normal,
                                     bool upward, f32 offset, f32 distance) {
    auto* actor = mActor;
    ksys::phys::RayCastBodyQuery cast(nullptr, ksys::phys::GroundHit::HitAll);
    cast.enableLayer(ksys::phys::ContactLayer::EntityGround);
    cast.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    cast.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    sead::Vector3f start = actor->getMtx() * sead::Vector3f(0.0f, offset, 0.0f);
    sead::Vector3f direction(0.0f, upward ? 1.0f : -1.0f, 0.0f);
    direction.rotate(actor->getMtx());
    cast.setStartAndDisplacementScaled(start, direction, distance);
    if (upward)
        cast.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_1);
    if (!cast.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;
    cast.getHitPosition(position);
    cast.getHitNormal(normal);
    if (upward)
        *normal = -*normal;
    return true;
}

void TreasureBoxRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TreasureBoxRoot::loadParams_() {
    getStaticParam(&mInGroundOffsetY_s, "InGroundOffsetY");
    getStaticParam(&mInGroundScale_s, "InGroundScale");
    getStaticParam(&mOnGroundOffsetY_s, "OnGroundOffsetY");
    getStaticParam(&mOnGroundScale_s, "OnGroundScale");
    getStaticParam(&mJumpPower_s, "JumpPower");
    getStaticParam(&mDebugDraw_s, "DebugDraw");
    getMapUnitParam(&mIsInGround_m, "IsInGround");
    getMapUnitParam(&mEnableRevival_m, "EnableRevival");
}

bool TreasureBoxRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() != ksys::MessageType(0x3000007))
        return false;

    auto* actor = mActor;
    if (*mEnableRevival_m)
        actor->becomePreActor(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason::_0);
    else
        actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    return true;
}

}  // namespace uking::ai
