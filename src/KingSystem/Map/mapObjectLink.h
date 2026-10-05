#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
class ActorLinkConstDataAccess;
}  // namespace ksys::act

namespace ksys::map {

class GenGroup;
class Object;
class Rail;

enum class MapLinkDefType {
    BasicSig = 0,
    AxisX = 1,
    AxisY = 2,
    AxisZ = 3,
    NAxisX = 4,
    NAxisY = 5,
    NAxisZ = 6,
    GimmickSuccess = 7,
    VelocityControl = 8,
    BasicSigOnOnly = 9,
    Remains = 10,
    DeadUp = 11,
    LifeZero = 12,
    Stable = 13,
    ChangeAtnSig = 14,
    Create = 15,
    Delete = 16,
    MtxCopyCreate = 17,
    Freeze = 18,
    ForbidAttention = 19,
    SyncLink = 20,
    CopyWaitRevival = 21,
    OffWaitRevival = 22,
    Recreate = 23,
    AreaCol = 24,
    SensorBlind = 25,
    ForSale = 26,
    ModelBind = 27,
    PlacementLOD = 28,
    DemoMember = 29,
    PhysSystemGroup = 30,
    StackLink = 31,
    FixedCs = 32,
    HingeCs = 33,
    LimitHingeCs = 34,
    SliderCs = 35,
    PulleyCs = 36,
    BAndSCs = 37,
    BAndSLimitAngYCs = 38,
    CogWheelCs = 39,
    RackAndPinionCs = 40,
    Reference = 41,
    Invalid = 42,
};

struct ObjectLink {
    ~ObjectLink() {}
    act::Actor* getObjectActor() const;
    bool getObjectProcWithAccessor(act::ActorLinkConstDataAccess& accessor) const;
    const char* getDescription() const;
    static const char* getDescriptionForType(MapLinkDefType t);
    static MapLinkDefType getTypeForName(const sead::SafeString& name);
    static bool sub_7100D4E310(MapLinkDefType t);
    static bool isPlacementLODOrForSaleLink(MapLinkDefType t);

    Object* other_obj = nullptr;
    MapLinkDefType type = MapLinkDefType::Invalid;
    MubinIter iter{};
};
KSYS_CHECK_SIZE_NX150(ObjectLink, 0x20);

struct ObjectLinkArray {
    bool checkLink(MapLinkDefType t, bool b);

    ObjectLink* findLinkWithType(MapLinkDefType type);
    ObjectLink* findLinkWithType_0(MapLinkDefType type);

    sead::Buffer<ObjectLink> links;
};
KSYS_CHECK_SIZE_NX150(ObjectLinkArray, 0x10);

class ObjectLinkData {
public:
    ObjectLinkData();

    void deleteArrays();
    void release(Object* obj, bool a1);
    bool allocLinksToSelf(s32 num_links, sead::Heap* heap);

    bool sub_7100D4EC40(Object* src, ObjectLink* link, Object* dest);
    void sub_7100D4FB78(Object* obj);
    bool checkCreateLinkObjRevival() const;
    bool checkDeleteLinkObjRevival() const;

    // 0x7100d4efa4: object with the given name among mObjects (declaration only).
    Object* sub_7100D4EFA4(const sead::SafeString& name);

    ObjectLink* findLinkWithType(MapLinkDefType t);
    ObjectLink* findLinkWithType_0(MapLinkDefType t);

    void setGenGroup(GenGroup* group);

    void x_1(act::Actor* actor, Object* obj);

    // lane4 s30: forwarders to mGenGroup (names from the CSV; the GenGroup callees are placeholders).
    // 0x7100d4f7c8: allocates `mRails` (num + 1 pointers, the last one null).
    bool allocRails(s32 num, sead::Heap* heap);
    // 0x7100d4f8f8 (CSV x) / 0x7100d4f968 (x_8) / 0x7100d4f97c (x_3) / 0x7100d4f9b0 (x_7) / 0x7100d4fa3c (x_0)
    void x();
    bool x_8(bool a1);
    void x_3(bool a1);
    bool x_7(bool a1);
    bool x_0();
    // 0x7100d4f908 / 0x7100d4f928: mGenGroup's atomic counter at +8.
    void incrementGenGroupNumPrepareDelete();
    void decrementGenGroupNumPrepareDelete();
    void deleteEachActorIfDeleteType2_0();
    void deleteEachActorIfDeleteType2();
    bool isGroupInitComplete() const;
    void setNumExecLinkTagTo1();
    bool hasCreateOrDeleteLinks() const;
    bool isGenGroupInitState3() const;
    // 0x7100d4faa4 / 0x7100d4fac0 (without a group: field_54).
    void counterStuff();
    u8 checkFrameCounter();
    void setFlagOnAllObjs(bool a1, u32 a2);
    bool checkContainsObjWithActorFlag(const u32* a1);
    bool checkContainsObjWithName(const sead::SafeString& name, const u32* mode);
    // 0x7100d4ef30: a Recreate link to the accessor's map object: sets Actor::_687 through the accessor.
    bool sub_7100D4EF30(const act::ActorConstDataAccess& accessor);
    // 0x7100d4f6a4: acquires the actor of the link of `type` (null accessor result without one).
    bool sub_7100D4F6A4(act::ActorLinkConstDataAccess& accessor, MapLinkDefType type);
    // 0x7100d4f9dc: whether `obj` is in the group's objects.
    bool sub_7100D4F9DC(Object* obj);
    // 0x7100d4fa90 / 0x7100d4fb88 / 0x7100d4fbf8: forwarders to GenGroup (_1f = 1 / sub_7100D51134 / sub_7100D51E6C).
    void sub_7100D4FA90();
    bool sub_7100D4FB88();
    bool sub_7100D4FBF8();

    bool checkCreateOrDeleteLinkObjRevival() const {
        return checkDeleteLinkObjRevival() || checkCreateLinkObjRevival();
    }

    Object* mCreateLinksSrcObj = nullptr;
    Object* mDeleteLinksSrcObj = nullptr;

    sead::Buffer<Object*> mObjects;
    ObjectLinkArray mLinksOther{};
    ObjectLinkArray mLinksCs{};
    ObjectLinkArray mLinksToSelf{};

    u32 field_50 = 0;
    bool field_54 = false;
    bool mAppearFade = false;
    bool mNoAutoDemoMember = false;
    bool field_57 = false;

    GenGroup* mGenGroup = nullptr;
    Rail** mRails = nullptr;  // array of rail pointers (plain delete[])
};
KSYS_CHECK_SIZE_NX150(ObjectLinkData, 0x68);

}  // namespace ksys::map
