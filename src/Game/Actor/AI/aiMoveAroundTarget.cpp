#include "Game/Actor/AI/aiMoveAroundTarget.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71007377D4.h"

namespace uking::ai {

MoveAroundTarget::MoveAroundTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoveAroundTarget::~MoveAroundTarget() = default;

bool MoveAroundTarget::isChangeable() const {
    if (!ActionBase::isChangeable())
        return false;
    return ksys::act::ai::Ai::isChangeable();
}

bool MoveAroundTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MoveAroundTarget::sub_71004B004C() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71004B0238(), "TargetPos", -1);
    changeChild("移動", &pack);
}

void MoveAroundTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = ksys::Timer(-1, -1);
    _80 = ksys::Timer(*mStartRange_s, *mStartRange_s, *mChangeRangeRate_s);
    const s32 base = *mTurnTimeBase_s;
    const s32 end = base + *mTurnTimeRand_s;
    _90 = sead::Mathi::min(base, end);
    _94 = sead::Mathi::max(base, end);
    _8c = _90 == _94 ? _90 : sead::GlobalRandom::instance()->getS32Range(_90, _94);
    sub_71004B004C();
}

void MoveAroundTarget::calc_() {
    sead::Vector3f target;
    if (!(_68.value <= sead::Mathf::epsilon()) &&
        sub_710072E154(mActor, _74, nullptr, -1)) {
        target = _74;
        _68.update();
        mFlags.reset(Flag::Changeable);
    } else {
        target = sub_71004B0238();
        mFlags.set(Flag::Changeable);
        if (_80.value > *mEndRange_s * 0.95f)
            _80.update();
    }
    getCurrentChild()->setDynamicParam(target, "TargetPos");
}

// NON_MATCHING: the final addition loads the base vector per component (three pointers) in the original, and the
// radius scaling multiplies in the other operand order.
sead::Vector3f MoveAroundTarget::sub_71004B0848(f32 angle, const sead::Vector3f& pos,
                                                const sead::Vector3f& target) {
    _8c = _90 == _94 ? _90 : sead::GlobalRandom::instance()->getS32Range(_90, _94);
    sead::Vector3f dir(pos.x - target.x, 0.0f, pos.z - target.z);
    const f32 distance = dir.normalize();
    if (distance > _80.value * 1.1f) {
        sead::Matrix34f rot;
        rot.makeR({0.0f, -angle, 0.0f});
        sead::Vector3f offset;
        offset.setRotated(rot, dir);
        const f32 radius = _80.value;
        const f32 length = offset.length();
        if (length > 0.0f)
            offset = offset * (radius / length);
        return offset + target;
    }
    return dir * 3.0f + pos;
}

void MoveAroundTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoveAroundTarget::loadParams_() {
    getStaticParam(&mTurnTimeBase_s, "TurnTimeBase");
    getStaticParam(&mTurnTimeRand_s, "TurnTimeRand");
    getStaticParam(&mStartRange_s, "StartRange");
    getStaticParam(&mEndRange_s, "EndRange");
    getStaticParam(&mChangeRangeRate_s, "ChangeRangeRate");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
