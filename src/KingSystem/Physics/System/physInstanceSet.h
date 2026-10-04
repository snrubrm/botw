#pragma once

#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadObjArray.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace gsys {
class Model;
}

namespace sead {
class DirectResource;
}

namespace ksys::res {
class Handle;
class RagdollBlendWeight;
class RagdollConfigList;
}  // namespace ksys::res

namespace ksys::phys {

class CharacterController;
class CharacterFormSet;
class ClothSet;
class CollisionInfo;
class ContactPointInfo;
class NavMeshCharacter;
class ParamSet;
class RagdollController;
class RagdollInstance;
class RigidBodySet;
class SphereParam;
class SphereRigidBody;
class SystemGroupHandler;
class UserTag;

class InstanceSet : public sead::hostio::Node {
public:
    enum class Flag : u32 {
        _1 = 1 << 0,
        _2 = 1 << 1,
        _8 = 1 << 3,
        DisableDraw = 1 << 2,
        _10 = 1 << 4,
        _800 = 1 << 11,
        _20000 = 1 << 17,
        _80000 = 1 << 19,
        _200000 = 1 << 21,
        Cloth1 = 1 << 22,
        Cloth2 = 1 << 23,
        Cloth3 = 1 << 24,
        InDemo = 1 << 25,
        _40000000 = 1 << 30,
        _80000000 = 1u << 31,
    };

    InstanceSet(const sead::SafeString& actor_name, const sead::SafeString& actor_profile,
                const ParamSet& param_set);
    virtual ~InstanceSet();

    const sead::SafeString& getName() const { return mName; }
    const ParamSet* getParamSet() const { return mParamSet; }
    CharacterController* getCharacterController() const { return mCharacterController; }
    NavMeshCharacter* getNavMeshCharacter() const { return mNavMeshCharacter; }
    RagdollInstance* getRagdollInstance() const { return mRagdollInstance; }
    // Read inline by ksys::act::ActorBind::m6-m8 (0x7100d3c78c...).
    const sead::TypedBitFlag<Flag>& getFlags() const { return mFlags; }
    sead::TypedBitFlag<Flag>& getFlags() { return mFlags; }

    void setFlag2();
    // Removes the system group handlers _178[0] / _178[1] from phys::System (clearing _188).
    void sub_7100FB835C();
    void clothVisibleStuff();
    void setInDemo();
    void resetInDemo();
    void clothVisibleStuff_0(s32 setting);
    void sub_7100FB9BAC(InstanceSet* other);
    u32 sub_7100FB9C2C() const;
    void sub_7100FBA9BC();
    // lane4 s30: apply-to-everything helpers (rigid body sets, listed bodies, character controller, ragdoll).
    // 0x7100fb9d24: resetFrozenState.
    void sub_7100FB9D24();
    // 0x7100fb9e90 (CSV ActorPhysics::calledIfStopTimerSmallMass): setEntityMotionFlag200.
    void sub_7100FB9E90(bool on);
    // 0x7100fbaa3c: removeFromWorld.
    void sub_7100FBAA3C();
    // 0x7100fbaac8: removeFromWorldAndResetLinks (true if all succeeded).
    bool sub_7100FBAAC8();
    void sub_7100FBAC4C(ContactLayer layer);
    void sub_7100FBACE0(ContactLayer layer);
    void sub_7100FBAD74();
    void sub_7100FBADDC();
    // 0x7100fba174 (declared only; lane3 s20; TurnToActorBase::leave_): triggers the scheduled motion type changes.
    void sub_7100FBA174();
    // 0x7100fbb29c (declared only; lane3 s20; Explode::leave_): loops over the body sets and bodies calling
    // sub_7100FBB00C.
    void sub_7100FBB29C();
    RigidBody* sub_7100FBAEDC(s32 rigidbody_idx, s32 ragdoll_idx) const;
    // 0x7100fbaf18: called with one body of the actor (actActorSensorUtil sub_71007A3768/3778).
    bool sub_7100FBAF18(RigidBody* body);
    void sub_7100FBB00C(RigidBody* body, RigidBodyParam* param);
    // 0x7100fbb18c: called with the actor's "Tgt" body set (actActorSensorUtil sub_71007A3800).
    bool sub_7100FBB18C(RigidBodySet* set);
    void setMtxAndScale(const sead::Matrix34f& mtx, bool a2, bool a3, f32 scale);
    // 0x7100fbb4b4: whether the ragdoll contact point info (_a8) has any contact (declaration only).
    bool sub_7100FBB4B4() const;
    void* findX(const sead::SafeString& a1, const sead::SafeString& a2) const;
    RigidBody* findRigidBody(const sead::SafeString& name) const;
    // 0x7100fbb7bc (CSV ActorPhysics::findBodyGroupByName): the rigid body set called `name`.
    RigidBodySet* findBodyGroupByName(const sead::SafeString& name);
    // 0x7100fbb50c (CSV ActorPhysics::findBodyByName, ~100 callers): byte-identical to
    // findBodyGroupByName (the original has two copies; const-ness is a guess).
    RigidBodySet* findBodyByName(const sead::SafeString& name) const;
    s32 findContactPointInfo(const sead::SafeString& name) const;
    // Inline in the original (StoneStickRoot::init_); null if `idx` is out of range.
    ContactPointInfo* getContactPointInfoAt(s32 idx) const { return mContactPointInfo[idx]; }
    s32 findCollisionInfo(const sead::SafeString& name) const;
    // 0x7100fbc838 (declaration only): selects ragdoll controller `idx` (clamped; resets the previous
    // one, stored in _112).
    void sub_7100FBC838(s32 idx);
    // 0x7100fbdb5c: resets the currently selected ragdoll controller (_112, clamped).
    void sub_7100FBDB5C();
    // 0x7100fbdb90 / 0x7100fbdbd8: RagdollController::setFactor / setBoneWeight of controller `idx` (false if
    // `idx` is out of range).
    bool sub_7100FBDB90(s32 idx, f32 factor);
    bool sub_7100FBDBD8(s32 idx, s32 bone, f32 weight);
    // 0x7100fbdc70 (declaration only): scales the friction of the bodies by the ragdoll config.
    void sub_7100FBDC70(f32 scale);
    // 0x7100fbdd40 (declaration only).
    void sub_7100FBDD40(bool on);
    // 0x7100fba010 (CSV ActorPhysics::x_1; declared only; IceMakerBlock): applies setFixed(fixed) to
    // every rigid body set, listed body and the ragdoll and updates flag 0x40000 (name is a guess).
    void sub_7100FBA010(bool fixed);
    // Read inline by Unk_71006ecc78::sub_71006ED9EC (currently selected ragdoll controller).
    s8 get112() const { return _112; }
    void sub_7100FBD284(const sead::Matrix34f& mtx);
    // 0x7100fbdfa4 (CSV ActorPhysics::x_5): sets `handler` as the system group handler of every
    // rigid body set, listed body, the ragdoll and the character controller.
    void sub_7100FBDFA4(SystemGroupHandler* handler);
    // 0x7100fbe0a0 (CSV InstanceSet::systemGroupHandlerStuff; declared only; lane2 s20; SiteBossSpearRoot::leave_
    // passes the player's handler and false).
    void systemGroupHandlerStuff(SystemGroupHandler* handler, bool a2);
    void sub_7100FBC890(const sead::Matrix34f& mtx, bool a2, bool a3);
    s32 sub_7100FBDA2C(const sead::SafeString& name) const;
    // 0x7100fbe7f0: CharacterControllerParam::findFormIdx(name) of the param data's character
    // controller param (`_18->_58`), or -1. Placeholder name (declaration only).
    s32 sub_7100FBE7F0(const sead::SafeString& name) const;
    // Read inline by ActorConstDataAccess::sub_7100D10448 (index clamped like a sead::SafeArray)
    // and MagneShaftRoot::m51.
    SystemGroupHandler* get178(s32 idx) const { return _178[idx]; }
    // Read inline (DisableCloth behavior); null if the actor has no cloth.
    ClothSet* getClothSet() const { return mClothSet; }
    // Read inline by LastBossRailWarpAction::leave_ and sub_710072E804 (index clamped).
    SystemGroupHandler* get188(s32 idx) const { return _188[idx]; }
    // 0x7100fbb668: index of the rigid body set called `name` (-1 if none).
    int sub_7100FBB668(const sead::SafeString& name) const;
    // Read inline by sub_71007A2EB0 (actActorSensorUtil; null if out of range).
    RigidBodySet* getRigidBodySet(int idx) const { return mRigidBodySets[idx]; }
    ContactPointInfo* getContactPointInfo(int idx) const { return mContactPointInfo[idx]; }
    // 0x7100fc012c / 0x7100fc01b0 (declared only): for every listed body (0xb0-byte entries at
    // 0x108) that has no 0x98 entry: calls 0xf8305c with `heap` (or the global heap pointer at GOT
    // 0x7102579290 if null) / unlinks the 0x98 and 0xa0 entries. Used by AddRigidBodyToWorld and
    // RemoveNavMeshObj (EnableNavMeshCut); names are placeholders.
    void sub_7100FC012C(sead::Heap* heap);
    void sub_7100FC01B0();
    // 0x7100fc0300: makes a sphere rigid body (group handler from _188 unless the param has one)
    // and links it into the body list at 0x148. Used by ksys::act::AITerror.
    SphereRigidBody* sub_7100FC0300(SphereParam* param, sead::Heap* heap);
    // 0x7100fc0600: unlinks `body` from that list and deletes it.
    void sub_7100FC0600(RigidBody* body);

private:
    struct Unk1 {
        u8 _0[0x48];
    };

    sead::SafeString mName;
    ParamSet* mParamSet;  // non-const: getRigidBodySet() is called on it (0x7100fbaf18)
    sead::TypedBitFlag<Flag> mFlags;
    u16 _24{};
    u16 _26{};
    gsys::Model* mModel;
    f32 mScale;
    UserTag* mUserTag;
    sead::PtrArray<RigidBodySet> mRigidBodySets;
    sead::PtrArray<CollisionInfo> mCollisionInfo;
    sead::PtrArray<ContactPointInfo> mContactPointInfo;
    sead::Buffer<res::Handle*> mRigidBodySetResHandles;

    CharacterController* mCharacterController{};
    CharacterFormSet* mCharacterFormSet{};

    RagdollInstance* mRagdollInstance{};
    sead::Buffer<RagdollController*> _98;
    ContactPointInfo* mRagdollContactPointInfo{};
    res::Handle* mRagdollResHandle{};
    res::RagdollBlendWeight* mRagdollBlendWt;
    res::RagdollConfigList* mRagdollConfigList;

    res::Handle* mClothResHandle{};
    sead::DirectResource* mClothRes{};
    ClothSet* mClothSet;

    res::Handle* mSupportBoneResHandle{};
    void* _e8{};
    void* _f0{};

    NavMeshCharacter* mNavMeshCharacter;
    sead::Buffer<void*> _100;
    u16 _110{};
    s8 _112;
    sead::ObjArray<Unk1> mLinkMatricesMaybe;
    sead::Buffer<void*> _138;
    sead::TList<RigidBody*> mList;
    sead::ListNode _160;
    u32 _170{};
    sead::SafeArray<SystemGroupHandler*, 2> _178;
    sead::SafeArray<SystemGroupHandler*, 2> _188;
};
KSYS_CHECK_SIZE_NX150(InstanceSet, 0x198);

}  // namespace ksys::phys
