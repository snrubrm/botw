#include "Game/AI/AI/aiSwarmRangeKeepCircleMove.h"
#include <cmath>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/VFR.h"
#include "Game/AI/aiUnk_7100742478.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SwarmRangeKeepCircleMove::SwarmRangeKeepCircleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwarmRangeKeepCircleMove::~SwarmRangeKeepCircleMove() = default;

bool SwarmRangeKeepCircleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwarmRangeKeepCircleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    {
        sead::Vector3f dir = mActor->getMtx().getTranslation() - sub_71005D9330(mActor);
        dir.normalize();
        _58 = std::atan2(dir.x, dir.z);
    }

    auto* actor = mActor;
    sead::Vector3f dir = actor->getMtx().getTranslation() - sub_71005D9330(actor);
    dir.normalize();
    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    front.normalize();
    _5c = front.cross(dir).y >= 0.0f ? 1 : -1;

    sub_71005B205C();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_60, "TargetPos", -1);
    changeChild("移動", &pack);
}

// NON_MATCHING: the original hoists the vtable loads above the isFinished/isFailed branches and
// schedules the distance loads differently
void SwarmRangeKeepCircleMove::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_60, "TargetPos", -1);
            changeChild("移動", &pack);
            return;
        }

        sead::Vector3f dir = mActor->getMtx().getTranslation() - sub_71005D9330(mActor);
        dir.normalize();
        _58 = std::atan2(dir.x, dir.z);
        _5c = -_5c;
        const f32 rate = _5c * (*mSpeed_s / *mBaseDist_s);
        _58 += rate * ksys::VFR::instance()->getDeltaFrame();
        _58 = ksys::util::sub_71011EF0CC(_58);
        sub_71005B205C();
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_60, "TargetPos", -1);
        changeChild("移動", &pack);
        return;
    }

    child->isChangeable();
    const auto& mtx = mActor->getMtx();
    const f32 dx = mtx(0, 3) - _60.x;
    const f32 dz = mtx(2, 3) - _60.z;
    const f32 dist = *mUpdateCircleMoveDistance_s;
    if (!(dx * dx + dz * dz > dist * dist)) {
        const f32 rate = _5c * (*mSpeed_s / *mBaseDist_s);
        _58 += rate * ksys::VFR::instance()->getDeltaFrame();
        _58 = ksys::util::sub_71011EF0CC(_58);
    }
    sub_71005B205C();
    getCurrentChild()->setDynamicParam(_60, "TargetPos");
}

void SwarmRangeKeepCircleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwarmRangeKeepCircleMove::loadParams_() {
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mUpdateCircleMoveDistance_s, "UpdateCircleMoveDistance");
}

bool SwarmRangeKeepCircleMove::isFinished() const {
    return ksys::act::ai::Ai::isFinished();
}

bool SwarmRangeKeepCircleMove::isFailed() const {
    if (ActionBase::isFailed())
        return true;
    if (!isChangeable())
        return false;

    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    const auto& target_pos = sub_71005D9330(mActor);
    return ksys::util::sqXZDistance(pos, target_pos) >
           sead::Mathf::square(*mOutDist_s + *mBaseDist_s);
}

void SwarmRangeKeepCircleMove::sub_71005B205C() {
    const auto& target = sub_71005D9330(mActor);
    sead::Vector3f dir = sead::Vector3f::ez;
    ksys::util::sub_71011EF010(&dir, _58);
    _60.setScaleAdd(*mBaseDist_s, dir, target);

    sead::Vector3f ground;
    sead::Vector3f pos = _60;
    pos.y += 3.85f;
    if (sub_7100742478(&ground, pos, 5.0f, 2)) {
        ground.y += 3.85f;
        _60.set(ground);
    }
}

}  // namespace uking::ai
