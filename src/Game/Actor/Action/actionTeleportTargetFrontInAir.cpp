#include "Game/Actor/Action/actionTeleportTargetFrontInAir.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/AutoPlacement/AutoPlacementMgr.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

TeleportTargetFrontInAir::TeleportTargetFrontInAir(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

TeleportTargetFrontInAir::~TeleportTargetFrontInAir() = default;

bool TeleportTargetFrontInAir::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TeleportTargetFrontInAir::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    sub_710072BB70(actor, &_50, false, false);
    if (auto* lod = actor->getLodState())
        lod->mFlags26.set(1);
    _5c = 0;
    _60 = sead::Vector3f::zero;
    if (!actor->getCharacterController() && !actor->getMainBody()) {
        _5c = 4;
        setFailed();
    }
}

void TeleportTargetFrontInAir::sub_7100296360() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sead::Vector3f dir = sub_71005D9330(mActor) - mActor->getMtx().getTranslation();
    dir.normalize();
    sead::Matrix34f mtx;
    ksys::util::sub_71011F00EC(&mtx, dir, sead::Vector3f::ey, sead::Vector3f::zero, false);
    controller->sub_7100F5FC8C(mtx);
}

void TeleportTargetFrontInAir::leave_() {
    sub_710072BEC4(mActor, &_50, false);
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.reset(1);
}

void TeleportTargetFrontInAir::loadParams_() {
    getStaticParam(&mDistMin_s, "DistMin");
    getStaticParam(&mDistMax_s, "DistMax");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getStaticParam(&mTerritoryArea_s, "TerritoryArea");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
}

// NON_MATCHING: territory selection, matrix stack slots and position loads.
void TeleportTargetFrontInAir::calc_() {
    switch (_5c) {
    case 0:
        if (auto* controller = mActor->getCharacterController())
            controller->warpActorToPosition(sub_71005D9330(mActor));
        _5c = 1;
        break;
    case 1: {
        const f32 territory = *mTerritoryArea_m > 0.0f ? *mTerritoryArea_m : *mTerritoryArea_s;
        sead::Vector3f home;
        mActor->getHomePos(&home);
        auto* actor = mActor;
        const sead::Vector3f position = actor->getMtx().getTranslation();
        const f32 dx = home.x - position.x;
        const f32 dz = home.z - position.z;
        bool invalid = dx * dx + dz * dz > territory * territory;
        if (!invalid) {
            if (auto* placement = AutoPlacementMgr::instance())
                invalid = placement->isNonAutoPlacement(position, true);
            actor = mActor;
        }
        if (invalid) {
            _5c = 5;
            sead::Matrix34f transform;
            actor->getHomeMtx(&transform);
            actor = mActor;
            if (auto* physics = actor->getPhysics())
                physics->setMtxAndScale(transform, false, false, actor->getScale().x);
            setFailed();
            return;
        }
        if (auto* controller = actor->getCharacterController())
            controller->warpActorToPosition(sub_71005D9330(mActor));
        if (sub_7100296134(&_60)) {
            _5c = 2;
            _6c = ksys::Timer(10.0f, 10.0f, -1.0f);
        }
        break;
    }
    case 2: {
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F5FBE0(_60);
        sub_7100296360();
        _6c.update();
        const f32 distance = (_60 - mActor->getMtx().getTranslation()).length();
        if (!(distance <= 0.1f) && !(_6c.value <= sead::Mathf::epsilon()))
            return;
        _60 = mActor->getMtx().getTranslation();
        _60.y += *mHeightOffset_s;
        _5c = 3;
        _6c = ksys::Timer(10.0f, 10.0f, -1.0f);
        break;
    }
    case 3: {
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F5FBE0(_60);
        sub_7100296360();
        _6c.update();
        const f32 distance = (_60 - mActor->getMtx().getTranslation()).length();
        if (!(distance <= 0.1f) && !(_6c.value <= sead::Mathf::epsilon()))
            return;
        _5c = 4;
        break;
    }
    case 4:
        sub_7100738428(mActor, 0.0f);
        sub_7100296360();
        setFinished();
        break;
    }
}

bool TeleportTargetFrontInAir::sub_7100296134(sead::Vector3f* out) {
    if (!sub_71005D94AC(mActor).hasProc()) {
        mActor->getHomePos(out);
        return true;
    }
    const auto& target_position = sub_71005D9330(mActor);
    if (auto* placement = AutoPlacementMgr::instance()) {
        if (placement->isNonAutoPlacement(target_position, true)) {
            mActor->getHomePos(out);
            return true;
        }
    }
    if (auto* nav = mActor->m45()) {
        if ((nav->_2a4.load() & 0xffff) == 0x17)
            return false;
    }
    sead::Vector3f direction;
    if (!sub_71005D8FBC(mActor) || !ksys::sub_7100D8C7FC(&direction))
        sub_71005D96A8(mActor).getBase(direction, 2);
    direction.y = 0.0f;
    const f32 angle = *mFrontAngle_s;
    ksys::util::sub_71011EF010(&direction,
                             sead::GlobalRandom::instance()->getF32Range(-angle, angle));
    direction.normalize();
    auto* actor = mActor;
    const auto& from = sub_71005D9330(actor);
    sead::Vector3f position;
    if (!sub_710072FD0C(actor, from, direction, &position, -1, *mDistMax_s,
                        *mDistMax_s - *mDistMin_s, 1.0f, -1.0f))
        return false;
    actor = mActor;
    if (!sub_710072F788(actor, position, sub_71005D9330(actor), nullptr))
        return false;
    if (auto* placement = AutoPlacementMgr::instance()) {
        if (placement->isNonAutoPlacement(position, true)) {
            mActor->getHomePos(out);
            return true;
        }
    }
    *out = position;
    return true;
}

}  // namespace uking::action
