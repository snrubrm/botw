#include "Game/AI/AI/aiSandwormBattle.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

SandwormBattle::SandwormBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormBattle::~SandwormBattle() = default;

bool SandwormBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    sub_7100557504();
}

void SandwormBattle::sub_7100557504() {
    if (!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
        const f32 interval = *mAttackInterval_s +
                             *mAttackIntervalRand_s * sead::GlobalRandom::instance()->getF32();
        _58.mTimer = ksys::Timer(interval, interval);
        _70.mTimer = ksys::Timer(*mBattleFailTimer_s, *mBattleFailTimer_s);
        sub_7100557744();
        return;
    }

    if (_58.mTimer.value <= sead::Mathf::epsilon()) {
        bool x;
        {
            ksys::act::acc::PlayerBase accessor;
            auto* link = sub_71005D9050(mActor);
            ksys::act::acquireActor(link ? link : &ksys::act::getDummyBaseProcLink(), &accessor);
            x = accessor.x_13();
        }
        if (!x && sub_710055785C()) {
            sub_710055762C();
            return;
        }
    }
    _70.mTimer = ksys::Timer(*mBattleFailTimer_s, *mBattleFailTimer_s);
    sub_7100557744();
}

// NON_MATCHING: stack layout — the original places the accessor at the top of the frame (sharing its
// slot with the "TargetPos" SafeString) and the position at the bottom
void SandwormBattle::sub_710055762C() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    {
        ksys::act::ActorConstDataAccess accessor;
        auto* link = sub_71005D9050(mActor);
        ksys::act::acquireActor(link ? link : &ksys::act::getDummyBaseProcLink(), &accessor);
        accessor.getActorMtx().getTranslation(pos);
    }
    params.addVec3(pos, "TargetPos", -1);
    changeChild("戦闘攻撃", &params);
}

// NON_MATCHING: same stack layout difference as sub_710055762C
void SandwormBattle::sub_7100557744() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    {
        ksys::act::ActorConstDataAccess accessor;
        auto* link = sub_71005D9050(mActor);
        ksys::act::acquireActor(link ? link : &ksys::act::getDummyBaseProcLink(), &accessor);
        accessor.getActorMtx().getTranslation(pos);
    }
    params.addVec3(pos, "TargetPos", -1);
    changeChild("戦闘準備", &params);
}

void SandwormBattle::calc_() {
    if (!(_58.mTimer.value <= sead::Mathf::epsilon()))
        _58.sub_7100D3BCE4();
    if (!(_70.mTimer.value <= sead::Mathf::epsilon()))
        _70.sub_7100D3BCE4();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("戦闘準備")) {
            if (child->isFailed()) {
                setFailed();
                return;
            }
            if (_58.mTimer.value <= sead::Mathf::epsilon()) {
                bool x;
                {
                    ksys::act::acc::PlayerBase accessor;
                    auto* link = sub_71005D9050(mActor);
                    ksys::act::acquireActor(link ? link : &ksys::act::getDummyBaseProcLink(),
                                            &accessor);
                    x = accessor.x_13();
                }
                if (!x && sub_710055785C()) {
                    sub_710055762C();
                    return;
                }
            }
            sub_7100557744();
        } else if (isCurrentChild("戦闘攻撃")) {
            if (child->isFailed()) {
                setFailed();
                return;
            }
            const f32 interval = *mAttackInterval_s +
                                 *mAttackIntervalRand_s * sead::GlobalRandom::instance()->getF32();
            _58.mTimer = ksys::Timer(interval, interval);
            _70.mTimer = ksys::Timer(*mBattleFailTimer_s, *mBattleFailTimer_s);
            sub_7100557744();
        }
        return;
    }

    if (child->isChangeable() && isCurrentChild("戦闘準備") &&
        _58.mTimer.value <= sead::Mathf::epsilon()) {
        bool x;
        {
            ksys::act::acc::PlayerBase accessor;
            auto* link = sub_71005D9050(mActor);
            ksys::act::acquireActor(link ? link : &ksys::act::getDummyBaseProcLink(), &accessor);
            x = accessor.x_13();
        }
        if (!x && sub_710055785C()) {
            sub_710055762C();
            return;
        }
    }

    sead::Vector3f pos;
    {
        ksys::act::ActorConstDataAccess accessor;
        auto* link = sub_71005D9050(mActor);
        ksys::act::acquireActor(link ? link : &ksys::act::getDummyBaseProcLink(), &accessor);
        accessor.getActorMtx().getTranslation(pos);
    }
    child->setDynamicParam(pos, "TargetPos");
    if (isCurrentChild("戦闘準備") && _70.mTimer.value <= sead::Mathf::epsilon())
        setFailed();
}

void SandwormBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormBattle::loadParams_() {
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mAttackInterval_s, "AttackInterval");
    getStaticParam(&mAttackIntervalRand_s, "AttackIntervalRand");
    getStaticParam(&mBattleFailTimer_s, "BattleFailTimer");
}

}  // namespace uking::ai
