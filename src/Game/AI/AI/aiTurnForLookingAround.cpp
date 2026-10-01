#include "Game/AI/AI/aiTurnForLookingAround.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

TurnForLookingAround::TurnForLookingAround(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TurnForLookingAround::~TurnForLookingAround() = default;

bool TurnForLookingAround::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TurnForLookingAround::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = 0;
    mActor->getMtx().getBase(_44, 2);
    _44.normalize();
    sub_71005D2384();
}

// NON_MATCHING: stack layout and scheduling (see lane2 log: the original inlines a shared
// 'set TargetPos + change to 回転 + set state' helper)
void TurnForLookingAround::sub_71005D2384() {
    sead::Vector3f dir = _44;
    if (*mAngle_s != 0.0f)
        ksys::util::sub_71011EF010(&dir, *mAngle_s);
    const sead::Vector3f target = mActor->getMtx().getTranslation() + dir;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    changeChild("回転", &params);
    _40 = 1;
}

void TurnForLookingAround::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("回転")) {
            if (_40 == 4)
                setFinished();
            else
                changeChild("待機");
        } else if (isCurrentChild("待機")) {
            switch (_40) {
            case 1:
                if (ksys::util::sub_71011EF0CC(*mAngle_s) > sead::Mathf::piHalf())
                    sub_71005D26A8();
                else
                    sub_71005D27A8();
                break;
            case 2:
                sub_71005D27A8();
                break;
            case 3:
                sub_71005D28DC();
                break;
            default:
                setFinished();
                break;
            }
        }
        return;
    }

    if (child->isChangeable() && _40 == 2) {
        sead::Vector3f side;
        mActor->getMtx().getBase(side, 2);
        side.normalize();
        sead::Vector3f dir = _44;
        ksys::util::sub_71011EF010(&dir, -*mAngle_s);
        sead::Vector3f cross;
        cross.setCross(side, dir);
        if (cross.y < 0.0f)
            sub_71005D27A8();
    }
}

// NON_MATCHING: stack layout and scheduling (see lane2 log: the original inlines a shared
// 'set TargetPos + change to 回転 + set state' helper)
void TurnForLookingAround::sub_71005D26A8() {
    const sead::Vector3f target = _44 + mActor->getMtx().getTranslation();
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    changeChild("回転", &params);
    _40 = 2;
}

// NON_MATCHING: stack layout and scheduling (see lane2 log: the original inlines a shared
// 'set TargetPos + change to 回転 + set state' helper)
void TurnForLookingAround::sub_71005D27A8() {
    sead::Vector3f dir = _44;
    const float angle = -*mAngle_s;
    if (angle != 0.0f)
        ksys::util::sub_71011EF010(&dir, angle);
    const sead::Vector3f target = mActor->getMtx().getTranslation() + dir;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    changeChild("回転", &params);
    _40 = 3;
}

// NON_MATCHING: stack layout and scheduling (see lane2 log: the original inlines a shared
// 'set TargetPos + change to 回転 + set state' helper)
void TurnForLookingAround::sub_71005D28DC() {
    const sead::Vector3f target = _44 + mActor->getMtx().getTranslation();
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    changeChild("回転", &params);
    _40 = 4;
}

void TurnForLookingAround::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TurnForLookingAround::loadParams_() {
    getStaticParam(&mAngle_s, "Angle");
}

}  // namespace uking::ai
