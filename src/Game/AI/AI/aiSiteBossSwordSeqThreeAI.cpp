#include "Game/AI/AI/aiSiteBossSwordSeqThreeAI.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

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

void SiteBossSwordSeqThreeAI::calc_() {
    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }

    child->setDynamicParam(*mTargetPos_d, "TargetPos");
    child->setDynamicParam(*mOldTargetPos_d, "OldTargetPos");
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("先行動")) {
        _70 = 1;
        sub_71005990E8("中行動");
        return;
    }

    if (isCurrentChild("中行動")) {
        if (*mIsSkipLastAction_s) {
            _70 = -1;
            setFinished();
            return;
        }
        auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
        if (!boss || !boss->_14c8._30.isOnBit(2)) {
            _70 = 2;
            sub_71005990E8("後行動");
            return;
        }
    }

    if (child->isFinished())
        setFinished();
    else
        setFailed();
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

void SiteBossSwordSeqThreeAI::sub_71005990E8(const char* name) {
    ksys::act::ai::InlineParamPack params;
    params.addBool(*mIsResetEndTime_d, "IsResetEndTime", -1);
    params.addBool(*mIsAttackPatternFixed_d, "IsAttackPatternFixed", -1);
    params.addBool(*mIsNoCharge_d, "IsNoCharge", -1);
    params.addBool(*mIsRestart_d, "IsRestart", -1);
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    params.addVec3(*mOldTargetPos_d, "OldTargetPos", -1);
    changeChild(name, &params);
}

}  // namespace uking::ai
