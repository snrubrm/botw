#include "Game/AI/AI/aiOnCliffEnemyBattle.h"
#include <cmath>
#include <random/seadGlobalRandom.h>
#include "KingSystem/System/Timer.h"
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

OnCliffEnemyBattle::OnCliffEnemyBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnCliffEnemyBattle::~OnCliffEnemyBattle() = default;

bool OnCliffEnemyBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnCliffEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    const int counter = *mLostCounter_s;
    const int counter2 = counter * 1.1f;
    _6c = sead::Mathi::min(counter, counter2);
    _70 = sead::Mathi::max(counter, counter2);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D960C(mActor), "TargetPos", -1);
    changeChild("追跡", &pack);
}

// NON_MATCHING: same instructions; the original computes `&enemy->_f28` after loading the scale argument, we compute
// it before (one address computation is scheduled differently).
void OnCliffEnemyBattle::calc_() {
    f32& timer = _68;
    const s32 state = sub_71005D9744(mActor);
    if (state != 2 && state != 5)
        ksys::Timer::update(&timer, -1.0f);
    else
        timer = _6c == _70 ? _6c : sead::GlobalRandom::instance()->getS32Range(_6c, _70);

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (timer <= 0.0f) {
            setFailed();
            return;
        }
        if (!isCurrentChild("攻撃")) {
            setFailed();
        } else {
            if (mActor) {
                const s32 time = static_cast<act::Enemy*>(mActor)->_f28.sub_7100001AA4(
                    *mAttackIntervalIntensity_s);
                if (time >= 0 && mActor)
                    static_cast<act::Enemy*>(mActor)->_e68 = ksys::Timer(time, time);
            }
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D960C(mActor), "TargetPos", -1);
            changeChild("追跡", &pack);
        }
    } else if (child->isChangeable()) {
        if (timer <= 0.0f) {
            setFailed();
            return;
        }
        if (isCurrentChild("追跡")) {
            auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
            if (enemy && enemy->_e68.value <= sead::Mathf::epsilon() && m34()) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D960C(mActor), "TargetPos", -1);
                changeChild("攻撃", &pack);
            }
        }
    }
    child->setDynamicParam(sub_71005D960C(mActor), "TargetPos");
}

bool OnCliffEnemyBattle::m34() {
    auto* actor = mActor;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    sead::Vector3f dir = pos - sub_71005D960C(actor);
    dir.negate();
    const f32 dist = dir.normalize();
    if (dist > *mAttackDist_s)
        return false;

    sead::Matrix34f inv;
    sead::Matrix34CalcCommon<f32>::inverse(inv, actor->getMtx());
    sead::Vector3f local;
    local.setRotated(inv, dir);

    const f32 angle_h = sead::Mathf::abs(ksys::util::sub_71011EF0CC(std::atan2(local.x, local.z)));
    if (angle_h > *mAttackAngleH_s)
        return false;

    const f32 angle_v = ksys::util::sub_71011EF0CC(
        std::atan2(local.y, std::sqrt(local.x * local.x + local.z * local.z)));
    return *mAttackAngleVMin_s < angle_v && angle_v < *mAttackAngleVMax_s;
}

void OnCliffEnemyBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnCliffEnemyBattle::loadParams_() {
    getStaticParam(&mLostCounter_s, "LostCounter");
    getStaticParam(&mAttackDist_s, "AttackDist");
    getStaticParam(&mAttackAngleH_s, "AttackAngleH");
    getStaticParam(&mAttackAngleVMax_s, "AttackAngleVMax");
    getStaticParam(&mAttackAngleVMin_s, "AttackAngleVMin");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
}

}  // namespace uking::ai
