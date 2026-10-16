#include "Game/Actor/AI/aiNPCRoot.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"
#include "Game/Actor/aiUnk_7102357210.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actModelMaterialUtil.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtManager.h"

// Declaration only; the original source namespace of this actor cleanup helper is unknown.
void sub_71007132E4(ksys::act::Actor* actor);

namespace uking::ai {

NPCRoot::NPCRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCRoot::~NPCRoot() = default;

bool NPCRoot::init_(sead::Heap* heap) {
    _68 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void NPCRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: CallArg metadata and zero-pointer stores merge into one pair.
void NPCRoot::sub_71004D8C5C() {
    if (auto* attention = ksys::act::getAttClientByName(mActor, "Talk")) {
        if (!attention->isEnabled())
            return;
    }
    if (!_68)
        return;
    sead::FixedSafeString<64> event;
    sead::FixedSafeString<128> entry;
    sead::FixedSafeString<32> type;
    sub_710040A3BC(_68, &event, &entry, &type);
    if (event.isEmpty() || entry.isEmpty())
        return;
    ksys::evt::Metadata metadata(event.cstr(), entry.cstr(), type.cstr());
    ksys::evt::CallArg arg;
    arg.metadata = &metadata;
    arg.proc = mActor;
    arg._31 = true;
    if (auto* manager = ksys::evt::Manager::instance())
        manager->callEvent(arg);
    sendMessage(*mActor->getMesTransceiverId(), static_cast<ksys::MessageType>(0x8000034), nullptr);
}

void NPCRoot::leave_() {
    _203 = false;
    _208 = sead::Vector3f::zero;
    if (mActor->getRootAi()->getNewChildIdx() != 0)
        return;

    if (_80.hasProc()) {
        _1c0 = {-1.0f, -1.0f, 0.0f};
        sub_71004DC3D4(&_80);
    }
    if (mActor->getASList()->x_1(1, 0).findIndex("Talk") != -1)
        changeAS("Face_C_Default", true, 1, 0);
    if (mActor->getName() == "Npc_Kakariko016") {
        if (auto* awareness = mActor->getAwareness())
            awareness->_320 |= 0x100000;
    }
}

void NPCRoot::onPreDelete() {
    sub_71007132E4(mActor);
}

void NPCRoot::loadParams_() {
    getStaticParam(&mReleaseInterest2Time_s, "ReleaseInterest2Time");
    getStaticParam(&mPlayerHitVelocity_s, "PlayerHitVelocity");
    getStaticParam(&mStaggerUpperASName_s, "StaggerUpperASName");
    getStaticParam(&mStaggerUpperRunASName_s, "StaggerUpperRunASName");
}

void NPCRoot::m34() {
    const sead::SafeString name = mActor->getASList()->sub_710115ECF4(59, 1);
    const bool is_name_empty = name.isEmpty();
    mActor->getASList()->x_2(66, 35, is_name_empty && _201, false);
    changeChild("Timeline");
    _201 = false;
    mActor->getASList()->x_2(66, 35, false, false);
}

bool NPCRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() != static_cast<ksys::MessageType>(0x08000034))
        return false;
    if (_68) {
        if (isCurrentChild("Timeline") || isCurrentChild("Rest")) {
            sead::FixedSafeString<64> name;
            mActor->getRootAi()->getCurrentName(&name, nullptr);
            _68->_a70.copy(name);
        }
        setRootAiFlag(ksys::act::ai::RootAiFlag::_5);
    }
    changeChild("EventStartWait", nullptr);
    return true;
}

// 0x71004dc010
bool NPCRoot::sub_71004DC010(ksys::act::Unk_7100d78e50* entry) {
    if (!entry)
        return false;
    auto& link = entry->_0.mLink;
    if (!link.hasProc())
        return false;
    bool result;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&link, &accessor) && accessor.getName().startsWith("RemoteBomb"))
        result = true;
    else if (uking::act::PlayerInfo::getSomeProcLink() == link && entry->_0.m5(9))
        result = true;
    else
        result = false;
    return result;
}

// 0x71004dc204
bool NPCRoot::sub_71004DC204() {
    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&uking::act::PlayerInfo::getSomeProcLink(), &accessor);
    sead::FixedSafeString<32> series;
    accessor.getArmorSeriesType(&series);
    return series == "Black" || series == "Stalfos" || series == "PhantomGanon";
}

// 0x71004dc100
bool NPCRoot::sub_71004DC100(sead::Vector3f* pos, ksys::act::BaseProcLink* attacker) {
    auto* mgr = sead::DynamicCast<act::DamageManagerBase>(mActor->getDamageMgr());
    if (!mgr)
        return false;
    switch (mgr->getField50()) {
    case 0:
    case 1:
    case 2:
    case 3:
        break;
    default:
        return false;
    }
    *attacker = *mgr->getAttacker();
    auto* npc = _68;
    if (!npc)
        return false;
    pos->x = npc->_e30._10.m[0][3];
    pos->y = npc->_e30._10.m[1][3];
    pos->z = npc->_e30._10.m[2][3];
    return true;
}

// 0x71004dc3d4
void NPCRoot::sub_71004DC3D4(ksys::act::BaseProcLink* link) {
    for (s32 i = 0; i < 3; ++i) {
        if (_90[i]._8.hasProc())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        if (!ksys::act::acquireActor(link, &accessor))
            continue;
        _90[i]._0 = true;
        _90[i]._8 = *link;
        _90[i]._18 = 10;
        _90[i]._1c = 10;
        _90[i]._20 = -1;
        _90[i]._28.copy(accessor.getName());
        return;
    }
}

// 0x71004d92dc
void NPCRoot::sub_71004D92DC() {
    sead::FixedSafeString<128> barefoot;
    sead::FixedSafeString<128> sand_boots;
    sead::FixedSafeString<128> snow_boots;
    barefoot.format("%s_Barefoot", mActor->getName().cstr());
    sand_boots.format("%s_SandBoots", mActor->getName().cstr());
    snow_boots.format("%s_SnowBoots", mActor->getName().cstr());

    bool boot = false;
    bool lower_141 = false;
    bool lower_049 = false;
    bool skin_leg = false;
    if (ksys::gdt::getBoolByKey(barefoot, false)) {
        skin_leg = true;
    } else if (ksys::gdt::getBoolByKey(sand_boots, false)) {
        lower_049 = true;
    } else {
        lower_141 = ksys::gdt::getBoolByKey(snow_boots, false);
        boot = !lower_141;
    }

    auto* model = mActor->getModel();
    if (!model)
        return;

    auto key = model->searchMaterial("Mt_Boot");
    if (key.isValid())
        act::setMaterialVisible(model, key, boot);
    key = model->searchMaterial("Mt_Skin_Leg");
    if (key.isValid())
        act::setMaterialVisible(model, key, skin_leg);
    key = model->searchMaterial("Mt_Lower_049");
    if (key.isValid())
        act::setMaterialVisible(model, key, lower_049);
    key = model->searchMaterial("Mt_Lower_141");
    if (key.isValid())
        act::setMaterialVisible(model, key, lower_141);
}

// NON_MATCHING: the original loads the entry position (z, x) before the actor position (operand order only).
void NPCRoot::sub_71004D9608() {
    if (auto* awareness = mActor->getAwareness()) {
        auto* entry = awareness->getSortedEntry(0);
        if (entry && entry->_0._48 >= 2) {
            const auto& mtx = mActor->getMtx();
            const f32 dx = mtx(0, 3) - entry->_58(0, 3);
            const f32 dz = mtx(2, 3) - entry->_58(2, 3);
            if (sead::Mathf::sqrt(dx * dx + dz * dz) < 5.0f) {
                ksys::act::acc::PlayerBase player;
                ksys::act::acquireActor(&entry->_0.mLink, &player);
                if (player.x_6() && !_1b0.hasProc() &&
                    mActor->getParam()->getRes().mGParamList->getNpc()->mIsReactNakedPlayer.ref()) {
                    _1b0 = entry->_0.mLink;
                    _1d8 = {1800.0f, 1800.0f, -1.0f};
                }
            }
        }
    }

    if (_68) {
        _68->_a70 = "";
        _68->_1048 = 3;
        sub_7100713564(mActor, 3);
        _68->_1038 = 0;
        _68->_c74 = 0;
    }
    sub_71005D7518(mActor, true);
}

}  // namespace uking::ai
