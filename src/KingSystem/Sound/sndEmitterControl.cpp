#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include <aal/aalArbiter.h>
#include <aal/aalEmitter.h>
#include <aal/aalSystemAccessor.h>

namespace ksys::snd {

Unk_710105abc0::Unk_710105abc0(sead::Heap* heap)
    : _8(nullptr), _38(0), _39(false), _3c(0.891f) {
    if (auto* arbiter = aal::SystemAccessor::getArbiter()) {
        _8 = arbiter->allocEmitter(nullptr, "Emitter");
        if (_8)
            _8->mSpatialSetting.setPositioned(false);
    }
}


Unk_710105abc0::~Unk_710105abc0() {
    if (_8) {
        if (auto* arbiter = aal::SystemAccessor::getArbiter()) {
            arbiter->freeEmitter(_8);
            _8 = nullptr;
        }
    }
}

bool Unk_710105abc0::sub_710105B090() {
    if (_38.isOn(1) && SoundMgr::instance()->_30->_60.getValue() !=
                           SoundMgr::instance()->_30->_60.getTarget())
        return false;
    return true;
}

}  // namespace ksys::snd
