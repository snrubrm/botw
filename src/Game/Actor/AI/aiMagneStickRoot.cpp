#include "Game/Actor/AI/aiMagneStickRoot.h"
#include <math/seadQuat.h>
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/System/VFR.h"
#include "Game/gameGearMgr.h"
#include <algorithm>
#include <math/seadBoundBox.h>
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/System/physShapeCastWithInfo.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/ActorSystem/actTag.h"
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

// NON_MATCHING: the original unswitches the loop three ways (filter / index / neither) with
// cleanup-state codes for the accessor; ours keeps fewer copies. Same calls and logic.
ksys::map::Object* MagneStickRoot::sub_71004A0174(ksys::act::BaseProc* proc, s32* idx,
                                                   Unk_7102407060* filter) {
    if (!proc) {
        if (idx)
            *idx = -1;
        return nullptr;
    }
    ksys::act::ActorLinkConstDataAccess accessor(proc);
    s32 start = 0;
    bool has_idx = false;
    if (idx) {
        start = std::max(*idx, 0);
        *idx = -1;
        has_idx = true;
    }
    auto* link_data = accessor.getMapObjectLinkData();
    if (!link_data)
        return nullptr;
    const s32 num = link_data->mObjects.size();
    for (s32 i = start; i < num; ++i) {
        auto* obj = link_data->mObjects.getBufferPtr()[i];
        if (!obj)
            continue;
        ksys::act::ActorLinkConstDataAccess obj_accessor;
        obj->getActorWithAccessor(obj_accessor);
        if (!obj_accessor.hasProc())
            continue;
        if (filter && !filter->m0(obj_accessor))
            continue;
        if (has_idx)
            *idx = i;
        return link_data->mObjects.getBufferPtr()[i];
    }
    return nullptr;
}

void MagneStickRoot::sub_71004A0384(ksys::act::ActorLinkConstDataAccess* out) {
    f32 min_dist = _88;
    s32 idx = 0;
    Unk_7102407060 filter(0x7fe6e43f);
    auto* actor = mActor;
    if (!actor)
        return;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    while (auto* obj = sub_71004A0174(actor, &idx, &filter)) {
        ksys::act::ActorLinkConstDataAccess accessor;
        obj->getActorWithAccessor(accessor);
        const f32 dist = (accessor.getActorMtx().getTranslation() - pos).length();
        if (dist < min_dist) {
            out->acquireActor(accessor);
            min_dist = dist;
        }
        ++idx;
    }
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

bool MagneStickRoot::m44(ksys::act::BaseProcAccessor* accessor, const sead::Vector3f* pos,
                         const sead::BoundBox3f* bounds) {
    return m46(accessor, pos, bounds);
}

bool MagneStickRoot::m47(ksys::act::BaseProcAccessor* accessor, const sead::Vector3f* pos,
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
bool MagneStickRoot::m45(ksys::act::BaseProcAccessor* accessor, const sead::Vector3f* pos,
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
bool MagneStickRoot::m46(ksys::act::BaseProcAccessor* accessor, const sead::Vector3f* pos,
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
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::sub_7100EEAC50(&accessor, (*it)->body_b);
        if (accessor.hasProc() && accessor.getName() == slider_name)
            return factor * radius;
    }
    return radius;
}

// NON_MATCHING: block layout of the contact-point loop (the original keeps the result in a register and
// returns through one exit).
bool MagneStickRoot::sub_71004A1138(ksys::phys::ShapeCast* cast) {
    if (!mActor)
        return false;
    auto* info = cast->getContactPointInfo();
    if (!info)
        return false;

    const u32 id = mActor->getId();
    info->subscribeLayer(ksys::phys::ContactLayer::EntityObject);
    info->subscribeLayer(ksys::phys::ContactLayer::EntitySmallObject);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityGroundObject);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityPlayer);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityNPC);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityRagdoll);
    if (!cast->executeQuery(ksys::phys::ShapeCast::WeldClosestPoints::Yes))
        return false;

    bool found = false;
    for (auto it = info->begin(), end = info->end(); it != end; ++it) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::sub_7100EEAC50(&accessor, it.getPoint()->body_b);
        if (accessor.hasProc() && !accessor.hasTag(ksys::act::tags::IgnoreMagneStickShapeCast)) {
            found = accessor.getId() != id;
            if (found)
                break;
        }
    }
    return found;
}

void MagneStickRoot::m48(f32 radius, const sead::Matrix34f* mtx, const sead::Vector3f* a,
                         const sead::Vector3f* b) {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* body = actor->getMainBody();
    if (!body)
        return;

    if ((sead::Vector3f::ez * a->z - *a).length() < radius) {
        body->changeMotionType(ksys::phys::MotionType::Keyframed);
        body->setMaxLinearVelocity(_80 * 0.1f);
        body->setMaxAngularVelocity(_84 * 0.1f);

        const f32 max_angle = ksys::VFR::instance()->getDeltaFrame() * 0.0523598790f;
        sead::Vector3f axis = sead::Vector3f::ey;
        sead::Matrix34f result;
        sead::Vector3f pos;
        sead::Matrix34f current = actor->getMtx();
        f32 angle = 0;
        ksys::util::sub_71011EF51C(&axis, &angle, current, *mtx, sead::Vector3f::ey);
        const f32 abs_angle = sead::Mathf::abs(angle);
        f32 step = angle;
        // Ordered compare: the original keeps the full step when max_angle >= |angle| (b.ge).
        if (!(max_angle >= abs_angle))
            step = max_angle * angle / abs_angle;

        sead::Quatf rotation;
        rotation.setAxisRadian(axis, step);
        sead::Matrix34f rotation_mtx;
        rotation_mtx.fromQuat(rotation);
        rotation_mtx.setTranslation(0.0f, 0.0f, 0.0f);
        result.setMul(current, rotation_mtx);

        m49(&pos, mtx->getTranslation(), *b);
        result.setTranslation(pos);
        body->changePositionAndRotation(result, sead::Mathf::epsilon());
    } else {
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
        body->setMaxLinearVelocity(_80);
        body->setMaxAngularVelocity(_84);
    }
}

// NON_MATCHING: scheduling of the front / back end points and the local target position, and the exit
// blocks around the accessor destructor.
bool MagneStickRoot::m40() {
    *mIsTargetFixedAcceptor_a = false;
    auto* actor = mActor;
    if (!actor)
        return false;

    ksys::act::ActorLinkConstDataAccess target;
    sub_71004A0384(&target);
    if (!target.hasProc())
        return false;

    *mIsTargetFixedAcceptor_a = target.hasTag(ksys::act::tags::IsFixedAcceptor);
    sead::Matrix34f target_mtx;
    m43(&target_mtx, &target);

    auto* body = actor->getMainBody();
    if (!body)
        return false;

    sead::BoundBox3f box;
    body->getAabbInLocal(&box);
    const f32 half_length = (box.getMax().z - box.getMin().z) * 0.5f;
    const sead::Vector3f target_pos = target_mtx.getTranslation();
    const sead::Matrix34f mtx = actor->getMtx();
    const sead::Vector3f front = mtx * sead::Vector3f(0, 0, half_length);
    const sead::Vector3f back = mtx * sead::Vector3f(0, 0, -half_length);
    sead::Matrix34f inv;
    inv.setInverse(mtx);
    const sead::Vector3f local = inv * target_pos;
    const sead::Vector3f end = local.z > 0 ? front : back;

    if (m44(&target, &end, &box)) {
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
        return false;
    }

    if (sead::Mathf::abs(local.z) - half_length <= 0.01f && m41(&target_mtx, &local, &end))
        return true;

    const f32 offset = local.z - m42() * (local.z > 0 ? 1.0f : -1.0f);
    if (sead::Mathf::abs(offset) - half_length <= 0.01f) {
        const f32 radius = sead::Mathf::min((box.getMax().x - box.getMin().x) * 0.5f,
                                            (box.getMax().y - box.getMin().y) * 0.5f);
        m48(radius, &target_mtx, &local, &end);
    }
    return false;
}

}  // namespace uking::ai
