#include "Game/AI/AI/aiBlownOff.h"
#include <math/seadBoundBox.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

BlownOff::BlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool BlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("ふっとび", params);
}

void BlownOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BlownOff::loadParams_() {
    getStaticParam(&mDrownDepth_s, "DrownDepth");
    getStaticParam(&mIsForceGetUp_s, "IsForceGetUp");
    getStaticParam(&mIsIceBreak_s, "IsIceBreak");
}

bool BlownOff::isFinished() const {
    return ActionBase::isFinished() || (isCurrentChild("起き上がり") && getCurrentChild()->isFinished());
}

void BlownOff::m34(ksys::act::ai::InlineParamPack* params) {
    changeChild("起き上がり", params);
}

// NON_MATCHING: same instructions, other scheduling / registers (the original keeps `pos` in memory across the
// AABB query and loads `pos.y` after it; the depth / reference swap s8 / s9)
bool BlownOff::sub_710032F364() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    f32 y;
    if (auto* controller = mActor->getCharacterController()) {
        if (!controller->isBit6Of116())
            return true;
        const f32 depth = *mDrownDepth_s;
        const f32 reference = controller->get194();
        sead::BoundBox3f aabb;
        controller->sub_7100F61A34()->getAabbInWorld(&aabb);
        if (pos.y < aabb.getMin().y)
            return true;
        aabb.getCenter(&pos);
        y = reference - depth;
    } else {
        f32 offset = 0;
        if (mActor->get68f()) {
            const f32 current = mActor->getMtx().m[1][3];
            offset = mActor->get6f0() - current;
        }
        y = pos.y + offset - *mDrownDepth_s;
    }
    sead::Vector3f to = pos;
    to.y = y;
    return sub_710072E928(pos, to, nullptr, nullptr, nullptr, 0.0f);
}

}  // namespace uking::ai
