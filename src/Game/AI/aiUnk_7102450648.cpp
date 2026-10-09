#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

bool Unk_7102450648::m2(const ksys::Message& message) {
    if (message.getType() != _34)
        return false;

    _8 = ksys::act::PlayerInfo::getSomeProcLink();
    const auto* data = static_cast<const bool*>(message.getUserData());
    _38 = data ? *data : false;
    _30 = true;
    _18 = message.getSource();
    return true;
}

// Signed IDs below this range are rejected before the second type query.
bool Unk_7102450648::sub_710070A674(const ksys::Message& message) {
    if (s32(message.getType()) >= 0x1800000 && s32(message.getType()) < 0x180002a) {
        _8 = ksys::act::PlayerInfo::getSomeProcLink();
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
