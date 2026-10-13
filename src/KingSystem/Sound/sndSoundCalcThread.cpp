#include "KingSystem/Sound/sndSoundCalcThread.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include <prim/seadNamable.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::snd {

SoundCalcThread2::SoundCalcThread2(sead::Heap* heap)
    : Thread("SoundCalcThread", heap, Thread::cDefaultPriority,
             sead::MessageQueue::BlockType::NonBlocking, 0x7fffffff, 0x8000, 0x20),
      _fc(false) {}

void SoundCalcThread2::calc_(sead::MessageQueue::Element msg) {
    if (!_fc) {
        if (auto* system = phys::System::instance()) {
            sead::INamable name("SoundCalcThread");
            system->runJobsMaybe(&name);
            _fc = true;
        }
    }
    Thread::sleep(sead::TickSpan::makeFromSeconds(1) * (1.0f / 30.0f));
    SoundMgr::instance()->calc();
}

}  // namespace ksys::snd

Unk_710251b5c0::~Unk_710251b5c0() = default;
