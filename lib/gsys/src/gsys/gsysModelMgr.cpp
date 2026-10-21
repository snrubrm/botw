#include <gsys/gsysModelMgr.h>
#include <gsys/gsysModelScene.h>
#include <utility/aglDevTools.h>

namespace gsys
{

// sInstance 0x71025fccf0, sStaticDisposer 0x71025fcce8, disposer vtable 0x71024ca078.
SEAD_SINGLETON_DISPOSER_IMPL(ModelMgr)

// 0x7100c030a8
void ModelMgr::createFFLTexturePerFrame(agl::DrawContext*) {}

// 0x7100c030ac
f32 ModelMgr::getMeterScale() const {
    return agl::utl::DevTools::getMeterScale();
}

// 0x7100c02d64
s32 ModelMgr::getXluZPrePassID() {
    return mXluZPrePassId++ & 0x7ff;
}

}  // namespace gsys
