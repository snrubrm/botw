#include "Game/AI/AI/aiEnemySearchHorse.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Resource/Actor/resResourceAttCheck.h"

namespace uking::ai {

bool EnemySearchHorse::sub_71003BA1C4(ksys::act::BaseProcLink* link) {
    auto* awareness = mActor->getAwareness();
    if (!awareness || !sead::DynamicCast<act::Enemy>(mActor))
        return false;

    Unk_7102451588 filter;
    while (awareness->_260[0]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_260[0]->_8, &filter);
        if (!entry)
            break;
        if (sub_71003BA2C4(&entry->_0.mLink)) {
            *link = entry->_0.mLink;
            return true;
        }
    }
    return false;
}

EnemySearchHorse::EnemySearchHorse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemySearchHorse::~EnemySearchHorse() = default;

bool EnemySearchHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// `_110.operator=(...)`: with the operator syntax (C++17 operand order) the RHS call would be evaluated before &_110.
void EnemySearchHorse::sub_71003B9624() {
    ksys::act::ai::InlineParamPack pack;
    if (_58.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_58, &accessor);
        sead::Vector3f pos;
        accessor.getActorMtx().getTranslation(pos);
        pack.addVec3(pos, "TargetPos", -1);
        _110 = _58;
        _58.reset();
    } else {
        sub_71005D7270(&pack, "TargetPos");
        _110.operator=(ksys::act::PlayerInfo::getSomeProcLink());
    }
    changeChild("怒り", &pack);
}

// NON_MATCHING: stack layout only (the original keeps the SafeString temporary and the accessor below the
// pack / AttCheck argument slot; ours puts the big slot lowest).
void EnemySearchHorse::sub_71003B977C() {
    bool found;
    {
        ksys::res::AttCheck_Unk1 arg;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_58, &accessor);
        arg._0 = mActor->getMtx();
        arg._34 = false;
        arg._36 = false;
        arg._30 =
            sead::Mathf::max(mActor->getScale().x, mActor->getScale().y) * *mParams.mRideRadius_s;
        found = accessor.sub_7100D13AE4("Ride", mActor, &arg, false);
    }
    if (found) {
        ksys::act::ai::InlineParamPack pack;
        pack.addActor(_58, "TargetActor", -1);
        changeChild("馬到達", &pack);
    } else {
        _58.reset();
        changeChild("馬未発見");
    }
}

// NON_MATCHING: stack layout (the original shares one 0x18 slot between the "直進" string temporaries and the accessor; ours
// needs 0x10 more) and the register of the accessor address
bool EnemySearchHorse::sub_71003B9914() {
    if (!*mParams.mNoWeaponRiding_s && sub_71005D8B60(mActor))
        return false;
    if (isCurrentChild("直進") && _58.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_58, &accessor);
        if (accessor.getLife() >= 1) {
            sead::Vector3f pos;
            accessor.getActorMtx().getTranslation(pos);
            if (sub_710072E154(mActor, pos, nullptr, -1))
                return true;
        } else {
            _58.reset();
        }
    }
    if (!sub_71003BA1C4(&_58))
        return false;
    if (!isCurrentChild("直進"))
        changeToStraightMove();
    return true;
}

void EnemySearchHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    _100 = ksys::Timer(*mParams.mRepathTime_s, *mParams.mRepathTime_s);
    if (sub_71003B9914())
        return;
    _58.reset();
    changeChild("馬未発見", params);
}

void EnemySearchHorse::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemySearchHorse::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("馬到達")) {
            if (child->isFinished())
                setFinished();
            else
                sub_71003B9624();
        } else if (isCurrentChild("馬未発見")) {
            if (child->isFinished())
                setFinished();
            else
                setFailed();
        } else if (isCurrentChild("怒り")) {
            _58.reset();
            changeChild("馬未発見", nullptr);
        } else if (isCurrentChild("直進")) {
            sub_71003B977C();
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("馬未発見")) {
            sub_71003B9914();
        } else if (!*mParams.mNoWeaponRiding_s && sub_71005D8B60(mActor)) {
            _58.reset();
            changeChild("馬未発見", nullptr);
        } else if (isCurrentChild("直進")) {
            sub_71003B9A48();
        }
    }
    if (isCurrentChild("怒り") && _110.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_110, &accessor);
        child->setDynamicParam(accessor.getActorMtx().getTranslation(), "TargetPos");
    }
}

void EnemySearchHorse::loadParams_() {
    getStaticParam(&mParams.mRepathTime_s, "RepathTime");
    getStaticParam(&mParams.mSearchDist_s, "SearchDist");
    getStaticParam(&mParams.mRideRadius_s, "RideRadius");
    getStaticParam(&mParams.mNoWeaponRiding_s, "NoWeaponRiding");
}

bool EnemySearchHorse::isFailed() const {
    if (ActionBase::isFailed())
        return true;
    if (isCurrentChild("馬未発見"))
        return getCurrentChild()->isFailed();
    return false;
}

bool EnemySearchHorse::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (isCurrentChild("馬未発見"))
        return getCurrentChild()->isFinished();
    return false;
}

void EnemySearchHorse::changeToStraightMove() {
    ksys::act::ai::InlineParamPack pack;
    if (_58.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_58, &accessor);
        sead::Vector3f pos;
        accessor.getActorMtx().getTranslation(pos);
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("直進", &pack);
    } else {
        _58.reset();
        changeChild("馬未発見", nullptr);
    }
}

}  // namespace uking::ai
