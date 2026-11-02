#include "Game/Actor/aiUnk_7102357210.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"

bool Unk_7102450648::m2(const ksys::Message& message) {
    if (message.getType() != _34)
        return false;

    _8 = uking::act::PlayerInfo::getSomeProcLink();
    const auto* data = static_cast<const bool*>(message.getUserData());
    _38 = data ? *data : false;
    _30 = true;
    _18 = message.getSource();
    return true;
}

// Signed IDs below this range are rejected before the second type query.
bool Unk_7102450648::sub_710070A674(const ksys::Message& message) {
    if (s32(message.getType()) >= 0x1800000 && s32(message.getType()) < 0x180002a) {
        _8 = uking::act::PlayerInfo::getSomeProcLink();
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    return false;
}

bool Unk_7102450648::sub_710070AEE4(const ksys::Message& message, ksys::act::Actor* a,
                                     ksys::act::Actor* b) {
    if (b)
        return sub_710070AEF4(message, a, b);
    return sub_710070AEF4(message, a, a);
}

void Unk_7102450648::sub_710070AE18(ksys::act::Actor* actor) {
    using ksys::act::AttActionCode;
    if (_34 != u32(AttActionCode::Dummy))
        return;
    const auto* attention = actor->getAttention();
    if (!attention)
        return;
    for (s32 i = 0; i < attention->getNumClients(); ++i) {
        const auto* client = attention->getClientByIdx(i);
        if (!client->isEnabled())
            continue;
        const auto code = static_cast<AttActionCode>(client->sub_7100D72544().getRelativeIndex());
        switch (code) {
        case AttActionCode::Pick:
        case AttActionCode::Catch:
        case AttActionCode::CheckCatch:
        case AttActionCode::CatchWeapon:
        case AttActionCode::Skin:
        case AttActionCode::Buy:
        case AttActionCode::Display:
        case AttActionCode::DisplayBow:
        case AttActionCode::DisplayShield:
        case AttActionCode::PickUp:
        case AttActionCode::PullOut:
            _34 = u32(code);
            return;
        default:
            break;
        }
    }
}
