#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

// The TU's static initialiser is 0x7101057c2c (`_GLOBAL__sub_I_sndResourceManager.cpp`).
static util::InitTimeInfo sInitTimeInfo;

}  // namespace ksys::snd
