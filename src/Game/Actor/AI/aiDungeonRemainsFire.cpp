#include "Game/Actor/AI/aiDungeonRemainsFire.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace uking::ai {

DungeonRemainsFire::DungeonRemainsFire(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The SafeString member makes the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
DungeonRemainsFire::~DungeonRemainsFire() { ; }

bool DungeonRemainsFire::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRemainsFire::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: block layout (the original branches to the slerp block with the target matrix address
// instead of selecting an index) and register allocation of the actor matrix copy.
void DungeonRemainsFire::calc_() {
    if (isFailed())
        return;

    f32 angle;
    if (auto* mgr = ksys::phys::System::instance()->getStaticCompoundMgr()) {
        const sead::Vector3f up{0, 1, 0};
        sead::Vector3f dir = mgr->getRotatedDir(mgr->getBodyGroup(0), up);
        dir.normalize();
        angle = sead::Mathf::acos(sead::Mathf::clamp(dir.dot(up), -0.999999f, 0.999999f));
        sead::Vector2f up_xy{up.x, up.y};
        up_xy.normalize();
        sead::Vector2f dir_xy{dir.x, dir.y};
        dir_xy.normalize();
        angle *= up_xy.x * dir_xy.y - up_xy.y * dir_xy.x >= 0.0f ? 1.0f : -1.0f;
    } else {
        angle = 0.0f;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        const sead::Matrix34f mtx = mActor->getMtx();
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(mtx.getTranslation(), "TargetPos", -1);
        pack.addVec3(mtx.getBase(1), "AxisY", -1);
        pack.addVec3(mtx.getBase(2), "AxisZ", -1);
        changeChild("停止", &pack);
        return;
    }

    const f32 ratio = angle / sead::Mathf::piHalf();
    const f32 rate = sead::Mathf::abs(ratio);
    if (rate < 0.99f && rate > 0.005f) {
        const sead::Matrix34f* target_ptr;
        if (ratio > 0.0f)
            target_ptr = &_48[2];
        else
            target_ptr = &_48[1];
        const sead::Matrix34f& target = *target_ptr;
        sead::Matrix34f mtx;
        sead::Matrix34CalcCommon<f32>::slerpTo(mtx, _48[0], target, rate);
        const sead::Vector3f pos{_48[0](0, 3) + rate * (target(0, 3) - _48[0](0, 3)),
                                 _48[0](1, 3) + rate * (target(1, 3) - _48[0](1, 3)),
                                 _48[0](2, 3) + rate * (target(2, 3) - _48[0](2, 3))};
        if (isCurrentChild("移動")) {
            getCurrentChild()->setDynamicParam(pos, "TargetPos");
            getCurrentChild()->setDynamicParam(mtx.getBase(1), "AxisY");
            getCurrentChild()->setDynamicParam(mtx.getBase(2), "AxisZ");
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(pos, "TargetPos", -1);
            pack.addVec3(mtx.getBase(1), "AxisY", -1);
            pack.addVec3(mtx.getBase(2), "AxisZ", -1);
            changeChild("移動", &pack);
        }
        return;
    }

    if (isCurrentChild("停止"))
        return;

    s32 idx = ratio >= 0.99f ? 2 : 0;
    if (ratio <= -0.99f)
        idx = 1;
    const auto& mtx = _48[idx];
    const sead::Vector3f pos = mtx.getTranslation();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addVec3(mtx.getBase(1), "AxisY", -1);
    pack.addVec3(mtx.getBase(2), "AxisZ", -1);
    changeChild("停止", &pack);
}

void DungeonRemainsFire::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRemainsFire::loadParams_() {
    getStaticParam(&mRailName_s, "RailName");
}

}  // namespace uking::ai
