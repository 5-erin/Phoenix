// Mesh.cpp, 06/11/2026
#include <format>

#include "componentsV2/Mesh.hpp"

#include "asset/MeshProvider.hpp"

MeshComponentRecord::MeshComponentRecord()
{
    fields = {
        { "asset", Reflection::FieldDescriptor{
            .Read = ECS_FIELD_READ(MeshComponentRecord, asset),
            .Write = [](ComponentRecordBase* cr, uint64_t index, const Reflection::GenericValue& value)
            {
                MeshComponentRecord* mcr = (MeshComponentRecord*)cr;
                MeshComponent& target = mcr->data[index];
                std::string newAsset = value.AsString();

                target.asset = newAsset;
                target.assetId = MeshProvider::Get()->LoadFromPath(newAsset);
            },
            .Type = Reflection::ValueType::String,
        } },
        { "tint", ECS_FIELD(MeshComponentRecord, tint, Color) },
        { "opacity", ECS_FIELD(MeshComponentRecord, opacity, Double) },
    };
}

Reflection::GenericValue MeshComponentRecord::getData(uint64_t index)
{
    Reflection::GenericValue cell;
    cell.Val.Component = { .cr = this, .index = index };
    cell.Type = Reflection::ValueType::Component;

    return cell;
}

void MeshComponentRecord::setData(uint64_t index, const Reflection::GenericValue& value)
{
    value.ForEachMapPair([&](const Reflection::GenericValue& k, const Reflection::GenericValue& v)
    {
        std::string_view field = k.AsStringView();

        if (field == "asset")
        {
            std::string asset = v.AsString();
            data[index].asset = asset;
            data[index].assetId = MeshProvider::Get()->LoadFromPath(asset);
        }
        else if (field == "tint")
            data[index].tint = v.AsColor();
        else if (field == "opacity")
            data[index].opacity = v.AsDouble();
        else
            throw std::runtime_error(std::format("Invalid field '{}'", field));
    });
}

const Reflection::FieldMap& MeshComponentRecord::getFields()
{
    return fields;
}
