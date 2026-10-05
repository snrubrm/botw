#include "Game/AI/Action/actionSetMaterialVisible.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetMaterialVisible::SetMaterialVisible(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetMaterialVisible::~SetMaterialVisible() = default;

bool SetMaterialVisible::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetMaterialVisible::loadParams_() {
    getStaticParam(&mIsVisible_s, "IsVisible");
    getDynamicParam(&mMaterialName_d, "MaterialName");
}

// NON_MATCHING: the visibility load and material index extraction are scheduled differently.
bool SetMaterialVisible::oneShot_() {
    if (!mActor)
        return false;
    auto* model = mActor->getModel();
    if (!model)
        return false;
    const auto key = model->searchMaterial(mMaterialName_d);
    if (!key.isValid())
        return false;
    model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->setMaterialVisible(
        key.material_index, *mIsVisible_s);
    return true;
}

}  // namespace uking::action
