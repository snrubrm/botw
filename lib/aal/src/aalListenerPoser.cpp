#include "aal/aalListenerPoser.h"
#include <gfx/seadCamera.h>
#include "aal/aalListenerMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// NON_MATCHING: the original calls the virtual setObjName here (it is not inlined in its translation unit).
// 0x7101406800
ListenerPoser::ListenerPoser(const sead::SafeString& name) {
    setObjName(name);
    SystemAccessor::getListenerMgr()->addListenerPoser(this);
}

// 0x71014068f0
void ListenerPoser::destroy() {
    SystemAccessor::getListenerMgr()->removeListenerPoser(this);
    delete this;
}

}  // namespace aal
