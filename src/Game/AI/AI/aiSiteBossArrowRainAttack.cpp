#include "Game/AI/AI/aiSiteBossArrowRainAttack.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

SiteBossArrowRainAttack::SiteBossArrowRainAttack(const InitArg& arg)
    : SiteBossReflectArrowRoot(arg) {}

SiteBossArrowRainAttack::~SiteBossArrowRainAttack() = default;

bool SiteBossArrowRainAttack::init_(sead::Heap* heap) {
    return SiteBossReflectArrowRoot::init_(heap);
}

void SiteBossArrowRainAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossReflectArrowRoot::enter_(params);
    _510 = ksys::Timer(25.0f, 25.0f);
    _50c = false;
}

void SiteBossArrowRainAttack::calc_() {
    SiteBossReflectArrowRoot::calc_();
    if (!isCurrentChild("溜め"))
        return;

    _510.update();
    if (_510.value <= sead::Mathf::epsilon() && !_50c) {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            for (int i = 0; i < 20; ++i)
                boss->_1560.sub_710066C60C(nullptr, i);
            _50c = true;
        }
    }
}

void SiteBossArrowRainAttack::leave_() {
    SiteBossReflectArrowRoot::leave_();
    if (!_50d)
        m42();
}

void SiteBossArrowRainAttack::m35() {
    ksys::act::ai::InlineParamPack params;
    params.addBool(true, "IsResetEndTime", -1);
    changeChild("子機発射", &params);
}

void SiteBossArrowRainAttack::m42() {
    if (_50d)
        return;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_1560.sub_710066C634(sub_71005D9050(mActor), 20);
        _50d = false;
    }
}

void SiteBossArrowRainAttack::loadParams_() {
    SiteBossReflectArrowRoot::loadParams_();
}

void SiteBossArrowRainAttack::m37() {
    SiteBossReflectArrowRoot::m37();
}

s32 SiteBossArrowRainAttack::m43() {
    return SiteBossReflectArrowRoot::m43();
}

void SiteBossArrowRainAttack::m45(sead::Vector3f* out) {
    SiteBossReflectArrowRoot::m45(out);
    out->y += -0.5f;
}

f32 SiteBossArrowRainAttack::m53() {
    return 15.0f;
}

bool SiteBossArrowRainAttack::m48() {
    return SiteBossReflectArrowRoot::m48();
}

}  // namespace uking::ai
