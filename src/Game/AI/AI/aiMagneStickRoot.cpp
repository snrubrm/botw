#include "Game/AI/AI/aiMagneStickRoot.h"
#include "Game/gameGearMgr.h"
#include <algorithm>
#include <math/seadBoundBox.h>
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/System/physShapeCastWithInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

MagneStickRoot::MagneStickRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MagneStickRoot::~MagneStickRoot() = default;

bool MagneStickRoot::init_(sead::Heap* heap) {
    if (*mRegistFromBeginning_m)
        m34();
    _8c = ksys::Timer(1, 1);
    return true;
}

void MagneStickRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _7c = 0;
    changeChild("通常");
    _8c = ksys::Timer(1, 1);
    auto* actor = mActor;
    if (!actor)
        return;

    auto* body = actor->getMainBody();
    if (!body)
        return;

    _98 = actor->findPhysicsBodyByName("EntitySensor", "SensorBody");
    sead::BoundBox3f aabb;
    body->getAabbInLocal(&aabb);
    _88 = aabb.getMax().z - aabb.getMin().z;
    _80 = body->getMaxLinearVelocity();
    _84 = body->getMaxAngularVelocity();
    sub_71007A458C(actor, *mIgnoreObstacle_m);
}

void MagneStickRoot::calc_() {
    auto* actor = mActor;
    if (!actor)
        return;

    const bool grabbed = actor->m128()->m2();
    if (auto* gear_mgr = GearMgr::instance()) {
        const bool registered = gear_mgr->sub_71006690B8(actor);
        if (actor->hasPlacementLinkForBasicSig()) {
            const bool signal = actor->checkBasicSig();
            if (!registered) {
                if (signal)
                    m34();
            } else if (!signal) {
                m35();
            }
        }
    }

    if (_79)
        return;
    if (!getCurrentChild()->isChangeable())
        return;

    if (isCurrentChild("はめ込まれた")) {
        if (grabbed) {
            changeChild("通常");
            _8c = ksys::Timer(30, 30);
            if (auto* body = actor->getMainBody()) {
                body->x_114(true);
                body->setMagneMassScalingFactor(1.0f);
            }
            m51();
        }
    } else if (_8c.value <= sead::Mathf::epsilon()) {
        if (m40()) {
            m50();
            changeChild("はめ込まれた");
            ksys::eft::searchAndEmitSLink(mActor, "Put", false);
            _79 = *mIsTargetFixedAcceptor_a;
        }
    } else {
        _8c.update();
    }
}

void MagneStickRoot::leave_() {
    if (auto* gear_mgr = GearMgr::instance())
        gear_mgr->sub_71006694B4(mActor);
}

bool MagneStickRoot::handleMessage_(const ksys::Message* message) {
    if (!message)
        return false;
    auto* gear_mgr = GearMgr::instance();
    if (!gear_mgr)
        return false;
    if (!mActor)
        return false;

    if (gear_mgr->sub_71006690B8(mActor)) {
        if (message->getType() == 0x3000003) {
            gear_mgr->sub_71006698B0(true);
            return false;
        }
        if (message->getType() == 0x3000004) {
            gear_mgr->sub_71006698B0(false);
            return true;
        }
        return false;
    }

    if (!isCurrentChild("はめ込まれた"))
        return false;
    if (message->getType() == 0x3000003) {
        m36();
        return false;
    }
    if (message->getType() == 0x3000004) {
        m37();
        return true;
    }
    return false;
}

void MagneStickRoot::loadParams_() {
    getStaticParam(&mDefaultConnectionDistance_s, "DefaultConnectionDistance");
    getStaticParam(&mCollideRadiusFactor_s, "CollideRadiusFactor");
    getMapUnitParam(&mCollideRadius_m, "CollideRadius");
    getMapUnitParam(&mJoinSystemGroup_m, "JoinSystemGroup");
    getMapUnitParam(&mRegistFromBeginning_m, "RegistFromBeginning");
    getMapUnitParam(&mIgnoreObstacle_m, "IgnoreObstacle");
    getAITreeVariable(&mIsTargetFixedAcceptor_a, "IsTargetFixedAcceptor");
}

void MagneStickRoot::m35() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_71006694B4(mActor);
}

void MagneStickRoot::m34() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_71006692F0(mActor, *mJoinSystemGroup_m);
}

void MagneStickRoot::m36() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_710066956C(mActor, *mJoinSystemGroup_m);
}

void MagneStickRoot::m37() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_71006695DC(mActor);
}

void MagneStickRoot::m38() {
    auto* gear_mgr = GearMgr::instance();
    if (!gear_mgr || !mActor || !*mJoinSystemGroup_m)
        return;
    auto* handler = gear_mgr->_1050;
    if (auto* body = mActor->getMainBody())
        body->setSystemGroupHandler(handler);
}

void MagneStickRoot::m39() {
    if (!GearMgr::instance() || !mActor || !*mJoinSystemGroup_m)
        return;
    if (auto* body = mActor->getMainBody())
        body->setSystemGroupHandler(nullptr);
}

bool MagneStickRoot::m41(const sead::Matrix34f* mtx, const sead::Vector3f* a,
                         const sead::Vector3f* b) {
    if (auto* actor = mActor) {
        if ((sead::Vector3f::ez * a->z - *a).length() <= 0.01f) {
            sead::Vector3f dir = actor->getMtx().getTranslation() - *b;
            dir.normalize();
            sead::Vector3f axis{mtx->m[0][2], mtx->m[1][2], mtx->m[2][2]};
            axis.normalize();
            if (std::acos(sead::Mathf::abs(dir.dot(axis))) <= sead::Mathf::deg2rad(4))
                return true;
        }
    }
    return false;
}

bool MagneStickRoot::m44(ksys::act::ActorLinkConstDataAccess* accessor, const sead::Vector3f* pos,
                         const sead::BoundBox3f* bounds) {
    return m46(accessor, pos, bounds);
}

bool MagneStickRoot::m47(ksys::act::ActorLinkConstDataAccess* accessor, const sead::Vector3f* pos,
                         const sead::BoundBox3f* bounds) {
    sead::Vector3f start;
    start = accessor->getActorMtx().getTranslation();
    bool result = false;
    if ((start - *pos).length() > sead::Mathf::epsilon()) {
        const f32 radius = sead::Mathf::max((bounds->getMax().x - bounds->getMin().x) * 0.5f,
                                            (bounds->getMax().y - bounds->getMin().y) * 0.5f);
        ksys::phys::SphereCast cast{ksys::phys::ContactLayer::EntityObject,
                                    ksys::phys::GroundHit::HitAll,
                                    nullptr,
                                    0x80,
                                    ksys::phys::ShapeCast::Mode::_0,
                                    sead::Vector3f::zero,
                                    radius,
                                    sead::SafeString::cEmptyString,
                                    ksys::phys::LowPriority::No};
        cast.setMode(ksys::phys::ShapeCast::Mode::_2);
        cast.setStartAndEnd(*pos, start);
        result = sub_71004A1138(&cast);
    }
    return result;
}

// NON_MATCHING: the original loads the actor matrix up front and copies rows 0-2 of it as 8-byte + 4-byte
// pieces; ours reloads the elements (scheduling / load order only)
bool MagneStickRoot::m45(ksys::act::ActorLinkConstDataAccess* accessor, const sead::Vector3f* pos,
                         const sead::BoundBox3f* bounds) {
    bool result = false;
    if (_98) {
        const sead::Matrix34f& mtx = accessor->getActorMtx();
        const sead::Vector3f trans = mtx.getTranslation();
        sead::Vector3f dir = trans - *pos;
        const f32 distance = dir.length();
        if (distance > sead::Mathf::epsilon()) {
            dir.normalize();
            const f32 half = (bounds->getMax().z - bounds->getMin().z) * 0.5f;
            const f32 length = sead::Mathf::min(half, distance * 0.5f);
            const sead::Vector3f end = trans - dir * length;
            sead::Vector3f x_axis = mtx.getBase(1).cross(dir);
            x_axis.normalize();
            sead::Vector3f y_axis = dir.cross(x_axis);
            y_axis.normalize();
            sead::Matrix34f rot;
            rot.setBase(0, x_axis);
            rot.setBase(1, y_axis);
            rot.setBase(2, dir);
            rot.setTranslation(0, 0, 0);
            const sead::Vector3f start = *pos + dir * length;
            ksys::phys::ShapeCastWithInfo cast{_98, 0x80, ksys::phys::ShapeCast::Mode::_0,
                                               sead::SafeString::cEmptyString,
                                               ksys::phys::LowPriority::No};
            cast.setRotation(rot);
            cast.setStartAndEnd(start, end);
            cast.setMode(ksys::phys::ShapeCast::Mode::_2);
            result = sub_71004A1138(&cast);
        }
    }
    return result;
}

// NON_MATCHING: the original loads the actor matrix rows up front (8-byte pair loads) and builds the
// rotation matrix from those registers; ours reloads the rows (scheduling / load order only)
bool MagneStickRoot::m46(ksys::act::ActorLinkConstDataAccess* accessor, const sead::Vector3f* pos,
                         const sead::BoundBox3f* bounds) {
    bool result = false;
    if (_98) {
        const sead::Matrix34f& mtx = accessor->getActorMtx();
        sead::Vector3f dir = mtx.getTranslation() - *pos;
        if (dir.length() > sead::Mathf::epsilon()) {
            dir.normalize();
            const f32 half = (bounds->getMax().z - bounds->getMin().z) * 0.5f;
            sead::Matrix34f rot{sead::Matrix33f{mtx}, {0, 0, 0}};
            sead::Vector3f end = mtx.getTranslation() + mtx.getBase(2) * half;
            sead::Vector3f start = end;
            ksys::phys::ShapeCastWithInfo cast{_98, 0x80, ksys::phys::ShapeCast::Mode::_0,
                                               sead::SafeString::cEmptyString,
                                               ksys::phys::LowPriority::No};
            cast.setRotation(rot);
            cast.setStartAndEnd(start, end);
            cast.setMode(ksys::phys::ShapeCast::Mode::_2);
            result = sub_71004A1138(&cast);
        }
    }
    return result;
}

void MagneStickRoot::m49(sead::Vector3f* out, sead::Vector3f pos, const sead::Vector3f& target) {
    auto* actor = mActor;
    if (!actor)
        return;
    const sead::Vector3f diff = pos - target;
    const f32 scale = 1.0f / std::max(diff.length(), 0.5f) * 0.25f;
    *out = actor->getMtx().getTranslation() + diff * scale;
}

// NON_MATCHING: the stack layout matches, but the original builds the SafeString at function entry (before
// the null checks) and orders the accessor stores after the argument loads; the final fmul commutes.
f32 MagneStickRoot::m42() {
    const f32 radius = *mCollideRadius_m;
    if (!mActor)
        return radius;

    const f32 factor = *mCollideRadiusFactor_s;
    auto* body = mActor->getMainBody();
    if (!body)
        return radius;
    auto* info = body->getContactPointInfo();
    if (!info || info->getNumContactPoints() == 0 || info->begin().isEnd())
        return radius;

    const sead::SafeString slider_name("DgnObj_DLC_SliderBlockIron_A_01");
    for (auto it = info->begin(), end = info->end(); it != end; ++it) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::sub_7100EEAC50(&accessor, (*it)->body_b);
        if (accessor.hasProc() && accessor.getName() == slider_name)
            return factor * radius;
    }
    return radius;
}

}  // namespace uking::ai
