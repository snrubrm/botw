#include "Game/AI/AI/aiSiteBossSwordSeqThreeAI.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::ai {

SiteBossSwordSeqThreeAI::SiteBossSwordSeqThreeAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSwordSeqThreeAI::~SiteBossSwordSeqThreeAI() = default;

bool SiteBossSwordSeqThreeAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossSwordSeqThreeAI::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsRestart_d)
        _70 = 0;

    switch (_70) {
    case 0:
        sub_71005990E8("先行動");
        break;
    case 1:
        sub_71005990E8("中行動");
        break;
    case 2:
        if (!*mIsSkipLastAction_s) {
            auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
            if (!boss || !boss->_14c8._30.isOnBit(2)) {
                sub_71005990E8("後行動");
                break;
            }
        }
        // fallthrough
    default:
        _70 = 0;
        sub_71005990E8("先行動");
        break;
    }
}

void SiteBossSwordSeqThreeAI::leave_() {
    ++_70;
}

void SiteBossSwordSeqThreeAI::loadParams_() {
    getStaticParam(&mIsSkipLastAction_s, "IsSkipLastAction");
    getDynamicParam(&mIsResetEndTime_d, "IsResetEndTime");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
    getDynamicParam(&mIsNoCharge_d, "IsNoCharge");
    getDynamicParam(&mIsRestart_d, "IsRestart");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mOldTargetPos_d, "OldTargetPos");
}

}  // namespace uking::ai
