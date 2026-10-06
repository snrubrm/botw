#include "Game/AI/Behavior/behaviorInterestNeckControl.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"

namespace uking::behavior {

InterestNeckControl::InterestNeckControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

InterestNeckControl::~InterestNeckControl() = default;

bool InterestNeckControl::m6(sead::Heap* heap) {
    auto* global = ksys::act::GlobalParameter::instance();
    _30 = global->getGlobalParam()->mNPCIgnorePlayerTime.ref();
    _34 = global->getGlobalParam()->mNPCCancelIgnorePlayerTime.ref();
    _40 = ksys::Timer(_30, _30);
    _4c = ksys::Timer(-1.0f, -1.0f, 0.0f);
    return true;
}

void InterestNeckControl::m7() {
    if (_3c <= 2) {
        ++_3c;
        return;
    }

    auto* actor = mActor;
    if (!actor)
        return;
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* control = bone_control->_0;

    if (_40.value <= sead::Mathf::epsilon()) {
        _4c.update();
        if (_4c.value <= sead::Mathf::epsilon())
            _40 = ksys::Timer(_30, _30);
    }

    auto* npc = sead::DynamicCast<act::NPC>(actor);
    if (npc && !npc->_1050) {
        if (control)
            control->sub_7100D85774();
        return;
    }

    ksys::act::acc::PlayerBase player;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::instance()->getPlayerLink(), &player);
    if (npc->_fe8 & 0x2000000) {
        control->sub_7100D8571C(player.getPreviousPos2());
        control->sub_7100D85750();
        return;
    }

    auto* awareness = actor->getAwareness();
    if (!awareness)
        return;
    awareness->sub_7100D7E74C(_38);

    awareness = actor->getAwareness();
    auto* entry = awareness->getSortedEntry(0);
    bool use_second = false;
    if (entry) {
        if (ksys::act::isPlayerProfile(&entry->_0.mLink) && _40.value <= sead::Mathf::epsilon() &&
            *mIgnorePlayerByTimePass_s) {
            entry = actor->getAwareness()->getSortedEntry(1);
            use_second = true;
        }
    } else {
        _40 = ksys::Timer(_30, _30);
    }
    if (!entry) {
        if (control)
            control->sub_7100D85774();
        return;
    }

    if (ksys::act::isPlayerProfile(&entry->_0.mLink)) {
        actor->getAwareness()->sub_7100D7E74C(_38 + sead::Mathf::deg2rad(5));
        if (player.x_6()) {
            _40 = ksys::Timer(_30, _30);
        } else {
            _40.update();
            if (_40.value <= sead::Mathf::epsilon())
                _4c = ksys::Timer(_34, _34);
        }
    } else if (!use_second) {
        _40 = ksys::Timer(_30, _30);
    }

    ksys::act::ActorConstDataAccess entry_accessor;
    ksys::act::acquireActor(&entry->_0.mLink, &entry_accessor);
    if (control) {
        control->sub_7100D8571C(entry_accessor.getPreviousPos2());
        control->sub_7100D85750();
    }
}

// NON_MATCHING: the original zeroes the request in aligned 8 / 16 byte chunks from +0x10 (we start at +0xc); the
// request layout is only partly known
void InterestNeckControl::m8() {
    _3c = 0;
    if (_38 < 0) {
        if (auto* awareness = mActor->getAwareness()) {
            Unk_71023e26d8 request;
            if (auto* sensor = awareness->_260[0]) {
                if (sensor->m5(&request))
                    _38 = request._c;
            }
        }
    }
}

void InterestNeckControl::loadParams() {
    getStaticParam(&mIgnorePlayerByTimePass_s, "IgnorePlayerByTimePass");
}

void InterestNeckControl::m9() {
    auto* actor = mActor;
    if (!actor || actor->get1a0())
        return;
    if (auto* obj = actor->getMapObject()) {
        if (obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000))
            return;
    }
    sub_71005DB3EC(actor);
}

}  // namespace uking::behavior
