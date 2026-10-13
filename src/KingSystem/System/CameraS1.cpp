#include "KingSystem/System/CameraS1.h"
#include <layer/aglLayer.h>
#include <layer/aglRenderer.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace ksys {

CameraS1::CameraS1(s32 id) : _d0(id) {}
CameraS1::~CameraS1() = default;

void CameraS1::sub_7101265390(s32 index) {
    _8 = index;
}

void CameraS1::sub_7101265398(s32 index, Unk_71024dd110* camera) {
    _d0.sub_710131E068(index, camera);
    if (_d0.sub_710131E060() != index)
        return;
    // The original makes this second index query and discards the result.
    _d0.sub_710131E060();
    _d0.sub_710131E118(index);
    auto* layer = agl::lyr::Renderer::instance()->mLayers[_8];
    if (!layer)
        return;
    auto* current = _d0.getLookAtCamera();
    if (current) {
        layer->mCamera = current;
        sub_7101265584();
        layer->mProjection = &_10;
    } else {
        layer->mProjection = nullptr;
    }
}

void CameraS1::sub_71012654D8(s32 index) {
    _d0.sub_710131E0D8(index);
    if (_d0.sub_710131E060() != index)
        return;
    // The original makes this second index query and discards the result.
    _d0.sub_710131E060();
    _d0.sub_710131E118(index);
    auto* layer = agl::lyr::Renderer::instance()->mLayers[_8];
    if (!layer)
        return;
    auto* current = _d0.getLookAtCamera();
    if (current) {
        layer->mCamera = current;
        sub_7101265584();
        layer->mProjection = &_10;
    } else {
        layer->mProjection = nullptr;
    }
}

void CameraS1::sub_7101265444(s32 index) {
    // The original queries the prior index and discards the result.
    _d0.sub_710131E060();
    _d0.sub_710131E118(index);
    auto* layer = agl::lyr::Renderer::instance()->mLayers[_8];
    if (!layer)
        return;
    auto* current = _d0.getLookAtCamera();
    if (current) {
        layer->mCamera = current;
        sub_7101265584();
        layer->mProjection = &_10;
    } else {
        layer->mProjection = nullptr;
    }
}

void CameraS1::sub_7101265584() {
    if (_d0.sub_710131E060() == -1)
        return;
    auto* layer = agl::lyr::Renderer::instance()->mLayers[_8];
    if (!layer)
        return;
    auto* camera = _d0.getLookAtCamera();
    if (!camera)
        return;
    _10.setOffset(camera->_78);
    _10.setFovy_(camera->_74);
    _10.setNear(camera->_6c);
    _10.setFar(camera->_70);
    _10.setAspect(layer->mViewport.getSizeX() / layer->mViewport.getSizeY());
}

Unk_71024dd110* CameraS1::getLookAtCamera() const {
    return _d0.getLookAtCamera();
}

sead::PerspectiveProjection* CameraS1::sub_7101265658() {
    return &_10;
}

const sead::Viewport* CameraS1::getViewport() const {
    auto* layer = agl::lyr::Renderer::instance()->mLayers[_8];
    if (!layer)
        return nullptr;
    return &layer->mViewport;
}

}  // namespace ksys

// vtable 0x7102517b28 (29 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102517b28 {
    SEAD_RTTI_BASE(Unk_7102517b28)
public:
    virtual ~Unk_7102517b28();
    virtual void m4() {}
    virtual void m5() {}
    virtual void m6();
    virtual void m7();
    virtual void m8() {}
    virtual void m9();
    virtual s32 m10() { return 1; }
    virtual void m11() {}
    virtual void m12() {}
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual s32 m26() { return 1; }
    virtual void m27();
    virtual void m28();
};

Unk_7102517b28::~Unk_7102517b28() = default;
