#include "Game/AI/Action/actionDemoMotorcyclePutMaterials.h"
#include <gsys/gsysModel.h>
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

void DemoMotorcyclePutMaterials::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
