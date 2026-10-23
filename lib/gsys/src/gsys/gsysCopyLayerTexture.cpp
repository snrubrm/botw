#include <gsys/gsysCopyLayerTexture.h>
#include <gsys/gsysLayer.h>

namespace gsys {

// 0x7100bf5fcc: binds this texture to `layer`; both ends of the association are cleared and
// replaced. The Layer back pointer is at +0x3e8, this object's at +0x500.
void CopyLayerTexture::setLayer(Layer* layer) {
    if (mLayer == layer)
        return;
    if (mLayer)
        mLayer->mCopyLayerTexture = nullptr;
    if (layer) {
        if (layer->mCopyLayerTexture)
            layer->mCopyLayerTexture->mLayer = nullptr;
        layer->mCopyLayerTexture = this;
    }
    mLayer = layer;
}

// 0x7100bf5ffc: the trim viewport follows the layer's viewport.
void CopyLayerTexture::adjustTrimViewportToLayer() {
    if (!mLayer)
        return;
    mViewport = mLayer->mViewport;
}

}  // namespace gsys
