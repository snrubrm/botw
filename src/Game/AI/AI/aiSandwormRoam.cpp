#include "Game/AI/AI/aiSandwormRoam.h"
#include <random/seadGlobalRandom.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ai {

SandwormRoam::SandwormRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormRoam::~SandwormRoam() = default;

bool SandwormRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    const f32 time =
        *mJumpTimerBase_s + *mJumpTimerRand_s * sead::GlobalRandom::instance()->getF32();
    _50.mTimer = ksys::Timer(time, time);

    auto* obj = mActor->getMapObject();
    if (obj && obj->getRails_0() && *obj->getRails_0())
        changeChild("レール移動");
    else
        changeChild("待ち伏せ");
}

void SandwormRoam::calc_() {
    auto* child = getCurrentChild();
    if (!isCurrentChild("ジャンプ")) {
        if (!(_50.mTimer.value <= sead::Mathf::epsilon()))
            _50.sub_7100D3BCE4();
        if (child->isChangeable() && _50.mTimer.value <= sead::Mathf::epsilon()) {
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            const auto& player_pos = getPlayerPosition();
            const sead::Vector2f diff(pos.x - player_pos.x, pos.z - player_pos.z);
            if (diff.length() > *mJumpDistanceXZ_s) {
                sub_710055D3F8();
                return;
            }
        }
        if (child->isChangeable() && isCurrentChild("待ち伏せ")) {
            auto* obj = mActor->getMapObject();
            if (obj && obj->getRails_0() && *obj->getRails_0()) {
                changeChild("レール移動");
                return;
            }
        }
    }

    if (child->isFinished() || child->isFailed()) {
        auto* obj = mActor->getMapObject();
        if (obj && obj->getRails_0() && *obj->getRails_0())
            changeChild("レール移動");
        else
            changeChild("待ち伏せ");
    }
}

void SandwormRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormRoam::loadParams_() {
    getStaticParam(&mJumpTimerBase_s, "JumpTimerBase");
    getStaticParam(&mJumpTimerRand_s, "JumpTimerRand");
    getStaticParam(&mJumpDistanceXZ_s, "JumpDistanceXZ");
}

void SandwormRoam::sub_710055D3F8() {
    const f32 time =
        *mJumpTimerBase_s + *mJumpTimerRand_s * sead::GlobalRandom::instance()->getF32();
    _50.mTimer = ksys::Timer(time, time);

    sead::Vector3f pos;
    pos.setMul(mActor->getMtx(), {0.0f, 0.0f, 0.1f});
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    params.addActor(ksys::act::getDummyBaseProcLink(), "TargetActor", -1);
    changeChild("ジャンプ", &params);
}

}  // namespace uking::ai
