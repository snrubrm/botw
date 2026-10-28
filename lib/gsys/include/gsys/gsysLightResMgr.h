#pragma once

#include <container/seadPtrArray.h>
#include <thread/seadCriticalSection.h>

namespace gsys {

class Model;

// The per-model pools of light rigs. Only the release path that ModelSceneGI::free
// 0x7100c33a70 / 0x7100c33c04 / 0x7100c33d8c calls is modelled; the two pointer arrays hold the
// available and in-use rigs and the critical section guards them.
template <typename T>
class LightResMgr {
public:
    virtual ~LightResMgr();
    // 0x7100c33a80 / 0x7100c33c14 / 0x7100c33d9c
    void free(T* rig, Model* model, int index);

private:
    /* 0x08 */ sead::PtrArrayImpl mFree;
    /* 0x18 */ sead::PtrArrayImpl mUsed;
    /* 0x28 */ sead::CriticalSection mCS;
};

}  // namespace gsys
