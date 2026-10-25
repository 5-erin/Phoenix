// BuiltinComponents.hpp, 20/10/2026
#pragma once

#include <string_view>
#include "Ecs.hpp"

struct Ec_
{
    enum EC : Id
    {
        start = 1,

        // Relationship wildcard.
        Wildcard = 1,
        // Exclusive relationship.
        Exclusive,
        ChildOf,
        Name,
        Transform,

        // Scene root.
        Root,

        afterEnd,
        count = afterEnd - 1
    };
};

using Ec = Ec_::EC;

constexpr std::string_view EcNames[] = {
    "Wildcard",
    "Exclusive",
    "ChildOf",
    "Name",
    "Transform",
    "Root",
};

static_assert(std::size(EcNames) == Ec::count);
