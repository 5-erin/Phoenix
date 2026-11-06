// Mesh.cpp, 06/11/2026
#include <format>

#include "componentsV2/Mesh.hpp"

#include "asset/MeshProvider.hpp"

MeshComponentRecord::MeshComponentRecord()
{
    fields = {
        { "asset", Reflection::FieldDescriptor{
            .Read = [](ComponentRecordBase* cr, uint64_t index) -> Reflection::GenericValue
            {
                MeshComponentRecord* mcr = (MeshComponentRecord*)cr;
                return mcr->data[index].asset;
            },
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
        { "tint", Reflection::FieldDescriptor{
            .Read = [](ComponentRecordBase* cr, uint64_t index) -> Reflection::GenericValue
            {
                MeshComponentRecord* mcr = (MeshComponentRecord*)cr;
                return mcr->data[index].tint.ToGenericValue();
            },
            .Write = [](ComponentRecordBase* cr, uint64_t index, const Reflection::GenericValue& value)
            {
                MeshComponentRecord* mcr = (MeshComponentRecord*)cr;
                mcr->data[index].tint = Color(value);
            },
            .Type = Reflection::ValueType::Color,
            .Serializes = false,
        } },
        { "opacity", Reflection::FieldDescriptor{
            .Read = [](ComponentRecordBase* cr, uint64_t index) -> Reflection::GenericValue
            {
                MeshComponentRecord* mcr = (MeshComponentRecord*)cr;
                return mcr->data[index].opacity;
            },
            .Write = [](ComponentRecordBase* cr, uint64_t index, const Reflection::GenericValue& value)
            {
                MeshComponentRecord* mcr = (MeshComponentRecord*)cr;
                mcr->data[index].opacity = value.AsDouble();
            },
            .Type = Reflection::ValueType::Double,
            .Serializes = false,
        } },
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
            data[index].tint = Color(v);
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
