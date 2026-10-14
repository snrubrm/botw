#include "Game/Actor/AI/aiEnemyRecognizeTargetBase.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/Actor/aiUnk_710001A69C.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyRecognizeTargetBase::EnemyRecognizeTargetBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRecognizeTargetBase::~EnemyRecognizeTargetBase() = default;

// NON_MATCHING: filter initialization stores and loop scheduling differ.
bool EnemyRecognizeTargetBase::sub_71003B12A4() {
    if (*mSpreadDist_s < 0.0f || _78 > 0.0f)
        return false;
    auto* actor = mActor;
    const sead::Vector3f position = actor->getMtx().getTranslation();
    const sead::Vector3f direction = position - sub_71005D9330(actor);
    if (direction.squaredLength() < *mNoCryDist_s * *mNoCryDist_s || !sub_71005D9E68(actor))
        return false;
    if (*mRandomCryInterval_s > 0 && _7c <= 0.0f)
        return true;
    if (!actor->getAwareness())
        return false;
    auto* entries = &actor->getAwareness()->_8;
    Unk_7102451448 filter;
    while (auto* entry = ksys::act::sub_7100D7EEE8(entries, &filter)) {
        if (entry->_a8 < *mSpreadDist_s) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&entry->_0.mLink, &accessor);
            if (accessor.hasTag(0x82ed5778) && !accessor.sub_7100D10E6C(25) &&
                !accessor.sub_7100D10E6C(26) && !sub_710001A69C(&accessor, 0x10000))
                return true;
        }
    }
    return false;
}

bool EnemyRecognizeTargetBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRecognizeTargetBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyRecognizeTargetBase::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

// NON_MATCHING: the original computes &_c0 into a callee-saved register before the sender call
void EnemyRecognizeTargetBase::leave_() {
    if (_c0._30) {
        _90.sub_710070DCC0(&_c0._38._10, true);
        _c0.x();
    }
}

void EnemyRecognizeTargetBase::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCryInterval_s, "CryInterval");
    getStaticParam(&mRandomCryInterval_s, "RandomCryInterval");
    getStaticParam(&mRandomCryIntervalMax_s, "RandomCryIntervalMax");
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mNoCryDist_s, "NoCryDist");
}

bool EnemyRecognizeTargetBase::m34() {
    return false;
}

bool EnemyRecognizeTargetBase::m35() {
    return true;
}

bool EnemyRecognizeTargetBase::handleMessage_(const ksys::Message* message) {
    return _c0.m2(*message);
}

void EnemyRecognizeTargetBase::changeToContact() {
    _78 = *mCryInterval_s;
    const s32 min = *mRandomCryInterval_s;
    const s32 max = *mRandomCryIntervalMax_s;
    _7c = sead::GlobalRandom::instance()->getS32Range(min, max);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("連絡", &pack);

    if (ksys::act::isPlayerProfile(&sub_71005D94AC(mActor))) {
        auto* actor = mActor;
        if (sead::IsDerivedFrom<act::Enemy>(actor))
            static_cast<act::Enemy*>(actor)->_e84.setBit(1);
    }
}

void EnemyRecognizeTargetBase::changeToDiscover() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("発見", &pack);

    if (ksys::act::isPlayerProfile(&sub_71005D94AC(mActor))) {
        auto* actor = mActor;
        if (sead::IsDerivedFrom<act::Enemy>(actor))
            static_cast<act::Enemy*>(actor)->_e84.setBit(1);
    }
}

void EnemyRecognizeTargetBase::changeToActivateTrap() {
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(_c0._38._0, "TargetActor", -1);
    ksys::act::ActorLinkConstDataAccess commander;
    ksys::act::acquireActor(&_c0._38._10, &commander);
    _80 = _c0._38._0;
    pack.addMesTransceiverId(*commander.getMessageTransceiverId(), "CommanderID", -1);
    changeChild("仕掛け作動", &pack);
}

void EnemyRecognizeTargetBase::changeToNotice() {
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(sub_71005D94AC(mActor), "TargetActor", -1);
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("気づき", &pack);

    if (ksys::act::isPlayerProfile(&sub_71005D94AC(mActor))) {
        auto* actor = mActor;
        if (sead::IsDerivedFrom<act::Enemy>(actor))
            static_cast<act::Enemy*>(actor)->_e84.setBit(1);
    }
}

}  // namespace uking::ai
