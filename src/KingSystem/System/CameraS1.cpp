#include "KingSystem/System/CameraS1.h"
#include <layer/aglLayer.h>
#include <layer/aglRenderer.h>

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
