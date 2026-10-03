#include "Game/AI/AI/aiSiteBossReflectArrowRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::ai {

SiteBossReflectArrowRoot::SiteBossReflectArrowRoot(const InitArg& arg)
    : SiteBossShootNormalArrowRoot(arg) {}

SiteBossReflectArrowRoot::~SiteBossReflectArrowRoot() = default;

bool SiteBossReflectArrowRoot::init_(sead::Heap* heap) {
    return SiteBossShootNormalArrowRoot::init_(heap);
}

void SiteBossReflectArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossShootNormalArrowRoot::enter_(params);

    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss) {
        setFailed();
        return;
    }

    _500 = 0;
    for (s32 i = 0; i < 20; ++i) {
        auto& link = boss->_1560._1e0[i];
        if (link.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (accessor.isStateCalc()) {
                ++_500;
                _488[i] = false;
                _49c[i] = false;
                _4b0[i] = 0.0f;
                continue;
            }
        }
        _488[i] = true;
        _49c[i] = false;
        _4b0[i] = -1.0f;
    }

    if (_500 > 20)
        _500 = 20;
    else if (_500 == 0)
        setFinished();

    _504 = -1;
    _508 = -1;
}

// NON_MATCHING: scheduling / register allocation of the arrow search loops and the `_1560` + `_1e0` address
// folding (the original adds 0x1560 before the saturated index and 0x1e0 after it); control flow identical
bool SiteBossReflectArrowRoot::sub_7100582C20(sead::Vector3f* out) {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss)
        return false;

    const u32 shot = _144;
    if (shot > 19)
        return false;

    bool found_none;
    if (_504 == s32(shot) && _508 != -1) {
        _504 = shot;
        found_none = false;
    } else {
        _504 = shot;
        found_none = true;
        for (u32 i = 0; i < u32(*mArrowNum_s); ++i) {
            if (!_49c[i] && _4b0[i] > 0) {
                _49c[i] = true;
                _508 = i;
                found_none = false;
                break;
            }
        }
    }

    if (_508 == -1)
        return false;

    if (!found_none && !(_4b0[_508] > 0)) {
        _49c[_508] = false;
        bool found = false;
        for (u32 i = 0; i < u32(*mArrowNum_s); ++i) {
            if (_4b0[i] > 0) {
                _49c[i] = true;
                _508 = i;
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }

    auto& link = boss->_1560._1e0[_508];
    if (link.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.isStateCalc()) {
            accessor.getActorMtx().getTranslation(*out);
            return true;
        }
    }
    return false;
}

void SiteBossReflectArrowRoot::leave_() {
    SiteBossShootNormalArrowRoot::leave_();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1560.sub_710066C540(sub_71005D9050(mActor), 20);
}

void SiteBossReflectArrowRoot::loadParams_() {
    SiteBossShootNormalArrowRoot::loadParams_();
    getDynamicParam(&mIsReflectAmongChild_d, "IsReflectAmongChild");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

bool SiteBossReflectArrowRoot::m34() {
    return sub_7100588164(false);
}

void SiteBossReflectArrowRoot::m41() {}

const sead::Vector3f& SiteBossReflectArrowRoot::m51() {
    return sead::Vector3f::zero;
}

f32 SiteBossReflectArrowRoot::m53() {
    return 40.0f;
}

s32 SiteBossReflectArrowRoot::m43() {
    return 1;
}

void SiteBossReflectArrowRoot::calc_() {
    sub_7100582688();
    SiteBossShootNormalArrowRoot::calc_();
}

void SiteBossReflectArrowRoot::m45(sead::Vector3f* out) {
    if (sub_7100582C20(out))
        return;
    SiteBossShootNormalArrowRoot::m45(out);
}

void SiteBossReflectArrowRoot::m46(sead::Vector3f* out) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(*out);
}

bool SiteBossReflectArrowRoot::m48() {
    return SiteBossShootNormalArrowRoot::m48() | (_144 >= _500);
}

// NON_MATCHING: the original null-checks the message reference
bool SiteBossReflectArrowRoot::handleMessage_(const ksys::Message& message) {
    if (message.getBrokerId() != u32(-1) || message.getType() != 0x8000057)
        return false;

    if (!message.getUserData())
        return false;
    const s32 idx = *static_cast<s32*>(message.getUserData());
    if (idx >= 0 && idx <= 20)
        _488[idx] = true;
    return true;
}

void SiteBossReflectArrowRoot::m37() {
    m41();
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    if (!sub_7100582C20(&pos))
        SiteBossShootNormalArrowRoot::m45(&pos);
    params.addVec3(pos, "TargetPos", -1);
    params.addPointer(nullptr, "ArrowHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    params.acquireActor(nullptr, "IgniteActor", -1);
    params.addInt(_144, "Index", -1);
    params.addInt(SiteBossShootNormalArrowRoot::m44(), "AtAttr", -1);
    changeChild("弾発射", &params);
}

}  // namespace uking::ai
