#include "KingSystem/Sound/sndSoundCalcThread.h"

namespace ksys::snd {

SoundCalcThread2::SoundCalcThread2(sead::Heap* heap)
    : Thread("SoundCalcThread", heap, Thread::cDefaultPriority,
             sead::MessageQueue::BlockType::NonBlocking, 0x7fffffff, 0x8000, 0x20),
      _fc(false) {}

}  // namespace ksys::snd
