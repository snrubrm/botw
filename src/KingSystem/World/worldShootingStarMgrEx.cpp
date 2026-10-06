#include "KingSystem/World/worldShootingStarMgrEx.h"

namespace ksys::world {

ShootingStarAnchor::~ShootingStarAnchor() = default;

// 0x710250cb50 (TU-local, .data)
static const sead::SafeString sUnk_710250CB50 = "MainField";

ShootingStarMgrEx::ShootingStarMgrEx() : mMapName(sUnk_710250CB50) {}

ShootingStarMgrEx::~ShootingStarMgrEx() {
    mAnchors.freeBuffer();
}

void ShootingStarMgrEx::init_(sead::Heap* heap) {
    ShootingStarMgr::init_(heap);
    mAnchors.allocBuffer(32, heap);
}

void ShootingStarMgrEx::calc_() {
    ShootingStarMgr::calc_();
    for (size_t i = 0; i < size_t(mAnchors.size()); ++i)
        mAnchors.at(i)->calcShootingStarDLC();
}

void ShootingStarMgrEx::spawnStar() {
    ShootingStarMgr::spawnStar();
    mAnchors.clear();
    sub_71010CFE18();
    for (size_t i = 0; i < size_t(mAnchors.size()); ++i)
        mAnchors.at(i)->sub_71010D00B0();
}

}  // namespace ksys::world
