#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actAiClassDef.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/ActorSystem/aiDemoRootAI.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"

namespace ksys::act::ai {

bool RootAi::isChildIdx0() const {
    return mChildIdx == 0;
}

void RootAi::onActorPreDelete1() {
    if (_14e)
        return;
    mActions.onPreDelete();
    mAis.onPreDelete();
    mBehaviors.onPreDelete();
    mQueries.onPreDelete();
    _14e = 1;
}

bool RootAi::stubbedRet0() const {
    return false;
}

DemoRootAI* RootAi::sub_7100D65CBC() {
    return sead::DynamicCast<DemoRootAI>(getChild(0));
}

void RootAi::enter_(InlineParamPack* params) {
    _16c.makeAllZero();
    _16e.makeAllZero();
    if (mI == 1) {
        if (isNPCProfile(mActor)) {
            changeChild(1u, nullptr);
            _16c.set(0x40);
        } else {
            changeChild(0u, nullptr);
        }
    } else {
        changeChild(1u, nullptr);
    }
    if (mActor->getChemicalContainer())
        sub_7100D65E1C();
    mI = 5;
}

// NON_MATCHING: tag-dependent flag selection uses a different equivalent instruction sequence.
void RootAi::sub_7100D65E1C() {
    auto* chemicals = mActor->getChemicalContainer();
    chemicals->sub_7100E37CE4();
    _40 = mActor->getScale().x;
    const auto* info = InfoData::instance();
    const char* name = mActor->getName().cstr();
    const bool has_tag_a = info->hasTag(name, 0x2813d81b);
    const bool has_tag_b = info->hasTag(name, 0x8f5d0d55);
    const s32 count = chemicals->_58.size() + chemicals->_80;
    for (s32 i = 0; i < count; ++i) {
        auto* element = chemicals->sub_7100E3718C(i);
        auto* chemical = chemicals->sub_7100E37788(i);
        const auto* root = element->_18;
        const u32 index = element->_288;
        if ((chemical->mMaterial->attribute.ref() & 0x2000000) && !(element->_30 & 0x10000)) {
            if ((mActor->getChemicalContainer()->sub_7100E3718C(i)->_3c & 1) &&
                (root->isRigidAttribute6Or14Set(index) ||
                 (mActor->getChemicalContainer()->sub_7100E3718C(i)->_3c & 0x100000))) {
                chemical->sub_7100D90858(root->isRigidAttribute14Set(index), 2, false, true, false);
            }
            element->_30 |= 0x8000;
        }
        if ((mActor->getChemicalContainer()->sub_7100E3718C(i)->_3c & 8) &&
            root->isRigidAttribute11Set(index)) {
            chemical->sub_7100D90A40();
        }
        if (root->isRigidAttribute12Set(index))
            chemical->sub_7100D91978(10000.0f);
        chemical->_d5 = 1;
        chemical->_bf &= ~0xc;
        if (has_tag_a)
            chemical->_bf |= 4;
        if (has_tag_b)
            chemical->_bf |= 8;
    }
}

void RootAi::setChemicalFlags3cMaybe(u32 mask, bool on) {
    auto* chemicals = mActor->getChemicalContainer();
    for (int i = 0; i < chemicals->_58.size() + chemicals->_80; ++i) {
        auto* element = chemicals->sub_7100E3718C(i);
        if (on)
            element->_3c |= mask;
        else
            element->_3c &= ~mask;
    }
}

void RootAi::sub_7100D66B48(const sead::Vector3f& a, const sead::Vector3f& b, f32 value) {
    _16c.setBit(9);
    _150 = a;
    _15c = b;
    _168 = value;
}

RootAi::RootAi(const InitArg& arg) : Ai(arg) {
    mBehaviorsByStopAndCalcTiming[0].fill({});
    mBehaviorsByStopAndCalcTiming[1].fill({});
}

RootAi::~RootAi() {
    mQueries.finalize();
    mBehaviors.finalize();
    mAis.finalize();
    mActions.finalize();
    if (_140)
        delete _140;
}

bool RootAi::init_(sead::Heap* heap) {
    return false;
}

void RootAi::leave_() {
    for (auto* behavior = _138; behavior; behavior = behavior->sub_7100D24B94()) {
    }
    auto* behavior = _138;
    while (behavior) {
        auto* next = behavior->sub_7100D24BD4();
        behavior->_20 = nullptr;
        behavior = next;
    }
    _138 = nullptr;
    if (mI == 5)
        mI = 0;
}

bool RootAi::loadMapUnitParams(const AIDef& def, sead::Heap* heap) {
    return mMapUnitParams.load(*mActor, def, heap, AIDefInstParamKind::MapUnit);
}

bool RootAi::loadAITreeParams(const AIDef& def, sead::Heap* heap) {
    return mAiTreeParams.load(*mActor, def, heap, AIDefInstParamKind::AITree);
}

}  // namespace ksys::act::ai

namespace ksys::act {

s32 getExtraHeapSizeForParams(InstParamPack::Buffer* buffer) {
    if (!buffer)
        return 0;

    s32 size = 0;
    s32 position = 0;
    for (s32 i = 0; i < buffer->getNumParams(); ++i) {
        InstParamPack::Entry entry;
        if (!buffer->pop(&position, &entry))
            break;
        if (entry.key[0] == '@')
            continue;
        if (ActorCreator::isAITreeParam(entry))
            continue;
        switch (entry.type) {
        case InstParamPack::EntryType::Int:
            size += 0x2c;
            break;
        case InstParamPack::EntryType::UInt:
            size += 0x2c;
            break;
        case InstParamPack::EntryType::Float:
            size += 0x2c;
            break;
        case InstParamPack::EntryType::Bool:
            size += 0x2c;
            break;
        case InstParamPack::EntryType::Vec3:
            size += 0x34;
            break;
        case InstParamPack::EntryType::String:
            size += 0x90;
            break;
        }
    }
    return size;
}

}  // namespace ksys::act

namespace ksys::act::ai {

void RootAi::setBehavior(Behavior* behavior) {
    behavior->sub_7100D24A10(
        &mBehaviorsByStopAndCalcTiming[behavior->isNoStop()][behavior->getCalcTiming()], &_138);
}

void RootAi::resetBehavior(Behavior* behavior) {
    behavior->sub_7100D24AC0(
        &mBehaviorsByStopAndCalcTiming[behavior->isNoStop()][behavior->getCalcTiming()], &_138);
}

bool RootAi::isActorDeletedOrDeleting() const {
    return mActor->isDeletedOrDeleting();
}

bool RootAi::getMapUnitParam(sead::SafeString* value, const sead::SafeString& key) const {
    sead::SafeString out;
    if (mMapUnitParams.getString(&out, key)) {
        *value = out.cstr();
        return true;
    }
    *value = sead::SafeString::cEmptyString;
    return false;
}

bool RootAi::getMapUnitParam(const s32** value, const sead::SafeString& key) const {
    auto* ptr =
        static_cast<int*>(mMapUnitParams.getAITreeVariablePointer(key, AIDefParamType::Int));
    static const s32 sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getMapUnitParam(const f32** value, const sead::SafeString& key) const {
    auto* ptr =
        static_cast<f32*>(mMapUnitParams.getAITreeVariablePointer(key, AIDefParamType::Float));
    static const f32 sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getMapUnitParam(const sead::Vector3f** value, const sead::SafeString& key) const {
    auto* ptr = static_cast<sead::Vector3f*>(
        mMapUnitParams.getAITreeVariablePointer(key, AIDefParamType::Vec3));
    *value = ptr ? ptr : &sead::Vector3f::zero;
    return ptr != nullptr;
}

bool RootAi::getMapUnitParam(const bool** value, const sead::SafeString& key) const {
    auto* ptr =
        static_cast<bool*>(mMapUnitParams.getAITreeVariablePointer(key, AIDefParamType::Bool));
    static const bool sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

namespace {
sead::FixedSafeString<64> sDefaultString;

struct Vec3Wrapper {
    util::InitTimeInfoEx init_time_info_ex;
    sead::Vector3f sDefaultVec3{0, 0, 0};
};
Vec3Wrapper sDefaultAITreeVariables;
}  // namespace

bool RootAi::getAITreeVariable(sead::SafeString** value, const sead::SafeString& key) const {
    auto* ptr = static_cast<sead::SafeString*>(
        mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::String));
    *value = ptr ? ptr : &sDefaultString;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable(s32** value, const sead::SafeString& key) const {
    auto* ptr = static_cast<s32*>(mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::Int));
    static s32 sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable(f32** value, const sead::SafeString& key) const {
    auto* ptr =
        static_cast<f32*>(mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::Float));
    static f32 sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable(sead::Vector3f** value, const sead::SafeString& key) const {
    auto* ptr = static_cast<sead::Vector3f*>(
        mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::Vec3));
    *value = ptr ? ptr : &sDefaultAITreeVariables.sDefaultVec3;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable(bool** value, const sead::SafeString& key) const {
    auto* ptr =
        static_cast<bool*>(mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::Bool));
    static bool sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable(void** value, const sead::SafeString& key) const {
    auto* ptr = static_cast<void**>(
        mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::AITreeVariablePointer));
    static void* sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable(u32** value, const sead::SafeString& key) const {
    auto* ptr =
        static_cast<u32*>(mAiTreeParams.getAITreeVariablePointer(key, AIDefParamType::UInt));
    static u32 sDefault{};
    *value = ptr ? ptr : &sDefault;
    return ptr != nullptr;
}

bool RootAi::getAITreeVariable2(sead::Vector3f** value, const sead::SafeString& key) const {
    return getAITreeVariable(value, key);
}

bool RootAi::getAITreeVariable2(bool** value, const sead::SafeString& key) const {
    return getAITreeVariable(value, key);
}

void RootAi::behaviorStuff() {
    for (auto& list : mBehaviorsByStopAndCalcTiming) {
        for (auto* head : list) {
            for (auto* behavior = head; behavior; behavior = behavior->_18)
                behavior->x();
        }
    }
}

const char* getDefaultAiName(s32 root_idx) {
    static constexpr const char* names[] = {"DemoRootAI", "Root"};
    if (root_idx >= 2)
        return "";
    return names[root_idx];
}

const char* getDefaultActionName(s32) {
    return "";
}

}  // namespace ksys::act::ai
