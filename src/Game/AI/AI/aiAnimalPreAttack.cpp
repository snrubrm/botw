#include "Game/AI/AI/aiAnimalPreAttack.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

AnimalPreAttack::AnimalPreAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalPreAttack::~AnimalPreAttack() = default;

bool AnimalPreAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalPreAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 minimum = *mForceEndTime_s;
    _5c = minimum;
    _60 = minimum + 15;
    _58 = f32(sead::GlobalRandom::instance()->getS32Range(minimum, minimum + 15));
    if (!((mActor->getMtx().getTranslation() - *mTargetPos_d).length() >
          *mKeepDistCheckLength_s) || sub_7100307B44()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("距離を取る", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("対象を向く", &pack);
    }
}

// Whether there is a cliff (or an obstacle) behind the animal, relative to the target.
bool AnimalPreAttack::sub_7100307B44() {
    auto* actor = mActor;
    if (!actor)
        return false;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    sead::Vector3f dir;
    actor->getMtx().getBase(dir, 2);
    dir = *mTargetPos_d - pos;
    dir.normalize();
    const sead::Vector3f axis = sead::Vector3f::ey;
    sead::Matrix34f rot;
    rot.makeR(axis * sead::Mathf::pi());
    dir.rotate(rot);
    return sub_710072FEC4(mActor, dir, *mBackCliffCheckLength_s, nullptr, false, nullptr);
}

// NON_MATCHING: a single instruction: the first read of `_58` after the first isCurrentChild is `ldr s0, [x19, #0x58]` in
// the original and `ldr s0, [x20]` (the hoisted &_58) here; flow, compares and calls match
// Child names: 対象を向く (face the target), 距離を取る (keep distance).
void AnimalPreAttack::calc_() {
    if (isFinished() || isFailed())
        return;
    ksys::Timer::update(&_58, -1.0f);
    if (isCurrentChild("対象を向く") && _58 <= 0.0f)
        setFinished();
    const s32 distance = s32((mActor->getMtx().getTranslation() - *mTargetPos_d).length());
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!(f32(distance) <= *mKeepDistCheckLength_s) || sub_7100307B44()) {
            if (!isCurrentChild("対象を向く")) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("対象を向く", &pack);
                return;
            }
        } else {
            if (_58 <= 0.0f) {
                setFinished();
                return;
            }
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("距離を取る", &pack);
            return;
        }
        setFinished();
        return;
    }
    if (child->isChangeable()) {
        if (isCurrentChild("距離を取る") && f32(distance) >= *mKeepDistCheckLength_s + 1.0f) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("対象を向く", &pack);
            return;
        }
        if (isCurrentChild("対象を向く") && f32(distance) <= *mKeepDistCheckLength_s - 1.0f &&
            !sub_7100307B44()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("距離を取る", &pack);
            return;
        }
    }
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void AnimalPreAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalPreAttack::loadParams_() {
    getStaticParam(&mForceEndTime_s, "ForceEndTime");
    getStaticParam(&mKeepDistCheckLength_s, "KeepDistCheckLength");
    getStaticParam(&mBackCliffCheckLength_s, "BackCliffCheckLength");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
