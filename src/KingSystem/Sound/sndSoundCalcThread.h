#pragma once

#include "KingSystem/Utils/Types.h"
#include <thread/seadThread.h>

namespace ksys::snd {

// Whole factory 11FC348 allocates 100 bytes; ctor 12C889C calls Thread at offset zero.
// Whole table 251B440 inherits all Thread slots except calc_ and deleting destruction.
// The D1 slot is Thread D1 B18E58; D0 12C8924 calls that D1 then operator delete.
class SoundCalcThread2 : public sead::Thread {
public:
    explicit SoundCalcThread2(sead::Heap* heap);

protected:
    void calc_(sead::MessageQueue::Element msg) override;

    // Whole ctor clears fc; whole calc_ checks and sets it after physics registration.
    bool _fc;
};
KSYS_CHECK_SIZE_NX150(SoundCalcThread2, 0x100);

}  // namespace ksys::snd
