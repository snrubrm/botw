#include "KingSystem/Sound/sndMgr.h"
#include <aal/aalListenerMgr.h>
#include <aal/aalSystemAccessor.h>

namespace ksys::snd {

ListenerPoser::ListenerPoser() = default;

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
