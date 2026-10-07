#include "Game/AI/AI/aiAirOctaState.h"
#include "Game/AI/AI/AirOcta/AirOctaDataMgr.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/System/VFR.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Utils/Thread/Message.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

AirOctaState::AirOctaState(const InitArg& arg) : EnemyRoot(arg) {}

AirOctaState::~AirOctaState() {
    if (_218.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_218, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool AirOctaState::init_(sead::Heap* heap) {
    if (!EnemyRoot::init_(heap))
        return false;
    sub_710073FA90(&_238, mActor);
    return true;
}

void AirOctaState::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void AirOctaState::leave_() {
    sub_71002FDF9C();
    EnemyRoot::leave_();
}

void AirOctaState::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mRopeGravityFactor_s, "RopeGravityFactor");
    getStaticParam(&mBalloonMassRatio_s, "BalloonMassRatio");
    getStaticParam(&mWindForceScale_s, "WindForceScale");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

void AirOctaState::changeToWait(bool a1) {
    if (isCurrentChild("逃げる"))
        return;
    if (isCurrentChild("滝死亡"))
        return;

    mActor->m93(0, 0.0f);
    ksys::act::ai::InlineParamPack params;
    mActor->getASList()->x_2(66, 40, _278.isOnBit(3), false);
    params.addBool(a1, "IsSameChange", -1);
    changeChild("待機", &params);
}

void AirOctaState::sub_71002FEC08() {
    if (_278.isOnBit(2))
        return;
    auto* manager = sead::DynamicCast<AirOctaDataMgr>(*static_cast<Unk_71025afb58**>(mAirOctaDataMgr_a));
    if (manager && (manager->mFlags & 8))
        return;
    if (isCurrentChild("待機")) {
        ksys::act::ai::InlineParamPack pack;
        mActor->getASList()->x_2(66, 40, _278.isOnBit(3), false);
        pack.addActor(ksys::act::PlayerInfo::getSomeProcLink(), "TargetActor", -1);
        pack.addBool(true, "ForceNotice", -1);
        changeChild("発見", &pack);
        _278.set(0x320);
    }
}

void AirOctaState::sub_71002FEDD0() {
    _278.set(0x320);
    if (isCurrentChild("待機")) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(getPlayerPosition(), "TargetPos", -1);
        changeChild("プレイヤが板に乗った", &pack);
        mActor->m93(4, 0.0f);
    }
}

// NON_MATCHING: register allocation only (case 8: the original keeps the bit pattern in s1 and -1.0f in s0 for the
// `getF32()` subtraction and reloads `_278` into w9 / w8 the other way round).
void AirOctaState::sub_71002FD5BC() {
    if (!isCurrentChild("待機") || m36())
        return;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(
            &sead::DynamicCast<AirOctaDataMgr>(*static_cast<Unk_71025afb58**>(mAirOctaDataMgr_a))
                 ->mBaseProcLink2,
            &accessor) &&
        accessor.hasProc() && accessor.sub_7100D13448(-1)) {
        if (auto* manager = sead::DynamicCast<AirOctaDataMgr>(
                *static_cast<Unk_71025afb58**>(mAirOctaDataMgr_a)))
            manager->mFlags |= 8;
        ksys::act::ai::InlineParamPack pack;
        mActor->getASList()->x_2(66, 40, _278.isOnBit(3), false);
        changeChild("板燃焼");
    }
}

// NON_MATCHING: the inlined SafeString comparison: in the original the loop is `for (i = 0; i < 0x80000; ++i)` and falls
// out of the loop with `true` (the code after the loop is the "equal" branch); lib/sead's isEqual loops to
// `<= cMaximumLength` and returns false after the loop.
void AirOctaState::sub_71002FDE2C() {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;
    ksys::as::ASList::Unk4 query;
    if (!as_list->x(57, &query, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        return;
    if (query.name == "板との接続解除") {
        sub_71002FDF9C();
        return;
    }
    if (query.name == "プレイヤの方向を向く")
        sub_71002FEF78(sead::Mathf::pi());
}

void AirOctaState::sub_71002FD7D8() {
    if (!_278.isOnBit(5))
        return;
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    const sead::Vector3f position = player.getPreviousPos();
    sub_71005DB068(mActor, position);
    if (_278.isOnBit(6)) {
        _204.y += ksys::VFR::instance()->getDeltaTime();
        if (_204.y > 5.0f) {
            _278.reset(0x60);
            sub_71005DB3EC(mActor);
        }
    }
}

bool AirOctaState::handleMessage_(const ksys::Message* message) {
    if (message->getType() != 0x80000c8)
        return EnemyRoot::handleMessage_(message);
    auto* payload = static_cast<const Payload*>(message->getUserData());
    if (!payload)
        return EnemyRoot::handleMessage_(message);

    switch (payload->kind) {
    case 2:
        if (!_278.isOnBit(1) && payload->value >= 0.0f)
            sub_71002FE668(payload->value);
        return true;
    case 5:
        if (!_278.isOnBit(1)) {
            auto* manager = sead::DynamicCast<AirOctaDataMgr>(*static_cast<Unk_71025afb58**>(mAirOctaDataMgr_a));
            manager->mFlags |= 2;
            _278.set(2);
        }
        return true;
    case 6:
        sub_71002FE490(payload);
        return true;
    case 7:
        if (!_278.isOn(0x202) && sub_71002FE954(1.04719758f, 0.52359879f))
            sub_71002FEC08();
        return true;
    case 8:
        if (!_278.isOnBit(1)) {
            _278.set(0x40);
            const f32 value = sead::GlobalRandom::instance()->getF32();
            _278.reset(0x300);
            _204.y = value * -2.5f;
        }
        return true;
    case 9:
        if (!_278.isOnBit(7)) {
            _278.set(0x80);
            mActor->m93(0, 0.0f);
            changeChild("逃げる");
        }
        return true;
    case 10:
        if (!_278.isOn(0x300))
            sub_71002FEDD0();
        return true;
    case 11:
        sub_71002FE55C(payload);
        return true;
    default:
        return false;
    }
}

void AirOctaState::sub_71002FE490(const Payload* payload) {
    if (_278.isOnBit(1))
        return;
    auto* manager = sead::DynamicCast<AirOctaDataMgr>(*static_cast<Unk_71025afb58**>(mAirOctaDataMgr_a));
    if (!manager)
        return;
    auto* data = manager->sub_71002FB32C();
    if (!data || data->_b1 || data->_b2)
        return;
    manager->unk_118 += payload->value;
    manager->changeOctasYheightMaybe();
}

void AirOctaState::sub_71002FE55C(const Payload* payload) {
    if (!isCurrentChild("待機"))
        return;
    if (u32(payload->mode - 1) > 1)
        return;
    auto* manager = sead::DynamicCast<AirOctaDataMgr>(*static_cast<Unk_71025afb58**>(mAirOctaDataMgr_a));
    auto* data = manager->sub_71002FB32C();
    if (!data || data->_b1 || data->_b2)
        return;
    changeChild("オクタの数が減った");
}

void AirOctaState::sub_71002FE668(f32 distance) {
    if (_278.isOnBit(3))
        return;
    auto* manager = sead::DynamicCast<AirOctaDataMgr>(*static_cast<Unk_71025afb58**>(mAirOctaDataMgr_a));
    if (manager && (manager->mFlags & 8))
        return;
    if (isCurrentChild("逃げる"))
        return;

    mActor->m93(0, 0.0f);
    if (auto* damage_manager = sead::DynamicCast<dmg::DamageManager>(mActor->getDamageMgr()))
        damage_manager->_216.setBit(3);
    _278.set(0x1c);
    manager = sead::DynamicCast<AirOctaDataMgr>(*static_cast<Unk_71025afb58**>(mAirOctaDataMgr_a));
    if (manager)
        manager->mFlags |= 0x10;

    if (distance != 0.0f) {
        ksys::act::ai::InlineParamPack pack;
        mActor->getASList()->x_2(66, 40, _278.isOnBit(3), false);
        pack.addFloat(distance, "TargetDistance", -1);
        changeChild("上昇", &pack);
        _204.x = 0.0f;
    } else {
        if (_278.isOnBit(2))
            _278.resetBit(2);
        changeToWait(true);
        _204.x = 4.0f;
    }
}

void AirOctaState::m37() {
    if (isCurrentChild("逃げる")) {
        auto* damage_manager = sub_710072BA90(mActor);
        if (damage_manager && damage_manager->getField54() == 20)
            return;
    }
    changeChild("リアクション");
}

void AirOctaState::m38() {
    changeToWait(false);
}

void AirOctaState::m39() {}

}  // namespace uking::ai
