#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

bool Unk_7102450648::m2(const ksys::Message& message) {
    if (message.getType().value != _34)
        return false;

    _8 = ksys::act::PlayerInfo::getSomeProcLink();
    const auto* data = static_cast<const bool*>(message.getUserData());
    _38 = data ? *data : false;
    _30 = true;
    _18 = message.getSource();
    return true;
}

// NON_MATCHING: the original compares the type value as signed (b.le/b.ge)
bool Unk_7102450648::sub_710070A674(const ksys::Message& message) {
    if (message.getType().value >= 0x1800000 && message.getType().value < 0x180002a) {
        _8 = ksys::act::PlayerInfo::getSomeProcLink();
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    return false;
}
