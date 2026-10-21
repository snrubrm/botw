#include "Game/Actor/Behavior/behaviorAnimalNeckRotate.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelNW.h>
#include <nn/g3d/SkeletonObj.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::behavior {

AnimalNeckRotate::AnimalNeckRotate(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AnimalNeckRotate::~AnimalNeckRotate() = default;

bool AnimalNeckRotate::init_(sead::Heap* heap) {
    return true;
}

// NON_MATCHING: the last node address is computed as base + size * 0x180 - 0xa8 in the original and its key
// halves are reloaded through it; the key stores are also swapped.
void AnimalNeckRotate::enter() {
    sub_71005DB068(mActor, sub_71005D960C(mActor));
    auto* model = mActor->getModel();
    auto* unit = sub_71007398C0(mActor);
    if (!model || !unit)
        return;

    if (unit->_18.size() > 0) {
        const auto& key = unit->_18.back()._a8.getKey();
        const s16 unit_index = key.model_unit_index;
        auto* model_unit = sead::DynamicCast<gsys::ModelNW>(model->getUnits()(unit_index)->mModelUnit);
        if (model_unit && model_unit->getSkeletonObj() && model_unit->getSkeletonObj()->GetRes()) {
            const auto* skeleton = model_unit->getSkeletonObj()->GetRes();
            if (const auto* bone = skeleton->GetBone(key.bone_index)) {
                gsys::BoneAccessKey parent_key;
                parent_key.model_unit_index = unit_index;
                parent_key.bone_index = bone->GetParentIndex();
                _48.search(model, parent_key);
            }
        }
    }

    if (*mRotRate_s >= 0.0f)
        unit->sub_7100D8A9D0(*mRotRate_s);
    else
        unit->_9c = unit->_98;

    if (*mResetRotRate_s >= 0.0f)
        unit->sub_7100D8A9EC(*mResetRotRate_s);
    else
        unit->_a4 = unit->_a0;
}

void AnimalNeckRotate::leave() {
    if (auto* unit = sub_71007398C0(mActor)) {
        sub_71005DB3EC(mActor);
        unit->sub_7100D8A830(0.0f, false);
        unit->_9c = unit->_98;
        unit->_a4 = unit->_a0;
    }
}

void AnimalNeckRotate::loadParams() {
    getStaticParam(&mLimitAngleLR_s, "LimitAngleLR");
    getStaticParam(&mRotRate_s, "RotRate");
    getStaticParam(&mResetRotRate_s, "ResetRotRate");
    getStaticParam(&mIsUseParentRotOffset_s, "IsUseParentRotOffset");
}

}  // namespace uking::behavior
