#include "Game/AI/AI/aiWizzrobeRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

WizzrobeRoot::WizzrobeRoot(const InitArg& arg) : EnemyRoot(arg) {}

WizzrobeRoot::~WizzrobeRoot() {
    auto** unit = static_cast<void**>(mWizzrobeMagicWeatherUnit_a);
    if (unit && *unit == &_208)
        *unit = nullptr;
}

bool WizzrobeRoot::init_(sead::Heap* heap) {
    if (!EnemyRoot::init_(heap))
        return false;
    _208.sub_71007420B8(mStartASName_s, mStopASName_s, *mMagicTargetIdx_s);
    *static_cast<void**>(mWizzrobeMagicWeatherUnit_a) = &_208;
    return true;
}

void WizzrobeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void WizzrobeRoot::calc_() {
    EnemyRoot::calc_();
    _208.sub_7100741C24();
}

void WizzrobeRoot::leave_() {
    EnemyRoot::leave_();
    if (_208._10)
        _208.sub_7100741E14();
}

void WizzrobeRoot::m37() {
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f dir;
        mActor->getMtx().getBase(dir, 2);
        dir.normalize();
        controller->sub_7100F5EDBC(dir);
        controller->sub_7100F5E7F0(0);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
    }
    EnemyRoot::m37();
}

void WizzrobeRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mMagicTargetIdx_s, "MagicTargetIdx");
    getStaticParam(&mStartASName_s, "StartASName");
    getStaticParam(&mStopASName_s, "StopASName");
    getAITreeVariable(&mWizzrobeMagicWeatherUnit_a, "WizzrobeMagicWeatherUnit");
}

}  // namespace uking::ai
