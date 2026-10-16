#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjList.h>
#include <container/seadStrTreeMap.h>
#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>
#include <gfx/seadCamera.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadDelegate.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

// Named camera registry: a name -> entry map over a pool of camera entries.
// vtable 0x71025137d0 (D2 0x71011f1b18, D0 0x71011f1ce4). The dtor clears and frees the map
// (node size 0x68: a 32-character key) and the entry list.
class Unk_71025137d0 {
public:
    // Pool entry (0x10 bytes, virtual dtor called by the ObjList clear in 0x71011f1b18).
    class Entry {
    public:
        virtual ~Entry();

        sead::Camera* camera;
    };

    virtual ~Unk_71025137d0();

    // 0x7100928874 (instantiated for ksys::Unk_71024dd110 in the uking camera code): the camera
    // registered under `name`, if it has type T.
    template <typename T>
    T* findCamera(const sead::SafeString& name) const {
        sead::Camera* camera = nullptr;
        if (auto* node = mMap.find(name))
            camera = node->value()->camera;
        return sead::DynamicCast<T>(camera);
    }

protected:
    sead::StrTreeMap<32, Entry*> mMap;
    // Set to -1 by the owner's ctor (0x71011f1358).
    s32 _28;
    sead::ObjList<Entry> mEntries;
};
KSYS_CHECK_SIZE_NX150(Unk_71025137d0, 0x60);

// vtable 0x71025137a8 (D2 0x71011f1528, D0 0x71011f1924, m2 0x71011f1a2c): the registry owned by
// Unk_71025136c8 at +0x178.
class Unk_71025137a8 : public Unk_71025137d0 {
public:
    ~Unk_71025137a8() override;

protected:
    // 0x20-byte pool set up by Unk_71025136c8's prepare (0x71011f164c); freed with delete[] in the
    // dtor.
    sead::FreeList _60;
    // Delegate bound to this object and 0x71011f1fa8 (vtable 0x7102513898); arity not confirmed.
    sead::Delegate<Unk_71025137a8> _70;
};
KSYS_CHECK_SIZE_NX150(Unk_71025137a8, 0x90);

// vtable 0x71025136c8 (23 slots); camera manager task (CSV: vlt::CameraMgrTask::ctor at
// 0x71011f1358). Task singleton: sInstance is the global at 0x71026522d8's target
// (setInstance_ 0x71011f1304, deleteInstance 0x71011f1324).
// Second base at 0x168: sead::hostio::Node (secondary vtable 0x7102513790, getNodeClassType).
class Unk_71025136c8 : public sead::CalculateTask, public sead::hostio::Node {
    SEAD_TASK_SINGLETON(Unk_71025136c8)
    SEAD_RTTI_OVERRIDE(Unk_71025136c8, sead::CalculateTask)
public:
    ~Unk_71025136c8() override;
    void enter() override {}
    void exit() override {}
    void calc() override {}

    Unk_71025137a8& getCameras() { return mCameras; }

private:
    Unk_71025137a8 mCameras;
};
KSYS_CHECK_SIZE_NX150(Unk_71025136c8, 0x208);
