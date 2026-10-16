#pragma once

#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>

namespace ksys {

class GameConfig {
public:
    static GameConfig* getInstance() { return sInstancePtr; }

    // vtable 0x710246ce50 (the instance made by 0x71008bba94, size 0x840). Placeholder slot names; not defined in our
    // build yet. Slot 0 is 0x71007d1f0c (returns 1), slots 3 - 5 return static data, slot 6 returns true.
    virtual u32 m0() const;
    virtual ~GameConfig();
    virtual const void* m3();
    virtual const void* m4();
    virtual const void* m5();
    // Placeholder enum (lane2's lead: `int(m6()) != 1` reproduces the stack spill in EventSysActors::
    // loadEventSystemActors / finishedLoading, which compare the result with 1). Value names unknown.
    SEAD_ENUM(Unk6, _0, _1)
    // EventSysActors::loadEventSystemActors / finishedLoading compare the result with 1.
    virtual Unk6 m6();

    char _8[0x3dc - 0x8];
    // VillagerMgr::init (0x7100d5e7f4) disables its updates when this byte is true.
    bool _3dc;
    bool _3dd;
    char _3de[0x3b];
    bool _419;
    sead::SafeString mPatrolFeatures;

private:
    static GameConfig* sInstancePtr;
};

}  // namespace ksys
