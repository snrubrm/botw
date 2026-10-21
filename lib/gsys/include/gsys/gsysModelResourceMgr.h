#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadCriticalSection.h>

namespace nn::g3d {
class ResModel;
}

namespace gsys {

// The model resource manager singleton. createInstance 0x7100c0c748 allocates 0x2a0 bytes; vtable
// 0x71024ca660 is the sead::hostio::Node stub, then D2 0x7100c0ca00 / D0 0x7100c0ca14. The
// destructor only tears down the critical section at +0x50. Only that member is modelled.
class ModelResourceMgr : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(ModelResourceMgr)

public:
    // Inlined into createInstance; declared only.
    ModelResourceMgr();
    virtual ~ModelResourceMgr();

    // 0x7100c0d5e0 (declared only): whether `model` belongs to a registered resource.
    bool isExist(const nn::g3d::ResModel* model) const;

private:
    u8 _28[0x50 - 0x28];
    sead::CriticalSection mCS;
    u8 _90[0x2a0 - 0x90];
};
static_assert(sizeof(ModelResourceMgr) == 0x2a0);

}  // namespace gsys
