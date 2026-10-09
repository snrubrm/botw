#include "Game/AI/Action/actionPriestBossFastWarpMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

// NON_MATCHING: the compiler removes redundant record zero stores after the bulk clear;
// default and explicit payload value initialization produce the same result.
PriestBossFastWarpMove::PriestBossFastWarpMove(const InitArg& arg) : PriestBossWarpOrVanish(arg) {}

PriestBossFastWarpMove::~PriestBossFastWarpMove() = default;

// NON_MATCHING: vector stores and accessor cleanup use different scheduling and registers.
void PriestBossFastWarpMove::sub_7100222070(s32 idx, const sead::Vector3f& start,
                                            const sead::Vector3f& end, f32 delay) {
    ksys::act::ActorConstDataAccess accessor;
    if (sub_710022134C(idx + 19, &accessor)) {
        const auto* target = idx == 0 ? mAfterImage0Pos_d : mTargetPos_d;
        sead::Vector3f direction;
        direction.x = target->x - end.x;
        direction.y = 0.0f;
        direction.z = target->z - end.z;
        direction.normalize();
        sead::Matrix34f matrix;
        const sead::Vector3f up = sead::Vector3f::ey;
        ksys::util::sub_71011F00EC(&matrix, direction, up, start, false);
        auto& entry = _80[idx];
        entry.payload.actor = mActor;
        entry.payload.position = end;
        entry.payload.time = delay;
        entry.payload._18 = idx != 4;
        entry.payload._19 = false;
        entry.payload._1a = 0;
        entry.pending = true;
        entry.destination = *accessor.getMessageTransceiverId();
        accessor.setProperties(matrix, nullptr, nullptr, nullptr, false, 0, -1);
        _228 |= 1 << idx;
    }
}

bool PriestBossFastWarpMove::init_(sead::Heap* heap) {
    return PriestBossWarpOrVanish::init_(heap);
}

void PriestBossFastWarpMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossWarpOrVanish::enter_(params);
}

void PriestBossFastWarpMove::leave_() {
    PriestBossWarpOrVanish::leave_();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F60604();
        controller->sub_7100F5E764(true);
        controller->sub_7100F62CA8(true);
    }
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
}

void PriestBossFastWarpMove::loadParams_() {
    PriestBossWarpOrVanish::loadParams_();
    getStaticParam(&mAfterImage0AppearFrame_s, "AfterImage0AppearFrame");
    getStaticParam(&mAfterImage1AppearFrame_s, "AfterImage1AppearFrame");
    getStaticParam(&mAppearFrame_s, "AppearFrame");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mCurrentFrame_d, "CurrentFrame");
    getDynamicParam(&mIsCloseMove_d, "IsCloseMove");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
    getDynamicParam(&mAfterImage0Pos_d, "AfterImage0Pos");
    getDynamicParam(&mAfterImage1Pos_d, "AfterImage1Pos");
}

void PriestBossFastWarpMove::calc_() {
    PriestBossWarpOrVanish::calc_();
}

}  // namespace uking::action
