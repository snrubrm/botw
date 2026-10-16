#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"

// Defined in actPlayerBase.cpp (0x710084beec).
bool j_eventMgrHasActiveEventMaybe(ksys::act::Actor* actor);

namespace uking::act {

Unk_71008502cc::Unk_71008502cc(ksys::act::Actor* actor)
    : Unk_710244dd20(actor), _13c(0), _140(0.0f), _144(0), _148(0) {}

Unk_71008502cc::~Unk_71008502cc() {
    _144 = 0;
    _140 = 0;
    _148 = 0;
}

bool Unk_71008502cc::m9() {
    return j_eventMgrHasActiveEventMaybe(sead::DynamicCast<ksys::act::Player>(_10));
}

void Unk_71008502cc::m12(int index) {
    switch (index) {
    case 0: {
        auto* player = sead::DynamicCast<uking::act::PlayerBase>(_10);
        if (!player || !player->sub_710084CF24())
            _8.setBit(0);
        break;
    }
    case 1: {
        auto* player = sead::DynamicCast<uking::act::PlayerBase>(_10);
        if (!player || !player->sub_710084CF24())
            _8.setBit(1);
        break;
    }
    case 5:
        _140 = _10->getParam()->getRes().mGParamList->getPlayer()->mShockTime.ref();
        _8.setBit(5);
        break;
    default:
        Unk_710244dd20::m12(index);
        break;
    }
}

void Unk_71008502cc::m13(int index) {
    switch (index) {
    case 0:
        _8.resetBit(0);
        break;
    case 1:
        _8.resetBit(1);
        break;
    case 5:
        _8.resetBit(5);
        break;
    default:
        Unk_710244dd20::m13(index);
        break;
    }
}

void Unk_71008502cc::m18() {
    Unk_710244dd20::m18();
}

void Unk_71008502cc::m19() {
    Unk_710244dd20::m19();
}

bool Unk_71008502cc::m14() {
    if (auto* player = sead::DynamicCast<uking::act::PlayerBase>(_10))
        return player->m200();
    return false;
}

bool Unk_71008502cc::m15() {
    if (Unk_710244dd20::m15())
        return true;
    auto* player = sead::DynamicCast<uking::act::PlayerBase>(_10);
    if (!player)
        return false;
    if (player->get1a0())
        return true;
    auto* obj = player->getMapObject();
    if (obj && obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000))
        return true;
    return false;
}

bool Unk_71008502cc::m16(s32 kind) {
    const bool ret = Unk_710244dd20::m16(kind);
    f32 time;
    if (kind == 3)
        time = _148;
    else if (kind == 4)
        time = _144;
    else
        return ret;
    return time <= 0.0f;
}

bool Unk_71008502cc::sub_7100850CE4() const {
    return _8.isOn(0x3);
}

bool Unk_71008502cc::sub_7100850CF4() const {
    return _8.isOn(0x587);
}

}  // namespace uking::act
