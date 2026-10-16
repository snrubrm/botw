#include "KingSystem/System/CameraS1.h"
#include <layer/aglLayer.h>
#include <layer/aglRenderer.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/Chemical/chmChemical.h"
#include "KingSystem/Chemical/chmElement.h"

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

void Element::emitWrap(const ElementName& name, ksys::act::Unk_71024dd490* holder_mgr) {
    if (name.mName.isEmpty())
        return;
    if (name.mName == "----")
        return;

    auto* chemical = ksys::chm::Chemical::instance();
    if (!chemical || !chemical->_78)
        return;

    auto* holder = new (chemical->_78, std::nothrow_t{}) ksys::act::Unk_71024dd1c8();
    if (!holder)
        return;

    holder->sub_7100D8CFF0(name, holder_mgr);
    setHolderMaybe(holder);
    if (!m29(name, mHeap) || !holder_mgr->sub_7100D9AFD8(holder)) {
        unlinkHolderMaybe();
        holder->sub_7100D8CFAC();
        delete holder;
    }
}

s32 Element::m25() {
    if (!mHolder)
        return 0;
    return mHolder->_78;
}

f32 Element::m14(sead::Vector3f* out, const sead::Vector3f& pos) {
    *out = mHolder->_1c;
    return mHolder->_3c;
}

f32 Element::m13(f32* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) {
    *out = 1.0f;
    return mHolder->_30;
}

f32 Element::m15(sead::Vector3f* out) {
    *out = mHolder->_1c;
    return mHolder->_44;
}

f32 Element::m17(ksys::act::Chemical* chemical) {
    if (!mHolder)
        return 0.0f;
    return mHolder->_34;
}

const sead::Vector3f& Element::m6() const {
    return sead::Vector3f::zero;
}

