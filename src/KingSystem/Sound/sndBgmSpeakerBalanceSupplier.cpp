// The TU after sndBgmMgr.cpp's static initialiser 0x7100ff8c18: the BGM speaker balance supplier
// (0x7100ff8c74 .. 0x7100ff8e90) and its static initialiser 0x7100ff8e94.
#include <cmath>
#include <aal/aalSettings.h>
#include <aal/aalSpeakerChannelVolume.h>
#include <aal/aalSystemAccessor.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace {
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

Unk_71024fc990::~Unk_71024fc990() = default;

// NON_MATCHING: clang merges the left / right stores into indexed stores (as in Unk_71025028c0) and copies the
// device earlier.
void Unk_71024fc990::calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device,
                                        s32 index_a, s32 index_b, f32 spread) {
    auto* mgr = ksys::snd::sub_7100FFD71C();
    if (mgr->sub_7100FF8AA0() &&
        aal::SystemAccessor::getSettings()->mOutputModes[device] == aal::OutputMode::Surround) {
        const f32 front = mgr->sub_7100FF8AAC();
        const f32 rear = mgr->sub_7100FF8AB8() * ksys::snd::SoundMgr::instance()->sub_71011FC310();
        if (_c == 1) {
            const f32 left = std::sqrt((1.0f - _8) * 0.5f) * spread;
            volume->volume[0] = front * left;
            volume->volume[2] = rear * left;
            const f32 right = std::sqrt((_8 + 1.0f) * 0.5f) * spread;
            volume->volume[1] = front * right;
            volume->volume[3] = rear * right;
        } else if (index_b) {
            volume->volume[1] = front * spread;
            volume->volume[3] = rear * spread;
        } else {
            volume->volume[0] = front * spread;
            volume->volume[2] = rear * spread;
        }
    } else if (_c == 1) {
        const f32 left = std::sqrt((1.0f - _8) * 0.5f);
        const f32 right = std::sqrt((_8 + 1.0f) * 0.5f);
        volume->volume[0] = left * spread;
        volume->volume[1] = right * spread;
    } else if (index_b) {
        volume->volume[1] = spread;
    } else {
        volume->volume[0] = spread;
    }
}
