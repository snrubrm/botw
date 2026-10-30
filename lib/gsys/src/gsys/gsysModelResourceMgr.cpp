#include <gsys/gsysModelResourceMgr.h>
#include <gsys/gsysModelResource.h>
#include <g3d/aglNW4FToNN.h>
#include <prim/seadScopedLock.h>

namespace gsys {

// sInstance 0x71025fd460, sStaticDisposer 0x71025fd458, disposer vtable 0x71024ca640.
SEAD_SINGLETON_DISPOSER_IMPL(ModelResourceMgr)

ModelResourceMgr::~ModelResourceMgr() = default;

void ModelResourceMgr::add_(ModelResource* resource) {
    auto lock = sead::makeScopedLock(mCS);
    resource->_1d0 = _34++;
    mResources.pushBack(resource);
    if ((_2a & 0xc) == 4)
        agl::g3d::ResFile::GetTextureCount(resource->getResFile());
    mFlags.setBit(3);
}

bool ModelResourceMgr::search_(const void* file, SearchResult* result) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& resource : mResources) {
        if (resource.getResFile() == file) {
            if (result)
                result->resource = &resource;
            return true;
        }
    }
    return false;
}

// NON_MATCHING: list traversal schedules node-offset arithmetic differently.
bool ModelResourceMgr::remove_(ModelResource* resource) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& item : mResources) {
        if (&item == resource) {
            mResources.erase(resource);
            mFlags.setBit(3);
            return true;
        }
    }
    return false;
}

bool ModelResourceMgr::isExist(const ModelResource* resource) const {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& item : mResources) {
        if (&item == resource)
            return true;
    }
    return false;
}

}  // namespace gsys
