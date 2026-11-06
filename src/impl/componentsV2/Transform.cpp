// Transform.cpp, 24/10/2026
#include <format>

#include "componentsV2/Transform.hpp"

TransformComponentRecord::TransformComponentRecord()
{
    fields = {
        { "relative", Reflection::FieldDescriptor{
            .Read = [](ComponentRecordBase* cr, uint64_t index) -> Reflection::GenericValue
            {
                TransformComponentRecord* tcr = (TransformComponentRecord*)cr;
                return tcr->data[index].relative;
            },
            .Write = [](ComponentRecordBase* cr, uint64_t index, const Reflection::GenericValue& value)
            {
                TransformComponentRecord* tcr = (TransformComponentRecord*)cr;
                tcr->data[index].relative = value.AsMatrix();
            },
            .Type = Reflection::ValueType::Matrix,
        } },
        { "absolute", Reflection::FieldDescriptor{
            .Read = [](ComponentRecordBase* cr, uint64_t index) -> Reflection::GenericValue
            {
                TransformComponentRecord* tcr = (TransformComponentRecord*)cr;
                return tcr->data[index].absolute;
            },
            .Write = [](ComponentRecordBase* cr, uint64_t index, const Reflection::GenericValue& value)
            {
                TransformComponentRecord* tcr = (TransformComponentRecord*)cr;
                tcr->data[index].absolute = value.AsMatrix();
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

        if (field == "relative")
            data[index].relative = v.AsMatrix();
        else if (field == "absolute")
            data[index].absolute = v.AsMatrix();
        else
            throw std::runtime_error(std::format("Invalid field '{}'", field));
    });
}

const Reflection::FieldMap& TransformComponentRecord::getFields()
{
    return fields;
}
