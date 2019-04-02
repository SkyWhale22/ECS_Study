#pragma once

#include <vector>
#include <array>

constexpr size_t MAX_ENTITIES = 500;
constexpr size_t MAX_COMPONENTS = 100;

struct Component;
using Entity = size_t;
using ComponentId = size_t;

using ComponentArray = std::vector<Component*>;
typedef std::array<int, MAX_COMPONENTS> EntityComponentArray;
