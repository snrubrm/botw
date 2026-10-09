#pragma once

#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadObjArray.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <gsys/gsysModelAccessKey.h>
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
class ClothResource;
class ModelBoneAccessor;
class ClothSet;
class CollisionInfo;
class ContactPointInfo;
class NavMeshCharacter;
class ParamSet;
class RagdollController;
class RagdollInstance;
class RigidBodySet;
class RigidBodySetParamAccessor;
class BoxRigidBody;
class CapsuleRigidBody;
class CylinderWaterRigidBody;
class RigidBodyFromShape;
class RigidBodyInstanceParam;
class SphereParam;
class SphereRigidBody;
class SystemGroupHandler;
class UserTag;
// Placeholder (vtable 0x7102519a10: the object Actor::initPhysics builds on its stack and passes to the physics
// initialisation): two virtual getters, the cloth / support bone file name overrides, then the destructor.
// Placeholder (declaration only; the constructor is 0x7101226aa8, 0x58 bytes): the runtime support bone object
// InstanceSet::_e8 owns (name is a guess; deleted through its virtual destructor).
class SupportBoneInstanceMaybe : public sead::hostio::Node {
public:
    virtual ~SupportBoneInstanceMaybe();
};

class Unk_7102519a10 {
public:
    virtual const sead::SafeString& getClothFileName() = 0;
    virtual const sead::SafeString& getSupportBoneFileName() = 0;
    virtual ~Unk_7102519a10();
};

class InstanceSet : public sead::hostio::Node {
public:
    // Reads _178/_188 (the system group handler tables).
    friend class RigidBodySetParamAccessor;
    enum class Flag : u32 {
        _1 = 1 << 0,
        _2 = 1 << 1,
        _8 = 1 << 3,
        DisableDraw = 1 << 2,
        _10 = 1 << 4,
        _40 = 1 << 6,
        _800 = 1 << 11,
        _40000 = 1 << 18,
        _8000 = 1 << 15,
        _10000 = 1 << 16,
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
    void sub_7100FB9F30(bool clear);
    void sub_7100FBA7BC(bool enabled, act::LodState* lod);
    void sub_7100FBBEC0();
    void sub_7100FBDA08(const sead::Vector3f& translation);
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
    // 0x7100fba0f4 (declared only; lane5 s5; TurnToActorBase::enter_ / PlayASForDemo::enter_): twin of sub_7100FBA174 that
    // calls updateMotionTypeRelatedFlags on the rigid body sets / bodies.
    void sub_7100FBA0F4();
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
    // 0x7100fbbaa0: find `a2` in the rigid body set named `a1` (null if absent).
    RigidBody* findX(const sead::SafeString& a1, const sead::SafeString& a2) const;
    // 0x7100fbb918 (lane4 s46): byte identical twin of findX (called by RigidBodySetParamAccessor::m1; a non-const
    // findX overload would change the overload picked by the existing callers).
    RigidBody* sub_7100FBB918(const sead::SafeString& a1, const sead::SafeString& a2) const;
    RigidBody* findRigidBody(const sead::SafeString& name) const;
    // 0x7100fbb7bc (CSV ActorPhysics::findBodyGroupByName): the rigid body set called `name`.
    RigidBodySet* findBodyGroupByName(const sead::SafeString& name);
    // 0x7100fbb50c (CSV ActorPhysics::findBodyByName, ~100 callers): byte-identical to
    // findBodyGroupByName (the original has two copies; const-ness is a guess).
    RigidBodySet* findBodyByName(const sead::SafeString& name) const;
    s32 findContactPointInfo(const sead::SafeString& name) const;
    bool sub_7100FBE184(RigidBody* body) const;
    // Inline in the original (StoneStickRoot::init_); null if `idx` is out of range.
    ContactPointInfo* getContactPointInfoAt(s32 idx) const { return mContactPointInfo[idx]; }
    s32 findCollisionInfo(const sead::SafeString& name) const;
    // Inline in the original (DamageField::calc_); null if `idx` is out of range.
    CollisionInfo* getCollisionInfoAt(s32 idx) const { return mCollisionInfo[idx]; }
    // 0x7100fbc838 (declaration only): selects ragdoll controller `idx` (clamped; resets the previous
    // one, stored in _112).
    void sub_7100FBC838(s32 idx);
    // 0x7100fbdb5c: resets the currently selected ragdoll controller (_112, clamped).
    void sub_7100FBDB5C();
    // 0x7100fbdb90 / 0x7100fbdbd8: RagdollController::setFactor / setBoneWeight of controller `idx` (false if
    // `idx` is out of range).
    bool sub_7100FBDB90(s32 idx, f32 factor);
    bool sub_7100FBDBD8(s32 idx, s32 bone, f32 weight);
    // 0x7100fbdc24 (lane4 s46): setBoneWeight(name, weight) of controller `idx` (false if out of range).
    bool sub_7100FBDC24(s32 idx, const sead::SafeString& bone_name, f32 weight);
    // 0x7100fc0234 (lane4 s46): any listed body (0xb0-byte entries at 0x108) has a 0x98 entry.
    bool sub_7100FC0234() const;
    // 0x7100fbd390 (lane4 s46): true without a cloth set or if any cloth has flag 4 (placeholder name).
    bool sub_7100FBD390() const;
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
    // 0x7100fbd324 / 0x7100fbd3ec / 0x7100fbd410 (declared only; lane4 s31, HorseObject::m69): cloth set helpers
    // (flags 0x18000 of the set, flag 0x8000 and the wind vector of the ClothSet at +0xd8).
    void sub_7100FBD324(bool a1, bool a2);
    void sub_7100FBD3EC(bool on);
    void sub_7100FBD410(const sead::Vector3f* vec);
    // 0x7100fbdfa4 (CSV ActorPhysics::x_5): sets `handler` as the system group handler of every
    // rigid body set, listed body, the ragdoll and the character controller.
    void sub_7100FBDFA4(SystemGroupHandler* handler);
    // 0x7100fbe0a0 (CSV InstanceSet::systemGroupHandlerStuff; declared only; lane2 s20; SiteBossSpearRoot::leave_
    // passes the player's handler and Entity; applies the handler to the sets / bodies of that layer type).
    void systemGroupHandlerStuff(SystemGroupHandler* handler, ContactLayerType layer_type);
    void sub_7100FBC890(const sead::Matrix34f& mtx, bool a2, bool a3);
    s32 sub_7100FBDA2C(const sead::SafeString& name) const;
    // 0x7100fbe808 (lane4 s48; placeholder name; called by the ragdoll part of init): creates the RagdollInstance and
    // loads "Physics/Ragdoll/<ragdoll_setup_file_path>" (false without a ragdoll param or file name).
    bool sub_7100FBE808(sead::Heap* heap, res::Handle* pack_handle);
    // 0x7100fbf368 (lane4 s48; placeholder name; called by the cloth part of init): creates the handle and loads
    // "Physics/Cloth/<name>" (`name`: the override's cloth file name, else the cloth set param's), then checks the
    // cloth type and sets flag Cloth1.
    bool sub_7100FBF368(sead::Heap* heap, Unk_7102519a10* arg, res::Handle* pack_handle);
    // 0x7100fbf87c (lane4 s48; placeholder name; called by the support bone part of init): releases `_e8` and the
    // handle, loads "Physics/SupportBone/<name>" (the override's name, else the support bone param's) and releases
    // everything again if there is no name or the load fails.
    bool sub_7100FBF87C(sead::Heap* heap, Unk_7102519a10* arg, res::Handle* pack_handle);
    // 0x7100fb8f10 (lane4 s48; placeholder name; called by init): deletes the ragdoll objects and the model bone
    // accessor (flag 0x40), then calls sub_7100FBE808 and deletes the ragdoll objects again if it fails.
    void sub_7100FB8F10(sead::Heap* heap, res::Handle* pack_handle);
    // 0x7100fbf158 (CSV ActorPhysics::initContactInfo; lane4 s48): creates the contact point infos / collision infos
    // of the contact info param (false without one).
    bool initContactInfo(sead::Heap* heap);
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
    // inline-only in the original; name is a guess. The size load at +0x40 repeats
    // in PhysBodyPartLod::sub_710021A344 and InstanceSet::sub_7100FBB668.
    s32 getNumRigidBodySets() const { return mRigidBodySets.size(); }
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
    // lane4 s46 (placeholder names): 0x7100fc03a0 / 0x7100fc0440 / 0x7100fc04e0: sub_7100FC0300 for a capsule / box /
    // water cylinder body; 0x7100fc0580: clones `shape` (no group handler) and links it into the same list.
    CapsuleRigidBody* sub_7100FC03A0(RigidBodyInstanceParam* param, sead::Heap* heap);
    BoxRigidBody* sub_7100FC0440(RigidBodyInstanceParam* param, sead::Heap* heap);
    CylinderWaterRigidBody* sub_7100FC04E0(RigidBodyInstanceParam* param, sead::Heap* heap);
    RigidBody* sub_7100FC0580(RigidBodyFromShape* shape, sead::Heap* heap);
    // 0x7100fbab68 (lane4 s46; placeholder name): nothing of the set is in the world or being added (and no rigid body
    // set has a body with flag 8).
    bool sub_7100FBAB68() const;
    // 0x7100fbb374 (lane4 s46; placeholder name): `body` belongs to a rigid body set or to the listed bodies.
    bool sub_7100FBB374(RigidBody* body) const;
    // 0x7100fbb420 (lane4 s46; placeholder name): any rigid body set has an active entity body, any listed
    // non-sensor body is active or the ragdoll is added to the world.
    bool sub_7100FBB420() const;
    // 0x7100fc0600: unlinks `body` from that list and deletes it.
    void sub_7100FC0600(RigidBody* body);
    // 0x7100fb83b8 (called by the destructor; lane4 s47, placeholder name): frees every collision info / contact
    // point info (and the arrays) and the ragdoll's contact point info.
    void sub_7100FB83B8();
    // 0x7100fb9db0: setUseSystemTimeFactor(use) on the character controller, the rigid body sets, the listed bodies
    // and the ragdoll.
    void sub_7100FB9DB0(bool use);
    // 0x7100fba0f4 / 0x7100fbd434 / 0x7100fbde90 / 0x7100fbdf08 / 0x7100fc00ec (lane4 s47; placeholder names): update
    // the motion type related flags of every body (and the controller); forward `type` to every set / listed body;
    // whether `body` is a linked sensor body or a link-matrix entry key; whether `key` is an entry key; the listed
    // body entry `idx` (null if out of range).
    void sub_7100FBD434(u8 type);
    bool sub_7100FBDE90(RigidBody* body) const;
    bool sub_7100FBDF08(const void* key) const;

    // 0x7100fbd918 / 0x7100fbd94c / 0x7100fbd984 (lane4 s47; placeholder names): set field 0x40 / byte 0x44 of the
    // entry of mLinkMatricesMaybe whose key (+0x38) is `key` / of every entry.
    void sub_7100FBD918(const void* key, s32 value);
    void sub_7100FBD94C(const void* key, bool value);
    void sub_7100FBD984(bool value);
    // 0x7100fbdf54: the bone key (+0x30) of the entry whose key is `key`, or the invalid key.
    gsys::BoneAccessKey sub_7100FBDF54(const void* key) const;

private:
    // inline-only in the original; name is a guess (evidence: the same sequence is inlined in 0x7100fb7f2c and twice in
    // 0x7100fb8f10): deletes the ragdoll controllers (_98), the ragdoll instance and its resource handle.
    void deleteRagdoll_() {
        for (s32 i = 0, n = _98.size(); i < n; ++i)
            delete _98[i];
        _98.freeBuffer();
        if (mRagdollInstance) {
            delete mRagdollInstance;
            mRagdollInstance = nullptr;
        }
        if (mRagdollResHandle) {
            delete mRagdollResHandle;
            mRagdollResHandle = nullptr;
        }
    }

    struct Unk1 {
        /* 0x00 */ u8 _0[0x30];
        /* 0x30 */ gsys::BoneAccessKey _30;
        /* 0x34 */ u8 _34[4];
        /* 0x38 */ const void* _38;  // the key sub_7100FBD918 / sub_7100FBD94C look entries up by
        /* 0x40 */ s32 _40;
        /* 0x44 */ bool _44;
        /* 0x45 */ u8 _45[3];
    };

    sead::SafeString mName;
    ParamSet* mParamSet;  // non-const: getRigidBodySet() is called on it (0x7100fbaf18)
    sead::TypedBitFlag<Flag> mFlags;
    u16 _24{};
    u8 _26{};  // bit 5 is tested by sub_7100FBA010
    u8 _27{};
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
    ClothResource* mClothRes{};
    ClothSet* mClothSet;

    res::Handle* mSupportBoneResHandle{};
    SupportBoneInstanceMaybe* _e8{};
    ModelBoneAccessor* _f0{};  // owned while flag _40 is set

    NavMeshCharacter* mNavMeshCharacter;
    // The listed bodies: 0xb0-byte entries (only the 0x98 entry is known).
    struct Unk2 {
        /* 0x00 */ u8 _0[0x98];
        /* 0x98 */ void* _98;
        /* 0xa0 */ u8 _a0[0xb0 - 0xa0];
    };
    sead::Buffer<Unk2> _100;

public:
    // 0x7100fc00ec (lane4 s47; placeholder name): the listed body entry `idx` (null if out of range).
    Unk2* sub_7100FC00EC(s32 idx);
    // 0x7100fc0124: the buffer of listed body entries.
    sead::Buffer<Unk2>* sub_7100FC0124();

private:
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
