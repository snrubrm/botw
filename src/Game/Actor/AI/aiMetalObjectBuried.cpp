#include "Game/Actor/AI/aiMetalObjectBuried.h"
#include <cmath>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/gameSceneSubsysMisc.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/Physics/System/physRayCast.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

MetalObjectBuried::MetalObjectBuried(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MetalObjectBuried::~MetalObjectBuried() = default;

bool MetalObjectBuried::init_(sead::Heap* heap) {
    _72 = false;
    return true;
}

void MetalObjectBuried::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _74 = 0;
    if (!actor->getMapObject())
        _72 = false;

    if (*mIsInGround_m && !_72) {
        changeToUnderground();
        return;
    }

    ksys::act::enableAllAttClients(actor);
    if (*mIsInGround_m) {
        if (auto* physics = actor->getPhysics())
            physics->sub_7100FBADDC();
    }
    _70 = true;
    _71 = false;
    _72 = true;
    changeChild("地上");
}

// NON_MATCHING: query setup and vector arithmetic scheduling differ.
bool MetalObjectBuried::sub_71004A5990(f32 scale, sead::Vector3f* hit_pos,
                                     sead::Vector3f* normal, f32* distance,
                                     const sead::Vector3f& target) {
    auto* actor = mActor;
    const sead::Vector3f position = actor->getMtx().getTranslation();
    sead::Vector3f direction = target - position;
    if (direction.x == 0.0f && direction.y == 0.0f && direction.z == 0.0f)
        return false;
    const f32 length = direction.normalize();
    if (distance)
        *distance = length;
    if (!(length > _74 * *mCheckGroundRadiusScale_s))
        return false;
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.setGroupHandlerIfAny(sub_710072E804(actor, 0));
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_1);
    sead::Vector3f start;
    sead::Vector3f end;
    if (*mIsCheckGrabYPosFix_s && target.y < position.y) {
        start = position + direction * (_74 * scale);
        end = position - direction * (_74 * scale);
    } else {
        start = position - direction * (_74 * scale);
        end = position + direction * (_74 * scale);
    }
    query.setStartAndEnd(start, end);
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        if (hit_pos)
            query.getHitPosition(hit_pos);
        if (normal) {
            query.getHitNormal(normal);
            *normal = -*normal;
            if (*mIsCheckSelfY_s) {
                sead::Vector3f up = mActor->getMtx().getBase(1);
                up.normalize();
                if (!(up.dot(*normal) >= std::cos(sead::Mathf::piHalf())))
                    return false;
            }
        }
        return true;
    }
    if (!*mIsCheckGrabYPosFix_s)
        return false;
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    if (target.y < position.y) {
        start = position - direction * (_74 * scale);
        end = position + direction * (_74 * scale);
    } else {
        start = position + direction * (_74 * scale);
        end = position - direction * (_74 * scale);
    }
    query.setStartAndEnd(start, end);
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;
    if (hit_pos)
        query.getHitPosition(hit_pos);
    if (normal) {
        query.getHitNormal(normal);
        if (*mIsCheckSelfY_s) {
            sead::Vector3f up = mActor->getMtx().getBase(1);
            up.normalize();
            if (!(up.dot(*normal) >= std::cos(sead::Mathf::piHalf())))
                return false;
        }
    }
    return true;
}

// NON_MATCHING: vector temporaries and the shared transition block differ.
void MetalObjectBuried::calc_() {
    if (!isCurrentChild("地中") || !(_74 > 0.0f))
        return;
    auto* actor = mActor;
    auto* state = actor->m128();
    if (state && !_71) {
        if (state->m2()) {
            auto* scene = GameSceneSubsys5::instance();
            if (scene && (scene->sub_7100905BEC() || *mIsIgnoreResistanceArea_s)) {
                sead::Vector3f target = scene->sub_7100905C38();
                sead::Vector3f hit_pos;
                sead::Vector3f normal;
                f32 distance;
                if (sub_71004A5990(1.6f, &hit_pos, &normal, &distance, target)) {
                    normal.normalize();
                    _71 = true;
                    _78 = actor->getMtx().getTranslation();
                    _84.set(normal);
                    if (!_70) {
                        Unk_71012419b4 handle{};
                        xlinkSearchAndEmit(actor, "DigOut", 2, &handle);
                        handle.sub_71012419B4(hit_pos);
                        _70 = true;
                    }
                } else if (_74 * 3.0f < distance) {
                    scene->sub_7100905C70();
                }
            }
        }
    }
    if (!_71)
        return;
    const sead::Vector3f position = actor->getMtx().getTranslation();
    if (!((_78 - position).length() >= _74 + _74)) {
        const sead::Vector3f target = position + _84 * 3.0f * _74;
        if (sub_71004A5990(1.0f, nullptr, nullptr, nullptr, target)) {
            // The original computes the speed and frame delta here but discards both results.
            mActor->getVelocity().length();
            ksys::VFR::instance()->getDeltaFrame();
            ksys::act::sub_7100EE5980(actor, *mPullOutSpeed_s * _84);
            return;
        }
    }
    ksys::act::enableAllAttClients(mActor);
    if (*mIsInGround_m) {
        if (auto* physics = mActor->getPhysics())
            physics->sub_7100FBADDC();
    }
    _70 = true;
    _71 = false;
    _72 = true;
    changeChild("地上");
}

void MetalObjectBuried::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MetalObjectBuried::loadParams_() {
    getStaticParam(&mPullOutSpeed_s, "PullOutSpeed");
    getStaticParam(&mCheckGroundRadiusScale_s, "CheckGroundRadiusScale");
    getStaticParam(&mIsIgnoreResistanceArea_s, "IsIgnoreResistanceArea");
    getStaticParam(&mIsCheckGrabYPosFix_s, "IsCheckGrabYPosFix");
    getStaticParam(&mIsCheckSelfY_s, "IsCheckSelfY");
    getMapUnitParam(&mIsInGround_m, "IsInGround");
    getMapUnitParam(&mEnableRevival_m, "EnableRevival");
}

bool MetalObjectBuried::handleMessage_(const ksys::Message* message) {
    if (message->getType() != 0x3000007)
        return false;

    auto* actor = mActor;
    if (*mEnableRevival_m)
        actor->becomePreActor(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason::_0);
    else
        actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    return true;
}

void MetalObjectBuried::changeToUnderground() {
    auto* actor = mActor;
    ksys::act::disableAllAttClients(actor);
    if (auto* body = actor->getMainBody()) {
        body->changeMotionType(ksys::phys::MotionType::Keyframed);
        sead::BoundBox3f box;
        body->getAabbInLocal(&box);
        _74 = (box.getMax() - box.getMin()).length() * 0.5f;
    }
    _70 = false;
    _71 = false;
    changeChild("地中");
}

}  // namespace uking::ai
