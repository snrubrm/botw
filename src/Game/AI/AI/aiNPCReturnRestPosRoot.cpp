#include "Game/AI/AI/aiNPCReturnRestPosRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

NPCReturnRestPosRoot::NPCReturnRestPosRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCReturnRestPosRoot::~NPCReturnRestPosRoot() = default;

bool NPCReturnRestPosRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCReturnRestPosRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCReturnRestPosRoot::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("Move")) {
        sead::Vector3f dir;
        sead::Matrix34f home;
        mActor->getHomeMtx(&home);
        home.getBase(dir, 2);

        sead::Vector3f axis;
        f32 angle;
        ksys::util::sub_71011EEB08(&axis, &angle, sead::Vector3f::ez, dir, sead::Vector3f::ey);
        const sead::Vector3f rot{0.0f, angle * axis.y, 0.0f};

        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        pack.addVec3(rot, "TargetRot", -1);
        changeChild("Turn", &pack);
    } else if (isCurrentChild("Turn")) {
        setFinished();
    }
}

void NPCReturnRestPosRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCReturnRestPosRoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
