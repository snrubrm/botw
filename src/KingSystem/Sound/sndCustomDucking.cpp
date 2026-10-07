#include "KingSystem/Sound/sndMgr.h"

namespace ksys::snd {

Unk_710103b704::~Unk_710103b704() = default;

void Unk_710103b704::sub_710103CFE8(int bgm_type, int se_type) {
    _5d0 = bgm_type;
    _5d4 = se_type;
}

}  // namespace ksys::snd
