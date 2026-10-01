#include "Game/AI/AI/aiWholeDungeonRotateTag.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WholeDungeonRotateTag::WholeDungeonRotateTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WholeDungeonRotateTag::~WholeDungeonRotateTag() = default;

bool WholeDungeonRotateTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WholeDungeonRotateTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WholeDungeonRotateTag::calc_() {
    auto* child = getCurrentChild();
    if (!m34()) {
        if (child->isFinished() || child->isFailed())
            m44();
        return;
    }

    if (m35())
        m39();
    else if (m36())
        m40();
    else if (m37())
        m41();

    if (!m38())
        m45();
}

void WholeDungeonRotateTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WholeDungeonRotateTag::m44() {
    changeChild("待機");
}

void WholeDungeonRotateTag::m45() {
    ksys::act::ai::InlineParamPack params;
    params.addFloat(_40, "DynTargetAng", -1);
    changeChild("回転", &params);
}

void WholeDungeonRotateTag::loadParams_() {
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
}

}  // namespace uking::ai
