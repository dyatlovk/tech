#pragma once

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "third_party/json/json.hpp"

namespace mtEngine
{
  class Nodes;
  class Meshes;
  class Accessors;
  class BufferViews;
  class Buffers;

  class FileGltf
  {
    struct Spec
    {
      Nodes *nodes;
      Meshes *meshes;
      Accessors *accessors;
      BufferViews *bufferViews;
      Buffers *buffers;
    } spec;

  public:
    FileGltf();
    ~FileGltf();

    Spec GetSpec() { return spec; };

    static std::shared_ptr<FileGltf> Create(const std::filesystem::path path);

  private:
    std::string _buffer;
    nlohmann::json _jsonParser;

    std::string LoadFromFile(const std::filesystem::path path) const;
    void CreateSpec();
    void CleanSpec();
  };

  //////////////////////////////////////////////////////////////////////////////
  // Nodes
  //////////////////////////////////////////////////////////////////////////////
  class Nodes
  {
    struct Item;

  public:
    using NodesItems = std::vector<Item>;
    Nodes(nlohmann::json::array_t *json)
        : json(json)
    {
      Parse();
    };

    ~Nodes() = default;

    NodesItems GetItems() { return _items; }

  private:
    NodesItems _items;
    struct Item
    {
      int mesh;
      std::string name;
    };
    nlohmann::json::array_t *json;

  private:
    void Parse()
    {
      for (const auto i : *json)
      {
        Item item;
        item.mesh = i["mesh"];
        item.name = i["name"];
        _items.push_back(item);
      }
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Meshes
  //////////////////////////////////////////////////////////////////////////////
  class Meshes
  {
    struct Item;
    struct PrimitiveItem;
    struct Attributes;

  public:
    using PrimitiveItems = std::vector<PrimitiveItem>;
    using MeshesItems = std::vector<Item>;

    Meshes(nlohmann::json::array_t *json)
        : json(json)
    {
      Parse();
    }

    ~Meshes() = default;

    MeshesItems GetItems() { return _items; }

  private:
    MeshesItems _items;
    PrimitiveItems _primitives;
    nlohmann::json::array_t *json;

    struct Attributes
    {
      int position;
      int normal;
      int textcoord_0;
    };

    struct PrimitiveItem
    {
      int indices;
      int material;
      Attributes attr;
    };

    struct Item
    {
      std::string name;
      PrimitiveItems primitives;
    };

  private:
    void Parse()
    {
      for (const auto &i : *json)
      {
        Item item;
        item.name = i["name"];

        for (const auto &p : i["primitives"])
        {
          Attributes attr;
          attr.position = p["attributes"]["POSITION"];
          attr.normal = p["attributes"]["NORMAL"];
          attr.textcoord_0 = p["attributes"]["TEXCOORD_0"];

          PrimitiveItem primitive;
          primitive.indices = p["indices"];
          primitive.material = p["material"];
          primitive.attr = attr;
          item.primitives.push_back(primitive);
        }

        _items.push_back(item);
      }
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Accessors
  //////////////////////////////////////////////////////////////////////////////
  class Accessors
  {
    struct Item;
    struct Min;
    struct Max;

  public:
    using AccessorItems = std::vector<Item>;
    Accessors(nlohmann::json::array_t *json)
        : json(json)
    {
      Parse();
    }

    ~Accessors() = default;

    AccessorItems GetItems() { return _items; }

  private:
    AccessorItems _items;
    nlohmann::json::array_t *json;

    struct Min
    {
      int x = 0;
      int y = 0;
      int z = 0;
    };

    struct Max
    {
      int x = 0;
      int y = 0;
      int z = 0;
    };

    struct Item
    {
      int bufferView;
      int componentType;
      int count;
      Min *min;
      Max *max;
      std::string type;
    };

  private:
    void Parse()
    {
      for (const auto &i : *json)
      {
        Min *min = new Min();
        if (i.contains("min"))
        {
          min->x = i["min"][0];
          min->y = i["min"][1];
          min->z = i["min"][2];
        }

        Max *max = new Max();
        if (i.contains("max"))
        {
          max->x = i["max"][0];
          max->y = i["max"][1];
          max->z = i["max"][2];
        }

        Item item;
        item.bufferView = i["bufferView"];
        item.componentType = i["componentType"];
        item.count = i["count"];
        item.type = i["type"];
        item.min = min;
        item.max = max;
        _items.push_back(item);

        min = nullptr;
        max = nullptr;
      }
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // BufferViews
  //////////////////////////////////////////////////////////////////////////////
  class BufferViews
  {
    struct Item;

  public:
    using BufferItems = std::vector<Item>;
    BufferViews(nlohmann::json::array_t *json)
        : json(json)
    {
      Parse();
    }

    ~BufferViews() = default;

    BufferItems GetItems() { return _items; }

  private:
    BufferItems _items;
    nlohmann::json::array_t *json;

    struct Item
    {
      int buffer;
      int byteLength;
      int byteOffset;
    };

  private:
    void Parse()
    {
      for (const auto &i : *json)
      {
        Item item;
        item.buffer = i["buffer"];
        item.byteLength = i["byteLength"];
        item.byteOffset = i["byteOffset"];
        _items.push_back(item);
      }
    }
  };

  class Buffers
  {
    struct Item;

  public:
    using BufferItems = std::vector<Item>;
    Buffers(nlohmann::json::array_t *json)
        : json(json)
    {
      Parse();
    }

    ~Buffers() = default;

    BufferItems GetItems() { return _items; }

  private:
    BufferItems _items;
    nlohmann::json::array_t *json;

    struct Item
    {
      int byteLength;
      std::string uri;
    };

  private:
    void Parse()
    {
      for (const auto &i : *json)
      {
        Item item;
        item.byteLength = i["byteLength"];
        item.uri = i["uri"];
        _items.push_back(item);
      }
    }
  };
} // namespace mtEngine
