#include "Game/Actor/Action/actionBackseatKorokLight.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include <random/seadRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Player/actPlayerInfo.h"

namespace uking::action {

BackseatKorokLight::BackseatKorokLight(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BackseatKorokLight::~BackseatKorokLight() = default;

// NON_MATCHING: the random choice branches are arranged differently.
bool BackseatKorokLight::init_(sead::Heap* heap) {
    _a0 = mPlacementType_m == "Ground";
    if (auto* model = mActor->getModel()) {
        const auto plant = model->searchMaterial("Mt_Korogu_PlantL_C_002");
        const auto left = model->searchMaterial("Mt_Korogu_PlantL_C_000");
        const auto right = model->searchMaterial("Mt_Korogu_PlantR_C_000");
        if (_a0) {
            sead::Random random;
            switch (random.getU32() & 3) {
            case 1:
                model->getUnits().unsafeAt(left.model_unit_index)->mModelUnit->setMaterialVisible(
                    left.material_index, true);
                model->getUnits().unsafeAt(right.model_unit_index)->mModelUnit->setMaterialVisible(
                    right.material_index, false);
                break;
            case 2:
                model->getUnits().unsafeAt(left.model_unit_index)->mModelUnit->setMaterialVisible(
                    left.material_index, false);
                model->getUnits().unsafeAt(right.model_unit_index)->mModelUnit->setMaterialVisible(
                    right.material_index, true);
                break;
            case 3:
                model->getUnits().unsafeAt(left.model_unit_index)->mModelUnit->setMaterialVisible(
                    left.material_index, false);
                model->getUnits().unsafeAt(right.model_unit_index)->mModelUnit->setMaterialVisible(
                    right.material_index, false);
                break;
            default:
                model->getUnits().unsafeAt(left.model_unit_index)->mModelUnit->setMaterialVisible(
                    left.material_index, true);
                model->getUnits().unsafeAt(right.model_unit_index)->mModelUnit->setMaterialVisible(
                    right.material_index, true);
                break;
            }
            model->getUnits().unsafeAt(plant.model_unit_index)->mModelUnit->setMaterialVisible(
                plant.material_index, false);
        } else {
            model->getUnits().unsafeAt(left.model_unit_index)->mModelUnit->setMaterialVisible(
                left.material_index, false);
            model->getUnits().unsafeAt(right.model_unit_index)->mModelUnit->setMaterialVisible(
                right.material_index, false);
            model->getUnits().unsafeAt(plant.model_unit_index)->mModelUnit->setMaterialVisible(
                plant.material_index, true);
        }
    }
    if (auto* model = mActor->getModel())
        model->sub_7100BF8C58(false, -1);
    return true;
}

void BackseatKorokLight::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!actor->isCalc()) {
        const sead::Vector3f& pos = actor->getMtx().getTranslation();
        const f32 x = pos.x;
        const f32 z = pos.z;
        const sead::Vector3f& player = getPlayerPosition();
        const f32 dx = x - player.x;
        const f32 dz = z - player.z;
        const f32 dist_sq = dx * dx + dz * dz;
        _a1 = dist_sq < *mDisappearDist_s * *mDisappearDist_s;
        if (dist_sq > *mAppearDist_s * *mAppearDist_s) {
            _a2 = true;
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        } else {
            _a2 = false;
        }
    }
    _a4 = mActor->getMtx().getTranslation();
    if (_a0)
        playAS(mGroundWaitASName_s.cstr(), false, 0, 0, -1.0f);
    else
        playAS(mFlyWaitASName_s.cstr(), false, 0, 0, -1.0f);
}

void BackseatKorokLight::leave_() {
    ksys::act::ai::Action::leave_();
}

void BackseatKorokLight::loadParams_() {
    getStaticParam(&mAppearDist_s, "AppearDist");
    getStaticParam(&mDisappearDist_s, "DisappearDist");
    getStaticParam(&mGroundWaitASName_s, "GroundWaitASName");
    getStaticParam(&mGroundAppearASName_s, "GroundAppearASName");
    getStaticParam(&mGroundDisappearASName_s, "GroundDisappearASName");
    getStaticParam(&mFlyWaitASName_s, "FlyWaitASName");
    getStaticParam(&mFlyAppearASName_s, "FlyAppearASName");
    getStaticParam(&mFlyDisappearASName_s, "FlyDisappearASName");
    getMapUnitParam(&mPlacementType_m, "PlacementType");
}

void BackseatKorokLight::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
