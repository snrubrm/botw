#include "Game/AI/Action/actionTeleportTargetFrontInAir.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "Game/AI/aiUnk_71005D6D10.h"
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

void TeleportTargetFrontInAir::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
