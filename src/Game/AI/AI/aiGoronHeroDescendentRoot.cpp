#include "Game/AI/AI/aiGoronHeroDescendentRoot.h"
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiUnkSingletons.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/Map/mapRail.h"

namespace uking::ui {
void sub_7100A9A694(const UiSubsys1PinArg* arg);
}

namespace uking::ai {

GoronHeroDescendentRoot::GoronHeroDescendentRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GoronHeroDescendentRoot::~GoronHeroDescendentRoot() {
    sub_7100A9A6AC(false);
}

bool GoronHeroDescendentRoot::init_(sead::Heap* heap) {
    mActor->getModel()->getBounding(&_f0);
    return true;
}

void GoronHeroDescendentRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GoronHeroDescendentRoot::leave_() {
    if (auto* controller = mActor->getCharacterController())
        *controller->_48->sub_7100F68F38() = 50.0f;
}

void GoronHeroDescendentRoot::loadParams_() {
    getStaticParam(&mGuardEndDelayTime_s, "GuardEndDelayTime");
    getStaticParam(&mWhistleReactTimeGo_s, "WhistleReactTimeGo");
    getStaticParam(&mWhistleReactTimeStop_s, "WhistleReactTimeStop");
    getStaticParam(&mAppearWaitTime_s, "AppearWaitTime");
    getStaticParam(&mPlayerNearDist_s, "PlayerNearDist");
    getStaticParam(&mPlayerLeaveDist_s, "PlayerLeaveDist");
    getStaticParam(&mPlayerSeparateDist_s, "PlayerSeparateDist");
    getStaticParam(&mFollowModeFlagName_s, "FollowModeFlagName");
    getStaticParam(&mPlayerFollowOffset_s, "PlayerFollowOffset");
}

bool GoronHeroDescendentRoot::sub_71004090D4() {
    if (isCurrentChild("ジャンプ準備") || isCurrentChild("ジャンプ") || isCurrentChild("砲台内") ||
        isCurrentChild("着地") || isCurrentChild("帰還")) {
        return true;
    }
    return false;
}

bool GoronHeroDescendentRoot::sub_71004095E4() {
    if (isCurrentChild("プレイヤー追従") || isCurrentChild("プレイヤー接近待機") ||
        isCurrentChild("停止命令") || isCurrentChild("減速") || isCurrentChild("待機")) {
        return true;
    }
    return false;
}

bool GoronHeroDescendentRoot::sub_71004091AC(sead::Vector3f* out) {
    auto* rail = sub_7100EEF034(mActor, 0);
    if (!rail)
        return false;
    const s32 num_points = rail->getNumPoints();
    if (num_points < 1)
        return false;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f nearest = rail->calcTranslate(0.0f);
    f32 nearest_dist = (nearest - pos).length();
    for (s32 i = 1; i < num_points; ++i) {
        const f32 dist = (rail->calcTranslate(i) - pos).length();
        if (dist < nearest_dist) {
            nearest = rail->calcTranslate(i);
            nearest_dist = dist;
        }
    }
    *out = nearest;
    return true;
}

void GoronHeroDescendentRoot::changeToStopCommand() {
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "TerrorOccurring", -1);
    pack.addVec3(mActor->getMtx().getTranslation(), "TargetPos", -1);
    changeChild("停止命令", &pack);
}

void GoronHeroDescendentRoot::changeToJumpPrepare() {
    ksys::act::setEnabledTalkAndLockOn(mActor, false);
    const sead::Vector3f target = _90.getTranslation();
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f to_target(target.x - position.x, 0.0f, target.z - position.z);
    to_target.normalize();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, sead::Vector3f::ez, to_target, sead::Vector3f::ey);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(mActor->getMtx().getTranslation(), "TargetPos", -1);
    pack.addVec3(sead::Vector3f(0.0f, angle * axis.y, 0.0f), "TargetRot", -1);
    changeChild("ジャンプ準備", &pack);
}

void GoronHeroDescendentRoot::updateYunboPin() {
    sub_7100A9A6AC(false);
    if (ksys::gdt::getBoolByKey("Fire_Relic_YunboStopGo", false)) {
        ui::UiSubsys1PinArg arg;
        arg.pos = mActor->getMtx().getTranslation();
        arg.index = 0;
        arg.value = 0;
        if (isCurrentChild("プレイヤー追従") || isCurrentChild("減速"))
            arg.value = 1;
        ui::sub_7100A9A694(&arg);
        sub_7100A9A6AC(true);
    }
}

void GoronHeroDescendentRoot::changeToFollowPlayer() {
    sead::Vector3f offset;
    offset = *mPlayerFollowOffset_s;
    offset.rotate(getPlayerPositionViaPlayerInfo());
    const sead::Vector3f target = offset + getPlayerPosition();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("プレイヤー追従", &pack);
}

void GoronHeroDescendentRoot::changeToWaitForPlayerApproach() {
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "TerrorOccurring", -1);
    pack.addVec3(mActor->getMtx().getTranslation(), "TargetPos", -1);
    changeChild("プレイヤー接近待機", &pack);
}

void GoronHeroDescendentRoot::sub_7100407988() {
    _160._18.y(mActor);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::findLinkedActor(&accessor, mActor, "RegistedActorMessageBroadCastTag");
    if (accessor.hasProc() && accessor.isStateCalc()) {
        _200._38 = true;
        _160.sub_710070DD78(accessor, true);
    }
}

}  // namespace uking::ai
