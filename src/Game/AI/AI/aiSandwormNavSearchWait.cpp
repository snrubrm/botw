#include "Game/AI/AI/aiSandwormNavSearchWait.h"
#include <cmath>
#include "Game/Actor/actSandworm.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SandwormNavSearchWait::SandwormNavSearchWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormNavSearchWait::~SandwormNavSearchWait() = default;

bool SandwormNavSearchWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormNavSearchWait::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("見まわす");
}

void SandwormNavSearchWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormNavSearchWait::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: register allocation of the XZ distance and the order of the two loads of the 12-byte copy
// 0x710055b34c
void SandwormNavSearchWait::sub_710055B34C() {
    sead::Vector3f pos = *mTargetPos_d;
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor)) {
        if (mActor->getMtx().m[1][3] + 5.0f > sandworm->_1644.y) {
            const f32 dx = mActor->getMtx().m[0][3] - sandworm->_1644.x;
            const f32 dz = mActor->getMtx().m[2][3] - sandworm->_1644.z;
            if (std::sqrt(dx * dx + dz * dz) > 1.0f)
                pos.set(sandworm->_1644);
        }
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("移動", &pack);
}

}  // namespace uking::ai
