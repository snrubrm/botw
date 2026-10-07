#include "Game/AI/AI/aiRemainsWaterWeakPointRoot.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

RemainsWaterWeakPointRoot::RemainsWaterWeakPointRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsWaterWeakPointRoot::~RemainsWaterWeakPointRoot() = default;

bool RemainsWaterWeakPointRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsWaterWeakPointRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71007A458C(mActor, true);
    if (ksys::gdt::getFlag_Water_Relic_Step4()) {
        changeChild("戦闘終了");
    } else if (mActor->checkLinkBasicSig()) {
        changeChild("機能停止");
    } else {
        const bool battle_time = ksys::gdt::getFlag_Water_Relic_BattleTime();
        mActor->emitBasicSigOff();
        if (battle_time)
            changeChild("起動中");
        else
            changeChild("待機");
    }
}

// NON_MATCHING: string temporary scheduling and state-branch sharing differ.
void RemainsWaterWeakPointRoot::calc_() {
    if (isCurrentChild("待機") && ksys::gdt::getFlag_Water_Relic_BattleTime()) {
        mActor->emitBasicSigOff();
        changeChild("起動中");
        return;
    }
    auto* child = getCurrentChild();
    if (isCurrentChild("格納中") && (child->isFinished() || child->isFailed())) {
        changeChild("機能停止");
        return;
    }
    if (!isCurrentChild("起動中") ||
        !(child->isChangeable() || child->isFinished() || child->isFailed()) ||
        !isAttackedByElectricArrow() || !ksys::gdt::getFlag_Water_Relic_BattleTime())
        return;
    auto* object = mActor->getMapObject();
    if (mActor->get1a0() ||
        (object && object->getFlags0().isOn(ksys::map::Object::Flag0::_20000)))
        return;
    {
        ksys::act::acc::PlayerBase player;
        if (player.getPlayerFromPlayerInfo() && player.m204())
            return;
    }
    sub_710054C520();
    mActor->emitBasicSigOn();
    changeChild("格納中");
}

// NON_MATCHING: accessor cleanup and boolean return sharing differ.
bool RemainsWaterWeakPointRoot::isAttackedByElectricArrow() {
    auto* damage = sub_710072BA90(mActor);
    if (!damage || !damage->_216.isOn(2))
        return false;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(damage->getAttacker(), &accessor) &&
        accessor.getName() == "ElectricArrow")
        return true;
    return false;
}

// NON_MATCHING: linked-object induction and temporary scheduling differ.
void RemainsWaterWeakPointRoot::sub_710054C520() {
    ksys::act::ActorConstDataAccess accessor;
    auto* object = mActor->getMapObject();
    if (!object || !object->getLinkData())
        return;
    auto& objects = object->getLinkData()->mObjects;
    for (s32 i = 0; i < objects.size(); ++i) {
        objects[i]->getActorWithAccessor(accessor);
        if (!accessor.hasProc() || accessor.getName() != sead::SafeString("RemainsWater"))
            continue;
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000069), nullptr);
        ksys::act::acc::PlayerBase player;
        if (player.getPlayerFromPlayerInfo())
            sendMessage(*player.getMessageTransceiverId(), ksys::MessageType(0x80000b2), nullptr);
        break;
    }
}

void RemainsWaterWeakPointRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWaterWeakPointRoot::loadParams_() {}

}  // namespace uking::ai
