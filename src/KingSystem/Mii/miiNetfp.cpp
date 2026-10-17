#include "KingSystem/Mii/miiNetfp.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <math/seadMatrix.h>
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/Mii/miiUMii.h"

namespace ksys::mii {

namespace {
// 0x710260dca0 (placeholder name): indexed by UMii::getAge(); TU-local (addressed directly), filled by
// sinitUmiiStrings2 0x7100f5cc00 with "", "C" and "X".
sead::SafeArray<sead::SafeString, 3> sUnk_710260DCA0{{"", "C", "X"}};
}  // namespace

// NON_MATCHING: register allocation (arg / umii swapped) and some block order.
void sub_7100F5A708(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii) {
    const auto& face = umii.getFace();
    switch (arg.type) {
    case 0:
        sub_7100F5B5B8(out, umii);
        return;
    case 1: {
        const char* name;
        const bool found = ModelCreator::instance()->sub_7100F4C9FC(&name, *face.mouth.type, arg);
        const char* part = sUnk_710260D1A0[arg.type].cstr();
        const char* mouth = sUnk_710260DC50[umii.sub_7100F4BF0C()].cstr();
        if (found)
            out->format("%s_%s_%s", part, mouth, name);
        else
            out->format("%s_%s_%03d", part, mouth, *face.mouth.type);
        return;
    }
    case 2:
        out->format("%s_%03d", sUnk_710260D1A0[arg.type].cstr(), *face.nose.type);
        return;
    case 3: {
        const auto& body = umii.getBody();
        const s32 hat = *umii.getCommon().hat;
        if ((hat >= 0 &&
             (*body.race != 0 || *body.type == 1 || *body.type == 4 || hat != 0)) ||
            *face.hair.type == 0x1e) {
            out->clear();
            return;
        }
        if (umii.getAge() != UMii::Personal::Age_Child) {
            const char* name;
            const bool found = ModelCreator::instance()->sub_7100F4C9FC(&name, *face.hair.type, arg);
            const char* part = sUnk_710260D1A0[arg.type].cstr();
            if (found)
                out->format("%s_C_%s", part, name);
            else
                out->format("%s_C_%03d", part, *face.hair.type);
            return;
        }
        const char* part = sUnk_710260D1A0[arg.type].cstr();
        const char* hair = sUnk_710260D7A0[umii.getAge()].cstr();
        s32 type = *face.hair.type;
        if (type > 6)
            type = 0;
        out->format("%s_%s_%03d", part, hair, type);
        return;
    }
    case 4:
        if (*face.glass.type == 0) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D1A0[arg.type].cstr(), *face.glass.type);
        return;
    case 5: {
        const s32 type = *face.beard.mustache;
        if (type == 0 || umii.isFemale() || umii.getAge() == UMii::Personal::Age_Child) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D1A0[arg.type].cstr(), type);
        return;
    }
    case 6: {
        const s32 type = *face.beard.type;
        if (u32(type - 1) > 2 || umii.isFemale() || umii.getAge() == UMii::Personal::Age_Child) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D1A0[arg.type].cstr(), type);
        return;
    }
    case 7:
        if (*umii.getCommon().backpack != 0) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D1A0[arg.type].cstr(), 0);
        return;
    case 8:
        sub_7100F5B774(out, umii);
        return;
    case 11:
        if (*face.hair.type == 0x1e && *umii.getCommon().hat < 0) {
            out->clear();
            return;
        }
        break;
    case 12:
        if (*face.glass.type == 0) {
            out->clear();
            return;
        }
        break;
    case 13:
        if ((*face.beard.type == 0 && *face.beard.mustache == 0) || umii.isFemale() ||
            umii.getAge() == UMii::Personal::Age_Child) {
            out->clear();
            return;
        }
        break;
    default:
        break;
    }
    out->format("%s", sUnk_710260D1A0[arg.type].cstr());
}

// NON_MATCHING: the plant checks compile to cmp 0 / b.le instead of cmp 1 / b.lt.
void sub_7100F5AB68(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii) {
    const auto& korok = umii.getKorok();
    switch (arg.type) {
    case 0:
        out->format("%s%s_%s_%03d", sUnk_710260D3A0[arg.type].cstr(),
                    sUnk_710260DB50[*umii.getBody().type].cstr(),
                    sUnk_710260D7A0[umii.getSexAge()].cstr(), *umii.getBody().number);
        return;
    case 1:
        out->format("%s_%s_%03d", sUnk_710260D3A0[arg.type].cstr(),
                    sUnk_710260D7A0[umii.getSexAge()].cstr(), *korok.mask);
        return;
    case 2:
        if (*korok.left_plant < 1) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D3A0[arg.type].cstr(), *korok.left_plant - 1);
        return;
    case 3:
        if (*korok.right_plant < 1) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D3A0[arg.type].cstr(), *korok.right_plant - 1);
        return;
    default:
        out->format("%s", sUnk_710260D3A0[arg.type].cstr());
        return;
    }
}

// NON_MATCHING: block order (the original tests 2, 1, then 0).
void sub_7100F5ADA8(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii) {
    const s32 type = arg.type;
    if (type == 2) {
        sub_7100F5BA04(out, umii);
        return;
    }
    if (type != 1) {
        if (type == 0) {
            out->format("%s%s_%s_%03d", sUnk_710260D480[type].cstr(),
                        sUnk_710260DB50[*umii.getBody().type].cstr(),
                        sUnk_710260D7A0[umii.getSexAge()].cstr(), *umii.getBody().number);
            return;
        }
        out->format("%s", sUnk_710260D480[type].cstr());
        return;
    }
    if (*umii.getCommon().backpack != 0) {
        out->clear();
        return;
    }
    out->format("%s_%03d", sUnk_710260D480[type].cstr(), 0);
}

namespace {
// inline-only in the original; name is a guess. The same code with a different table is inlined into
// 0x7100f5a550 for races 3, 5 and 6 (and is the body of 0x7100f5af44).
inline void formatSinglePartName(sead::BufferedSafeString* out, const ModelCreator::Arg& arg,
                                 const UMii& umii, const sead::SafeArray<sead::SafeString, 1>& names) {
    const s32 type = arg.type;
    const char* part = names[type].cstr();
    if (type != 0) {
        out->format("%s", part);
        return;
    }
    out->format("%s%s_%s_%03d", part, sUnk_710260DB50[*umii.getBody().type].cstr(),
                sUnk_710260D7A0[umii.getSexAge()].cstr(), *umii.getBody().number);
}
}  // namespace

void sub_7100F5AF44(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii) {
    formatSinglePartName(out, arg, umii, sUnk_710260D510);
}

void sub_7100F5A39C(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii) {
    sead::FixedSafeString<64> name{sead::SafeString::cEmptyString};
    sub_7100F5A550(&name, arg, umii);
    if (name.isEmpty())
        out->clear();
    else
        out->format("Model/%s.bfres", name.cstr());
}

void sub_7100F5A550(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii) {
    switch (*umii.getBody().race) {
    case UMii::Body::Race_Hylian:
        sub_7100F5A708(out, arg, umii);
        return;
    case UMii::Body::Race_Korok:
        sub_7100F5AB68(out, arg, umii);
        return;
    case UMii::Body::Race_Goron:
        sub_7100F5ADA8(out, arg, umii);
        return;
    case UMii::Body::Race_Sheikah:
        formatSinglePartName(out, arg, umii, sUnk_710260D510);
        return;
    case UMii::Body::Race_Gerudo:
        sub_7100F5B02C(out, arg, umii);
        return;
    case UMii::Body::Race_Zora:
        formatSinglePartName(out, arg, umii, sUnk_710260D610);
        return;
    case UMii::Body::Race_Rito:
        formatSinglePartName(out, arg, umii, sUnk_710260D630);
        return;
    default:
        out->clear();
        return;
    }
}

void sub_7100F5B02C(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii) {
    const auto& body = umii.getBody();
    const auto& gerudo = umii.getGerudo();
    switch (arg.type) {
    case 0:
        out->format("%s%s_%s_%03d", sUnk_710260D530[arg.type].cstr(),
                    sUnk_710260DB50[*body.type].cstr(), sUnk_710260D7A0[umii.getSexAge()].cstr(),
                    *body.number);
        return;
    case 1:
        if (umii.getAge() == UMii::Personal::Age_Adult && *body.type == UMii::Body::Type_C) {
            out->format("%s_C_%03d", sUnk_710260D530[arg.type].cstr(), *gerudo.hair);
            return;
        }
        if (umii.getAge() != UMii::Personal::Age_Child) {
            out->clear();
            return;
        }
        out->format("%s_G_%03d", sUnk_710260D530[arg.type].cstr(), *gerudo.hair);
        return;
    case 2:
        if (umii.getAge() == UMii::Personal::Age_Adult && *body.type == UMii::Body::Type_C &&
            *gerudo.glass != 0) {
            out->format("%s_%s_%03d", sUnk_710260D530[arg.type].cstr(),
                        sUnk_710260D7A0[umii.getSexAge()].cstr(), *gerudo.glass);
            return;
        }
        out->clear();
        return;
    case 3:
        if (*umii.getCommon().backpack != 0) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D530[arg.type].cstr(), 0);
        return;
    case 5:
        if (*gerudo.glass == 0) {
            out->clear();
            return;
        }
        out->format("%s", sUnk_710260D530[arg.type].cstr());
        return;
    default:
        out->format("%s", sUnk_710260D530[arg.type].cstr());
        return;
    }
}

// NON_MATCHING: the body type is loaded one instruction later in the original (scheduling).
void sub_7100F5B8C0(sead::BufferedSafeString* out, const UMii& umii) {
    const auto& body = umii.getBody();
    const s32 hat = *umii.getCommon().hat;
    if (hat >= 0) {
        const s32 type = *body.type;
        const bool hylian_hair = *body.race == UMii::Body::Race_Hylian &&
                                 type != UMii::Body::Type_N && type != UMii::Body::Type_SK &&
                                 hat == 0;
        if (!hylian_hair) {
            switch (type) {
            case UMii::Body::Type_C:
            case UMii::Body::Type_T:
            case UMii::Body::Type_S:
                out->format("HatC_C_Pattern");
                return;
            case UMii::Body::Type_N:
            case UMii::Body::Type_SK:
                out->format("Hat%s_%s_Pattern", sUnk_710260DB50[type].cstr(),
                            sUnk_710260D7A0[umii.getSexAge()].cstr());
                return;
            default:
                return;
            }
        }
    }
    const auto age = umii.getAge();
    if (age == UMii::Personal::Age_Child) {
        out->format("Hair_%s_Pattern", sUnk_710260D7A0[age].cstr());
        return;
    }
    out->format("Hair_C_Pattern");
}

// NON_MATCHING: the original tests the age for 2, then 1, then 0 (ours tests 0 first).
void sub_7100F5B4F0(sead::BufferedSafeString* out, const UMii& umii) {
    const sead::SafeString* name;
    switch (*umii.getBody().race) {
    case UMii::Body::Race_Hylian:
        if (*umii.getCommon().backpack != 0)
            break;
        name = &sUnk_710260D1A0[7];
        out->format("%s_%03d", name->cstr(), 0);
        return;
    case UMii::Body::Race_Goron:
        if (*umii.getCommon().backpack != 0)
            break;
        name = &sUnk_710260D480[1];
        out->format("%s_%03d", name->cstr(), 0);
        return;
    case UMii::Body::Race_Gerudo:
        if (*umii.getCommon().backpack != 0)
            break;
        name = &sUnk_710260D530[3];
        out->format("%s_%03d", name->cstr(), 0);
        return;
    default:
        break;
    }
    out->clear();
}

void sub_7100F5B5B8(sead::BufferedSafeString* out, const UMii& umii) {
    const auto& body = umii.getBody();
    if (*body.type == UMii::Body::Type_N) {
        const auto age = umii.getAge();
        if (age == UMii::Personal::Age_OldAdult) {
            out->format("%s%s_X_%03d", sUnk_710260D1A0[0].cstr(),
                        sUnk_710260DB50[*body.type].cstr(), *body.number);
            return;
        }
        if (age != UMii::Personal::Age_Adult) {
            if (age != UMii::Personal::Age_Child)
                return;
            out->format("%s%s_B_%03d", sUnk_710260D1A0[0].cstr(),
                        sUnk_710260DB50[*body.type].cstr(), *body.number);
            return;
        }
    }
    out->format("%s%s_%s_%03d", sUnk_710260D1A0[0].cstr(), sUnk_710260DB50[*body.type].cstr(),
                sUnk_710260D7A0[umii.getSexAge()].cstr(), *body.number);
}

void sub_7100F5B774(sead::BufferedSafeString* out, const UMii& umii) {
    const auto& common = umii.getCommon();
    if (*common.hat == 4 || *common.hat < 0) {
        out->clear();
        return;
    }
    const s32 type = *umii.getBody().type;
    switch (type) {
    case UMii::Body::Type_C:
    case UMii::Body::Type_T:
    case UMii::Body::Type_S:
        out->format("%sC_C_%03d", sUnk_710260D1A0[8].cstr(), *common.hat);
        return;
    case UMii::Body::Type_N:
    case UMii::Body::Type_SK:
        out->format("%s%s_%s_%03d", sUnk_710260D1A0[8].cstr(), sUnk_710260DB50[type].cstr(),
                    sUnk_710260D7A0[umii.getSexAge()].cstr(), *common.hat);
        return;
    default:
        return;
    }
}

void sub_7100F5BA04(sead::BufferedSafeString* out, const UMii& umii) {
    const auto& common = umii.getCommon();
    if (*common.hat == 0) {
        out->format("%s_%s_%03d", sUnk_710260D480[2].cstr(), sUnk_710260DCA0[umii.getAge()].cstr(),
                    *common.hat);
        return;
    }
    if (*common.hat > 0) {
        out->format("%s_C_%03d", sUnk_710260D480[2].cstr(), *common.hat);
        return;
    }
    out->clear();
}

void sub_7100F5BC74(gsys::Model* model, ksys::as::ASList* as_list, const UMii& umii,
                    const f32* opacity) {
    if (!model)
        return;
    sead::FixedSafeString<64> name;
    sub_7100F5B4F0(&name, umii);
    const s32 index = model->searchUnitIndex(name);
    if (index == -1)
        return;
    auto* unit = model->getUnits()(index)->mModelUnit;
    if (unit)
        sub_7100F5BD3C(unit, as_list, opacity);
}

// NON_MATCHING: the 4-byte ModelCreator::Arg temporary lands at sp instead of sp + 4 (stack slot
// allocation only).
void sub_7100F5BFE4(gsys::Model* model, const UMii& umii, const f32* opacity) {
    if (!model)
        return;
    sead::FixedSafeString<64> name;
    sub_7100F5A708(&name, ModelCreator::Arg{4}, umii);
    const s32 index = model->searchUnitIndex(name);
    if (index == -1)
        return;
    auto* unit = model->getUnits()(index)->mModelUnit;
    if (!unit)
        return;

    const f32 value = *opacity;
    u16 flag;
    if (value < 0.0f) {
        sub_7100F1DD24(0.0f, ::Unk_710260af28::instance(), unit, 0);
        flag = 0;
    } else if (value > 1.0f) {
        sub_7100F1DD24(1.0f, ::Unk_710260af28::instance(), unit, 0);
        flag = 0xffff;
    } else {
        sub_7100F1DD24(value, ::Unk_710260af28::instance(), unit, 0);
        flag = 0;
        if (value > 0.0f)
            flag = 0xffff;
    }
    *(u16*)((u8*)unit + 0xc) = flag;   // TODO: the u16 at ModelUnit+0xc is unmodelled
}

void sub_7100F5C8D4(gsys::Model* model) {
    if (!model)
        return;
    const auto key = model->searchMaterial("Mt_Hair");
    if (key.isValid())
        model->getUnits()(key.model_unit_index)->mModelUnit->setMaterialVisible(key.material_index, false);
}

// NON_MATCHING: the original keeps the clamped opacity in a register besides its stack copy (regalloc /
// block order of the clamps).
void sub_7100F5C128(gsys::Model* model, const UMii& umii, const f32* opacity, const f32* opacity2) {
    if (!model)
        return;

    f32 value = *opacity < 0.0f ? 0.0f : (*opacity > 1.0f ? 1.0f : *opacity);
    f32 value2 = *opacity2 < 0.0f ? 0.0f : (*opacity2 > 1.0f ? 1.0f : *opacity2);

    gsys::ModelUnit* unit;
    s32 material;
    if (*umii.getBody().race == UMii::Body::Race_Sheikah) {
        const auto key = model->searchMaterial("Mt_Kasa");
        if (!key.isValid())
            return;
        material = key.material_index;
        unit = model->getUnits()(key.model_unit_index)->mModelUnit;
    } else {
        sead::FixedSafeString<64> name;
        sub_7100F5B774(&name, umii);
        const s32 index = model->searchUnitIndex(name);
        if (index == -1)
            return;
        unit = model->getUnits()(index)->mModelUnit;
        if (!unit)
            return;
        if (name.findIndex("HatSK") == -1 || *umii.getCommon().no_hat_always) {
            const auto& body = umii.getBody();
            if (*body.race != UMii::Body::Race_Hylian || *body.type == UMii::Body::Type_N ||
                *body.type == UMii::Body::Type_SK || *umii.getCommon().hat != 0) {
                return;
            }
            const f32 alpha = unit->getMaterialParamXluAlpha(0, 0);
            sub_7100F5C394(model, unit, umii, &value, &value2, alpha != value);
            return;
        }
        material = unit->searchMaterialIndex("Mt_Kasa");
        if (material < 0)
            return;
    }
    Unk_710260af28::instance()->sub_7100F1DFF0(unit, material, value, false);
}

// NON_MATCHING: the original walks the name table by byte offset and schedules the rotation differently.
void sub_7100F5C6F4(gsys::ModelUnit* unit, const sead::Vector3f& rotation) {
    if (!unit)
        return;
    for (const auto& name : sUnk_710260DC80) {
        const s32 bone = unit->searchBoneIndex(name);
        sead::Matrix34f local;
        sead::Vector3f scale;
        unit->getBoneLocalMatrix(&local, &scale, bone);
        sead::Matrix34f rotate;
        rotate.makeR(rotation);
        local.setMul(rotate, local);
        unit->setBoneLocalRTMatrix(local, bone);
    }
}

}  // namespace ksys::mii
