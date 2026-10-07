#include "aal/aalDebugDrawUtil.h"
#include <gfx/seadPrimitiveRenderer.h>
#include <math/seadMatrix.h>

namespace aal {

namespace DebugDrawUtil {

// 0x7100ba97ac
void initializePrimitiveDrawer(sead::PrimitiveDrawer* drawer, const sead::Camera& camera,
                               const sead::Projection& projection) {
    drawer->setCamera(&camera);
    drawer->setProjection(&projection);
    drawer->setModelMatrix(&sead::Matrix34f::ident);
}

}  // namespace DebugDrawUtil

}  // namespace aal
