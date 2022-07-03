#pragma once

#include <any>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "third_party/json/json.hpp"

namespace mtEngine
{
  class Asset;
  class Nodes;
  class Meshes;
  class Accessors;
  class BufferViews;
  class Buffers;
  class Extras;

  class FileGltf
  {
    struct Spec
    {
      Asset *assets;
      Nodes *nodes;
      Meshes *meshes;
      Accessors *accessors;
      BufferViews *bufferViews;
      Buffers *buffers;
      Extras *extras;
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
  // Asset
  //////////////////////////////////////////////////////////////////////////////
  class Asset
  {
    struct Item;

  public:
    Asset(nlohmann::json::object_t *json)
        : json(json)
    {
      Parse();
    };

    ~Asset()
    {
      json = nullptr;
    }

    Item GetSection() { return _item; }

  private:
    nlohmann::json::object_t *json;

    struct Item
    {
      /* @brief A copyright message suitable for display to credit the content
       * creator. */
      std::string *copyright = nullptr;

      /** @brief Tool that generated this glTF model. Useful for debugging */
      std::string *generator = nullptr;

      /** @brief The glTF version in the form of <major>.<minor> that this asset
       * targets. */
      std::string version;

      /** #brief The minimum glTF version in the form of <major>.<minor> that
       * this asset targets. This property MUST NOT be greater than the asset
       * version. */
      std::string *minVersion = nullptr;

      /** @brief JSON object with extension-specific objects. */
      std::vector<std::any> extensions;

      /** #brief Application-specific data. */
      std::vector<std::any> extras;
    } _item;

  private:
    void Parse()
    {
      if (json->find("copyright") != json->end())
      {
        _item.copyright = new std::string(json->at("copyright"));
      }
      if (json->find("generator") != json->end())
      {
        _item.generator = new std::string(json->at("generator"));
      }
      _item.version = json->at("version");
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Nodes
  //////////////////////////////////////////////////////////////////////////////
  class Nodes
  {
    struct Item;
    struct Children;
    struct Rotation;
    struct Scale;
    struct Translation;

  public:
    using NodesItems = std::vector<Item>;
    Nodes(nlohmann::json::array_t *json)
        : json(json)
    {
      Parse();
    };

    ~Nodes()
    {
      _items.clear();
      json = nullptr;
    }

    NodesItems GetItems() { return _items; }

  private:
    NodesItems _items;
    struct Item
    {
      /** @brief The index of the camera referenced by this node. */
      int *camera = nullptr;

      /** @brief The indices of this node’s children. */
      Children *children = nullptr;

      /** @brief The node’s unit quaternion rotation in the order (x, y, z, w),
       * where w is the scalar. */
      Rotation *rotation = nullptr;

      /** @brief The node’s non-uniform scale, given as the scaling factors
       * along the x, y, and z axes. */
      Scale *scale = nullptr;

      /** @brief The node’s translation along the x, y, and z axes. */
      Translation *translation = nullptr;

      /** @brief The index of the mesh in this node. */
      int *mesh = nullptr;

      /** @brief The user-defined name of this object. */
      std::string *name = nullptr;
    };

    struct Children
    {
      std::vector<int> childs;
    };

    struct Rotation
    {
      int x = 0;
      int y = 0;
      int z = 0;
      int w = 1;
    };

    struct Scale
    {
      int x = 1;
      int y = 1;
      int z = 1;
    };

    struct Translation
    {
      int x = 0;
      int y = 0;
      int z = 0;
    };

    nlohmann::json::array_t *json;

  private:
    void Parse()
    {
      for (const auto i : *json)
      {
        Item item;
        if (i.contains("mesh"))
        {
          item.mesh = new int(i["mesh"]);
        }
        if (i.contains("name"))
        {
          item.name = new std::string(i["name"]);
        }
        if (i.contains("rotation"))
        {
          auto rot = new Rotation();
          rot->x = i["rotation"][0];
          rot->y = i["rotation"][1];
          rot->z = i["rotation"][2];
          rot->w = i["rotation"][3];
          item.rotation = rot;
          rot = nullptr;
        }
        if (i.contains("scale"))
        {
          auto scale = new Scale();
          scale->x = i["scale"][0];
          scale->y = i["scale"][1];
          scale->z = i["scale"][2];
          item.scale = scale;
          scale = nullptr;
        }
        if (i.contains("translation"))
        {
          auto tr = new Translation();
          tr->x = i["translation"][0];
          tr->y = i["translation"][1];
          tr->z = i["translation"][2];
          item.translation = tr;
          tr = nullptr;
        }
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
    struct Targets;
    enum class Modes : int;

  public:
    using PrimitiveItems = std::vector<PrimitiveItem>;
    using MeshesItems = std::vector<Item>;

    Meshes(nlohmann::json::array_t *json)
        : json(json)
    {
      Parse();
    }

    ~Meshes()
    {
      _items.clear();
      json = nullptr;
    }

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

    struct Targets
    {
      std::vector<int> targets;
    };

    struct PrimitiveItem
    {
      /** @brief The index of the accessor that contains the vertex indices. */
      int *indices = nullptr;

      /** @brief The index of the material to apply to this primitive when
       * rendering. */
      int *material = nullptr;

      /** @brief The topology type of primitives to render. */
      Modes *mode = nullptr;

      /** @brief An array of morph targets. */
      Targets *targets;

      /** @brief A plain JSON object, where each key corresponds to a mesh
       * attribute semantic and each value is the index of the accessor
       * containing attribute’s data. */
      Attributes attr;
    };

    struct Item
    {
      /** @breif The user-defined name of this object. */
      std::string *name = nullptr;

      /** @brief An array of primitives, each defining geometry to be rendered.
       */
      PrimitiveItems primitives;
    };

    enum class Modes
    {
      POINTS = 0,
      LINES = 1,
      LINE_LOOP = 2,
      LINE_STRIP = 3,
      TRIANGLES = 4,
      TRIANGLE_STRIP = 5,
      TRIANGLE_FAN = 6,
    };

  private:
    void Parse()
    {
      for (const auto &i : *json)
      {
        Item item;
        if (i.contains("name"))
        {
          item.name = new std::string(i["name"]);
        }

        for (const auto &p : i["primitives"])
        {
          Attributes attr;
          attr.position = p["attributes"]["POSITION"];
          attr.normal = p["attributes"]["NORMAL"];
          attr.textcoord_0 = p["attributes"]["TEXCOORD_0"];

          PrimitiveItem primitive;
          if (p.contains("indices"))
          {
            primitive.indices = new int(p["indices"]);
          }
          if (p.contains("material"))
          {
            primitive.material = new int(p["material"]);
          }
          if (p.contains("mode"))
          {
            if (p["mode"] == Modes::POINTS)
            {
              primitive.mode = new Modes{Modes::POINTS};
            }
            if (p["mode"] == Modes::LINES)
            {
              primitive.mode = new Modes{Modes::LINES};
            }
            if (p["mode"] == Modes::LINE_LOOP)
            {
              primitive.mode = new Modes{Modes::LINE_LOOP};
            }
            if (p["mode"] == Modes::LINE_STRIP)
            {
              primitive.mode = new Modes{Modes::LINE_STRIP};
            }
            if (p["mode"] == Modes::TRIANGLES)
            {
              primitive.mode = new Modes{Modes::TRIANGLES};
            }
            if (p["mode"] == Modes::TRIANGLE_STRIP)
            {
              primitive.mode = new Modes{Modes::TRIANGLE_STRIP};
            }
            if (p["mode"] == Modes::TRIANGLE_FAN)
            {
              primitive.mode = new Modes{Modes::TRIANGLE_FAN};
            }
          }
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
    struct Sparse;
    struct Indices;
    struct Values;

  public:
    enum class AccessorsComponentTypes : int
    {
      BYTE = 5120,
      UNSIGNED_BYTE = 5121,
      SHORT = 5122,
      UNSIGNED_SHORT = 5123,
      UNSIGNED_INT = 5125,
      FLOAT = 5126,
    };
    enum AccessorsTypes
    {
      SCALAR,
      VEC2,
      VEC3,
      VEC4,
      MAT2,
      MAT3,
      MAT4
    };
    using AccessorItems = std::vector<Item>;
    Accessors(nlohmann::json::array_t *json)
        : json(json)
    {
      Parse();
    }

    ~Accessors()
    {
      _items.clear();
      json = nullptr;
    }

    AccessorItems GetItems() { return _items; }

  private:
    using MinValues = std::vector<double>;
    using MaxValues = std::vector<double>;
    MinValues _min;
    MaxValues _max;
    AccessorItems _items;
    nlohmann::json::array_t *json;

    struct Indices
    {
      /** @brief The index of the buffer view with sparse indices. The
       * referenced buffer view MUST NOT have its target or byteStride
       * properties defined. The buffer view and the optional byteOffset MUST be
       * aligned to the componentType byte length. */
      unsigned int bufferView;

      /** @brief The offset relative to the start of the buffer view in bytes.
       */
      unsigned int *byteOffset = nullptr;

      /** @brief The indices data type. */
      AccessorsComponentTypes componentType;
    };

    struct Values
    {
      /** @brief The index of the bufferView with sparse values. The referenced
       * buffer view MUST NOT have its target or byteStride properties defined.
       */
      unsigned int bufferView;

      /** @brief The offset relative to the start of the bufferView in bytes. */
      unsigned int *byteOffset = nullptr;
    };

    struct Sparse
    {
      /** @brief Number of deviating accessor values stored in the sparse array.
       */
      unsigned int count;

      /** @brief An object pointing to a buffer view containing the indices of
       * deviating accessor values. The number of indices is equal to count.
       * Indices MUST strictly increase. */
      Indices indices;

      /** @brief An object pointing to a buffer view containing the deviating
       * accessor values. */
      Values values;
    };

    struct Item
    {
      /** @brief The index of the bufferView. */
      int *bufferView = nullptr;

      /** @brief The offset relative to the start of the buffer view in bytes.
       */
      int *byteOffset = nullptr;

      /** @brief The datatype of the accessor’s components. */
      AccessorsComponentTypes componentType;

      /** Specifies whether integer data values are normalized before usage. */
      bool *normalized = nullptr;

      /** @brief The number of elements referenced by this accessor. */
      int count;

      /** @brief Specifies if the accessor’s elements are scalars, vectors, or
       * matrices. */
      std::string type;

      /** @brief Minimum value of each component in this accessor. */
      MinValues *min = nullptr;

      /** @brief Maximum value of each component in this accessor. */
      MaxValues *max = nullptr;

      /** @brief Sparse storage of elements that deviate from their
       * initialization value. */
      Sparse *sparce = nullptr;

      /** @brief The user-defined name of this object. */
      std::string *name = nullptr;
    };

  private:
    void Parse()
    {
      for (const auto &i : *json)
      {
        Item item;

        if (i.contains("min"))
        {
          for (const auto &it : i["min"])
          {
            _min.push_back(it);
          }
          item.min = &_min;
        }

        if (i.contains("max"))
        {
          for (const auto &it : i["max"])
          {
            _max.push_back(it);
          }
          item.max = &_max;
        }

        if (i.contains("byteOffset"))
        {
          item.byteOffset = new int(i["byteOffset"]);
        }

        if (i.contains("bufferView"))
        {
          item.bufferView = new int(i["bufferView"]);
        }
        // Component Type ------------------------------------------------------
        if (i["componentType"] == AccessorsComponentTypes::BYTE)
        {
          item.componentType = AccessorsComponentTypes::BYTE;
        }
        if (i["componentType"] == AccessorsComponentTypes::UNSIGNED_BYTE)
        {
          item.componentType = AccessorsComponentTypes::UNSIGNED_BYTE;
        }
        if (i["componentType"] == AccessorsComponentTypes::SHORT)
        {
          item.componentType = AccessorsComponentTypes::SHORT;
        }
        if (i["componentType"] == AccessorsComponentTypes::UNSIGNED_INT)
        {
          item.componentType = AccessorsComponentTypes::UNSIGNED_INT;
        }
        if (i["componentType"] == AccessorsComponentTypes::FLOAT)
        {
          item.componentType = AccessorsComponentTypes::FLOAT;
        }
        // End of Component Type -----------------------------------------------

        if (i.contains("normalized"))
        {
          item.normalized = new bool(i["normalized"]);
        }

        // Sparse --------------------------------------------------------------
        if (i.contains("sparse"))
        {
          auto s = new Sparse();
          if (i["sparse"].contains("count"))
          {
            s->count = i["sparse"]["count"];
          }
          if (i["sparse"].contains("indices"))
          {
            Indices ind;
            ind.bufferView = (unsigned int)i["sparse"]["indices"];
            if (i["sparse"]["indices"].contains("byteOffset"))
            {
              ind.byteOffset =
                  new unsigned int(i["sparse"]["indices"]["byteOffset"]);
            }
            s->indices = ind;
          }
          if (i["sparse"].contains("values"))
          {
            Values v;
            v.bufferView = (unsigned int)i["sparse"]["values"];
            if (i["sparse"]["values"].contains("byteOffset"))
            {
              v.byteOffset =
                  new unsigned int(i["sparse"]["values"]["byteOffset"]);
            }
            s->values = v;
          }
          item.sparce = s;
        }
        // End of Sparse -------------------------------------------------------

        item.count = i["count"];
        item.type = i["type"];
        if (i.contains("name"))
        {
          item.name = new std::string(i["name"]);
        }
        // Type ----------------------------------------------------------------
        if (i["type"] == AccessorsTypes::SCALAR)
        {
          item.type = "SCALAR";
        }
        if (i["type"] == AccessorsTypes::VEC2)
        {
          item.type = "VEC2";
        }
        if (i["type"] == AccessorsTypes::VEC3)
        {
          item.type = "VEC3";
        }
        if (i["type"] == AccessorsTypes::VEC4)
        {
          item.type = "VEC4";
        }
        if (i["type"] == AccessorsTypes::MAT2)
        {
          item.type = "MAT2";
        }
        if (i["type"] == AccessorsTypes::MAT3)
        {
          item.type = "MAT3";
        }
        if (i["type"] == AccessorsTypes::MAT4)
        {
          item.type = "MAT4";
        }
        // End of Type ---------------------------------------------------------
        _items.push_back(item);
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
    enum class Targets : int
    {
      ARRAY_BUFFER = 34962,
      ELEMENT_ARRAY_BUFFER = 34963,
    };
    using BufferItems = std::vector<Item>;
    BufferViews(nlohmann::json::array_t *json)
        : json(json)
    {
      Parse();
    }

    ~BufferViews()
    {
      json = nullptr;
      _items.clear();
    }

    BufferItems GetItems() { return _items; }

  private:
    BufferItems _items;
    nlohmann::json::array_t *json;

    struct Item
    {
      /** @brief The index of the buffer. */
      unsigned int buffer;

      /** @brief The offset into the buffer in bytes. */
      unsigned int *byteOffset = nullptr;

      /** @brief The length of the bufferView in bytes. */
      unsigned int byteLength;

      /** @brief The stride, in bytes. */
      uint8_t *byteStride = nullptr;

      /** @brief The hint representing the intended GPU buffer type to use with
       * this buffer view. */
      Targets *target = nullptr;

      /** @brief The user-defined name of this object. */
      std::string *name = nullptr;
    };

  private:
    void Parse()
    {
      for (const auto &i : *json)
      {
        Item item;
        item.buffer = (unsigned int)i["buffer"];
        item.byteLength = (unsigned int)i["byteLength"];
        if (i.contains("byteOffset"))
        {
          item.byteOffset = new unsigned int(i["byteOffset"]);
        }
        if (i.contains("byteStride"))
        {
          item.byteStride = new uint8_t(i["byteStride"]);
        }
        if (i.contains("target"))
        {
          if (i["target"] == Targets::ARRAY_BUFFER)
          {
            item.target = new Targets{Targets::ARRAY_BUFFER};
          }
          if (i["target"] == Targets::ELEMENT_ARRAY_BUFFER)
          {
            item.target = new Targets{Targets::ELEMENT_ARRAY_BUFFER};
          }
        }
        if (i.contains("name"))
        {
          item.name = new std::string(i["name"]);
        }
        _items.push_back(item);
      }
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Buffers
  //////////////////////////////////////////////////////////////////////////////
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

    ~Buffers()
    {
      _items.clear();
      json = nullptr;
    }

    BufferItems GetItems() { return _items; }

  private:
    BufferItems _items;
    nlohmann::json::array_t *json;

    struct Item
    {
      /** @brief The length of the buffer in bytes */
      unsigned int byteLength;

      /** @brief The URI (or IRI) of the buffer. */
      std::string *uri = nullptr;

      /** @brief The user-defined name of this object. */
      std::string *name = nullptr;
    };

  private:
    void Parse()
    {
      for (const auto &i : *json)
      {
        Item item;
        item.byteLength = i["byteLength"];
        if (i.contains("uri"))
        {
          item.uri = new std::string(i["uri"]);
        }
        if (i.contains("name"))
        {
          item.name = new std::string(i["name"]);
        }
        _items.push_back(item);
      }
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Extras
  //////////////////////////////////////////////////////////////////////////////
  class Extras
  {
    struct Item;

  public:
    Extras(nlohmann::json::object_t *json)
        : json(json)
    {
      Parse();
    }
    ~Extras()
    {
      delete _item.gameModelsRelativePath;
      delete _item.gameTexturesRelativePath;
    }

    Item GetSection() { return _item; }

  private:
    struct Item
    {
      /** @brief Relative path to models from game root */
      std::string *gameModelsRelativePath = nullptr;

      /** @brief Relative path to textures from game root */
      std::string *gameTexturesRelativePath = nullptr;
    } _item;
    nlohmann::json::object_t *json;

    void Parse()
    {
      if (json->find("gameModelsRelativePath") != json->end())
      {
        _item.gameModelsRelativePath =
            new std::string(json->at("gameModelsRelativePath"));
      }
      if (json->find("gameTexturesRelativePath") != json->end())
      {
        _item.gameTexturesRelativePath =
            new std::string(json->at("gameTexturesRelativePath"));
      }
    }
  };
} // namespace mtEngine
