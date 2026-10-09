#include "Game/AI/Action/actionDemoMotorcyclePutMaterials.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/actMotorcycle.h"
#include "Game/gameSceneSubsys12.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

DemoMotorcyclePutMaterials::DemoMotorcyclePutMaterials(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DemoMotorcyclePutMaterials::~DemoMotorcyclePutMaterials() = default;

bool DemoMotorcyclePutMaterials::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: register assignment, load scheduling and if-conversion only — ours keeps fewer
// callee-saved regs (0x80 frame vs 0x90; no x25=&_64 / x26=idx) and if-converts the Loc/Fairy
// selection to csels (the original keeps branches), with csel lt vs lo. All calls, constants,
// loop bounds and the _60 tail match. The _40/_44/_48/_4c BoneAccessKey layout (from the str w0
// searchBone stores) is required for this to compile at all.
void DemoMotorcyclePutMaterials::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* scene = GameSceneSubsys12::instance();
    f32 frames;
    if (!scene) {
        frames = 0.0f;
        _64 = 0;
        _68 = 0;
    } else {
        _68 = scene->sub_7100664D64();
        _64 = scene->sub_710066358C() - _68;
        scene->sub_7100665304();
        frames = _64;
    }
    auto* as_list = mActor->getASList();
    as_list->x_6(0x11, 0, frames);
    as_list->x_6(0x19, 0, _68);
    as_list->startAnimationMaybe(-1.0f, -1.0f, "PreCooking", 1, 0, true);
    if (_68 >= 1)
        as_list->startAnimationMaybe(-1.0f, -1.0f, "PreCookingFairy", 2, 0, true);
    xlinkSearchAndEmit(mActor, _68 > 0 ? "DLC2_Bike_EnergyChargeFairy" : "DLC2_Bike_EnergyCharge",
                       2, nullptr);
    if (auto* model = mActor->getModel()) {
        _40 = model->searchBone("Loc_Root");
        _44 = model->searchBone("Loc_AnimRoot");
        _48 = model->searchBone("Fairy_AnimRoot");
        s64 i = 0;
        if (_64 + _68 >= 1) {
            do {
                const char* fmt;
                int n;
                if (i < _64) {
                    fmt = "Loc_%02d";
                    n = i + 1;
                } else {
                    fmt = "Fairy_%02d";
                    n = i + 1 - _64;
                }
                sead::FormatFixedSafeString<32> name(fmt, n);
                _4c[i < 5 ? i : 0] = model->searchBone(name);
                ++i;
            } while (i < (s64)_64 + _68);
        }
    }
    _60 = -1.0f;
}

void DemoMotorcyclePutMaterials::leave_() {
    if (auto* motorcycle = sead::DynamicCast<act::Motorcycle>(mActor)) {
        if (motorcycle->_bc8.getMotorcycleEnergy() > 0.0f)
            motorcycle->_bc8._19e = false;
    }
}

void DemoMotorcyclePutMaterials::loadParams_() {
    getStaticParam(&mCloseSaddleFramesSincePut_s, "CloseSaddleFramesSincePut");
    getStaticParam(&mFinishCookFramesSincePut_s, "FinishCookFramesSincePut");
    getStaticParam(&mCloseSaddleFramesSincePutFairy_s, "CloseSaddleFramesSincePutFairy");
    getStaticParam(&mFinishCookFramesSincePutFairy_s, "FinishCookFramesSincePutFairy");
}

// NON_MATCHING: matrix/vector temporaries and loop register allocation differ.
void DemoMotorcyclePutMaterials::sub_7100055160(GameSceneSubsys12* scene, bool pre_animation) {
    auto* model = mActor->getModel();
    if (!model)
        return;
    sead::Matrix34f matrix;
    sead::Matrix34f root_local;
    sead::Vector3f scale;
    if (_40.isValid()) {
        model->getUnits()(_40.model_unit_index)->mModelUnit->getBoneWorldMatrix(&matrix,
                                                                            _40.bone_index);
        model->getUnits()(_40.model_unit_index)->mModelUnit->getBoneLocalMatrix(
            &root_local, &scale, _40.bone_index);
    } else {
        matrix = mActor->getMtx();
        root_local = sead::Matrix34f::ident;
    }
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    const auto& player_position = ksys::act::PlayerInfo::instance()->getPlayerPos();
    sead::Vector3f front(player_position.x - position.x, 0.0f, player_position.z - position.z);
    const f32 length = front.normalize();
    sead::Matrix34f facing = sead::Matrix34f::ident;
    if (length != 0.0f) {
        facing.setBase(0, sead::Vector3f(front.z, 0.0f, -front.x));
        facing.setBase(1, sead::Vector3f::ey);
        facing.setBase(2, front);
    }
    facing.setTranslation(position);
    const sead::Matrix34f actor_matrix = mActor->getMtx();
    sead::Matrix34f inverse;
    inverse.setTranspose(actor_matrix);
    sead::Vector3f inverse_translation = actor_matrix.getTranslation();
    inverse_translation.rotate(inverse);
    inverse.setTranslation(-inverse_translation);
    facing.setMul(inverse, facing);
    matrix.setMul(matrix, facing);
    scene->sub_7100664F00(matrix);

    sead::Matrix34f local;
    if (_44.isValid())
        model->getUnits()(_44.model_unit_index)->mModelUnit->getBoneLocalMatrix(
            &local, &scale, _44.bone_index);
    else
        local = sead::Matrix34f::ident;
    scene->sub_7100664F3C(local);
    if (_48.isValid())
        model->getUnits()(_48.model_unit_index)->mModelUnit->getBoneLocalMatrix(
            &local, &scale, _48.bone_index);
    else
        local = sead::Matrix34f::ident;
    scene->sub_7100664F64(local);
    for (s32 index = 0; index < _64 + _68; ++index) {
        const auto& key = _4c[index < 5 ? index : 0];
        if (key.isValid())
            model->getUnits()(key.model_unit_index)->mModelUnit->getBoneLocalMatrix(
                &local, &scale, key.bone_index);
        else
            local = root_local;
        if (pre_animation && index < _64) {
            sead::Matrix33f scaling;
            scaling.makeS(sead::Vector3f(0.01f, 0.01f, 0.01f));
            local.setMul(local, scaling);
        }
        scene->sub_7100664F8C(index, local);
    }
}

void DemoMotorcyclePutMaterials::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
