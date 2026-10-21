// The TU at 0x7101048ac0 .. 0x7101049570: the sound status (SoundMgr::_288) and its debug reports.
#include <cstdarg>
#include <prim/seadSafeString.h>
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/System/PlayReportMgr.h"

namespace ksys::snd {

// NON_MATCHING: the original stores mMaxChannelNum first (store scheduling).
Unk_SoundMgrStatus::Unk_SoundMgrStatus() = default;

Unk_SoundMgrStatus::~Unk_SoundMgrStatus() = default;

// NON_MATCHING: the va_list save area is laid out differently (as in sndStreamPath.cpp).
void debugReportStatus2(Unk_SoundMgrStatus* status, PlayReportEvent event, const char* format, ...) {
    sead::FixedSafeString<256> value;
    std::va_list args;
    va_start(args, format);
    value.formatV(format, args);
    va_end(args);

    sead::FixedSafeString<64> key;
    key.appendWithFormat("Snd_%s", event.text());
    PlayReportMgr::instance()->reportDebug(key, value);
}

}  // namespace ksys::snd
