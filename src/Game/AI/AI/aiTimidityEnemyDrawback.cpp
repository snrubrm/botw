#include "Game/AI/AI/aiTimidityEnemyDrawback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

TimidityEnemyDrawback::TimidityEnemyDrawback(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TimidityEnemyDrawback::~TimidityEnemyDrawback() = default;

bool TimidityEnemyDrawback::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TimidityEnemyDrawback::enter_(ksys::act::ai::InlineParamPack* params) {
    _6c = 6;
    _70 = 15;

    if (sead::Mathf::sqrt(ksys::util::sqXZDistance(mActor->getMtx().getTranslation(),
                                                   *mTargetPos_d)) < *mEscapeDist_s) {
        auto* actor = mActor;
        bool can_flee = false;
        if (actor) {
            sead::Vector3f home;
            actor->getHomePos(&home);
            can_flee = sead::Mathf::sqrt(ksys::util::sqXZDistance(
                           home, actor->getMtx().getTranslation())) <= *mEscapeDistFromHome_s;
        }

        if (!can_flee) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("発狂", &pack);
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("逃走", &pack);
        }
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("警戒", &pack);
    }
}

void TimidityEnemyDrawback::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TimidityEnemyDrawback::loadParams_() {
    getStaticParam(&mEscapeDist_s, "EscapeDist");
    getStaticParam(&mEscapeDistFromHome_s, "EscapeDistFromHome");
    getStaticParam(&mLostRange_s, "LostRange");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
