#pragma once

#include <math/seadBoundBox.h>
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
class NavMeshCharacter;
class SystemGroupHandler;
}

namespace ksys::res {
struct AttCheck_Unk1;
class GParamList;
class Shop;
}  // namespace ksys::res

namespace ksys::xlink {
class XLink;
}

namespace ksys::act {

class Actor;
class Chemical;
class Schedule;

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
    // 0x7100d0f57c (lane4 s29; HorseFollow::enter_ / m35): the NavMeshCharacter of the actor: the ride info's
    // `_28` (Actor slot 130) when set, else Actor slot 45.
    phys::NavMeshCharacter* sub_7100D0F57C() const;
    // 0x7100d1443c (lane4 s29; HorseFollow::m35): `_18._b` of the actor's RideableBase (Actor slot 132),
    // or `_18._9` if it is 0; 0 without a RideableBase.
    u64 sub_7100D1443C() const;
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
    // 0x7100d0f57c (lane1 s26): the actor's ride info's NavMeshCharacter if it has one (HorseRideInfo::_28),
    // else the actor's own (Actor::m45()); null if the proc is not an actor. Name is a guess.
    phys::NavMeshCharacter* sub_7100D0F57C() const;
    // 0x7100d142e0 (declared only; lane1 s26): int result read by EnemyTargetGearSelect::calc_ (the target's gear).
    // Placeholder name.
    u64 sub_7100D142E0() const;
    // 0x7100d11188 (declared only; lane1 s21): the actor's chemical matrix (Chemical 0x7100d9153c)
    // into `out` and true; `*out = Matrix34f::ident` and false without a chemical.
    bool sub_7100D11188(sead::Matrix34f* out) const;
    // 0x7100d11254 (declared only): Chemical::_34 of the actor's chemical (0 if none).
    f32 sub_7100D11254() const;
    // 0x7100d110e4 (declared only; lane2 s21): how far the actor's position is below its `_6f0` (0 unless
    // the proc is an Actor with Actor::get68f() set).
    f32 sub_7100D110E4() const;
    // 0x7100d131d0: Chemical::_c0 (a state; 0 if none) of the actor's chemical `idx`
    // (getChemicalStuff() if idx < 0).
    int sub_7100D131D0(int idx) const;
    // 0x7100d13448 (lane1 s24): whether Chemical::_c0 of the actor's chemical `max(idx, 0)` is 2 (false without one).
    bool sub_7100D13448(int idx) const;
    // 0x7100d1463c (lane1 s22): Actor::m140() (false if the proc is not an actor).
    bool sub_7100D1463C() const;
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
    // 0x7100d105a8 (CSV act::acc::Actor::getHomePos; lane4 s29): the raw home matrix (identity if not an actor).
    void sub_7100D105A8(sead::Matrix34f* mtx) const;
    // 0x7100d10bd4 (CSV act::acc::getField464_Vec3; lane4 s29): copies Actor::_46c (zero if not an actor) to `out`.
    void sub_7100D10BD4(sead::Vector3f* out) const;
    bool getAabb(sead::Vector3f* min, sead::Vector3f* max) const;
    // 0x7100d0fd54 (CSV act::acc::Actor::getAabb_0; lane1 s22, declared only): the actor's AABB
    // (Actor::mAabb if it has a model, else a static default box).
    const sead::BoundBox3f& sub_7100D0FD54() const;

    void setThisActorAsParent(BaseProc* child, bool delete_parent_on_delete);
    void setThisActorAsChild(BaseProc* parent, bool delete_child_on_delete);

    bool isAttClientEnabled(const sead::SafeString& client) const;

    // 0x0000007100009130 (defined in actPlayerOrEnemy.cpp)
    bool isPlayerOrEnemy() const;

    bool isFlyingBalloon() const;
    u32 getBalloonHungActorBaseProcID() const;

    bool checkFlag25() const;

    // lane4 s29: field accessors (false / null / 0 if not an actor). Placeholder names = addresses.
    // 0x7100d0f048: Actor::_4f8 > 0.
    bool sub_7100D0F048() const;
    // 0x7100d0f180: Actor::mFadeOutDeleteType != 0.
    bool sub_7100D0F180() const;
    // 0x7100d0ff48: Actor::_68f (CSV act::acc::Actor::*).
    bool sub_7100D0FF48() const;
    // 0x7100d0f214 (CSV ActorAccessor::getField568): Actor::mXLink.
    xlink::XLink* sub_7100D0F214() const;
    // 0x7100d0f3d0 (CSV act::acc::Actor::getQuestLink): Actor::mSchedule.
    Schedule* sub_7100D0F3D0() const;
    // 0x7100d10a08 (CSV act::acc::getField488): Actor::_490.
    f32 sub_7100D10A08() const;
    // 0x7100d12100 (CSV act::actor::getScaleX): Actor::mScale.x.
    f32 sub_7100D12100() const;
    // 0x7100d1525c: Actor::_687 = true.
    void sub_7100D1525C() const;
    // 0x7100d11048 / 0x7100d14114 / 0x7100d14e0c: forward Actor::m57() / m38() / getChemicalStuff().
    bool sub_7100D11048() const;
    f32 sub_7100D14114() const;
    Chemical* sub_7100D14E0C() const;
    // 0x7100d13080 / 0x7100d13128: Chemical::_1b8 / _1bc of the actor's chemical (0 without).
    f32 sub_7100D13080() const;
    f32 sub_7100D13128() const;
    // 0x7100d146d8: the DynamicActor's m100() object has `_100 == 2`.
    bool sub_7100D146D8() const;
    // 0x7100d0efa4: bit `idx` of Actor::mSpecialJobTypesMaskOverride.
    bool sub_7100D0EFA4(s32 idx) const;
    // 0x7100d15448 / 0x7100d154dc: Actor::_720 += 1 / -= 1 (atomically).
    void sub_7100D15448() const;
    void sub_7100D154DC() const;
    // 0x7100d13c64 / 0x7100d13d10: Unk_71006e45c4::m9() / m16() of Actor::m128().
    bool sub_7100D13C64() const;
    bool sub_7100D13D10() const;

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
