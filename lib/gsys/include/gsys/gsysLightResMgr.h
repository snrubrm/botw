#pragma once

#include <container/seadPtrArray.h>
#include <thread/seadCriticalSection.h>

#include "gsys/gsysLightRig.h"
#include "gsys/gsysLightRigObj.h"

namespace gsys {

class Model;

// The per-model pools of light rigs. The two pointer arrays hold the available and in-use rig
// objects and the critical section guards them. Only the release and allocate paths that
// ModelSceneGI uses are modelled.
template <typename T>
class LightResMgr {
public:
    using LightType = typename T::LightType;
    using Obj = LightRigObj<LightType>;

    virtual ~LightResMgr();
    // 0x7100c33a80 / 0x7100c33c14 / 0x7100c33d9c
    void free(T* rig, Model* model, int index);

    // Inline-only in the original; the three ModelSceneGI::alloc bodies 0x7100c339cc /
    // 0x7100c33b60 / 0x7100c33cf4 contain it. Takes the last free rig object, binds it to the
    // rig and enables it.
    Obj* alloc(T* rig);

private:
    /* 0x08 */ sead::PtrArray<Obj> mFree;
    /* 0x18 */ sead::PtrArray<Obj> mUsed;
    /* 0x28 */ sead::CriticalSection mCS;
};

}  // namespace gsys
