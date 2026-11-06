// Mesh.hpp, 06/11/2026
#pragma once

#include "datatype/Ecs.hpp"
#include "datatype/Color.hpp"
#include "asset/FaceCullingMode.hpp"

struct MeshComponent
{
    std::string asset = "phoenix://meshes/Cube";
    std::string material = "phoenix://materials/Checkered.mtl";
    uint32_t assetId = 0;
    uint32_t materialId = UINT32_MAX;
    Color tint = { 1.f, 1.f, 1.f };

    float opacity = 0.f;

    FaceCullingMode culling = FaceCullingMode::BackFace;
    bool castsShadows = true;
};

struct MeshComponentRecord : public ComponentRecord<MeshComponent>
{
    MeshComponentRecord();

    Reflection::GenericValue getData(uint64_t index) override;
    void setData(uint64_t index, const Reflection::GenericValue& value) override;
    const Reflection::FieldMap& getFields() override;

    Reflection::FieldMap fields;
};
