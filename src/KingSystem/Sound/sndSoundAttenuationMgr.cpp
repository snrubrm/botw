// The TU at 0x71012c2870 .. 0x71012c2b98: SoundMgr::_70 (Unk_710251af30), with the static initialiser 0x71012c2b60.
#include "KingSystem/Sound/sndSoundAttenuationMgr.h"
#include <aal/aalSystemAccessor.h>
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

Unk_710251af30::~Unk_710251af30() {
    if (_10) {
        delete _10;
        _10 = nullptr;
    }
    if (_18) {
        delete _18;
        _18 = nullptr;
    }
    if (_20) {
        if (auto* arbiter = aal::SystemAccessor::getArbiter())
            arbiter->setEmitterAllocateCallback(nullptr);
        delete _20;
        _20 = nullptr;
    }
}

void Unk_710251af30::init(sead::Heap* heap) {
    _10 = new (heap) Unk_710251b7a0;
    _10->sub_71012CEE90(heap);
}

void Unk_710251af30::init2(sead::Heap* heap, sead::Heap* callback_heap) {
    _18 = new (heap) Unk_710251b730;
    if (_18)
        _18->sub_71012CEBC0(heap);
    if (_10)
        _10->sub_71012CEE94();

    if (!callback_heap)
        return;

    _20 = new (callback_heap) Unk_710251afc8;
    if (_20) {
        _20->init(callback_heap);
        if (auto* arbiter = aal::SystemAccessor::getArbiter())
            arbiter->setEmitterAllocateCallback(_20);
    }
}

namespace {
util::InitConstants sInitConstants;
util::InitTimeInfo sInitTimeInfo;
}  // namespace

}  // namespace ksys::snd
