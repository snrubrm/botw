#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadBitFlag.h>
#include <thread/seadCriticalSection.h>

namespace nn::g3d {
class ResModel;
}

namespace gsys {

class ModelResource;

// The model resource manager singleton. createInstance 0x7100c0c748 allocates 0x2a0 bytes; vtable
// 0x71024ca660 is the sead::hostio::Node stub, then D2 0x7100c0ca00 / D0 0x7100c0ca14. The
// destructor tears down the critical section at +0x50. The resource list and state it uses
// are modeled; the remaining members are opaque.
class ModelResourceMgr : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(ModelResourceMgr)

public:
    // Inlined into createInstance; declared only.
    ModelResourceMgr();
    virtual ~ModelResourceMgr();

    // 0x7100c0d5e0 (declared only): whether `model` belongs to a registered resource.
    bool isExist(const nn::g3d::ResModel* model) const;
    bool isExist(const ModelResource* resource) const;

    // create_ c0aa18 supplies an eight-byte result and reads this pointer.
    struct SearchResult {
        ModelResource* resource;
    };
    static_assert(sizeof(SearchResult) == 8);
    void add_(ModelResource* resource);
    bool search_(const void* file, SearchResult* result);
    bool remove_(ModelResource* resource);

private:
    // add_ and remove_ set bit 3; the constructor initializes this halfword.
    sead::BitFlag16 mFlags;
    u16 _2a;
    u32 _2c;
    u32 _30;
    u32 _34;
    // createInstance c0c7dc initializes this list and sets its node offset
    // to ModelResource+28; isExist/search/remove traverse it under mCS.
    sead::OffsetList<ModelResource> mResources;
    mutable sead::CriticalSection mCS;
    u8 _90[0x2a0 - 0x90];
};
static_assert(sizeof(ModelResourceMgr) == 0x2a0);

}  // namespace gsys
