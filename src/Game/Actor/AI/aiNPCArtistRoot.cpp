#include "Game/Actor/AI/aiNPCArtistRoot.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "Game/Actor/actModelMaterialUtil.h"

namespace uking::ai {

static const sead::SafeString sUnk_710240AAB8 = "Hair_Root";
static const sead::SafeString sUnk_710240ABF0 = "Mt_Hat_1";
static const sead::SafeString sUnk_710240AC00 = "Mt_Hat_2";

NPCArtistRoot::NPCArtistRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCArtistRoot::~NPCArtistRoot() {
    mActor->sub_71011DA868(&_248);
}

// NON_MATCHING: the original loads sead::Vector3f::zero once, before the sin/cos calls; ours
// reloads it after each call
bool NPCArtistRoot::init_(sead::Heap* heap) {
    if (!NPCRoot::init_(heap))
        return false;
    _308 = sead::DynamicCast<act::NPC>(mActor);
    _248.setName(sUnk_710240AAB8);
    mActor->boneHandleStuff(&_248, false);
    _248._68.makeRT(sead::Vector3f::zero, sead::Vector3f::zero);
    return true;
}

// NON_MATCHING: Timer stores and matrix construction are scheduled differently.
void NPCArtistRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
    if (!mActor->isCalc())
        return;
    const bool sleeping = _308 && _308->_1028 == "Sleep";
    const bool bad_weather = wm::callIsRainingOrSnowingOrThunderStorm(true);
    if (sleeping || !bad_weather) {
        _2f0 = false;
        _2f4 = 0.0f;
        _2f8 = ksys::Timer(50.0f, 50.0f);
        const sead::Vector3f zero = sead::Vector3f::zero;
        _248._68.makeRT(zero, zero);
    } else {
        _2f0 = true;
        _2f4 = 1.0f;
        _2f8 = ksys::Timer(60.0f, 60.0f);
        _248._68.makeRT({0.0f, 0.0f, -sead::Mathf::deg2rad(35.0f)},
                       {-0.0147f, -0.0298f, 0.0f});
    }
}

// NON_MATCHING: Timer and weight branch layout, identity matrix construction and registers.
void NPCArtistRoot::calc_() {
    NPCRoot::calc_();
    if (!isCurrentChild("Timeline"))
        return;
    const bool sleeping = _308 && _308->_1028 == "Sleep";
    const bool detected = _308 && (_308->_fe8 & 0x80000);
    const f32 step = ksys::VFR::instance()->getDeltaFrame() / 6.0f;
    const f32 scale = mActor->m139();
    const bool bad_weather = wm::callIsRainingOrSnowingOrThunderStorm(true);
    if (!_2f0) {
        if (!detected && !sleeping && bad_weather) {
            _2f0 = true;
            _2f8.reset(50.0f);
            return;
        }
        _2f8.update();
        if (sead::Mathf::epsilon() < _2f8.value)
            return;
        _2f4 -= step;
        if (!(_2f4 >= 0.0f))
            _2f4 = 0.0f;
        else if (_2f4 > 1.0f)
            _2f4 = 1.0f;
        if (_2f4 == 0.0f)
            _248._68.makeRT(sead::Vector3f::zero, sead::Vector3f::zero);
    } else {
        if (detected || sleeping || !bad_weather) {
            _2f0 = false;
            _2f8.reset(60.0f);
            return;
        }
        _2f8.update();
        if (sead::Mathf::epsilon() < _2f8.value)
            return;
        _2f4 += step;
        if (_2f4 < 0.0f)
            _2f4 = 0.0f;
        else if (!(_2f4 <= 1.0f))
            _2f4 = 1.0f;
        if (_2f4 == 1.0f)
            _248._68.makeRT({0.0f, 0.0f, -sead::Mathf::deg2rad(35.0f)},
                           {-0.0147f, -0.0298f, 0.0f});
    }
    sub_71004BE960(scale * _2f4);
}

void NPCArtistRoot::sub_71004BE960(f32 scale) {
    auto* model = mActor->getModel();
    if (!model)
        return;
    const auto first = model->searchMaterial(sUnk_710240ABF0);
    if (first.isValid()) {
        const f32 opacity = 1.0f - scale;
        Unk_710260af28::instance()->sub_7100F1DFF0(
            model->getUnits().unsafeAt(first.model_unit_index)->mModelUnit,
            first.material_index, opacity, false);
        act::setMaterialVisible(model, first, opacity > 0.0f);
    }
    const auto second = model->searchMaterial(sUnk_710240AC00);
    if (second.isValid()) {
        Unk_710260af28::instance()->sub_7100F1DFF0(
            model->getUnits().unsafeAt(second.model_unit_index)->mModelUnit,
            second.material_index, scale, false);
        act::setMaterialVisible(model, second, scale > 0.0f);
    }
}

void NPCArtistRoot::leave_() {
    if (mActor->getRootAi()->getNewChildIdx() != 0) {
        if (auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild())) {
            mActor->resetConnectedCalcChild(false);
            child->deleteEx(ksys::act::Actor::DeleteType::_1,
                            ksys::act::BaseProc::DeleteReason::_0, nullptr);
        }
    }
    NPCRoot::leave_();
}

void NPCArtistRoot::loadParams_() {
    NPCRoot::loadParams_();
    getMapUnitParam(&mActorName_m, "ActorName");
}

}  // namespace uking::ai
