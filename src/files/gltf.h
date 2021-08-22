#pragma once

#include "geom/vertex.h"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"
#include "glm/gtc/type_ptr.hpp"

void loadGLTFModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    // Read in the model file
    bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path);

    if (!warn.empty()) {
        std::cout << warn << std::endl;
    }
    if (!err.empty()) {
        std::cout << err << std::endl;
    }
    if (!ret) {
        throw std::runtime_error("Failed to parse glTF model.");
    }

    // For each primitive in the buffer
    for (const auto& mesh : model.meshes) {
        for (const auto& prim : mesh.primitives) {
            // Load position buffer
            const tinygltf::Accessor& positionAccessor = model.accessors[prim.attributes.at("POSITION")];
            const tinygltf::BufferView& positionBufferView = model.bufferViews[positionAccessor.bufferView];
            const tinygltf::Buffer& positionBuffer = model.buffers[positionBufferView.buffer];
            const float* positions = reinterpret_cast<const float*>(&positionBuffer.data[positionBufferView.byteOffset + positionAccessor.byteOffset]);

            // Load UV buffer
            const tinygltf::Accessor &uvAccessor = model.accessors[prim.attributes.at("TEXCOORD_0")];
            const tinygltf::BufferView &uvView = model.bufferViews[uvAccessor.bufferView];
            const tinygltf::Buffer& uvBuffer = model.buffers[uvView.buffer];
            const float* uvs = reinterpret_cast<const float *>(&(uvBuffer.data[uvAccessor.byteOffset + uvView.byteOffset]));

            // Create vertices
            for (int i = 0; i < positionAccessor.count; i++) {
                Vertex vertex {};
                vertex.pos = { positions[i * 3 + 0], positions[i * 3 + 1], positions[i * 3 + 2]};
                vertex.texCoord = { uvs[i * 2 + 0], uvs[i * 2 + 1]};
                vertex.color = {1.0, 1.0, 1.0};
                vertices.push_back(vertex);
            }

            // Load indices
            const tinygltf::Accessor &indexAccessor = model.accessors[prim.indices > -1 ? prim.indices : 0];
            const tinygltf::BufferView &indexBufferView = model.bufferViews[indexAccessor.bufferView];
            const tinygltf::Buffer &indexBuffer = model.buffers[indexBufferView.buffer];
            const void* indexData = reinterpret_cast<const uint32_t*>(&indexBuffer.data[indexBufferView.byteOffset + indexAccessor.byteOffset]);
            switch (indexAccessor.componentType) {
                case TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT: {
                    const uint32_t *buf = static_cast<const uint32_t*>(indexData);
                    for (size_t i = 0; i < indexAccessor.count; i++) {
                        indices.push_back(buf[i]);
                    }
                    break;
                }
                case TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT: {
                    const uint16_t *buf = static_cast<const uint16_t*>(indexData);
                    for (size_t i = 0; i < indexAccessor.count; i++) {
                        indices.push_back(buf[i]);
                    }
                    break;
                }
                case TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE: {
                    const uint8_t *buf = static_cast<const uint8_t*>(indexData);
                    for (size_t i = 0; i < indexAccessor.count; i++) {
                        indices.push_back(buf[i]);
                    }
                    break;
                }
                default:
                    std::cerr << "Index component type " << indexAccessor.componentType << " not supported!" << std::endl;
                    return;
            }
        }
    }
}
