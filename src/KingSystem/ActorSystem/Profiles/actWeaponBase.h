#pragma once

#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace ksys::act {

class InstParamPack;

// TODO
class WeaponBase : public Actor {
public:
    bool areExtraActorsReady() const;

    // FIXME: figure out return types, parameters and names
    virtual void m148();
    virtual void m149();
    virtual void m150();
    virtual void m151();
    virtual void m152();
    virtual void m153();
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual void m157();
    virtual void m158();
    virtual const sead::SafeString& m159() const;
    virtual const sead::SafeString& m160() const;

    static void requestCreateWeaponActor(const char* actor, const sead::Matrix34f& matrix,
                                         f32 scale, sead::Heap* heap,
                                         ksys::act::BaseProcHandle* handle, s32 life,
                                         ksys::act::InstParamPack* params, s32 task_lane_id);

protected:
    // TODO
    u8 _840[0xaa0 - 0x840];
    BaseProcHandle mExtraActorHandle;
};

}  // namespace ksys::act
