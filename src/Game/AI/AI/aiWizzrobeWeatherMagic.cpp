#include "Game/AI/AI/aiWizzrobeWeatherMagic.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WizzrobeWeatherMagic::WizzrobeWeatherMagic(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeWeatherMagic::~WizzrobeWeatherMagic() = default;

bool WizzrobeWeatherMagic::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeWeatherMagic::enter_(ksys::act::ai::InlineParamPack* params) {
    _78 = sead::DynamicCast<Unk_7102431fa8>(
        *static_cast<Unk_71025afb58**>(mWizzrobeMagicWeatherUnit_a));
    _74 = -1.0f;
    _70 = mActor->getMtx().m[1][3] + *mRiseLength_s;
    sub_71005FF9BC();
}

void WizzrobeWeatherMagic::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WizzrobeWeatherMagic::loadParams_() {
    getStaticParam(&mRiseLength_s, "RiseLength");
    getStaticParam(&mTimer_s, "Timer");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mWizzrobeMagicWeatherUnit_a, "WizzrobeMagicWeatherUnit");
}

bool WizzrobeWeatherMagic::isFinished() const {
    return ksys::act::ai::Ai::isFinished() ||
           (isCurrentChild("発動") && getCurrentChild()->isFinished());
}

void WizzrobeWeatherMagic::sub_71005FF9BC() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    params.addVec3(*mTargetPos_d, "AttPos", -1);
    sub_71005FFF84(&pos);
    params.addVec3(pos, "TargetPos", -1);
    _58.mTimer = ksys::Timer(*mTimer_s, *mTimer_s);
    if (_78)
        _78->_c = 1;
    changeChild("準備", &params);
}

// 0x71005ffe8c
void WizzrobeWeatherMagic::sub_71005FFE8C() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    pack.addVec3(*mTargetPos_d, "AttPos", -1);
    sub_71005FFF84(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("詠唱", &pack);
}

}  // namespace uking::ai
