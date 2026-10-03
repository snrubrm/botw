#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace uking::act {
class Rideable;
class Unk_7100e8b2b8;
}  // namespace uking::act

namespace ksys::map {
class Object;
class ObjectLinkData;
}  // namespace ksys::map

namespace ksys::phys {
class SystemGroupHandler;
}

namespace ksys::res {
struct AttCheck_Unk1;
class GParamList;
class Shop;
}  // namespace ksys::res

namespace ksys::act {

class Actor;

class ActorConstDataAccess : public ActorLinkConstDataAccess {
public:
    ActorConstDataAccess() = default;
    explicit ActorConstDataAccess(BaseProc* proc) : ActorLinkConstDataAccess(proc) {}

    bool acquireActor(const ActorLinkConstDataAccess& other);

    bool hasProc() const { return ActorLinkConstDataAccess::hasProc(); }

    /// Checks whether the acquired BaseProc is `proc`.
    bool hasProc(BaseProc* proc) const;

    /// Checks whether the acquired BaseProc and the BaseProcLink's actor are the same
    /// by comparing the IDs.
    bool hasProc(const BaseProcLink& link) const;

    template <typename T>
    bool isDerivedFrom() const {
        return sead::IsDerivedFrom<T>(mProc);
    }

    bool linkAcquire(BaseProcLink* link) const;
    bool linkAcquireImmediately(BaseProcLink* link) const;

    void debugLog(s32, const sead::SafeString& method_name) const;

    bool isPlayerProfile() const;
    bool isWeaponProfile() const;
    bool isNPCProfile() const;
    bool isEnemyProfile() const;

    const sead::SafeString& getProfile() const;
    const sead::SafeString& getName() const;

    const sead::SafeString& getLiftType() const;
    bool isDisableFreezeLift() const;
    bool isDisableBurnLift() const;

    bool hasTag(const char* tag) const;
    bool hasTag(u32 tag) const;
    const char* getUniqueName() const;
    u32 getId() const;
    bool acquireConnectedCalcParent(ActorLinkConstDataAccess* accessor) const;
    bool acquireConnectedCalcChild(ActorLinkConstDataAccess* accessor) const;
    bool hasConnectedCalcParent() const;
    bool checkFlag2B() const;

    bool deleteLater(BaseProc::DeleteReason reason) const;
    bool deleteEx(BaseProc::DeleteReason reason) const;
    bool sleep(BaseProc::SleepWakeReason reason) const;
    bool wakeUp(BaseProc::SleepWakeReason reason) const;
    // vel, ang_vel and scale are optional (Actor::setProperties null-checks them).
    bool setProperties(int x, const sead::Matrix34f& mtx, const sead::Vector3f* vel,
                       const sead::Vector3f* ang_vel, const sead::Vector3f* scale,
                       bool is_life_infinite, int i, int life) const;
    bool setProperties(const sead::Matrix34f& mtx, const sead::Vector3f* vel,
                       const sead::Vector3f* ang_vel, const sead::Vector3f* scale,
                       bool is_life_infinite, int i, int life) const;
    bool isStateSleep() const;
    bool isStateCalc() const;
    bool isDeletedOrDeleting() const;

    res::GParamList* getGParamList() const;
    res::Shop* getShopData() const;

    const sead::SafeString& getAttackSpHitActor() const;
    const sead::SafeString& getAttackSpHitTag() const;
    const sead::SafeString& getAttackWeakHitTag() const;
    f32 getAttackSpHitRatio() const;
    s32 getAttackPower() const;

    bool checkLinkTagActivated(bool a, bool b);
    void triggerLink();
    map::ObjectLinkData* getMapObjectLinkData() const;
    map::Object* getMapObject() const;

    s32 getEnemyRank() const;

    bool getSameGroupActorName(sead::SafeString* name) const;

    bool checkFlag18() const;
    bool isPlayerTheConnectedParent() const;

    const sead::Vector3f& getPreviousPos() const;
    const sead::Vector3f& getPreviousPos2() const;
    // CSV name; returns Actor::_454
    const sead::Vector3f& getField44C_Vec3() const;
    uking::act::Rideable* getHorseOptions() const;
    uking::act::Unk_7100e8b2b8* getHorseRideStuff() const;
    const sead::Vector3f& getVelocity() const;
    const sead::Vector3f& getAngVelocity() const;
    // 0x7100d10e6c (~50 callers): checks a bit of the actor's previous ActorFlag2 value (Actor::_51c);
    // AI code passes 26 (ActorFlag2::Alive).
    bool sub_7100D10E6C(int bit) const;
    // 0x7100d10fb8 (~25 callers): Actor::mActorFlags2 & ActorFlag2::_40.
    bool sub_7100D10FB8() const;
    // 0x7100d11f10: the actor has a main rigid body or a character controller.
    bool sub_7100D11F10() const;
    // 0x7100d12e64: bit 0 of byte +0x30 of the object returned by Actor vtable slot 130 (+0x410);
    // false if there is none.
    bool sub_7100D12E64() const;
    // 0x7100d0feac (declared only): Actor vtable slot 50 (false if the proc is not an actor).
    bool sub_7100D0FEAC() const;
    // 0x7100d11188 (declared only; lane1 s21): the actor's chemical matrix (Chemical 0x7100d9153c)
    // into `out` and true; `*out = Matrix34f::ident` and false without a chemical.
    bool sub_7100D11188(sead::Matrix34f* out) const;
    // 0x7100d11254 (declared only): Chemical::_34 of the actor's chemical (0 if none).
    f32 sub_7100D11254() const;
    // 0x7100d131d0: Chemical::_c0 (a state; 0 if none) of the actor's chemical `idx`
    // (getChemicalStuff() if idx < 0).
    int sub_7100D131D0(int idx) const;
    // 0x7100d13fd0 (CSV actorGetLife): *Actor::getLife(), 1 if the actor has no life value.
    s32 getLife() const;
    // 0x7100d14078: Actor::getMaxLife().
    s32 getMaxLife() const;
    // 0x7100d13bb8: Unk_71006e45c4::m2() of the actor's m128() object.
    bool sub_7100D13BB8() const;
    // 0x7100d13ae4: AttClient::sub_7100D72554 of the actor's attention client `name`.
    bool sub_7100D13AE4(const sead::SafeString& name, BaseProc* proc,
                        const res::AttCheck_Unk1* arg, bool a4) const;
    // 0x7100d10448: the physics instance set's system group handler `idx` (0 / 1).
    phys::SystemGroupHandler* sub_7100D10448(s32 idx) const;
    // 0x7100d103a0 (CSV act::acc::Actor::x): the physics instance set's handler _188[idx] (0 / 1).
    phys::SystemGroupHandler* x(s32 idx) const;
    void getHomeMtx(sead::Matrix34f* mtx) const;
    bool getAabb(sead::Vector3f* min, sead::Vector3f* max) const;

    void setThisActorAsParent(BaseProc* child, bool delete_parent_on_delete);
    void setThisActorAsChild(BaseProc* parent, bool delete_child_on_delete);

    bool isAttClientEnabled(const sead::SafeString& client) const;

    // 0x0000007100009130 (defined in actPlayerOrEnemy.cpp)
    bool isPlayerOrEnemy() const;

    bool isFlyingBalloon() const;
    u32 getBalloonHungActorBaseProcID() const;

    bool checkFlag25() const;

    // Defined in Profiles/actDynamicActor.cpp (the DynamicActor TU). sub_71006DE298 returns the bool
    // map unit parameter `name` (actorAIGetBool), sub_71006DE338 the AI tree variable
    // (getBoolParam); both false if not an actor.
    bool sub_71006DE298(const sead::SafeString& name) const;
    bool sub_71006DE338(const sead::SafeString& name) const;
    // 0x71006e3e00: the actor's "IsEnemyLiftable" AI bool (true by default).
    bool sub_71006E3E00() const;
    // 0x71006e3fb4: DynamicActor::_a69 != 0 (false if not a DynamicActor).
    bool sub_71006E3FB4() const;
    // 0x71006de850 (CSV act::acc::isBgGroundHit; debugLog name)
    bool isBgGroundHit() const;

    // NPC accessors (placeholder names; defined in Game/Actor/actNPC.cpp, the NPC TU):
    // each casts the actor to uking::act::NPC and reads an NPC field (false / zero if not an NPC).
    bool sub_7100022ED8() const;
    bool sub_7100022FD0() const;
    bool sub_7100023358() const;
    bool sub_7100023450() const;
    const sead::Vector3f& sub_710002354C() const;

    f32 getHorseMoveRadius() const;
    f32 getHorseAvoidOffset() const;
    bool horseTargetedIsCircularMoveAlways() const;

private:
    Actor* getActor() const;

    u8 _10 = 0;
};
KSYS_CHECK_SIZE_NX150(ActorConstDataAccess, 0x18);

bool acquireActor(BaseProcLink* link, ActorConstDataAccess* accessor);

}  // namespace ksys::act
