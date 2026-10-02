#pragma once

#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <math/seadBoundBox.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <xlink2/xlink2Handle.h>
#include "KingSystem/ActorSystem/actActorEditorNode.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcJobHandler.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actPhysicsConstraints.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/AtomicLongBitFlag.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"

namespace gsys {
class Model;
}  // namespace gsys

namespace uking::act {
class HorseRideInfo;
class Rideable;
class RideableBase;
class Unk_7100d3cd74;
class Unk_7100e8b2b8;
}  // namespace uking::act

namespace uking::dmg {
class DamageManagerBase;
}  // namespace uking::dmg

namespace ksys {

namespace as {
class ASList;
}  // namespace as

namespace map {
enum class MapLinkDefType;
class Object;
struct ObjectLink;
}  // namespace map

namespace mii {
class HylianInfo;
class UMii;
}  // namespace mii

namespace phys {
class StaticCompoundRigidBodyGroup;
class InstanceSet;
class RigidBodySet;
class NavMeshCharacter;
class Reaction;
class RigidBody;
class CharacterController;
}  // namespace phys

namespace res {
class Handle;
}  // namespace res

namespace xlink {
class XLink;
}  // namespace xlink

namespace act {

namespace ai {
class RootAi;
}

class LifeRecoverInfo;
class Actor;
class ActorAtk;
class ActorConstDataAccess;
class ActorChemicals;
class Unk_71006e45c4;
class Unk_7100e4e084;
class Unk_71025ae640;
class Unk_71025b08f8;
class ActorCreator;
class ActorParam;
class ActorWeapons;
class ActorAttention;
class Awareness;
class AwarenessInstance;
class Unk_71024dc900;
class BaseProcLink;
class BoneControl;
class Unk_7100d860d8;
class BoneHandleBase;
class Chemical;
class DropData;
class Unk_71025ae620;
class ImpulseBaseProcLink;
class LodState;
class ModelBindInfo;
class Schedule;

// FIXME: move this to a separate file and rename
class UMiiModelLink {
public:
    explicit UMiiModelLink(Actor* actor) : mActor(actor) {}

    virtual void m0() {}
    virtual void m1() {}
    virtual void m2() {}
    virtual void m3() {}

private:
    Actor* mActor = nullptr;
};
KSYS_CHECK_SIZE_NX150(UMiiModelLink, 0x10);

struct ActorUniqueName {
    sead::BufferedSafeString* unique_name;
    sead::FixedSafeString<16> change_attention_type;
};
KSYS_CHECK_SIZE_NX150(ActorUniqueName, 0x30);

class Actor : public BaseProc, public ActorMessageTransceiver::IHandler {
public:
    enum class StasisFlag {
        _1 = 1,
        _2 = 2,
        _4 = 4,
    };

    enum class ActorFlag {
        _5 = 0x5,
        _6 = 0x6,
        _18 = 0x18,
        _1c = 0x1c,
        _20 = 0x20,
        _25 = 0x25,
        _29 = 0x29,
        _2b = 0x2b,
        _2c = 0x2c,
        _2e = 0x2e,
        _34 = 0x34,
        _39 = 0x39,
        _3a = 0x3a,
    };

    enum class ActorFlag2 : u32 {
        _1 = 0x1,
        InstEvent = 0x8,
        _10 = 0x10,
        _40 = 0x40,
        _20 = 0x20,
        NoDistanceCheck = 0x80,
        _2000 = 0x2000,
        _4000 = 0x4000,
        _20000 = 0x20000,
        _1000000 = 0x1000000,
        _2000000 = 0x2000000,
        Alive = 0x4000000,
        _10000000 = 0x10000000,
        _20000000 = 0x20000000,
        _40000000 = 0x40000000,
        _80000000 = 0x80000000,
    };

    enum class DeleteType {
        _1 = 1,
        _2 = 2,
        _3 = 3,
        _4 = 4,
        _5 = 5,
    };

    explicit Actor(const CreateArg& arg);
    ~Actor() override;

protected:
    void destruct_(int should_destruct) override;
    void onDeleteRequested_(DeleteReason reason) override;
    bool shouldClearStateFlag4000_() override;
    void preDelete1_() override;
    PreDeletePrepareResult prepareForPreDelete_() override;
    bool startPreparingForPreDelete_() override;
    void onEnterDelete_() override;
    void afterUpdateState_() override;
    // BaseProc virtuals that the original Actor vtable also overrides (CSV Actor::finalizeInit,
    // onEnterCalc, preSleep, preWakeUp, onEnterSleep, preDelete3, isSpecialJobType, canWakeUp,
    // shouldSkipJobPush_, prePushJob1, prePushJob2)
    void finalizeInit_(InitContext* context) override;
    void onEnterCalc_() override;
    void onSleepRequested_(SleepWakeReason reason) override;
    void onWakeUpRequested_(SleepWakeReason reason) override;
    void onEnterSleep_() override;
    void preDelete3_(const PreDeleteArg& arg) override;
    IsSpecialJobTypeResult isSpecialJobType_(JobType type) override;
    bool canWakeUp_() override;
    bool shouldSkipJobPush_(JobType type) override;
    void onJobPush1_(JobType type) override;
    void onJobPush2_(JobType type) override;

public:
    SEAD_RTTI_OVERRIDE(Actor, BaseProc)

public:
    // Returned by vtable slot 135 (DynamicActor::_a78, Horse::_1168, MapConst::_848,
    // Weapon::_1008). Callers set _4 (e.g. to 1 before deleting the actor).
    // 8 bytes: the members that follow it differ (DynamicActor: a BaseProcLink; Horse: a damage
    // callback; MapConst: end of the class).
    struct Unk3 {
        u8 _0 = 0;
        s32 _4 = 0;
    };

    const sead::SafeString& getProfile() const;
    const char* getUniqueName() const;

    ai::RootAi* getRootAi() const { return mRootAi; }
    const ActorParam* getParam() const { return mActorParam; }
    map::Object* getMapObject() const { return mMapObject; }
    const map::MubinIter& getMapObjIter() const { return mMapObjIter; }
    as::ASList* getASList() const { return mASList; }
    xlink::XLink* getXLink() const { return mXLink; }
    AwarenessInstance* getAwareness() const { return mAwareness; }
    Unk_71024dc900* get548() const { return _548; }
    ActorAttention* getAttention() const { return mAttention; }
    int getFadeOutDeleteType() const { return mFadeOutDeleteType; }
    ImpulseBaseProcLink* getImpulseBaseProcLink() const { return mImpulseBaseProcLink; }
    BoneControl* getBoneControl() const { return mBoneControl; }
    gsys::Model* getModel() const { return mModel; }

    const sead::Matrix34f& getMtx() const { return mMtx; }
    const sead::Vector3f& getVelocity() const { return mVelocity; }
    const sead::Vector3f& getAngVelocity() const { return mAngVelocity; }
    const sead::Vector3f& getScale() const { return mScale; }
    // mScale and mStartModelOpacity are written inline (element-wise / single stores) by AI actions
    // (EquipedWeaponChild, PlayerStoleOpen, ChemicalAttack, ForkModelVisibleOff) and other classes.
    void setScale(const sead::Vector3f& scale) { mScale = scale; }
    void setStartModelOpacity(f32 opacity) { mStartModelOpacity = opacity; }
    phys::RigidBody* getMainBody() const { return mMainBody; }
    phys::RigidBody* getTgtBody() const { return mTgtBody; }

    const MesTransceiverId* getMesTransceiverId() const { return mMsgTransceiver.getId(); }
    ActorMessageTransceiver& getMessageTransceiver() { return mMsgTransceiver; }
    bool sendMessage(const MesTransceiverId& dest, const MessageType& type, void* user_data,
                     bool ack);
    // 0x71011daf34 (CSV Actor::sendMessage3)
    bool sendMessage(IMessageBroker& broker, const MessageType& type, void* user_data, bool ack);

    f32 getDeleteDistance() const {
        return sead::Mathf::sqrt(sead::Mathf::clampMin(mDeleteDistanceSq, 0.0f));
    }

    void setDeleteDistance(f32 distance) { mDeleteDistanceSq = sead::Mathf::square(distance); }

    phys::CharacterController* getCharacterController();
    // 0x71011d7c18 (not decompiled): the character controller's main body if any, else mMainBody.
    phys::RigidBody* getPhysicsMainBody();
    phys::InstanceSet* getPhysics() const { return mPhysics; }
    phys::StaticCompoundRigidBodyGroup* getFieldBodyGroup() const { return mFieldBodyGroup; }

    void getHomeMtx(sead::Matrix34f* mtx) const;
    bool shouldUnloadBecauseOfDistance();
    void getHomePos(sead::Vector3f* pos) const;
    void setModelDrawEnabled(bool enabled);
    const sead::Vector3f& getPreviousPos() const;
    // CSV name. Adds `handle` to the bone handle list _4d8 (if the actor has a model).
    void boneHandleStuff(BoneHandleBase* handle, bool sorted);
    // Removes `handle` from the bone handle list _4d8.
    void sub_71011DA868(BoneHandleBase* handle);
    // Read inline by the Unk_7102459df8 helpers (isBgGroundHit, ...).
    BaseProcLink& getCreateArgBaseProcLink() { return mCreateArgBaseProcLink; }
    // AI code reads the LOD state's flags (_10, _14, _26) inline.
    LodState* getLodState() const { return _598; }
    // CSV name. deleteLater(_0) unless the actor is (being) deleted or _687 is set; then
    // emitSignalsOrDisappearEffectForDelete(a1).
    // CSV name (0x71011cc45c).
    void emitSignalsOrDisappearEffectForDelete(int a1);
    // CSV name.
    void clearFadeInCreate();
    // CSV Actor::x_9: sets _4f0 (and _68e when it changes).
    void sub_71011CCB1C(f32 value);
    // Sets mModelBindInfo (ignored while ActorFlag::_5 is set).
    void sub_71011DA824(ModelBindInfo* info);
    // Clears mModelBindInfo (ignored while ActorFlag::_5 is set). `info` (the object passed to
    // sub_71011DA824 by every caller) is unused.
    void sub_71011DA834(ModelBindInfo* info);
    // 0x71011da808 (declared only): forwards `accessor` to the map object's link data (0x7100d4ef30:
    // handles a Recreate link to the accessor's map object); false without a map object or link
    // data.
    bool sub_71011DA808(const ActorConstDataAccess& accessor);
    // CSV name: the physics rigid body set called `name` (null without physics).
    phys::RigidBodySet* getRigidBodyByName(const char* name);
    // CSV Actor::x_4: mChemical->getStuff(idx), if any.
    Chemical* sub_71011D8A34(int idx);
    // mChemical->sub_7100E37788(idx), if any.
    Chemical* sub_71011D8A44(int idx);
    // The spine controller of the bone control (BoneControl::_0->_10), if any.
    Unk_7100d860d8* sub_71011D8A10();
    // 0x71011d57f8: the world matrix of the model bone `bone_name` (false without a model or bone).
    bool sub_71011D57F8(sead::Matrix34f* mtx, const sead::SafeString& bone_name) const;

    void clearFlag(ActorFlag flag);
    bool checkFlag(ActorFlag flag) const;
    void setFlag(ActorFlag flag);
    void setFlag(ActorFlag flag, bool on);
    bool deleteEx(DeleteType type, DeleteReason reason, bool* ok = nullptr);
    // 0x71011c9814 (CSV Actor::deleteAndEmit): deleteLater + emitSignalsOrDisappearEffectForDelete
    bool deleteAndEmit(s32 type);

    // vel, ang_vel and scale are optional (null-checked by the original).
    void setProperties(int x, const sead::Matrix34f& mtx, const sead::Vector3f* vel,
                       const sead::Vector3f* ang_vel, const sead::Vector3f* scale,
                       bool is_life_infinite, int i, int life) const;

    // FIXME: figure out return types, parameters and names
    virtual s32 getMaxLife();
    virtual Actor* m31();
    virtual void m32();
    virtual bool m33();
    virtual void m34(sead::Vector3f* pos, f32* value);
    virtual void m35();
    virtual void m36();
    virtual f32 getGuardableAngle();
    virtual void m38();
    virtual bool m39();
    virtual void m40();
    virtual void m41();
    // Called by setMtx with the new matrix (Player::m42 forwards it).
    virtual void m42(const sead::Matrix34f& mtx);
    virtual void m43(bool on);
    virtual void m44();
    // Returns mPhysics->mNavMeshCharacter (or null).
    virtual phys::NavMeshCharacter* m45();
    virtual void m46();
    virtual bool m47();
    virtual Actor* m48();
    virtual void m49();
    virtual bool m50();
    virtual void m51();
    virtual void m52();
    virtual bool m53();
    virtual void killWithDropsAndEffects(int a1);
    virtual bool m55();
    virtual bool m56(sead::Vector3f* pos);
    virtual bool m57();
    virtual void onPreFadeOutDelete();
    virtual void onFadeOutSleep();
    virtual void m60();
    virtual void m61();
    virtual bool shouldUnload();
    virtual void m63();
    virtual void initMaybe();
    virtual void updateLodStuff();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void calcMaybe();
    virtual void m70();
    virtual void updatePositionMaybe();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76(VFR::ScopedDeltaSetter* setter);
    virtual void m77(VFR::ScopedDeltaSetter* setter);
    virtual void afterModelMatrixUpdate();
    virtual void m79();
    // Message ack handler (Actor::handleAck forwards the ack here first).
    virtual bool m80(const MessageAck& ack);
    // Message handler (overrides forward the message to sub-objects).
    virtual bool m81(const Message& message) { return false; }
    virtual int getCalcTiming();
    virtual bool m83();
    virtual void updateMtxFromPhysics();
    virtual void setMtx(const sead::Matrix34f& mtx, bool a2, bool a3);
    virtual void m86();
    virtual s32* getLife();
    virtual void m88();
    virtual void m89();
    virtual void m90();
    virtual void m91();
    virtual void m92();
    virtual void m93(int a1, float a2);
    virtual s32 m94();
    virtual void m95();
    virtual void m96(s32* a1, s32* a2);
    virtual Chemical* getChemicalStuff();
    virtual ActorWeapons* getWeapons();
    virtual void getArmors();
    virtual Unk_7100e4e084* m100();
    virtual uking::act::Unk_7100d3cd74* m101();
    virtual int getExtraHeapSize();
    virtual void m103();
    // Order matters: these overrides of MessageReceiverEx virtuals get primary vtable slots 104 (handleAck)
    // and 105 (handleMessage) in the original.
    void handleAck(const MessageAck& ack) override;
    int handleMessage(const Message& message) override;
    virtual bool m106();
    virtual void m107();
    virtual void m108();
    virtual int m109();
    virtual void m110();
    virtual void m111();
    virtual void m112();
    virtual void m113();
    virtual void m114();
    virtual void m115();
    virtual void m116();
    virtual void m117();
    virtual void m118();
    virtual void m119();
    virtual void m120();
    virtual void m121();
    virtual void m122();
    virtual bool m123();
    virtual void onPlacementObjReset();
    virtual Unk_71025ae640* getAtk();
    virtual Unk_71025b08f8* m126();
    virtual uking::dmg::DamageManagerBase* getDamageMgr();
    virtual Unk_71006e45c4* m128();
    virtual void m129();
    virtual uking::act::HorseRideInfo* getPlayerRideInfo();
    virtual uking::act::Rideable* getHorseOptionsMaybe();
    virtual uking::act::RideableBase* m132();
    virtual uking::act::Unk_7100e8b2b8* getMotorcyclePriorityStuffMaybe();
    virtual Unk_71025ae620* getDropData();
    virtual Unk3* m135();
    virtual LifeRecoverInfo* getLifeRecoverInfo();
    virtual bool m137();
    virtual bool m138();
    virtual void m139();
    virtual bool m140();
    virtual void m141();
    virtual bool m142();
    virtual void m143();
    virtual void m144();
    virtual void m145();
    virtual bool m146();
    virtual void m147();

    sead::Atomic<bool>& get689() { return _689; }
    sead::Atomic<bool>& get68c() { return _68c; }
    sead::Atomic<bool>& get68f() { return _68f; }
    float get6f0() const { return _6f0; }

    bool becomePreActor(DeleteType type, DeleteReason reason);
    void fadeOutSleep(SleepWakeReason reason);
    void emitDeadUpLifeZeroAndSetRevival();
    void setRevivalFlagForUsed(bool value);
    bool isWaitRevivalForUsed() const;

    void emitBasicSigOn();
    void emitBasicSigOff();
    bool checkBasicSig() const;

    // 0x00000071011da6c0
    void emitSignal(map::MapLinkDefType type, bool on);
    // 0x00000071011cdcac
    bool checkSignal(map::MapLinkDefType type) const;
    // 0x00000071011da678
    bool checkLinkSignal(map::MapLinkDefType type) const;
    // 0x00000071011d1808
    map::ObjectLink* findPlacementLinkWithType(map::MapLinkDefType type) const;
    // 0x00000071011da7a0
    bool hasForbidAttentionLink() const;

    bool checkLinkBasicSig() const;
    bool hasPlacementLinkForBasicSig() const;
    bool checkRemainsSignal() const;
    bool hasPlacementLinkWithTypeRemains() const;
    bool checkAxisXSignal() const;
    void emitSignalAxisY_1();
    void emitSignalAxisY_0();
    bool checkAxisYSignal() const;
    bool hasPlacementLinkWithTypeAxisY() const;
    bool checkAxisZSignal() const;
    bool checkNAxisXSignal() const;
    void emitSignalNAxisY_1();
    void emitSignalNAxisY_0();
    bool checkNAxisYSignal() const;
    bool hasPlacementLinkWithType5AxisY() const;
    bool checkNAxisZSignal() const;
    void emitGimmickSuccessSignal_1();
    void emitGimmickSuccessSignal_0();
    bool checkGimmickSuccessSignal() const;
    bool checkLinkGimmickSuccessSignal() const;
    bool checkVelocityControlSignal() const;
    bool checkFreezeSignal() const;
    bool hasPlacementLinkWithTypeFreeze() const;
    bool checkForbidAttentionSignal() const;
    phys::RigidBody* findPhysicsBodyByName(const char* group_name, const char* body_name) const;

    void nullsub_4648();
    void unlinkPlacementObj();
    void setFlag0x40();
    void setVelocity(const sead::Vector3f* vel, const sead::Vector3f* ang_vel);
    // 0x71011c88f8: sets the translation / rotation (radians) / scale (each optional).
    void sub_71011C88F8(const sead::Vector3f* pos, const sead::Vector3f* rot,
                        const sead::Vector3f* scale);
    void resetMubinBymlIter();
    s32 getMaxHp_();
    void nullsub_4649();  // Some kind of logging which has been excluded from the build?

    // 0x00000071011cf108
    bool x_18(sead::Vector3f* out) const;

    sead::TypedBitFlag<ActorFlag2>& getActorFlags2() { return mActorFlags2; }
    const sead::TypedBitFlag<ActorFlag2>& getActorFlags2() const { return mActorFlags2; }

    void onAiEnter(const char* name, const char* context);

    static constexpr size_t getCreatorListNodeOffset() {
        return offsetof(Actor, mCreatorActorListNode);
    }

protected:
    friend class ActorCreator;
    friend class ActorConstDataAccess;
    friend class ActorSystem;
    friend class ActorBind;  // sub_7100D3C5E0 reads _738 and mSpecialJobTypesMaskOverride

    struct Unk1 {
        Actor* actor;
        u32 _4;
    };

    struct Unk2 {
        s16 _0 = -1;
        s16 _2 = -1;
    };

    // FIXME: rename
    void job0_1();
    void job0_2();
    void job1_1();
    void job1_2();
    void job2_1();
    void job2_2();
    void job4();

    /* 0x190 */ sead::Atomic<phys::RigidBody*> mMainBody = nullptr;
    /* 0x198 */ sead::Atomic<phys::RigidBody*> mTgtBody = nullptr;
    /* 0x1a0 */ void* _1a0 = nullptr;
    /* 0x1a8 */ void* _1a8 = nullptr;
    /* 0x1b0 */ Unk1 mUnk1;
    /* 0x1c0 */ u32 _1c0 = 3;

    /* 0x1c8 */ BaseProcJobHandlerDualT<Actor> mJob0{this, &Actor::job0_1, &Actor::job0_2};
    /* 0x238 */ BaseProcJobHandlerDualT<Actor> mJob1{this, &Actor::job1_1, &Actor::job1_2};
    /* 0x2a8 */ BaseProcJobHandlerDualT<Actor> mJob2{this, &Actor::job2_1, &Actor::job2_2};
    /* 0x318 */ BaseProcJobHandlerT<Actor> mJob4{this, &Actor::job4};

    /* 0x368 */ sead::ListNode mActiveActorListNode;
    /* 0x378 */ sead::ListNode mActorsThatLostPlacementObjListNode;
    /* 0x388 */ sead::ListNode mVillagerListNode;

    /* 0x398 */ sead::Matrix34f mMtx = sead::Matrix34f::ident;
    /* 0x3c8 */ sead::Matrix34f* mPhysicsMtx = nullptr;
    /* 0x3d0 */ sead::Matrix34f mHomeMtx = sead::Matrix34f::ident;
    /* 0x400 */ sead::Vector3f mVelocity{0, 0, 0};
    /* 0x40c */ sead::Vector3f mAngVelocity{0, 0, 0};
    /* 0x418 */ sead::Vector3f mScale{1, 1, 1};
    /* 0x424 */ float mDispDistanceSq;
    /* 0x428 */ float mDeleteDistanceSq = -1.0;
    /* 0x42c */ float mLoadDistance = -1.0;
    /* 0x430 */ sead::Vector3f mPreviousPos{0, 0, 0};
    /* 0x43c */ sead::Vector3f mPreviousPos2{0, 0, 0};
    /* 0x448 */ sead::Vector3f _448{0, 0, 0};
    /* 0x454 */ sead::Vector3f _454{0, 0, 0};
    /* 0x460 */ sead::Vector3f _460{0, 0, 0};
    /* 0x46c */ sead::Vector3f _46c{0, 0, 0};
    /* 0x478 */ sead::Vector3f _478;
    /* 0x484 */ sead::Vector3f mPreviousPos3{0, 0, 0};
    /* 0x490 */ float _490 = 0.0;
    /* 0x494 */ float _494 = 0.0;
    /* 0x498 */ Unk2 _498;
    /* 0x49c */ Unk2 _49c;
    /* 0x4a0 */ s16 _4a0 = -1;
    /* 0x4a2 */ s16 _4a2 = -1;
    /* 0x4a4 */ s16 _4a4 = -1;
    /* 0x4a6 */ s16 _4a6 = -1;
    /* 0x4a8 */ s16 _4a8 = -1;
    /* 0x4aa */ s16 _4aa = -1;
    /* 0x4ac */ s16 _4ac = -1;
    /* 0x4ae */ s16 _4ae = -1;
    /* 0x4b0 */ s16 _4b0 = -1;
    /* 0x4b2 */ s16 _4b2 = -1;
    /* 0x4b4 */ sead::Vector3f _4b4{0, 0, 0};
    /* 0x4c0 */ sead::Vector3f mEnterCalcPos{0, 0, 0};

    /* 0x4d0 */ ModelBindInfo* mModelBindInfo = nullptr;
    /* 0x4d8 */ BoneHandleBase* _4d8 = nullptr;  // list of bone handles (actBoneHandle.h)
    /* 0x4e0 */ gsys::Model* mModel = nullptr;
    /* 0x4e8 */ float _4e8 = 1.0;
    /* 0x4ec */ float mStartModelOpacity = 0.0;
    /* 0x4f0 */ float _4f0 = 1.0;
    /* 0x4f4 */ float _4f4 = 0.0;
    /* 0x4f8 */ float _4f8 = 0.0;
    /* 0x4fc */ float _4fc = 0.0;
    /* 0x500 */ sead::BoundBox3f mAabb{sead::Vector3f::zero, sead::Vector3f::zero};

    /* 0x518 */ sead::TypedBitFlag<ActorFlag2> mActorFlags2{};
    /* 0x51c */ sead::TypedBitFlag<ActorFlag2> mActorFlags2Prev{};
    /* 0x520 */ util::AtomicLongBitFlag<64, ActorFlag> mActorFlags{};

    /* 0x528 */ PhysicsUserTag mPhysicsUserTag{this};
    /* 0x540 */ sead::Atomic<bool> _540 = false;

    // Created by 0x71011c57c0 (CSV Actor::x_27; new(0x80)).
    /* 0x548 */ Unk_71024dc900* _548 = nullptr;
    /* 0x550 */ AwarenessInstance* mAwareness = nullptr;
    /* 0x558 */ ai::RootAi* mRootAi = nullptr;
    /* 0x560 */ as::ASList* mASList = nullptr;
    /* 0x568 */ xlink::XLink* mXLink = nullptr;
    /* 0x570 */ ActorParam* mActorParam = nullptr;
    /* 0x578 */ phys::InstanceSet* mPhysics = nullptr;
    /* 0x580 */ PhysicsConstraints mConstraints;
    /* 0x598 */ LodState* _598 = nullptr;  // created by Actor::makeField598 (0x710124b050)
    /* 0x5a0 */ BoneControl* mBoneControl = nullptr;
    /* 0x5a8 */ phys::StaticCompoundRigidBodyGroup* mFieldBodyGroup = nullptr;
    /* 0x5b0 */ void* _5b0 = nullptr;
    /* 0x5b8 */ sead::Heap* mDualHeap = nullptr;   // TODO: rename
    /* 0x5c0 */ sead::Heap* mDualHeap2 = nullptr;  // TODO: rename
    /* 0x5c8 */ sead::Heap* mHeap = nullptr;       // TODO: rename
    /* 0x5d0 */ ActorUniqueName* mUniqueName = nullptr;
    /* 0x5d8 */ ActorAttention* mAttention = nullptr;
    /* 0x5e0 */ ActorMessageTransceiver mMsgTransceiver{*this, this};
    /* 0x638 */ Schedule* mSchedule = nullptr;

    /* 0x640 */ u32 mHashId = 0;
    /* 0x648 */ map::MubinIter mMapObjIter;

    /* 0x658 */ xlink2::Handle _658;
    /* 0x668 */ xlink2::Handle _668;
    /* 0x678 */ res::Handle* mModelResMaybe = nullptr;
    /* 0x680 */ u8 _680 = 0;
    /* 0x681 */ u8 _681 = 0;
    /* 0x682 */ u8 _682 = 0;
    /* 0x683 */ u8 _683 = 0;
    /* 0x684 */ u8 mSkipJobPushTimer = 0;
    /* 0x685 */ sead::BitFlag8 mSpecialJobTypesMaskOverride;
    /* 0x686 */ s8 _686 = -1;
    /* 0x687 */ sead::Atomic<bool> _687 = false;
    /* 0x688 */ sead::Atomic<bool> mLifeInfiniteMaybe = false;
    /* 0x689 */ sead::Atomic<bool> _689 = false;
    /* 0x68a */ sead::Atomic<bool> _68a = false;
    /* 0x68b */ sead::Atomic<bool> mNoFadeInCreate = false;
    /* 0x68c */ sead::Atomic<bool> _68c = false;
    /* 0x68d */ sead::Atomic<bool> _68d = false;
    /* 0x68e */ sead::Atomic<bool> _68e = false;
    /* 0x68f */ sead::Atomic<bool> _68f = false;
    /* 0x690 */ bool _690 = false;
    /* 0x691 */ bool _691 = false;
    /* 0x694 */ sead::Atomic<int> mFadeOutDeleteType = 0;
    /* 0x698 */ sead::Atomic<u32> mFadeOutSleepFlags;
    /* 0x6a0 */ void* _6a0 = nullptr;
    /* 0x6a8 */ ActorChemicals* mChemical = nullptr;
    /* 0x6b0 */ phys::Reaction* mReaction = nullptr;
    /* 0x6b8 */ void* _6b8 = nullptr;
    /* 0x6c0 */ UMiiModelLink mUMiiModelLink{this};
    /* 0x6d0 */ float _6d0 = 0.0;
    /* 0x6d8 */ void* _6d8 = nullptr;
    /* 0x6e0 */ float _6e0 = 0.0;
    /* 0x6e4 */ float _6e4 = 0.0;
    /* 0x6e8 */ float _6e8 = -1.0;
    /* 0x6ec */ int _6ec = 0;
    /* 0x6f0 */ float _6f0 = -1.0;
    /* 0x6f4 */ float _6f4 = 0.0;
    /* 0x6f8 */ float _6f8 = 0.0;
    /* 0x6fc */ int _6fc = 0;
    /* 0x700 */ int _700 = 0;
    /* 0x708 */ ImpulseBaseProcLink* mImpulseBaseProcLink = nullptr;
    /* 0x710 */ sead::TypedBitFlag<StasisFlag> mStasisFlags;  // TODO: probably need to rename this
    /* 0x714 */ float mLodLoadDistanceMultiplier = 1.0;
    /* 0x718 */ float _718 = 0.0;
    /* 0x71c */ sead::BitFlag32 mSignals;
    /* 0x720 */ sead::BitFlag32 _720;
    /* 0x728 */ void* _728 = nullptr;
    /* 0x730 */ u16 _730 = 0;
    /* 0x732 */ sead::BitFlag16 mDrawDistanceFlags;
    /* 0x738 */ BaseProcLink _738;
    /* 0x748 */ BaseProcLink mCreateArgBaseProcLink;
    /* 0x758 */ void* _758 = nullptr;
    /* 0x760 */ xlink2::Handle _760;
    /* 0x770 */ xlink2::Handle _770;
    /* 0x780 */ xlink2::Handle mSwordBlurHandle;
    /* 0x790 */ xlink2::Handle _790;
    /* 0x7a0 */ sead::Vector3f _7a0 = sead::Vector3f::zero;

    /* 0x7b0 */ ActorCreator* mCreator{};
    /* 0x7b8 */ sead::ListNode mCreatorActorListNode;
    /* 0x7c8 */ map::Object* mMapObject{};

    /* 0x7d0 */ void* _7d0 = nullptr;
    /* 0x7d8 */ bool _7d8 = false;

    /* 0x7e0 */ ActorEditorNode mActorEditorNode;
    /* 0x810 */ sead::Buffer<void*> mUMiiBones;  // FIXME: type
    /* 0x820 */ mii::UMii* mUMii = nullptr;
    /* 0x828 */ mii::HylianInfo* mUMiiHylianInfo = nullptr;

    /* 0x830 */ float _830 = 1.0;
    /* 0x834 */ int _834 = 0;
    /* 0x838 */ int _838 = 0;

private:
    enum class HandleMessageResult {
        _0,
        _1,
        _2,
    };

    HandleMessageResult doHandleMessage_(const Message& message);
};
KSYS_CHECK_SIZE_NX150(Actor, 0x840);

BaseProcLink& getDummyBaseProcLink();

}  // namespace act

}  // namespace ksys
