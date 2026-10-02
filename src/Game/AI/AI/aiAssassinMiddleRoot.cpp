#include "Game/AI/AI/aiAssassinMiddleRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponCommon.h"

namespace uking::ai {

bool Unk_71023d8e28::m3(gsys::Model* model, bool sorted) {
    return _20.isValid();
}

AssassinMiddleRoot::AssassinMiddleRoot(const InitArg& arg) : EnemyRoot(arg) {}

AssassinMiddleRoot::~AssassinMiddleRoot() {
    if (_208._8)
        mActor->sub_71011DA868(&_208);
    if (_268._8)
        mActor->sub_71011DA868(&_268);
}

bool AssassinMiddleRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void AssassinMiddleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

// NON_MATCHING: the original writes the bone key with one 32-bit store (ldrh + str w); ours uses
// two 16-bit stores
void AssassinMiddleRoot::calc_() {
    if (!_268._8) {
        _268.setName(mPodNodeName_s);
        _268._68.makeRT(sead::Vector3f::zero, *mSheathOffset_s);
        mActor->boneHandleStuff(&_268, false);
    }

    if (!_208._8) {
        _208._20.model_unit_index = *mPodModelUnitIdx_s;
        _208._20.bone_index = 0;
        auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
        if (actor) {
            auto* weapon =
                sead::DynamicCast<act::Weapon>(actor->getWeapons()->getEquippedWeapon(0));
            if (weapon) {
                const f32 scale = weapon->getParam()
                                      ->getRes()
                                      .mGParamList->getWeaponCommon()
                                      ->mEnemyEqScale.ref();
                _208._54.x = scale;
                _208._54.y = scale;
                _208._54.z = scale;
                mActor->boneHandleStuff(&_208, false);
            }
        }
    }

    EnemyRoot::calc_();
}

void AssassinMiddleRoot::leave_() {
    EnemyRoot::leave_();
}

void AssassinMiddleRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mPodModelUnitIdx_s, "PodModelUnitIdx");
    getStaticParam(&mPodNodeName_s, "PodNodeName");
    getStaticParam(&mSheathOffset_s, "SheathOffset");
    getStaticParam(&mMagicUsePartsName_s, "MagicUsePartsName");
}

bool AssassinMiddleRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x3000003 && !mMagicUsePartsName_s.isEmpty()) {
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        if (enemy) {
            auto& link = enemy->_1128.getActorPartsActor(mMagicUsePartsName_s);
            if (link.hasProcInCalcState()) {
                _310.sub_710070DF20(&link, true);
            } else {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&link, &accessor);
                accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            }
        }
    }
    return EnemyRoot::handleMessage_(message);
}

void AssassinMiddleRoot::m43() {
    auto* actor = mActor;
    if (isCurrentChild("騎乗") || isCurrentChild("リアクション")) {
        ksys::act::disableAttClient(actor, "SleepSilentKill");
        ksys::act::disableAttClient(actor, "AwakeSilentKill");
        return;
    }

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    if (enemy->_e84.isOnBit(8)) {
        ksys::act::enableAttClient(actor, "SleepSilentKill");
        ksys::act::disableAttClient(actor, "AwakeSilentKill");
        return;
    }

    ksys::act::disableAttClient(actor, "SleepSilentKill");
    auto& link = sub_71005D94AC(actor);
    if (*mForceSealSilentKillCount_a > 0 ||
        actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_1000000) ||
        (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000) &&
         link == ksys::act::PlayerInfo::getSomeProcLink())) {
        ksys::act::disableAttClient(actor, "AwakeSilentKill");
    } else {
        ksys::act::enableAttClient(actor, "AwakeSilentKill");
    }
}

}  // namespace uking::ai
