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
class RagdollInstance;
class RigidBodySet;
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
        _200000 = 1 << 21,
        Cloth1 = 1 << 22,
        Cloth2 = 1 << 23,
        Cloth3 = 1 << 24,
        InDemo = 1 << 25,
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
    void sub_7100FBAC4C(ContactLayer layer);
    void sub_7100FBACE0(ContactLayer layer);
    void sub_7100FBAD74();
    void sub_7100FBADDC();
    void* sub_7100FBAEDC(s32 rigidbody_idx, s32 ragdoll_idx) const;
    // 0x7100fbaf18: called with one body of the actor (actActorSensorUtil sub_71007A3768/3778).
    void sub_7100FBAF18(RigidBody* body);
    void sub_7100FBB00C(RigidBody* body, RigidBodyParam* param);
    // 0x7100fbb18c: called with the actor's "Tgt" body set (actActorSensorUtil sub_71007A3800).
    void sub_7100FBB18C(RigidBodySet* set);
    void setMtxAndScale(const sead::Matrix34f& mtx, bool a2, bool a3, f32 scale);
    void sub_7100FBB4B4();
    void* findX(const sead::SafeString& a1, const sead::SafeString& a2) const;
    RigidBody* findRigidBody(const sead::SafeString& name) const;
    // 0x7100fbb7bc (CSV ActorPhysics::findBodyGroupByName): the rigid body set called `name`.
    RigidBodySet* findBodyGroupByName(const sead::SafeString& name);
    // 0x7100fbb50c (CSV ActorPhysics::findBodyByName, ~100 callers): byte-identical to
    // findBodyGroupByName (the original has two copies; const-ness is a guess).
    RigidBodySet* findBodyByName(const sead::SafeString& name) const;
    s32 findContactPointInfo(const sead::SafeString& name) const;
    s32 findCollisionInfo(const sead::SafeString& name) const;
    void sub_7100FBD284(const sead::Matrix34f& mtx);
    // 0x7100fbdfa4 (CSV ActorPhysics::x_5): sets `handler` as the system group handler of every
    // rigid body set, listed body, the ragdoll and the character controller.
    void sub_7100FBDFA4(SystemGroupHandler* handler);
    void sub_7100FBC890(const sead::Matrix34f& mtx, bool a2, bool a3);
    s32 sub_7100FBDA2C(const sead::SafeString& name) const;
    // Read inline by ActorConstDataAccess::sub_7100D10448 (index clamped like a sead::SafeArray)
    // and MagneShaftRoot::m51.
    SystemGroupHandler* get178(s32 idx) const { return _178[idx]; }
    // Read inline by LastBossRailWarpAction::leave_ and sub_710072E804 (index clamped).
    SystemGroupHandler* get188(s32 idx) const { return _188[idx]; }
    // 0x7100fbb668: index of the rigid body set called `name` (-1 if none).
    int sub_7100FBB668(const sead::SafeString& name) const;
    // Read inline by sub_71007A2EB0 (actActorSensorUtil; null if out of range).
    RigidBodySet* getRigidBodySet(int idx) const { return mRigidBodySets[idx]; }

private:
    struct Unk1 {
        u8 _0[0x48];
    };

    sead::SafeString mName;
    const ParamSet* mParamSet;
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
    sead::Buffer<void*> _98;
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
