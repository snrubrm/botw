#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

// The TU's static initialiser is 0x7101057c2c (`_GLOBAL__sub_I_sndResourceManager.cpp`).
static util::InitTimeInfo sInitTimeInfo;

Unk_7102502950::~Unk_7102502950() {
    mHandles.freeBuffer();
}

}  // namespace ksys::snd
