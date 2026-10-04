#include "KingSystem/Map/mapObjectLink.h"
#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectGenGroup.h"
#include "KingSystem/Map/mapRail.h"

namespace ksys::map {

struct MapLinkDefinition {
    const char* name;
    const char* desc;
    MapLinkDefType type;
};

static constexpr u32 sNumTypes = 42;
static constexpr sead::SafeArray<MapLinkDefinition, sNumTypes> sMapLinkDefinitions{{
    {"-AxisX", "マイナスX軸シグナル", MapLinkDefType::NAxisX},
    {"-AxisY", "マイナスY軸シグナル", MapLinkDefType::NAxisY},
    {"-AxisZ", "マイナスZ軸シグナル", MapLinkDefType::NAxisZ},
    {"AreaCol", "エリア(センサ)指定", MapLinkDefType::AreaCol},
    {"AxisX", "X軸シグナル", MapLinkDefType::AxisX},
    {"AxisY", "Y軸シグナル", MapLinkDefType::AxisY},
    {"AxisZ", "Z軸シグナル", MapLinkDefType::AxisZ},
    {"BAndSCs", "ボール＆ソケットCS", MapLinkDefType::BAndSCs},
    {"BAndSLimitAngYCs", "Y角速度制限付ボール＆ソケットCS", MapLinkDefType::BAndSLimitAngYCs},
    {"BasicSig", "基本シグナル", MapLinkDefType::BasicSig},
    {"BasicSigOnOnly", "オンのみ基本シグナル", MapLinkDefType::BasicSigOnOnly},
    {"ChangeAtnSig", "アテンション変更時シグナル", MapLinkDefType::ChangeAtnSig},
    {"CogWheelCs", "歯車CS", MapLinkDefType::CogWheelCs},
    {"CopyWaitRevival", "配置自動セーブ継承", MapLinkDefType::CopyWaitRevival},
    {"Create", "生成", MapLinkDefType::Create},
    {"DeadUp", "死んだらオン", MapLinkDefType::DeadUp},
    {"DemoMember", "デモ参加", MapLinkDefType::DemoMember},
    {"FixedCs", "固定CS", MapLinkDefType::FixedCs},
    {"ForSale", "売り物", MapLinkDefType::ForSale},
    {"ForbidAttention", "アテンションタイプ変更", MapLinkDefType::ForbidAttention},
    {"Freeze", "凍結", MapLinkDefType::Freeze},
    {"GimmickSuccess", "ネタ成功シグナル", MapLinkDefType::GimmickSuccess},
    {"HingeCs", "ヒンジCS", MapLinkDefType::HingeCs},
    {"LifeZero", "ライフ0", MapLinkDefType::LifeZero},
    {"LimitHingeCs", "制限付ヒンジCS", MapLinkDefType::LimitHingeCs},
    {"ModelBind", "モデルバインド", MapLinkDefType::ModelBind},
    {"MtxCopyCreate", "位置継承生成", MapLinkDefType::MtxCopyCreate},
    {"OffWaitRevival", "配置自動セーブオフ", MapLinkDefType::OffWaitRevival},
    {"PhysSystemGroup", "物理システムグループ", MapLinkDefType::PhysSystemGroup},
    {"PlacementLOD", "配置LOD", MapLinkDefType::PlacementLOD},
    {"PulleyCs", "滑車CS", MapLinkDefType::PulleyCs},
    {"RackAndPinionCs", "ラック＆ピニオンCS", MapLinkDefType::RackAndPinionCs},
    {"Recreate", "再生成", MapLinkDefType::Recreate},
    {"Reference", "参照", MapLinkDefType::Reference},
    {"Remains", "遺物シグナル", MapLinkDefType::Remains},
    {"SensorBind", "センサバインド", MapLinkDefType::SensorBlind},
    {"SliderCs", "スライダーCS", MapLinkDefType::SliderCs},
    {"Stable", "安定", MapLinkDefType::Stable},
    {"StackLink", "スタック", MapLinkDefType::StackLink},
    {"SyncLink", "生成グループ", MapLinkDefType::SyncLink},
    {"VelocityControl", "速度制御シグナル", MapLinkDefType::VelocityControl},
}};

const char* ObjectLink::getDescription() const {
    return getDescriptionForType(type);
}

const char* ObjectLink::getDescriptionForType(MapLinkDefType t) {
    const char* desc = "不定";  // invalid

    for (int i = 0; i < sMapLinkDefinitions.size(); ++i) {
        if (sMapLinkDefinitions[i].type == t) {
            desc = sMapLinkDefinitions[i].desc;
            break;
        }
    }

    return desc;
}

MapLinkDefType ObjectLink::getTypeForName(const sead::SafeString& name) {
    sead::Buffer<const MapLinkDefinition> buf{sMapLinkDefinitions.size(),
                                              sMapLinkDefinitions.getBufferPtr()};

    s32 idx = buf.binarySearchC(
        [&](const MapLinkDefinition& item) { return sead::SafeString(item.name).compare(name); });

    if (idx == -1)
        return MapLinkDefType::Invalid;
    return buf[idx].type;
}

bool ObjectLink::sub_7100D4E310(MapLinkDefType t) {
    switch (t) {
    case MapLinkDefType::Create:
    case MapLinkDefType::Delete:
    case MapLinkDefType::MtxCopyCreate:
    case MapLinkDefType::Freeze:
    case MapLinkDefType::ForbidAttention:
        return true;
    default:
        break;
    case MapLinkDefType::BasicSig:
    case MapLinkDefType::AxisX:
    case MapLinkDefType::AxisY:
    case MapLinkDefType::AxisZ:
    case MapLinkDefType::NAxisX:
    case MapLinkDefType::NAxisY:
    case MapLinkDefType::NAxisZ:
    case MapLinkDefType::GimmickSuccess:
    case MapLinkDefType::VelocityControl:
    case MapLinkDefType::BasicSigOnOnly:
    case MapLinkDefType::Remains:
    case MapLinkDefType::DeadUp:
    case MapLinkDefType::LifeZero:
    case MapLinkDefType::Stable:
    case MapLinkDefType::ChangeAtnSig:
        return true;
    }

    return false;
}

bool ObjectLink::isPlacementLODOrForSaleLink(MapLinkDefType t) {
    return t == MapLinkDefType::PlacementLOD || t == MapLinkDefType::ForSale;
}

act::Actor* ObjectLink::getObjectActor() const {
    if (other_obj == nullptr)
        return nullptr;

    return other_obj->tryGetActor(false);
}

bool ObjectLink::getObjectProcWithAccessor(act::ActorLinkConstDataAccess& accessor) const {
    if (other_obj == nullptr)
        return accessor.acquire(nullptr);
    else
        return other_obj->getActorWithAccessor(accessor);
}

ObjectLinkData::ObjectLinkData() = default;

void ObjectLinkData::release(Object* obj, bool a1) {
    if (a1) {
        for (const auto& link : mLinksToSelf.links) {
            Object* other = link.other_obj;
            if (!other || !other->getLinkData())
                continue;

            ObjectLinkArray* array;
            switch (link.type) {
            case MapLinkDefType::FixedCs:
            case MapLinkDefType::HingeCs:
            case MapLinkDefType::LimitHingeCs:
            case MapLinkDefType::SliderCs:
            case MapLinkDefType::PulleyCs:
            case MapLinkDefType::BAndSCs:
            case MapLinkDefType::BAndSLimitAngYCs:
            case MapLinkDefType::CogWheelCs:
            case MapLinkDefType::RackAndPinionCs:
                array = &other->getLinkData()->mLinksCs;
                break;
            default:
                array = &other->getLinkData()->mLinksOther;
                break;
            }

            for (auto& other_link : array->links) {
                if (other_link.other_obj == obj && other_link.type == link.type) {
                    other_link.other_obj = nullptr;
                    other_link.type = MapLinkDefType::Invalid;
                    other_link.iter = MubinIter();
                    break;
                }
            }
        }
    }

    obj->x(&mLinksOther);
    obj->x(&mLinksCs);

    if (mGenGroup) {
        mGenGroup->sub_7100D50778(obj);
        mGenGroup = nullptr;
    }

    deleteArrays();
    delete this;
}

void Object::x(ObjectLinkArray* links) {
    for (const auto& link : links->links) {
        if (link.type >= MapLinkDefType::Reference)
            continue;

        Object* other = link.other_obj;
        if (!other)
            continue;

        ObjectLinkData* data = other->mLinkData;
        if (!data)
            continue;

        if (data->mCreateLinksSrcObj == this)
            data->mCreateLinksSrcObj = nullptr;
        if (data->mDeleteLinksSrcObj == this)
            data->mDeleteLinksSrcObj = nullptr;

        for (auto& other_link : data->mLinksToSelf.links) {
            if (other_link.other_obj == this && other_link.type == link.type) {
                other_link.other_obj = nullptr;
                other_link.type = MapLinkDefType::Invalid;
                other_link.iter = MubinIter();
                other->decrementLinkNum();
                break;
            }
        }
    }
}

bool ObjectLinkData::sub_7100D4EC40(Object* src, ObjectLink* link, Object* dest) {
    const auto type = link->type;
    for (auto& entry : mLinksToSelf.links) {
        if (entry.other_obj == src && entry.type == type)
            return true;

        if (!entry.other_obj) {
            entry.other_obj = src;
            entry.type = type;
            entry.iter = link->iter;

            switch (type) {
            case MapLinkDefType::BasicSig:
            case MapLinkDefType::BasicSigOnOnly: {
                bool value = false;
                if (link->iter.tryGetParamBoolByKey(&value, "NoAutoDemoMember"))
                    mNoAutoDemoMember = value;
                break;
            }
            case MapLinkDefType::Create:
            case MapLinkDefType::MtxCopyCreate:
                if (src->getFlags().isOn(Object::Flag::IsLinkTag)) {
                    bool value = false;
                    if (link->iter.tryGetParamBoolByKey(&value, "AppearFade"))
                        mAppearFade = value;
                    mCreateLinksSrcObj = src;
                }
                break;
            case MapLinkDefType::Delete:
                if (src->getFlags().isOn(Object::Flag::IsLinkTag))
                    mDeleteLinksSrcObj = src;
                break;
            default:
                break;
            }
            return true;
        }
    }
    return false;
}

void ObjectLinkData::deleteArrays() {
    if (mRails) {
        delete[] mRails;
        mRails = nullptr;
    }

    mLinksOther.links.freeBuffer();
    mLinksCs.links.freeBuffer();
    mObjects.freeBuffer();
    mLinksToSelf.links.freeBuffer();
}

bool ObjectLinkData::allocLinksToSelf(s32 num_links, sead::Heap* heap) {
    if (num_links >= 1) {
        mLinksToSelf.links.tryAllocBuffer(num_links, heap);
        if (!mLinksToSelf.links.isBufferReady())
            return false;
    }
    return true;
}

ObjectLink* ObjectLinkData::findLinkWithType(MapLinkDefType t) {
    return findLinkWithType_0(t);
}

ObjectLink* ObjectLinkData::findLinkWithType_0(MapLinkDefType t) {
    switch (t) {
    case MapLinkDefType::FixedCs:
    case MapLinkDefType::HingeCs:
    case MapLinkDefType::LimitHingeCs:
    case MapLinkDefType::SliderCs:
    case MapLinkDefType::PulleyCs:
    case MapLinkDefType::BAndSCs:
    case MapLinkDefType::BAndSLimitAngYCs:
    case MapLinkDefType::CogWheelCs:
    case MapLinkDefType::RackAndPinionCs:
        return mLinksCs.findLinkWithType(t);
    default:
        return mLinksOther.findLinkWithType(t);
    }
}

bool ObjectLinkData::checkCreateLinkObjRevival() const {
    if (mCreateLinksSrcObj)
        return !mCreateLinksSrcObj->checkRevivalMaybe(false);
    return false;
}

bool ObjectLinkData::checkDeleteLinkObjRevival() const {
    if (mDeleteLinksSrcObj)
        return mDeleteLinksSrcObj->checkRevivalMaybe(true);
    return false;
}

void ObjectLinkData::sub_7100D4FB78(Object* obj) {
    if (mGenGroup)
        mGenGroup->sub_7100D5119C(obj);
}

bool ObjectLinkData::allocRails(s32 num, sead::Heap* heap) {
    mRails = new (heap, 8) Rail*[num + 1];
    if (!mRails)
        return false;
    mRails[num] = nullptr;
    return true;
}

void ObjectLinkData::x() {
    if (mGenGroup)
        mGenGroup->sub_7100D50E00();
}

bool ObjectLinkData::x_8(bool a1) {
    if (mGenGroup)
        return mGenGroup->sub_7100D50E44(a1);
    return false;
}

void ObjectLinkData::x_3(bool a1) {
    if (mGenGroup)
        mGenGroup->sub_7100D50E90(a1);
}

bool ObjectLinkData::x_7(bool a1) {
    if (mGenGroup)
        return mGenGroup->sub_7100D50EF4(a1);
    return true;
}

bool ObjectLinkData::x_0() {
    if (mGenGroup)
        return mGenGroup->sub_7100D51064();
    return true;
}

void ObjectLinkData::incrementGenGroupNumPrepareDelete() {
    if (mGenGroup)
        mGenGroup->mNumPrepareDelete.increment();
}

void ObjectLinkData::decrementGenGroupNumPrepareDelete() {
    if (mGenGroup)
        mGenGroup->mNumPrepareDelete.decrement();
}

void ObjectLinkData::deleteEachActorIfDeleteType2_0() {
    if (mGenGroup)
        mGenGroup->sub_7100D507F8();
}

void ObjectLinkData::deleteEachActorIfDeleteType2() {
    if (mGenGroup)
        mGenGroup->deleteEachActorIfDeleteType2();
}

bool ObjectLinkData::isGroupInitComplete() const {
    if (mGenGroup)
        return mGenGroup->mInitState == 2;
    return true;
}

void ObjectLinkData::setNumExecLinkTagTo1() {
    if (mGenGroup)
        mGenGroup->mNumExecLinkTag = 1;
}

bool ObjectLinkData::hasCreateOrDeleteLinks() const {
    if (mGenGroup)
        return mGenGroup->mHasCreateOrDeleteLinks != 0;
    return false;
}

bool ObjectLinkData::isGenGroupInitState3() const {
    if (mGenGroup)
        return mGenGroup->mInitState == 3;
    return false;
}

void ObjectLinkData::counterStuff() {
    if (mGenGroup)
        mGenGroup->sub_7100D510D0();
    else
        field_54 = true;
}

u8 ObjectLinkData::checkFrameCounter() {
    if (mGenGroup)
        return mGenGroup->sub_7100D510FC();
    return field_54;
}

void ObjectLinkData::setFlagOnAllObjs(bool a1, u32 a2) {
    if (mGenGroup)
        mGenGroup->sub_7100D51250(a1, a2);
}

bool ObjectLinkData::checkContainsObjWithActorFlag(const u32* a1) {
    if (mGenGroup)
        return mGenGroup->sub_7100D51330(a1);
    return false;
}

bool ObjectLinkData::checkContainsObjWithName(const sead::SafeString& name, const u32* mode) {
    if (mGenGroup)
        return mGenGroup->checkContainsObjWithName(name, mode);
    return false;
}

void ObjectLinkData::setGenGroup(GenGroup* group) {
    if (mGenGroup == nullptr)
        mGenGroup = group;
}

// NON_MATCHING
bool ObjectLinkArray::checkLink(MapLinkDefType t, bool b) {
    bool x_exists;
    ObjectLink* link = nullptr;

    if (t != MapLinkDefType::BasicSig) {
        x_exists = false;
    } else {
        link = findLinkWithType(MapLinkDefType::BasicSigOnOnly);
        x_exists = link != nullptr;

        if (link != nullptr)
            goto done;
    }

    link = findLinkWithType(t);

    if (link == nullptr)
        return false;
    if (link->type == MapLinkDefType::VelocityControl)
        return false;

done:
    act::ActorConstDataAccess acc{};

    if (link->other_obj != nullptr)
        link->other_obj->getActorWithAccessor(acc);
    else
        acc.acquire(nullptr);
    return acc.checkLinkTagActivated(b, x_exists);
}

ObjectLink* ObjectLinkArray::findLinkWithType(MapLinkDefType type) {
    return findLinkWithType_0(type);
}

ObjectLink* ObjectLinkArray::findLinkWithType_0(MapLinkDefType type) {
    for (auto it = links.begin(), end = links.end(); it != end; ++it) {
        if (it->type == type)
            return &*it;
    }
    return nullptr;
}

}  // namespace ksys::map
