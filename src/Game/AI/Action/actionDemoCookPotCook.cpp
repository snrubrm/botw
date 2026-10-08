#include "Game/AI/Action/actionDemoCookPotCook.h"
#include "Game/AI/AI/aiCookPotRoot.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/gameSceneSubsys12.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <gsys/gsysModelUnit.h>

namespace {
// Original pointer tables at 0x7102373988 and 0x71023739b0.
const char* const sMaterialBoneNames[] = {"Loc_01", "Loc_02", "Loc_03", "Loc_04", "Loc_05"};
const char* const sFairyBoneNames[] = {"Fairy_01", "Fairy_02", "Fairy_03", "Fairy_04", "Fairy_05"};
}

namespace uking::action {

DemoCookPotCook::DemoCookPotCook(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoCookPotCook::~DemoCookPotCook() = default;

// NON_MATCHING: matrix temporary layout and vector/loop register allocation differ.
void DemoCookPotCook::sub_71000E8D94() {
    auto* scene = GameSceneSubsys12::instance();
    auto* model = mActor->getModel();
    if (!scene || !model)
        return;
    sead::Matrix34f matrix = mActor->getMtx();
    sead::Matrix34f root_local = sead::Matrix34f::ident;
    sead::Vector3f scale;
    if (_48.isValid()) {
        model->getUnits()(_48.getKey().model_unit_index)->mModelUnit->getBoneWorldMatrix(
            &matrix, _48.getKey().bone_index);
        model->getUnits()(_48.getKey().model_unit_index)->mModelUnit->getBoneLocalMatrix(
            &root_local, &scale, _48.getKey().bone_index);
    }
    if (sub_710072B8E4()) {
        const sead::Vector3f position = mActor->getMtx().getTranslation();
        sead::Vector3f front = getPlayerPosition() - position;
        front.y = 0.0f;
        front.normalize();
        sead::Matrix34f facing = sead::Matrix34f::ident;
        const sead::Matrix34f actor_matrix = mActor->getMtx();
        sead::Matrix34f inverse;
        inverse.setInverse(actor_matrix);
        sead::Vector3f up = actor_matrix.getBase(1);
        up.normalize();
        ksys::util::sub_71011F00EC(&facing, front, up, position, false);
        facing.setMul(inverse, facing);
        matrix.setMul(matrix, facing);
    }
    scene->sub_7100664F00(matrix);
    sead::Matrix34f local;
    if (_80.isValid())
        model->getUnits()(_80.getKey().model_unit_index)->mModelUnit->getBoneLocalMatrix(
            &local, &scale, _80.getKey().bone_index);
    else
        local = sead::Matrix34f::ident;
    scene->sub_7100664F3C(local);
    if (_b8.isValid())
        model->getUnits()(_b8.getKey().model_unit_index)->mModelUnit->getBoneLocalMatrix(
            &local, &scale, _b8.getKey().bone_index);
    else
        local = sead::Matrix34f::ident;
    scene->sub_7100664F64(local);
    for (s64 index = 0; index < _208 + _20c; ++index) {
        const auto& key = _f0[index].getKey();
        if (key.isValid())
            model->getUnits()(key.model_unit_index)->mModelUnit->getBoneLocalMatrix(
                &local, &scale, key.bone_index);
        else
            local = root_local;
        scene->sub_7100664F8C(index, local);
    }
}

bool DemoCookPotCook::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: holder null/type-check folding and loop index addressing differ.
void DemoCookPotCook::enter_(ksys::act::ai::InlineParamPack* params) {
    _210 = false;
    if (mCurrentCookResultHolder_a) {
        auto* holder = sead::DynamicCast<uking::ai::Unk_71023e0418>(
            static_cast<Unk_71025afb58*>(*static_cast<void**>(mCurrentCookResultHolder_a)));
        if (holder && uking::ui::PauseMenuDataMgr::instance()) {
            _210 = holder->mCookItem.is_crit;
            uking::ui::PauseMenuDataMgr::instance()->cookItemGet(holder->mCookItem);
            holder->mCookItem.reset();
        }
        if (CookingMgr::instance())
            CookingMgr::instance()->resetCookItem();
    }
    _40 = 0;
    _208 = 0;
    _20c = 0;
    if (auto* scene = GameSceneSubsys12::instance()) {
        _208 = scene->sub_7100664D24();
        _20c = scene->sub_7100664D64();
        if (!*mIsSuccess_d)
            _20c = 0;
        else
            _208 -= _20c;
    }
    if (auto* as = mActor->getASList()) {
        as->x_6(17, 0, _208);
        as->x_6(25, 0, _20c);
    }
    if (auto* model = mActor->getModel()) {
        _48.search(model, "Loc_Root");
        _80.search(model, "Loc_AnimRoot");
        _b8.search(model, "Fairy_AnimRoot");
        // The original constructs this unused buffer (0xe8ca4..0xe8cec).
        sead::FixedSafeString<64> unused;
        for (s64 i = 0; i < _208 + _20c; ++i) {
            auto& key = _f0[i < 5 ? i : 0];
            if (i < _208)
                key.search(model, sMaterialBoneNames[i]);
            else
                key.search(model, sFairyBoneNames[i - _208]);
        }
    }
}

void DemoCookPotCook::leave_() {
    auto* actor = mActor;
    _48.getKey() = {};
    _80.getKey() = {};
    _b8.getKey() = {};
    for (auto& key : _f0)
        key.getKey() = {};
    if (auto* as = actor->getASList()) {
        if (!isFinishedAS(*mMaterialTargetBone_s, 0)) {
            const f32 end_frame = as->x_5(*mMaterialTargetBone_s, 0,
                                          &ksys::as::ASList::Unk2::sub_710116323C);
            as->x_3(*mMaterialTargetBone_s, 0, &ksys::as::ASList::Unk2::sub_7101163298, end_frame);
        }
        as->sub_710115B01C(*mFairyTargetBone_s, 0, false);
    }
    auto* scene = GameSceneSubsys12::instance();
    if (!scene || _40 == 3)
        return;
    if (_40 == 0) {
        scene->_d0 = 0;
        scene->sub_7100665304();
        _40 = 1;
    }
    if (!*mIsSuccess_d) {
        xlinkSearchAndEmit(actor, "Fail", 2, nullptr);
    } else if (_210) {
        xlinkSearchAndEmit(actor, "Success", 0, nullptr);
        xlinkSearchAndEmit(actor, "Success_Great", 1, nullptr);
    } else {
        xlinkSearchAndEmit(actor, "Success", 2, nullptr);
    }
    scene->sub_7100665360();
    _40 = 3;
}

void DemoCookPotCook::loadParams_() {
    getStaticParam(&mMaterialTargetBone_s, "MaterialTargetBone");
    getStaticParam(&mFairyTargetBone_s, "FairyTargetBone");
    getDynamicParam(&mIsSuccess_d, "IsSuccess");
    getAITreeVariable(&mCurrentCookResultHolder_a, "CurrentCookResultHolder");
}

// NON_MATCHING: material/fairy AS slot selection uses a conditional select instead of branches.
void DemoCookPotCook::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* scene = GameSceneSubsys12::instance();
    if (!scene)
        return;
    auto* actor = mActor;
    switch (_40) {
    case 0:
        _40 = 1;
        playAS("PreCooking", false, *mMaterialTargetBone_s, 0, -1);
        if (_20c > 0)
            playAS("PreCookingFairy", false, *mFairyTargetBone_s, 0, -1);
        scene->_d0 = 0;
        scene->sub_7100665304();
        break;
    case 1:
        sub_71000E8D94();
        if ((_208 > 0 || _20c > 0) &&
            !isFinishedAS(_208 > 0 ? *mMaterialTargetBone_s : *mFairyTargetBone_s, 0)) {
            if (auto* as = actor->getASList()) {
                const f32 frame = as->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011632F8);
                const f32 end_frame = as->x_5(0, 0, &ksys::as::ASList::Unk2::sub_710116323C);
                f32 ratio = frame / end_frame;
                if (ratio < 0)
                    ratio = 0;
                else if (ratio > 1)
                    ratio = 1;
                scene->_d0 = ratio;
            }
            return;
        }
        _40 = 2;
        scene->_d0 = 1;
        if (*mIsSuccess_d) {
            playAS("Cooking", false, *mMaterialTargetBone_s, 0, -1);
            if (_20c > 0)
                playAS("CookingFairy", false, *mFairyTargetBone_s, 0, -1);
        } else {
            playAS("FailCooking", false, *mMaterialTargetBone_s, 0, -1);
        }
        break;
    case 2:
        sub_71000E8D94();
        if ((_208 > 0 || _20c > 0) &&
            !isFinishedAS(_208 > 0 ? *mMaterialTargetBone_s : *mFairyTargetBone_s, 0))
            return;
        if (!*mIsSuccess_d) {
            xlinkSearchAndEmit(actor, "Fail", 2, nullptr);
        } else if (_210) {
            xlinkSearchAndEmit(actor, "Success", 0, nullptr);
            xlinkSearchAndEmit(actor, "Success_Great", 1, nullptr);
        } else {
            xlinkSearchAndEmit(actor, "Success", 2, nullptr);
        }
        _40 = 3;
        scene->sub_7100665360();
        setFinished();
        break;
    }
}

}  // namespace uking::action
