#include "Game/Actor/actArmorBase.h"
#include "Game/Actor/actArmorStrings.h"
#include "Game/Actor/actModelMaterialUtil.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelAnimation.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtManagerInline.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include <basis/seadNew.h>
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectArmor.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectArmorEffect.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectArmorHead.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectArmorUpper.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSeriesArmor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/XLink/xlinkXLink.h"

using ksys::act::Actor;
using ksys::act::BaseProc;

// inline-only in the original; name is a guess (the null test comes before the RTTI check, like in acc::Weapon).
static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}


namespace uking::act {

ArmorBase::ArmorBase(const CreateArg& arg) : Actor(arg) {
    _1c0 = 0;
    if (mName != "Item_Conductor") {
        mJobHandlers[0] = nullptr;
        mJobHandlers[2] = nullptr;
    }
}

ArmorBase::~ArmorBase() = default;

bool ArmorBase::sub_7100E29B8C() {
    bool attack = false;
    bool bow = false;
    bool shield = false;
    if (auto* mgr = ksys::gdt::Manager::instance()) {
        ksys::gdt::getBoolByName(mgr, &attack, "Guide_Attack");
        ksys::gdt::getBoolByName(mgr, &bow, "Guide_Bow");
        ksys::gdt::getBoolByName(mgr, &shield, "Guide_Shield");
    }
    return attack || bow || shield;
}

ksys::act::BaseProc::InitResult ArmorBase::init_() {
    if (getProfile() != "ArmorUpper" || sub_7100E29B8C() || mName != "Armor_Default_Upper") {
        _861 = 1;
        return InitResult::Ok;
    }
    auto* model = mModel;
    const auto key = model->searchMaterial("Mt_Belt_B");
    model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->setMaterialVisible(key.material_index, false);
    _861 = 0;
    return InitResult::Ok;
}

bool ArmorBase::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    _8b0.sub_7100E4DA54(heap, mModel);
    return true;
}

void ArmorBase::onPreDeleteStart_(PrepareArg& arg) {
    _8b0.sub_7100E4DB7C();
}

ksys::act::Actor* ArmorBase::m31() {
    return getOwner();
}

void ArmorBase::initMaybe() {}

void ArmorBase::calcMaybe() {
    if (getOwner())
        m148();
}

void ArmorBase::m70() {
    if (getProfile() == "ArmorExtra2") {
        m148();
        if (ksys::evt::sub_7100DC866C()) {
            auto* owner = getOwner();
            if (owner && !owner->get1a0() &&
                (!owner->getMapObject() ||
                 !owner->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
                if (auto* xlink = getXLink())
                    xlink->_cc.reset(4);
            }
        }
    }
}

void ArmorBase::updatePositionMaybe() {
    if (getProfile() == "ArmorExtra2") {
        const sead::SafeString* name = &sead::SafeString::cEmptyString;
        {
            ksys::act::ActorConstDataAccess accessor;
            if (auto* owner = getOwner()) {
                if (auto* armors = owner->getArmors()) {
                    ksys::act::acquireActor(&armors->getPartsLink(1), &accessor);
                    if (accessor.hasProc())
                        name = &accessor.getName();
                }
            }
        }
        _998 = *name;
        return;
    }

    if (getOwner())
        m148();
    else
        handleModelFadeInOutAndFadeDelete();
    sub_7100E29F3C();
    sub_7100E2A060();
    if (!_861 && sub_7100E29B8C()) {
        auto* model = mModel;
        const auto key = model->searchMaterial("Mt_Belt_B");
        model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->setMaterialVisible(key.material_index, true);
        _861 = 1;
    }
    sub_7100E2A3EC();
}

int ArmorBase::getCalcTiming() {
    return getProfile() != "ArmorExtra2";
}

bool ArmorBase::m86() {
    if (getOwner() && getOwner()->checkFlag(ActorFlag::_2b))
        return false;
    return Actor::m86();
}

ksys::act::Chemical* ArmorBase::getChemicalStuff() {
    if (auto* owner = getOwner())
        return owner->getChemicalStuff();
    return nullptr;
}

void ArmorBase::m148() {
    x_57(getOwner());
    if (getProfile() == "ArmorExtra2") {
        if (auto* xlink = getXLink())
            xlink->_cc.set(4);
    }
}

// NON_MATCHING: the original merges the exits with a boolean flag and branches around the Actor cast
ksys::act::Actor* ArmorBase::getOwner() {
    if (!_840.hasProc())
        return nullptr;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_840, &accessor);
    Actor* owner = nullptr;
    if (accessor.isStateCalc() || accessor.isPlayerProfile() || accessor.getProfile() == "PauseMenuPlayer")
        owner = static_cast<Actor*>(getProcIfActor(accessor.getProc()));
    return owner;
}

void ArmorBase::sub_7100E2A060() {
    if (getProfile() != "ArmorUpper")
        return;
    auto* model = mModel;
    if (!model)
        return;

    if (!_850 || !_850->sub_7100E2F428()) {
        auto key = model->searchMaterial("Mt_Mant");
        if (key.isValid()) {
            if (!isMaterialVisible(model, key))
                setMaterialVisible(model, key, true);
        }
        key = model->searchMaterial("Mt_Mant_B");
        if (!key.isValid())
            return;
        if (!isMaterialVisible(model, key))
            return;
        setMaterialVisible(model, key, false);
    } else {
        auto key = model->searchMaterial("Mt_Mant");
        if (key.isValid()) {
            if (_850->sub_7100E2F358() && isMaterialVisible(model, key)) {
                setMaterialVisible(model, key, false);
            } else if (!_850->sub_7100E2F358() && !isMaterialVisible(model, key)) {
                setMaterialVisible(model, key, true);
            }
        }
        key = model->searchMaterial("Mt_Mant_B");
        if (!key.isValid())
            return;
        if (!_850->sub_7100E2F358() && isMaterialVisible(model, key)) {
            setMaterialVisible(model, key, false);
        } else if (_850->sub_7100E2F358() && !isMaterialVisible(model, key)) {
            setMaterialVisible(model, key, true);
        }
    }
}

void ArmorBase::sub_7100E2A3EC() {
    if (getProfile() != "ArmorExtra0" && getProfile() != "ArmorExtra1")
        return;
    auto* owner = getOwner();
    if (!owner || owner->getActorFlags2().isOn(ActorFlag2::_20))
        return;

    ksys::act::ActorConstDataAccess accessor;
    if (auto* wearer = getOwner()) {
        if (auto* armors = wearer->getArmors()) {
            ksys::act::acquireActor(&armors->getPartsLink(1), &accessor);
            if (accessor.hasProc()) {
                auto* upper = static_cast<Actor*>(getProcIfActor(accessor.getProc()));
                const auto* gparams = upper ? upper->getParam()->getRes().mGParamList : nullptr;
                const auto* object = gparams ? gparams->getArmorUpper() : nullptr;
                if (object && object->mIsDispOffPorch.ref())
                    mActorFlags2.set(ActorFlag2::_20);
                else
                    mActorFlags2.reset(ActorFlag2::_20);
            }
        }
    }
}

void ArmorBase::sub_7100E2BACC(const s32* frame) {
    if (!_860)
        return;
    if (u32(*frame) > 15)
        return;
    _858 = *frame;
    auto* model = mModel;
    if (!model)
        return;
    auto* animation = model->getAnimation();
    if (!animation)
        return;
    auto& anms = animation->getMaterialAnms();
    if (anms.size() >= 2) {
        s32 last = anms.size() - 1;
        if (anms[last].getKey().isValid())
            animation->setMaterialAnmFrame(last, f32(_858));
        last = anms.size() - 2;
        if (anms[last].getKey().isValid())
            animation->setMaterialAnmFrame(last, f32(_858));
        model->applyAnimationTo(model, 2);
    }
}

}  // namespace uking::act

namespace {

// Placeholder name and layout (only the six {combined, a, b} entries are read: acc::Armor::getArmorEffectEffectLevel_checkEffect;
// the original initialises the object dynamically in the static initializer 0x7100e2d0f0).
struct Unk_7102602670 {
    Unk_7102602670() {}
    s32 _0 = 0;
    s32 _4 = 0x8004ef;
    struct Entry {
        s32 combined;
        s32 a;
        s32 b;
    };
    sead::SafeArray<Entry, 6> entries = {{{13, 2, 12}, {14, 3, 12}, {15, 4, 12}, {16, 6, 12}, {21, 1, 18}, {22, 20, 19}}};
};

Unk_7102602670 sUnk_7102602670;

}  // namespace

namespace ksys::act {

sead::SafeString sUnk_71026022e8 = "Armor_Default";
sead::SafeArray<sead::SafeString, 6> sUnk_71026022f8 = {{
    "Armor_Default_Head",  // +0x0
    "Armor_Default_Upper",  // +0x10
    "Armor_Default_Lower",  // +0x20
    "Armor_Default_Extra_00",  // +0x30
    "Armor_Default_Extra_01",  // +0x40
    "Item_Conductor",  // +0x50
}};
sead::SafeArray<sead::SafeString, 23> sUnk_7102602358 = {{
    "None",  // +0x0
    "ResistHot",  // +0x10
    "ResistBurn",  // +0x20
    "ResistCold",  // +0x30
    "ResistElectric",  // +0x40
    "ResistLightning",  // +0x50
    "SwimSpeed",  // +0x60
    "ClimbSpeed",  // +0x70
    "AttackUp",  // +0x80
    "Quietness",  // +0x90
    "SandMove",  // +0xa0
    "SnowMove",  // +0xb0
    "ResistAncient",  // +0xc0
    "ResistBurnAndResistAncient",  // +0xd0
    "ResistColdAndResistAncient",  // +0xe0
    "ResistElectricAndResistAncient",  // +0xf0
    "SwimSpeedAndResistAncient",  // +0x100
    "ResistFreeze",  // +0x110
    "WakeWind",  // +0x120
    "BeamPowerUp",  // +0x130
    "ClimbSpeedHorizontalOnly",  // +0x140
    "ResistHotAndWakeWind",  // +0x150
    "ClimbSpeedAndBeamPowerUp",  // +0x160
}};
sead::SafeArray<sead::SafeString, 24> sUnk_71026024c8 = {{
    "Zora",  // +0x0
    "Gerudo",  // +0x10
    "GerudoCloth",  // +0x20
    "Rito",  // +0x30
    "Goron",  // +0x40
    "Sheikah",  // +0x50
    "Stalfos",  // +0x60
    "Ancient",  // +0x70
    "Climb",  // +0x80
    "Rubber",  // +0x90
    "Power",  // +0xa0
    "Korok",  // +0xb0
    "AmiiboOcarinaOfTime",  // +0xc0
    "AmiiboWindWaker",  // +0xd0
    "AmiiboTwilightPrincess",  // +0xe0
    "AmiiboSkywardSword",  // +0xf0
    "AmiiboFirstHero",  // +0x100
    "AmiiboMajorasMask",  // +0x110
    "Black",  // +0x120
    "Tingle",  // +0x130
    "Phantom",  // +0x140
    "Collaboration",  // +0x150
    "PhantomGanon",  // +0x160
    "RoyalGuard",  // +0x170
}};
}  // namespace ksys::act

namespace uking::act {

sead::SafeString ArmorDyeColor = "ArmorDyeColor";
sead::SafeString EnableDynamicColorChange = "EnableDynamicColorChange";

}  // namespace uking::act

namespace ksys::act::acc {


int Armor::getArmorDefenceAddLevel() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    if (!actor)
        return 0;
    const auto* param = actor->getParam();
    if (param->getActorName().isEmpty()) {
        const char* name = actor->getName().getStringTop();
        return ksys::act::getArmorDefenceAddLevel(InfoData::instance(), name);
    }
    return param->getRes().mGParamList->getArmor()->mDefenceAddLevel.ref();
}

const sead::SafeString& Armor::getSeriesArmorSeriesType() const {
    if (auto* actor = static_cast<Actor*>(getProcIfActor(mProc)))
        return actor->getParam()->getRes().mGParamList->getSeriesArmor()->mSeriesType.ref();
    return sead::SafeString::cEmptyString;
}

bool Armor::getSeriesArmorEnableCompBonus() const {
    if (auto* actor = static_cast<Actor*>(getProcIfActor(mProc))) {
        const auto* param = actor->getParam();
        if (param->getActorName().isEmpty()) {
            const char* name = actor->getName().getStringTop();
            return ksys::act::getSeriesArmorEnableCompBonus(InfoData::instance(), name);
        }
        return param->getRes().mGParamList->getSeriesArmor()->mEnableCompBonus.ref();
    }
    return false;
}

bool Armor::sub_7100E2BF44() const {
    int type = 0;
    if (auto* actor = static_cast<Actor*>(getProcIfActor(mProc))) {
        const auto* param = actor->getParam();
        if (param->getActorName().isEmpty()) {
            const char* name = actor->getName().getStringTop();
            type = ksys::act::getArmorHeadMantleType(InfoData::instance(), name);
        } else
            type = param->getRes().mGParamList->getArmorHead()->mMantleType.ref();
    }
    return type > 0;
}

int Armor::getArmorHeadMantleType() const {
    if (auto* actor = static_cast<Actor*>(getProcIfActor(mProc))) {
        const auto* param = actor->getParam();
        if (param->getActorName().isEmpty()) {
            const char* name = actor->getName().getStringTop();
            return ksys::act::getArmorHeadMantleType(InfoData::instance(), name);
        }
        return param->getRes().mGParamList->getArmorHead()->mMantleType.ref();
    }
    return 0;
}

bool Armor::getArmorUpperDisableSelfMantle() const {
    if (auto* actor = static_cast<Actor*>(getProcIfActor(mProc))) {
        const auto* param = actor->getParam();
        if (param->getActorName().isEmpty()) {
            const char* name = actor->getName().getStringTop();
            return ksys::act::getArmorUpperDisableSelfMantle(InfoData::instance(), name);
        }
        return param->getRes().mGParamList->getArmorUpper()->mDisableSelfMantle.ref();
    }
    return false;
}

int Armor::getArmorUpperUseMantleType() const {
    if (auto* actor = static_cast<Actor*>(getProcIfActor(mProc))) {
        const auto* param = actor->getParam();
        if (param->getActorName().isEmpty()) {
            const char* name = actor->getName().getStringTop();
            return ksys::act::getArmorUpperUseMantleType(InfoData::instance(), name);
        }
        return param->getRes().mGParamList->getArmorUpper()->mUseMantleType.ref();
    }
    return 0;
}

const char* Armor::getArmorEffectEffectType() const {
    if (auto* actor = static_cast<Actor*>(getProcIfActor(mProc))) {
        const auto* param = actor->getParam();
        if (param->getActorName().isEmpty()) {
            const char* name = actor->getName().getStringTop();
            return ksys::act::getArmorEffectEffectType(InfoData::instance(), name);
        }
        return param->getRes().mGParamList->getArmorEffect()->mEffectType.ref().cstr();
    }
    return "";
}

// inline-only in the original (the level lookup is inlined twice into getArmorEffectEffectLevel_checkEffect); name is a guess.
inline int Armor::getArmorEffectEffectLevel() const {
    if (auto* actor = static_cast<Actor*>(getProcIfActor(mProc))) {
        const auto* param = actor->getParam();
        if (param->getActorName().isEmpty()) {
            const char* name = actor->getName().getStringTop();
            return ksys::act::getArmorEffectEffectLevel(InfoData::instance(), name);
        }
        return param->getRes().mGParamList->getArmorEffect()->mEffectLevel.ref();
    }
    return 0;
}

// NON_MATCHING: the loop counter lives in a 64-bit register (zero-extended update, sign-extended index) in the original;
// ours keeps a 32-bit counter and sign-extends it inside the loop
int Armor::getArmorEffectEffectLevel_checkEffect(const sead::SafeString& effect) const {
    const sead::SafeString effect_type = getArmorEffectEffectType();
    if (effect_type == effect)
        return getArmorEffectEffectLevel();
    s32 i = 0;
    while (!(effect_type == ksys::act::sUnk_7102602358[sUnk_7102602670.entries(i).combined])) {
        if (++i == 6)
            return 0;
    }
    if (effect == ksys::act::sUnk_7102602358[sUnk_7102602670.entries(i).a] ||
        effect == ksys::act::sUnk_7102602358[sUnk_7102602670.entries(i).b]) {
        return getArmorEffectEffectLevel();
    }
    return 0;
}

bool Armor::getArmorEffectAncientPowUp() const {
    if (auto* actor = static_cast<Actor*>(getProcIfActor(mProc))) {
        const auto* param = actor->getParam();
        if (param->getActorName().isEmpty()) {
            const char* name = actor->getName().getStringTop();
            return ksys::act::getArmorEffectAncientPowUp(InfoData::instance(), name);
        }
        return param->getRes().mGParamList->getArmorEffect()->mAncientPowUp.ref();
    }
    return false;
}

bool Armor::getArmorEffectEnableClimbWaterfall() const {
    if (auto* actor = static_cast<Actor*>(getProcIfActor(mProc))) {
        const auto* param = actor->getParam();
        if (param->getActorName().isEmpty()) {
            const char* name = actor->getName().getStringTop();
            return ksys::act::getArmorEffectEnableClimbWaterfall(InfoData::instance(), name);
        }
        return param->getRes().mGParamList->getArmorEffect()->mEnableClimbWaterfall.ref();
    }
    return false;
}

bool Armor::getArmorEffectEnableSpinAttack() const {
    if (auto* actor = static_cast<Actor*>(getProcIfActor(mProc))) {
        const auto* param = actor->getParam();
        if (param->getActorName().isEmpty()) {
            const char* name = actor->getName().getStringTop();
            return ksys::act::getArmorEffectEnableSpinAttack(InfoData::instance(), name);
        }
        return param->getRes().mGParamList->getArmorEffect()->mEnableSpinAttack.ref();
    }
    return false;
}

const sead::SafeString& Armor::getArmorHeadMaskType() const {
    if (auto* actor = static_cast<Actor*>(getProcIfActor(mProc)))
        return actor->getParam()->getRes().mGParamList->getArmorHead()->mMaskType.ref();
    return sead::SafeString::cEmptyString;
}

// NON_MATCHING: instruction order of the shared tail of the Vector3f copies
void Armor::sub_7100E2CBB8(sead::Vector3f* out) const {
    auto* armor = sead::DynamicCast<uking::act::ArmorBase>(static_cast<Actor*>(getProcIfActor(mProc)));
    if (!armor || armor->getParam()->getActorName().isEmpty()) {
        *out = sead::Vector3f::zero;
        return;
    }
    *out = armor->getParam()->getRes().mGParamList->getArmor()->mAffectRotOffsetShield.ref();
}

// NON_MATCHING: instruction order of the shared tail of the Vector3f copies
void Armor::sub_7100E2CD1C(sead::Vector3f* out) const {
    auto* armor = sead::DynamicCast<uking::act::ArmorBase>(static_cast<Actor*>(getProcIfActor(mProc)));
    if (!armor || armor->getParam()->getActorName().isEmpty()) {
        *out = sead::Vector3f::zero;
        return;
    }
    *out = armor->getParam()->getRes().mGParamList->getArmor()->mAffectTransOffsetShield.ref();
}

s32 Armor::sub_7100E2CE80() const {
    auto* armor = sead::DynamicCast<uking::act::ArmorBase>(static_cast<Actor*>(getProcIfActor(mProc)));
    if (!armor)
        return -1;
    return armor->_858;
}

}  // namespace ksys::act::acc
