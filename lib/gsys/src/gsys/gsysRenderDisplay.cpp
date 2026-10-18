#include "layer/aglRenderDisplay.h"

#include "gsys/gsysModel.h"

namespace agl::lyr {

// 0x7100c84620
void RenderDisplay::dumpDisplayListInfo() const {
    gsys::Model** it = mDisplayList;
    gsys::Model** const end = it + mDisplayListCount;
    for (; it != end; ++it)
        (*it)->requestDraw();
}

}  // namespace agl::lyr
