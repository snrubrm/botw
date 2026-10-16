#include "Game/Actor/AI/aiEnemyRoot.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"

Unk_7100700834::Unk_7100700834() : _0(0), _4(0), _8(0) {}

Unk_7100700834::~Unk_7100700834() = default;

bool Unk_7100700834::sub_7100700844(const ksys::Message* message) {
    if (message->getType() != 0x80000ca)
        return false;
    auto* payload = static_cast<Payload*>(message->getUserData());
    if (!payload)
        return false;
    switch (payload->mType) {
    case 1:
        if (payload->mValue > 0.0f) {
            _4 = payload->mValue;
            _8 = 1;
        }
        break;
    case 2:
        _8 = 2;
        break;
    }
    return true;
}

// NON_MATCHING: Unk_71006ecc78::sub_71006EE274 is declared to return u8 (the original caller tests it as a
// bool: tbnz instead of and + cbnz).
void Unk_7100700834::sub_71007008E0(ksys::act::Actor* actor) {
    if (!actor || _8 == 0)
        return;
    auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor);
    if (!dynamic_actor)
        return;
    auto* controller = actor->getCharacterController();
    if (!controller)
        return;
    auto* ragdoll = dynamic_actor->_868;
    if (!ragdoll)
        return;

    if ((ragdoll->sub_71006EE274() || ragdoll->sub_71006ED9EC() || ragdoll->sub_71006EDDD4()) &&
        _8 != 2) {
        if (_0 <= 0.0f)
            _0 = controller->sub_7100F60390();
        if (_4 != controller->sub_7100F60390())
            controller->sub_7100F60378(_4);
        return;
    }

    if (_0 > 0.0f && _0 != controller->sub_7100F60390())
        controller->sub_7100F60378(_0);
    if (_8 == 2) {
        _8 = 0;
        _0 = 0;
        _4 = 0;
    }
}

void Unk_7100702370::sub_7100702370() {
    _14 = 0;
    _10 = mActor->getMtx().m[1][3];
}

// NON_MATCHING: the original keeps the ragdoll test as a bool that is merged through a phi (`mov w0, wzr; tbz w0`) and reads
// `_14` through `this` in every block; ours shares one address computation (`add x20, x19, #0x14` + pre-indexed loads)
void Unk_7100702370::sub_7100702384() {
    const f32 y = mActor->getMtx().m[1][3];
    if (auto* controller = mActor->getCharacterController()) {
        if (controller->mFlags.isOnBit(0))
            _14 |= 1;
    }
    bool dead_ragdoll = false;
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (dynamic_actor->_868)
            dead_ragdoll = dynamic_actor->_868->sub_71006ED9EC();
    }
    if (!dead_ragdoll && !(_14 & 4) && !isBgGroundHit(mActor, false) &&
        !mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2(0x21))) {
        auto* ride_info = mActor->getPlayerRideInfo();
        if (!ride_info || !(ride_info->_30 & 1)) {
            if (_14 & 1)
                return;
            if (_10 - y > *mFallHeight)
                _14 |= 2;
            return;
        }
    }
    _14 = 0;
    _10 = y;
}
