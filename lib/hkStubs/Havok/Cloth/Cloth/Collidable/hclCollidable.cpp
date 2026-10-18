#include <Havok/Cloth/Cloth/Collidable/hclCollidable.h>
#include <Havok/Cloth/Cloth/Shape/hclShape.h>

hclCollidable::~hclCollidable() {
    m_shape->removeReference();
}
