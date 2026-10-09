#include "KingSystem/Sound/sndMgr.h"

namespace ksys::snd {

Unk_710103b704::~Unk_710103b704() = default;

bool Unk_710103b704::isBgmReady() {
    return _5e0.sub_710105B090();
}

void Unk_710103b704::setWorldMuteType(bool movie, const sead::SafeString& type) {
    if (movie)
        _5e0.sub_710105B37C();
    else
        _5e0.sub_710105B394(type);
    _5e0.sub_710105B8EC();
}

void Unk_710103b704::sub_710103CFE8(int bgm_type, int se_type) {
    _5d0 = bgm_type;
    _5d4 = se_type;
}

}  // namespace ksys::snd
