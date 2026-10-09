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

// NON_MATCHING: matrix copy and scalar dot products have a different instruction schedule.
// 0x7101406934
void ListenerPoser::makeListenerMatrix_(sead::Matrix34f* out, const sead::Camera& camera,
                                        const sead::Vector3f& position,
                                        const sead::Vector3f& offset) {
    if (!out)
        return;

    sead::Vector3f right, up, look;
    camera.getRightVectorByMatrix(&right);
    camera.getUpVectorByMatrix(&up);
    camera.getLookVectorByMatrix(&look);
    *out = camera.getMatrix();
    out->m[0][3] = -(offset.x + right.dot(position));
    out->m[2][3] = -(offset.z + look.dot(position));
    out->m[1][3] = -(offset.y + up.dot(position));
}

}  // namespace aal
