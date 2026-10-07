#include "KingSystem/Sound/sndMgr.h"
#include <aal/aalListenerMgr.h>
#include <aal/aalSystemAccessor.h>

// Address placeholder: the original factory returns a concrete aal::ListenerPoser subclass.
aal::ListenerPoser* sub_71012C5810(const sead::SafeString& name, sead::Heap* heap);

namespace ksys::snd {

ListenerPoser::ListenerPoser() = default;

void ListenerPoser::init(sead::Heap* heap) {
    mPoser = sub_71012C5810("snd::ListenerPoser", heap);
    mListener = aal::SystemAccessor::getListenerMgr()->createListener("デフォルトリスナー");
    mListener->setPoser(mPoser);
    mListener->_f0 = true;
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
