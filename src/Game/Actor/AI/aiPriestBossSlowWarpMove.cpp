#include "Game/Actor/AI/aiPriestBossSlowWarpMove.h"
#include <cmath>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PriestBossSlowWarpMove::PriestBossSlowWarpMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossSlowWarpMove::~PriestBossSlowWarpMove() = default;

bool PriestBossSlowWarpMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// 0x710052f740
// NON_MATCHING: vector interpolation, basis snapshots and normalization registers differ.
void PriestBossSlowWarpMove::enter_(ksys::act::ai::InlineParamPack*) {
    _a8 = false;
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    auto* actor = mActor;
    const sead::Vector3f old_forward = actor->getMtx().getBase(2);
    const sead::Vector3f up = actor->getMtx().getBase(1);
    f32 time = *mCurrentFrame_d;
    f32 duration = *mAfterImage0AppearFrame_s;
    sead::Vector3f start;
    sead::Vector3f end;
    if (time < duration) {
        _a4 = 0;
        start = actor->getMtx().getTranslation();
        end = *mAfterImage0Pos_d;
    } else if (time < *mAfterImage1AppearFrame_s) {
        _a4 = 1;
        time -= duration;
        duration = *mAfterImage1AppearFrame_s - duration;
        start = *mAfterImage0Pos_d;
        end = *mAfterImage1Pos_d;
    } else {
        _a4 = 2;
        time -= *mAfterImage1AppearFrame_s;
        duration = *mAppearFrame_s - *mAfterImage1AppearFrame_s;
        start = *mAfterImage1Pos_d;
        end = *mMoveDstPos_d;
    }
    sead::Vector3f direction = end - start;
    const f32 length = direction.normalize();
    const sead::Vector3f position = start + direction * (std::fmin(time / duration, 1.0f) * length);
    sead::Vector3f forward = end - position;
    forward.y = 0.0f;
    forward.normalize();
    if (forward.isNan() || forward == sead::Vector3f::zero)
        forward = old_forward;
    sead::Vector3f right;
    right.setCross(sead::Vector3f::ey, forward);
    right.normalize();
    sead::Matrix34f matrix;
    matrix.setBase(0, right);
    matrix.setBase(1, up);
    matrix.setBase(2, forward);
    matrix.setTranslation(position);
    controller->sub_7100F60500(matrix);
    _80[0] = *mAfterImage0Pos_d;
    _80[1] = *mAfterImage1Pos_d;
    _80[2] = *mMoveDstPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_80[_a4], "TargetPos", -1);
    if (*mTurnFirst_s) {
        _a8 = true;
        changeChild("回転", &pack);
    } else {
        changeChild("移動", &pack);
    }
}

// 0x710052fc00
// NON_MATCHING: next-stage index temporary and target parameter stores differ.
void PriestBossSlowWarpMove::calc_() {
    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("移動")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D93CC(mActor), "TargetPos", -1);
            changeChild("回転", &pack);
        } else if (isCurrentChild("回転")) {
            switch (_a4) {
            case 0:
                if (_a8)
                    _a8 = false;
                else
                    ++_a4;
                break;
            case 1:
                ++_a4;
                break;
            case 2:
                setFinished();
                return;
            }
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_80[_a4], "TargetPos", -1);
            changeChild("移動", &pack);
        }
    }
    if (isCurrentChild("回転")) {
        sead::Vector3f target;
        if (_a4 < 2 && mActor->getASList()->x(
                0x34, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
            target = _80[_a4 + 1];
        } else {
            target = sub_71005D93CC(mActor);
        }
        child->setDynamicParam(target, "TargetPos");
    }
}

void PriestBossSlowWarpMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossSlowWarpMove::loadParams_() {
    getStaticParam(&mAfterImage0AppearFrame_s, "AfterImage0AppearFrame");
    getStaticParam(&mAfterImage1AppearFrame_s, "AfterImage1AppearFrame");
    getStaticParam(&mAppearFrame_s, "AppearFrame");
    getStaticParam(&mTurnFirst_s, "TurnFirst");
    getDynamicParam(&mCurrentFrame_d, "CurrentFrame");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
    getDynamicParam(&mAfterImage0Pos_d, "AfterImage0Pos");
    getDynamicParam(&mAfterImage1Pos_d, "AfterImage1Pos");
}

}  // namespace uking::ai
