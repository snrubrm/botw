#include "Game/AI/AI/aiMiniGolemRoot.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

MiniGolemRoot::MiniGolemRoot(const InitArg& arg) : GolemRootBase(arg) {}

MiniGolemRoot::~MiniGolemRoot() = default;

bool MiniGolemRoot::init_(sead::Heap* heap) {
    return GolemRootBase::init_(heap);
}

void MiniGolemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _320 = false;
    _324 = ksys::Timer(0, 0, 1.0f);
    GolemRootBase::enter_(params);
}

void MiniGolemRoot::calc_() {
    if (_320) {
        _324.update();
        if (_324.value >= *mLiftDeadTime_s) {
            if (auto* life = mActor->getLife())
                *life = 0;
        }
        if (auto* as_list = mActor->getASList()) {
            const f32 max = *mLiftDeadTime_s;
            f32 ratio = (max - _324.value) / max;
            if (ratio < 0)
                ratio = 0;
            else if (ratio > 1)
                ratio = 1;
            as_list->sub_710115F228(ratio);
            sub_71012412E4(mActor, 29, ratio, false);
        }
    }
    GolemRootBase::calc_();
    sub_71003B5804(false);
}

void MiniGolemRoot::leave_() {
    GolemRootBase::leave_();
}

bool MiniGolemRoot::m36() {
    return isCurrentChild("リアクション") || isCurrentChild("逆さまリアクション");
}

void MiniGolemRoot::m37() {
    if (_320)
        changeChild("逆さまリアクション");
    else
        GolemRootBase::m37();
}

void MiniGolemRoot::m38() {
    if (_320)
        changeChild("逆さま");
    else
        GolemRootBase::m38();
}

void MiniGolemRoot::m40() {
    mActor->getCharacterController();
    _320 = true;
    EnemyRoot::m40();
}

bool MiniGolemRoot::m44() {
    if (isCurrentChild("所持"))
        return false;
    if (!m36())
        return true;
    return *mIsAllowReactionLift_a;
}

void MiniGolemRoot::loadParams_() {
    GolemRootBase::loadParams_();
    getStaticParam(&mLiftDeadTime_s, "LiftDeadTime");
    getAITreeVariable(&mIsAllowReactionLift_a, "IsAllowReactionLift");
}

}  // namespace uking::ai
