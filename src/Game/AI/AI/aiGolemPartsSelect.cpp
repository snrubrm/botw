#include "Game/AI/AI/aiGolemPartsSelect.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GolemPartsSelect::GolemPartsSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemPartsSelect::~GolemPartsSelect() = default;

bool GolemPartsSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// inline-only in the original; name is a guess. Both enter_ and calc_ contain this sequence (the key
// check + material visibility query, evaluated for the left then the right arm).
bool GolemPartsSelect::isMaterialVisible(const gsys::MaterialAccessKeyEx& key) const {
    auto* model = mActor->getModel();
    if (!model)
        return true;
    if (!key.isValid())
        return true;
    return model->getUnits()
        .unsafeAt(key.getKey().model_unit_index)
        ->mModelUnit->isMaterialVisible(key.getKey().material_index);
}

void GolemPartsSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* model = mActor->getModel();
    _58.search(model, mParams.mArmLModelMatrialName_s);
    _90.search(model, mParams.mArmRModelMatrialName_s);
    const bool left = isMaterialVisible(_58);
    const bool right = isMaterialVisible(_90);
    if (left && right)
        changeChild("両腕有", params);
    else if (left)
        changeChild("左腕のみ", params);
    else if (right)
        changeChild("右腕のみ", params);
    else
        changeChild("腕なし", params);
}

void GolemPartsSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;
    const bool left = isMaterialVisible(_58);
    const bool right = isMaterialVisible(_90);
    if (left && right) {
        const sead::SafeString name = "両腕有";
        if (!isCurrentChild(name))
            changeChild(name.cstr());
    } else if (left) {
        const sead::SafeString name = "左腕のみ";
        if (!isCurrentChild(name))
            changeChild(name.cstr());
    } else if (right) {
        const sead::SafeString name = "右腕のみ";
        if (!isCurrentChild(name))
            changeChild(name.cstr());
    } else {
        const sead::SafeString name = "腕なし";
        if (!isCurrentChild(name))
            changeChild(name.cstr());
    }
}

bool GolemPartsSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool GolemPartsSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void GolemPartsSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemPartsSelect::loadParams_() {
    getStaticParam(&mParams.mArmRModelMatrialName_s, "ArmRModelMatrialName");
    getStaticParam(&mParams.mArmLModelMatrialName_s, "ArmLModelMatrialName");
}

}  // namespace uking::ai
