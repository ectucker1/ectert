#include "obj.h"

#include "shapes/group.h"
#include "shapes/triangle.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

std::shared_ptr<Shape> load_obj_group(std::string input) {
    auto group = std::make_shared<Group>();

    // Results of loading. Will by filled by tinyobjloader.
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, input.c_str(), nullptr, true);

    // Print out error if present
    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    // Return empty group if loading failed
    if (!ret) {
        return group;
    }

    // Loop over shapes in file
    for (tinyobj::shape_t shape : shapes) {
        int index_offset = 0;
        // Loop over faces
        for (int fv : shape.mesh.num_face_vertices) {
            // If the face is a triangle
            if (fv == 3) {
                Tuple vertices[3];
                Tuple normals[3];

                // Loop over vertices in the face.
                for (int v = 0; v < 3; v++) {
                    // Index structure for this vertex
                    tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                    tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
                    tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
                    tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
                    tinyobj::real_t nx = attrib.vertices[3 * idx.normal_index + 0];
                    tinyobj::real_t ny = attrib.vertices[3 * idx.normal_index + 1];
                    tinyobj::real_t nz = attrib.vertices[3 * idx.normal_index + 2];

                    vertices[v] = Tuple::point(vx, vy, vz);
                    normals[v] = Tuple::vector(nx, ny, nz);
                }

                auto tri = std::make_shared<Triangle>(vertices[0], vertices[1], vertices[2], normals[0], normals[1], normals[2]);
                group->add_child(tri);
            }

            index_offset += fv;
        }
    }

    return group;
}
