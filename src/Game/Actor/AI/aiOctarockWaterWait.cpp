#include "Game/Actor/AI/aiOctarockWaterWait.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_7102450d10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldWeatherMgr.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

OctarockWaterWait::OctarockWaterWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OctarockWaterWait::~OctarockWaterWait() = default;

bool OctarockWaterWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OctarockWaterWait::enter_(ksys::act::ai::InlineParamPack* params) {
    _70 = 0;
    {
        const s32 a = *mRiseDelayTimeMin_s;
        const s32 b = *mRiseDelayTimeMax_s;
        const s32 min = sead::Mathi::min(a, b);
        const s32 max = sead::Mathi::max(a, b);
        _78 = min;
        _7c = max;
        s32 time = min;
        if (max != min)
            time = min + s32(sead::GlobalRandom::instance()->getU32(max - min));
        _74 = time;
    }
    {
        const s32 a = *mFinishFloatDelayTimeMin_s;
        const s32 b = *mFinishFloatDelayTimeMax_s;
        const s32 min = sead::Mathi::min(a, b);
        const s32 max = sead::Mathi::max(a, b);
        _84 = min;
        _88 = max;
        s32 time = min;
        if (max != min)
            time = min + s32(sead::GlobalRandom::instance()->getU32(max - min));
        _80 = time;
    }
    _8c = -1.0f;

    if (mActor->getRootAi()->getI() != 5 && ksys::world::Manager::instance() &&
        ksys::world::Manager::instance()->getWeatherMgr()->isRaining()) {
        auto* unit = sead::DynamicCast<Unk_7102450d10>(
            *static_cast<Unk_71025afb58**>(mOctarockFormChangeUnit_a));
        if (unit)
            unit->sub_7100714B88();
        changeChild("浮上");
    } else {
        _70 = 0;
        changeChild("待機");
    }
}

void OctarockWaterWait::leave_() {
    auto* unit = sead::DynamicCast<Unk_7102450d10>(
        *static_cast<Unk_71025afb58**>(mOctarockFormChangeUnit_a));
    if (unit)
        unit->sub_7100714918();
    mActor->m93(0, 0.0f);
}

void OctarockWaterWait::loadParams_() {
    getStaticParam(&mNoRiseTime_s, "NoRiseTime");
    getStaticParam(&mRiseDelayTimeMin_s, "RiseDelayTimeMin");
    getStaticParam(&mRiseDelayTimeMax_s, "RiseDelayTimeMax");
    getStaticParam(&mFinishFloatDelayTimeMin_s, "FinishFloatDelayTimeMin");
    getStaticParam(&mFinishFloatDelayTimeMax_s, "FinishFloatDelayTimeMax");
    getStaticParam(&mMinHeightFromWater_s, "MinHeightFromWater");
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

bool OctarockWaterWait::isChangeable() const {
    return isCurrentChild("待機") && getCurrentChild()->isChangeable();
}

// 0x71004f10ec
void OctarockWaterWait::sub_71004F10EC() {
    if (_8c < 0.0f)
        _8c = mActor->getMtx().m[1][3];
    mActor->m93(0, 0.0f);
    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(_8c, "BaseHeight", -1);
    changeChild("浮遊", &pack);
}

// 0x71004f0fc8
void OctarockWaterWait::sub_71004F0FC8(const sead::Vector3f& pos) {
    if (_8c < 0.0f)
        _8c = mActor->getMtx().m[1][3];
    mActor->m93(2, 0.0f);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addFloat(_8c, "BaseHeight", -1);
    changeChild("音気づき", &pack);
}

}  // namespace uking::ai
