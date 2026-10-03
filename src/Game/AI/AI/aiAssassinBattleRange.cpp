#include "Game/AI/AI/aiAssassinBattleRange.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/System/Timer.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AssassinBattleRange::AssassinBattleRange(const InitArg& arg) : EnemyBattle(arg) {}

AssassinBattleRange::~AssassinBattleRange() = default;

bool AssassinBattleRange::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void AssassinBattleRange::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
    _b8 = *mScapeGoatCheckInterval_s;
    _bc = *mServiceCheckInterval_s;
}

// NON_MATCHING: load scheduling of the service distance test (the original loads target.x and target.z
// before the actor's x); everything else (frame, calls, branches) matches
void AssassinBattleRange::calc_() {
    auto* child = getCurrentChild();
    if (isCurrentChild("変わり身")) {
        child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
        if (child->isFinished() || child->isFailed()) {
            _b8 = *mScapeGoatCheckInterval_s;
            sub_7100381ED4();
            m37();
        }
    } else if (isCurrentChild("サービス")) {
        child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
        if (child->isFinished() || child->isFailed()) {
            _bc = *mServiceCheckInterval_s;
            m37();
        }
    } else {
        if (_b8 > 0.0f)
            ksys::Timer::update(&_b8, -1.0f);
        if (_bc > 0.0f)
            ksys::Timer::update(&_bc, -1.0f);

        if (child->isChangeable() || child->isFinished() || child->isFailed()) {
            if (_b8 <= 0.0f && sub_7100313B64()) {
                if (isCurrentChild("戦闘攻撃"))
                    sub_7100381ED4();
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("変わり身", &pack);
                return;
            }
            if (_bc <= 0.0f) {
                auto* actor = mActor;
                const auto& target = sub_71005D9330(actor);
                const sead::Vector2f diff(target.x - actor->getMtx().m[0][3],
                                          target.z - actor->getMtx().m[2][3]);
                if (!(diff.squaredLength() < *mServiceDist_s * *mServiceDist_s)) {
                    if (sead::GlobalRandom::instance()->getF32() * 100.0f < *mServicePer_s) {
                        if (isCurrentChild("戦闘攻撃"))
                            sub_7100381ED4();
                        ksys::act::ai::InlineParamPack pack;
                        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                        changeChild("サービス", &pack);
                        return;
                    }
                    _bc = *mServiceCheckInterval_s;
                }
            }
        }
        EnemyBattle::calc_();
    }
}

void AssassinBattleRange::leave_() {
    EnemyBattle::leave_();
}

void AssassinBattleRange::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mScapeGoatCheckInterval_s, "ScapeGoatCheckInterval");
    getStaticParam(&mServiceCheckInterval_s, "ServiceCheckInterval");
    getStaticParam(&mServicePer_s, "ServicePer");
    getStaticParam(&mScapeGoatPer_s, "ScapeGoatPer");
    getStaticParam(&mServiceDist_s, "ServiceDist");
}

bool AssassinBattleRange::isChangeable() const {
    if (isCurrentChild("戦闘攻撃") || isCurrentChild("変わり身"))
        return false;
    return getCurrentChild()->isChangeable();
}

bool AssassinBattleRange::sub_7100313B64() {
    if (sead::GlobalRandom::instance()->getF32() * 100.0f < *mScapeGoatPer_s) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("変わり身", &pack);
        return true;
    }
    _b8 = *mScapeGoatCheckInterval_s;
    return false;
}

}  // namespace uking::ai
