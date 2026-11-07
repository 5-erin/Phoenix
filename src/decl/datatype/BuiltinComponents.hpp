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
        Mesh,

        afterEnd,
        count = afterEnd - 1
    };
};

using Ec = Ec_::EC;

constexpr std::string_view EcNames[] = {
    "phoenix.Wildcard",
    "phoenix.Exclusive",
    "phoenix.ChildOf",
    "phoenix.Name",
    "phoenix.Transform",
    "phoenix.Mesh",
};

static_assert(std::size(EcNames) == Ec::count);
