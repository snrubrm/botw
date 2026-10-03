#include "Game/AI/AI/aiSunazarashiReturn.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

SunazarashiReturn::SunazarashiReturn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SunazarashiReturn::~SunazarashiReturn() = default;

bool SunazarashiReturn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SunazarashiReturn::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }

    if (!*mIsForceReturnHome_s) {
        changeChild("待機", nullptr);
        return;
    }

    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f home;
    mActor->getHomePos(&home);
    pack.addVec3(home, "TargetPos", -1);

    sead::Vector3f dir = home;
    dir -= mActor->getMtx().getTranslation();
    dir.y = 0;
    dir.normalize();
    pack.addVec3(dir, "TargetFoward", -1);
    changeChild("強制復帰", &pack);
}

void SunazarashiReturn::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished()) {
        if (isCurrentChild("待機")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mSunazarashiReturnPos_a, "TargetPos", -1);
            changeChild("移動", &pack);
        } else {
            setFinished();
        }
    }

    if (isCurrentChild("移動") && child->isFailed()) {
        if (auto* controller = mActor->getCharacterController()) {
            controller->sub_7100F5F6FC(sead::Vector3f::zero);
            controller->sub_7100F5FB24(sead::Vector3f::zero);
        }

        ksys::act::ai::InlineParamPack pack;
        const sead::Vector3f home = *mSunazarashiReturnPos_a;
        pack.addVec3(home, "TargetPos", -1);

        sead::Vector3f dir = home;
        dir -= mActor->getMtx().getTranslation();
        dir.y = 0;
        dir.normalize();
        pack.addVec3(dir, "TargetFoward", -1);
        changeChild("強制復帰", &pack);
    }
}

void SunazarashiReturn::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SunazarashiReturn::loadParams_() {
    getStaticParam(&mIsForceReturnHome_s, "IsForceReturnHome");
    getAITreeVariable(&mSunazarashiReturnPos_a, "SunazarashiReturnPos");
}

}  // namespace uking::ai
