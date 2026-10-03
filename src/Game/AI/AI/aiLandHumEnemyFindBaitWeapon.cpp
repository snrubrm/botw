#include "Game/AI/AI/aiLandHumEnemyFindBaitWeapon.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LandHumEnemyFindBaitWeapon::LandHumEnemyFindBaitWeapon(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

LandHumEnemyFindBaitWeapon::~LandHumEnemyFindBaitWeapon() = default;

void LandHumEnemyFindBaitWeapon::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("拾う")) {
        if (getCurrentChild()->isFinished())
            changeChild("喜ぶ");
        else
            setFailed();
    } else if (isCurrentChild("喜ぶ")) {
        changeChild("食べる");
    } else if (isCurrentChild("食べる")) {
        changeChild("怪しむ");
    } else if (isCurrentChild("怪しむ")) {
        sub_71004604A8();
    } else if (isCurrentChild("捨てる")) {
        setFinished();
    }
}

// NON_MATCHING: same instructions, but the original builds the TargetPos vector after the
// "TargetPos" SafeString temporary (GOT load scheduled after the matrix loads).
void LandHumEnemyFindBaitWeapon::sub_71004604A8() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f dir;
    mActor->getMtx().getBase(dir, 2);
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    pack.addVec3(dir * 2 + pos, "TargetPos", -1);
    changeChild("捨てる", &pack);
}

void LandHumEnemyFindBaitWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(*mTargetWeapon_d, "TargetWeapon", -1);
    changeChild("拾う", &pack);
}

bool LandHumEnemyFindBaitWeapon::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void LandHumEnemyFindBaitWeapon::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LandHumEnemyFindBaitWeapon::loadParams_() {
    getDynamicParam(&mTargetWeapon_d, "TargetWeapon");
}

}  // namespace uking::ai
