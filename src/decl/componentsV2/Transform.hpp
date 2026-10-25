// Transform.hpp, 24/10/2026
#include <glm/mat4x4.hpp>

#include "datatype/Ecs.hpp"

struct TransformComponent
{
    glm::mat4 Local = { 1.f };
    glm::mat4 World = { 1.f };
};

struct TransformComponentRecord : public ComponentRecord<TransformComponent>
{
    TransformComponentRecord();

    Reflection::GenericValue getData(uint64_t index) override;
    void setData(uint64_t index, const Reflection::GenericValue& value) override;
    const Reflection::FieldMap& getFields() override;

    Reflection::FieldMap fields;
};
