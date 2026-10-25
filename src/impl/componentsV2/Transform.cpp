// Transform.cpp, 24/10/2026
#include "componentsV2/Transform.hpp"

TransformComponentRecord::TransformComponentRecord()
{
    fields = {
        { "Local", Reflection::FieldDescriptor{
            .Read = [](ComponentRecordBase* cr, uint64_t index) -> Reflection::GenericValue
            {
                TransformComponentRecord* tcr = (TransformComponentRecord*)cr;
                return tcr->data[index].Local;
            },
            .Write = [](ComponentRecordBase* cr, uint64_t index, const Reflection::GenericValue& value)
            {
                TransformComponentRecord* tcr = (TransformComponentRecord*)cr;
                tcr->data[index].Local = value.AsMatrix();
            },
            .Type = Reflection::ValueType::Matrix,
        } },
        { "World", Reflection::FieldDescriptor{
            .Read = [](ComponentRecordBase* cr, uint64_t index) -> Reflection::GenericValue
            {
                TransformComponentRecord* tcr = (TransformComponentRecord*)cr;
                return tcr->data[index].World;
            },
            .Write = [](ComponentRecordBase* cr, uint64_t index, const Reflection::GenericValue& value)
            {
                TransformComponentRecord* tcr = (TransformComponentRecord*)cr;
                tcr->data[index].World = value.AsMatrix();
            },
            .Type = Reflection::ValueType::Matrix,
            .Serializes = false,
        } },
    };
}

Reflection::GenericValue TransformComponentRecord::getData(uint64_t index)
{
    Reflection::GenericValue cell;
    cell.Val.Component = { .cr = this, .index = index };
    cell.Type = Reflection::ValueType::Component;

    return cell;
}

void TransformComponentRecord::setData(uint64_t index, const Reflection::GenericValue& value)
{
    value.ForEachMapPair([&](const Reflection::GenericValue& k, const Reflection::GenericValue& v)
    {
        std::string_view field = k.AsStringView();

        if (field == "Local")
            data[index].Local = v.AsMatrix();
        else if (field == "World")
            data[index].World = v.AsMatrix();
    });
}

const Reflection::FieldMap& TransformComponentRecord::getFields()
{
    return fields;
}
