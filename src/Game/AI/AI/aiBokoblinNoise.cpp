#include "Game/AI/AI/aiBokoblinNoise.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

BokoblinNoise::BokoblinNoise(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool BokoblinNoise::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BokoblinNoise::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sead::GlobalRandom::instance()->getS32Range(0, 100) < *mEnterNoiseRate_s) {
        _50 = sead::GlobalRandom::instance()->getU32(*mMaxContinueNum_s) + 1;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("囃し立てる", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("待機", &pack);
    }
}

void BokoblinNoise::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BokoblinNoise::loadParams_() {
    getStaticParam(&mMaxContinueNum_s, "MaxContinueNum");
    getStaticParam(&mEnterNoiseRate_s, "EnterNoiseRate");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool BokoblinNoise::isChangeable() const {
    if (getCurrentChild()->isChangeable())
        return true;
    if (!isCurrentChild("囃し立てる"))
        return false;
    auto* child = getCurrentChild();
    return child->isFinished() || child->isFailed();
}

void BokoblinNoise::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("囃し立てる")) {
            if (--_50 <= 0) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("待機", &pack);
            } else {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("囃し立てる", &pack);
            }
        } else {
            const u32 max = *mMaxContinueNum_s;
            _50 = sead::GlobalRandom::instance()->getU32(max) + 1;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("囃し立てる", &pack);
        }
    }
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
