#include "Game/AI/AI/aiCreateOnFaceSelect.h"

namespace uking::ai {

CreateOnFaceSelect::CreateOnFaceSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CreateOnFaceSelect::~CreateOnFaceSelect() = default;

bool CreateOnFaceSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool CreateOnFaceSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool CreateOnFaceSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CreateOnFaceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsCreateOnFace_m)
        changeChild("表面生成", params);
    else
        changeChild("通常", params);
}

void CreateOnFaceSelect::calc_() {}

void CreateOnFaceSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CreateOnFaceSelect::loadParams_() {
    getMapUnitParam(&mIsCreateOnFace_m, "IsCreateOnFace");
}

}  // namespace uking::ai
