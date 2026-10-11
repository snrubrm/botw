#include "KingSystem/System/CameraMgr.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(CameraMgr)

CameraMgr::~CameraMgr() = default;

bool CameraMgr::init(const InitArg& arg) {
    _28.sub_7101265390(arg._0);
    _118.sub_7101265390(arg._4);
    return true;
}

void CameraMgr::sub_7100D8C484() {}

void CameraMgr::sub_7100D8C488(s32 index, Unk_71024dd110* camera) {
    _28.sub_7101265398(index, camera);
}

void CameraMgr::sub_7100D8C490(s32 index, Unk_71024dd110* camera) {
    _118.sub_7101265398(index, camera);
}

void CameraMgr::sub_7100D8C498(s32 index) {
    _28.sub_71012654D8(index);
}

void CameraMgr::sub_7100D8C4A0(s32 index) {
    _118.sub_71012654D8(index);
}

void CameraMgr::sub_7100D8C4A8(s32 index) {
    _28.sub_7101265444(index);
}

void CameraMgr::sub_7100D8C4B0(s32 index) {
    _118.sub_7101265444(index);
}

sead::LookAtCamera* CameraMgr::getLookAtCamera() const {
    return _28.getLookAtCamera();
}

const sead::Viewport* CameraMgr::sub_7100D8C4C8() const {
    return _28.getViewport();
}

Unk_71024dd110* CameraMgr::sub_7100D8C4C0() const {
    return _118.getLookAtCamera();
}

s32 CameraMgr::sub_7100D8C4D0() const {
    return _28._8;
}

void CameraMgr::sub_7100D8C4D8() {
    _28.sub_7101265584();
}

void CameraMgr::sub_7100D8C4E0() {
    _118.sub_7101265584();
}

sead::PerspectiveProjection* CameraMgr::sub_7100D8C4E8() {
    return _28.sub_7101265658();
}

sead::PerspectiveProjection* CameraMgr::sub_7100D8C4F0() {
    return _118.sub_7101265658();
}

}  // namespace ksys
