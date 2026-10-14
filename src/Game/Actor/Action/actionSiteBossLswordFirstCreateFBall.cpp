#include "Game/Actor/Action/actionSiteBossLswordFirstCreateFBall.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossLswordFirstCreateFBall::SiteBossLswordFirstCreateFBall(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossLswordFirstCreateFBall::~SiteBossLswordFirstCreateFBall() = default;

bool SiteBossLswordFirstCreateFBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original keeps &boss->_1560 in a register for the stores after the name copy.
void SiteBossLswordFirstCreateFBall::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mParams.mASName_s.cstr(), true, 0, 0, -1.0f);
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        auto& info = boss->_1560;
        info._8 = true;
        info._c = 8.0f;
        info._10 = 0;
        info._18 = mParams.mThrowActorName_s;
        s32 num = getNumberOfDeadBlights();
        switch (boss->_1534 & ~3) {
        case 4:
            num = 3;
            break;
        case 8:
            num = 4;
            break;
        }
        const s32 add = *mParams.mAddAttackPower_s * num;
        info._70 = *mParams.mAttackPower_s + add;
        info._74 = 1.0f;
        info._78 = 200.0f;
        info._7c = *mParams.mFireBallScale_s;
        info._80 = *mParams.mFireBallScale_s;
        info._84 = *mParams.mAtMinDamage_s + add;
        info._88 = *mParams.mBindPosOffset_s;
        info._94 = 0;
    }
    _74 = ksys::Timer(1.0f, 1.0f, -1.0f);
    _70 = false;
}

void SiteBossLswordFirstCreateFBall::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossLswordFirstCreateFBall::loadParams_() {
    getStaticParam(&mParams.mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mParams.mAttackPower_s, "AttackPower");
    getStaticParam(&mParams.mCreateNum_s, "CreateNum");
    getStaticParam(&mParams.mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mParams.mFireBallScale_s, "FireBallScale");
    getStaticParam(&mParams.mThrowActorName_s, "ThrowActorName");
    getStaticParam(&mParams.mASName_s, "ASName");
    getStaticParam(&mParams.mBindPosOffset_s, "BindPosOffset");
}

void SiteBossLswordFirstCreateFBall::calc_() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        bool all_bound = true;
        for (u32 i = 0; i < u32(*mParams.mCreateNum_s); ++i) {
            if (!(boss->_1560._9c & (1u << i))) {
                all_bound = false;
                break;
            }
        }
        if (all_bound)
            _70 = true;
    }
    if (_70) {
        if (!mActor->getASList()->x(22, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                                    true))
            setFinished();
    }
    _74.update();
    if (_74.value <= sead::Mathf::epsilon())
        setFinished();
}

}  // namespace uking::action
