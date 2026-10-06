#include "Game/AI/AI/aiEnemyHide.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/gameSceneSubsysMisc.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

EnemyHide::EnemyHide(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyHide::~EnemyHide() {
    GameSceneSubsys4::instance()->sub_710066B8C0(mActor);
}

bool EnemyHide::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    return true;
}

// NON_MATCHING: the original builds the end iterator of the path list before the begin iterator (sub x2 before
// sub x1)
void EnemyHide::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _278 = sub_71005E2BCC(actor);
    auto* nav = actor->m45();
    if (!nav) {
        setFailed();
        changeChild("待機", nullptr);
        return;
    }
    if (!nav->_18)
        ksys::phys::HavokAI::instance()->sub_7100F82BCC(nav);
    if (_278 && _278->_0)
        _278->_0->sub_7100F7604C(0.2f);
    _38.clear();
    if (sub_7100393EC4() == 2 && _38.size() != 0) {
        if (auto* move = _278; move && move->_0) {
            move->_0->sub_7100394884(_38.begin(), _38.end());
            move->_8 = 0;
        }
    }
    changeChild("見まわす", nullptr);
    GameSceneSubsys4::instance()->sub_710066B8C0(mActor);
}

bool EnemyHide::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyHide::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyHide::loadParams_() {
    if (mActor->getParam()) {
        getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
        getStaticParam(&mParams.mTurnStartAng_s, "TurnStartAng");
        getStaticParam(&mParams.mRepathTime_s, "RepathTime");
    }
}

// NON_MATCHING: the original stores the timer's previous value before the value in the 回転 branch, and
// schedules the loads of the actor position after the NaN check of nav->_194 differently
void EnemyHide::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("隠れる")) {
            setFinished();
            changeChild("待機", nullptr);
            return;
        }
        if (isCurrentChild("見まわす")) {
            setFailed();
            changeChild("待機", nullptr);
            return;
        }
        if (isCurrentChild("回転")) {
            _254.reset(f32(*mParams.mRepathTime_s));
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_248, "TargetPos", -1);
            changeChild("隠れる", &pack);
            return;
        }
    }

    if (!getCurrentChild()->isChangeable())
        return;

    if (isCurrentChild("隠れる")) {
        auto* move = _278;
        if (move) {
            if (move->_8 == 3) {
                setFinished();
                changeChild("待機", nullptr);
                return;
            }
            if (move->_8 == 2) {
                setFailed();
                changeChild("待機", nullptr);
                return;
            }
        }
        if (!(_254.value <= sead::Mathf::epsilon())) {
            _254.update();
            return;
        }
        _254 = ksys::Timer(f32(*mParams.mRepathTime_s), f32(*mParams.mRepathTime_s));
        if (move && move->_0) {
            move->_0->sub_7100F75F8C(_248);
            move->_8 = 0;
        }
    } else if (isCurrentChild("見まわす")) {
        if (_278 && _278->_8 == 1) {
            auto* nav = mActor->m45();
            if (nav) {
                if (nav->_194.isNan())
                    return;
                sead::Vector3f delta = mActor->getMtx().getTranslation();
                delta -= nav->_194;
                if (!(delta.length() <= 1.0f)) {
                    sub_710039439C();
                    return;
                }
                setFinished();
                changeChild("待機", nullptr);
            }
        }
    }
}

s32 EnemyHide::sub_7100393EC4() {
    _38.clear();
    sead::FixedObjList<sead::Vector3f, 15> points;
    if (!sub_71005DA164(mActor, &points))
        return -1;
    return GameSceneSubsys4::instance()->sub_710066B1BC(3.0f, mActor, mActor->m45(), &points, &_38);
}

// NON_MATCHING: same timer store order and one float load scheduling difference as calc_
void EnemyHide::sub_710039439C() {
    auto* nav = mActor->m45();
    if (nav) {
        nav->_1e0.lock();
        const u8 state = nav->_294 | 1;
        nav->_1e0.unlock();
        if (state == 5)
            nav->sub_7100F76790();
    }
    GameSceneSubsys4::instance()->sub_710066B8C0(mActor);
    _248 = sead::Vector3f::zero;
    if (nav)
        _248 = nav->_194;
    if (GameSceneSubsys4::instance()->sub_710066B73C(mActor, &_248) != 1) {
        sub_7100394648();
        return;
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_248, "TargetPos", -1);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir(_248.x - pos.x, 0.0f, _248.z - pos.z);
    dir.normalize();
    if (!(dir.dot(mActor->getMtx().getBase(2)) <= sead::Mathf::cos(*mParams.mTurnStartAng_s))) {
        _254.reset(f32(*mParams.mRepathTime_s));
        changeChild("隠れる", &pack);
    } else {
        changeChild("回転", &pack);
    }
}

// NON_MATCHING: same iterator order as enter_
void EnemyHide::sub_7100394648() {
    if (sub_7100393EC4() == 2 && _38.size() != 0) {
        if (auto* move = _278; move && move->_0) {
            move->_0->sub_7100394884(_38.begin(), _38.end());
            move->_8 = 0;
        }
        if (!isCurrentChild("見まわす"))
            changeChild("見まわす", nullptr);
    } else {
        changeChild("見まわす", nullptr);
    }
}

}  // namespace uking::ai
