#include "KingSystem/Physics/System/physCharacterControllerParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterFormSet.h"
#include <basis/seadRawPrint.h>
#include "KingSystem/Physics/RigidBody/Shape/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCharacterPrismShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCylinderShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physListShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physPolytopeShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physShapeParamObj.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

// NON_MATCHING: the original compares the type name with one virtual terminate call; our
// SafeStringBase::isEqual terminates both operands. It also passes (name, 0) to the
// NavMeshCharacter constructor, which our declaration (no arguments) does not.
// 0x710128247c: see the header.
NavMeshCharacter* CharacterControllerParam::createNavMeshCharacter(const sead::SafeString& name,
                                                                 sead::Heap* heap, f32 scale) {
    if (!use_nav_mesh_character.ref())
        return nullptr;

    NavMeshCharacter::InitArg arg;
    arg._0 = sead::Vector3f::zero;
    arg._c = sead::Vector3f::ez;
    arg._18 = 1.0f;
    arg._1c = 1.75f;
    arg._20 = 16;
    arg._24 = 3.0f;
    arg._28 = 3.0f;
    arg._2c = sUnk_7101ec27f4;
    arg._30 = sUnk_7101ec27f4;
    arg._34 = sUnk_7101ec27f4;
    arg._38 = 1.0f;
    arg._3c = 1.0f;
    arg._40 = 100.0f;
    arg._44 = 1.0f;
    arg._48 = 0.01f;
    arg._4c = 0;
    arg._50 = 4;
    arg._54 = 0;
    arg._58 = 0;
    arg._59 = 0;

    if (!(nav_mesh_character_radius.ref() > 0.0f))
        return nullptr;
    arg._18 = nav_mesh_character_radius.ref() * scale;
    if (!(nav_mesh_character_height.ref() > 0.0f))
        return nullptr;
    arg._1c = nav_mesh_character_height.ref() * scale;
    if (nav_mesh_character_avoidance_priority.ref() != 0)
        arg._20 = nav_mesh_character_avoidance_priority.ref();
    if (nav_mesh_character_max_speed.ref() > 0.0f)
        arg._28 = nav_mesh_character_max_speed.ref();
    if (nav_mesh_character_max_acceleration.ref() > 0.0f)
        arg._2c = nav_mesh_character_max_acceleration.ref();
    if (nav_mesh_character_max_angular_velocity.ref() > 0.0f)
        arg._34 = nav_mesh_character_max_angular_velocity.ref();

    for (s32 i = 0; i < 0x15; ++i) {
        if (nav_mesh_character_type.ref() == sead::SafeString(NavMeshCharacterType::text(i))) {
            arg._50 = i;
            NavMeshCharacter::sub_7100F7E598(&arg, NavMeshCharacterType(i));
            auto* nav = new (heap, 8) NavMeshCharacter();
            nav->init(arg, heap, HavokAI::instance());
            return nav;
        }
    }
    return nullptr;
}

bool navMeshCharacterTypeFromText(NavMeshCharacterType& value, const sead::SafeString& text) {
    for (auto type : NavMeshCharacterType()) {
        if (sead::SafeString(type.text()) == text) {
            value = type;
            return true;
        }
    }
    return false;
}

CharacterControllerParam::CharacterControllerParam()
    : mass(100.0, "mass", &obj), volume(1.0, "volume", &obj), max_force(20.0, "max_force", &obj),
      form_num(0, "form_num", &obj), layer({"EntityNPC"}, "layer", &obj),
      groundhit({"HitAll"}, "groundhit", &obj), initial_state({"Default"}, "initial_state", &obj),
      initial_form({"Standing"}, "initial_form", &obj), max_impulse(-1.0, "max_impulse", &obj),
      contact_point_info(sead::SafeString::cEmptyString, "contact_point_info", &obj),
      collision_info(sead::SafeString::cEmptyString, "collision_info", &obj),
      use_nav_mesh_character(false, "use_nav_mesh_character", &obj),
      nav_mesh_character_radius(0.0, "nav_mesh_character_radius", &obj),
      nav_mesh_character_height(0.0, "nav_mesh_character_height", &obj),
      nav_mesh_character_avoidance_priority(0, "nav_mesh_character_avoidance_priority", &obj),
      nav_mesh_character_max_speed(0.0, "nav_mesh_character_max_speed", &obj),
      nav_mesh_character_max_acceleration(0.0, "nav_mesh_character_max_acceleration", &obj),
      nav_mesh_character_max_angular_velocity(0.0, "nav_mesh_character_max_angular_velocity", &obj),
      nav_mesh_character_type(sead::SafeString::cEmptyString, "nav_mesh_character_type", &obj),
      enable_water_effect(false, "enable_water_effect", &obj),
      enable_force_fall_cliff_edge(false, "enable_force_fall_cliff_edge", &obj),
      water_effective_height(1.0, "water_effective_height", &obj),
      water_flow_effective_rate(0.0, "water_flow_effective_rate", &obj),
      water_attn_effective_rate(0.0, "water_attn_effective_rate", &obj),
      max_force_scale_NPC(100.0, "max_force_scale_NPC", &obj),
      water_buoyancy_scale(1.0, "water_buoyancy_scale", &obj),
      magne_mass_scaling_factor(1.0, "magne_mass_scaling_factor", &obj),
      height_enable_hitting_wall(0.1, "height_enable_hitting_wall", &obj) {}

CharacterControllerParam::~CharacterControllerParam() {
    forms.freeBuffer();
}

bool CharacterControllerParam::parse(agl::utl::ResParameterList res_list, sead::Heap* heap) {
    if (!res_list || res_list.getResParameterObjNum() < 1)
        return false;

    obj.applyResParameterObj(res_list.getResParameterObj(0));

    const int num_forms = *form_num;
    if (num_forms < 0)
        return false;

    if (num_forms == 0)
        return true;

    forms.allocBufferAssert(num_forms, heap);
    for (int i = 0; i < num_forms; ++i) {
        if (!forms[i].parse(res_list.getResParameterList(i), heap))
            return false;

        addList(&forms[i], sead::FormatFixedSafeString<32>("Form_%d", i));
    }

    return true;
}

Shape* CharacterControllerParam::createShape(int form_idx, sead::Heap* heap) {
    if (form_idx >= getNumForms() || form_idx < 0)
        return nullptr;
    return forms[form_idx].createShape(heap);
}

CharacterFormSet* CharacterControllerParam::createFormSet(sead::Heap* heap) {
    auto* form_set = new (heap) CharacterFormSet(height_enable_hitting_wall.ref());
    if (!form_set->init(this, heap)) {
        delete form_set;
        return nullptr;
    }
    return form_set;
}

CharacterControllerParam::Form::Form()
    : shape_num(0, "shape_num", &form_header_obj),
      form_type(sead::SafeString::cEmptyString, "form_type", &form_header_obj) {
    addObj(&form_header_obj, "FormHeader");
}

CharacterControllerParam::Form::~Form() {
    shape_params.freeBuffer();
}

bool CharacterControllerParam::Form::parse(agl::utl::ResParameterList res_list, sead::Heap* heap) {
    if (!res_list || res_list.getResParameterObjNum() < 2)
        return false;

    form_header_obj.applyResParameterObj(res_list.getResParameterObj(0));

    const int num_shapes = *shape_num;
    if (num_shapes < 1)
        return true;

    shape_params.allocBufferAssert(num_shapes, heap);
    for (int i = 0; i < num_shapes; ++i) {
        if (!shape_params[i].parse(res_list.getResParameterObj(i + 1), heap))
            return false;
        addObj(&shape_params[i], sead::FormatFixedSafeString<32>("ShapeParam_%d", i));
    }

    return true;
}

Shape* CharacterControllerParam::Form::createShape(sead::Heap* heap) const {
    if (*shape_num == 1) {
        switch (shape_params[0].getShapeType()) {
        case ShapeType::Sphere: {
            SphereShapeParam param;
            shape_params[0].getSphere(&param);
            return SphereShape::make(param, heap);
        }

        case ShapeType::Capsule: {
            CapsuleShapeParam param;
            shape_params[0].getCapsule(&param);
            return CapsuleShape::make(param, heap);
        }

        case ShapeType::Box: {
            BoxShapeParam param;
            shape_params[0].getBox(&param);
            return BoxShape::make(param, heap);
        }

        case ShapeType::Cylinder: {
            CylinderShapeParam param;
            shape_params[0].getCylinder(&param);
            return CylinderShape::make(param, heap);
        }

        case ShapeType::Polytope: {
            PolytopeShapeParam param;
            shape_params[0].getPolytope(&param);
            auto* shape = PolytopeShape::make(param, heap);
            for (int i = 0, n = *shape_params[0].vertex_num; i < n; ++i) {
                shape->setVertex(i, *shape_params[0].vertices[i]);
            }
            shape->updateHavokShape();
            return shape;
        }

        case ShapeType::CharacterPrism: {
            CharacterPrismShapeParam param;
            shape_params[0].getCharacterPrism(&param);
            return CharacterPrismShape::make(param, heap);
        }

        case ShapeType::List:
        case ShapeType::BoxWater:
        case ShapeType::CylinderWater:
        case ShapeType::Unknown:
            break;
        }

        SEAD_ASSERT_MSG(false, "unsupported shape type for CharacterController with one shape");
        return nullptr;
    }

    ListShapeParam list_param;
    list_param.num_shapes = static_cast<decltype(list_param.num_shapes)>(*shape_num);

    auto* list_shape = ListShape::make(list_param, heap);

    for (int i = 0; i < int(list_param.num_shapes); ++i) {
        switch (shape_params[i].getShapeType()) {
        case ShapeType::Sphere: {
            SphereShapeParam param;
            shape_params[i].getSphere(&param);
            list_shape->replaceWithNewSphere(i, param, heap);
            continue;
        }

        case ShapeType::Capsule: {
            CapsuleShapeParam param;
            shape_params[i].getCapsule(&param);
            list_shape->replaceWithNewCapsule(i, param, heap);
            continue;
        }

        case ShapeType::Box: {
            BoxShapeParam param;
            shape_params[i].getBox(&param);
            list_shape->replaceWithNewBox(i, param, heap);
            continue;
        }

        case ShapeType::Cylinder: {
            CylinderShapeParam param;
            shape_params[i].getCylinder(&param);
            list_shape->replaceWithNewCylinder(i, param, heap);
            continue;
        }

        case ShapeType::Polytope: {
            PolytopeShapeParam param;
            shape_params[i].getPolytope(&param);
            auto* shape =
                static_cast<PolytopeShape*>(list_shape->replaceWithNewPolytope(i, param, heap));
            for (int vertex = 0, n = *shape_params[i].vertex_num; vertex < n; ++vertex) {
                shape->setVertex(vertex, *shape_params[i].vertices[vertex]);
            }
            shape->updateHavokShape();
            continue;
        }

        case ShapeType::CharacterPrism: {
            CharacterPrismShapeParam param;
            shape_params[i].getCharacterPrism(&param);
            list_shape->replaceWithNewCharacterPrism(i, param, heap);
            continue;
        }

        case ShapeType::List:
        case ShapeType::BoxWater:
        case ShapeType::CylinderWater:
        case ShapeType::Unknown:
            break;
        }

        SEAD_ASSERT_MSG(false, "unsupported child shape type for CharacterController");
        util::safeDelete(list_shape);
        return nullptr;
    }

    list_shape->updateHavokShape();
    return list_shape;
}

int CharacterControllerParam::findFormIdx(const sead::SafeString& form_type) const {
    for (int i = 0, n = forms.size(); i < n; ++i) {
        if (form_type == *forms[i].form_type)
            return i;
    }
    return -1;
}

}  // namespace ksys::phys
