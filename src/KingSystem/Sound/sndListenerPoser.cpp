#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Sound/sndListenerPoserImpl.h"
#include <aal/aalListenerMgr.h>
#include <aal/aalSystemAccessor.h>

namespace ksys::snd {

ListenerPoser::ListenerPoser() = default;

void ListenerPoser::sub_7101055100() {
    _a8.moveTo(1.0f, 0.5f);
}

void ListenerPoser::init(sead::Heap* heap) {
    mPoser = sub_71012C5810("snd::ListenerPoser", heap);
    mListener = aal::SystemAccessor::getListenerMgr()->createListener("デフォルトリスナー");
    mListener->setPoser(mPoser);
    mListener->_f0 = true;
}

void ListenerPoser::sub_7101054C10(bool on) {
    _a8.moveTo(on ? 1.0f : 0.0f, 0.5f);
    _85 = on;
}

void ListenerPoser::sub_7101055538(s32 value) {
    if (!_70) {
        _70 = true;
        _74 = value;
    }
}

void ListenerPoser::sub_71010554C8() {
    if (mPoser)
        mPoser->_d8 = 1;
    if (!_85)
        _a8.moveTo(0.0f, 0.5f);
    sub_7101055538(15);
    if (_78 == 5 || _78 == 6)
        _78 = 0;
}

ListenerPoser::~ListenerPoser() {
    if (mListener) {
        aal::SystemAccessor::getListenerMgr()->destroyListener(mListener);
        mListener = nullptr;
    }
    if (mPoser) {
        mPoser->destroy();
        mPoser = nullptr;
    }
}

}  // namespace ksys::snd
