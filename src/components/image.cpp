#include "image.h"
#include "imgui.h"
#include <OpenGL/gltypes.h>
#include <cmath>
#include <cstdlib>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"

#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvgrast.h"

namespace ImModernUI {
    GLuint load_image(
        const char * path, 
        int * w, 
        int * h, 
        bool grayscale /* = false */
    ) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(
            GL_TEXTURE_2D, 
            GL_TEXTURE_MIN_FILTER, 
            GL_LINEAR
        );
        glTexParameteri(
            GL_TEXTURE_2D, 
            GL_TEXTURE_MAG_FILTER, 
            GL_LINEAR
        );

        auto data = stbi_load(
            path, 
            w, 
            h, 
            nullptr, 
            4
        );
        if (data == nullptr) return GLuint(-1);
        if (grayscale) {
            for (int i=0; i<(*w * *h); ++i) {
                unsigned char r = data[i * 4];
                unsigned char g = data[i * 4 + 1];
                unsigned char b = data[i * 4 + 2];

                unsigned char gray = (unsigned char)(0.299f*r + 0.587f*g + 0.114f*b);
                data[i * 4] = gray;
                data[i * 4 + 1] = gray;
                data[i * 4 + 2] = gray;
            }
        }
        
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            *w, 
            *h, 
            0, 
            GL_RGBA, 
            GL_UNSIGNED_BYTE, 
            data
        );

        stbi_image_free(data);

        return texture;
    }

    GLuint load_svg(
        const char * path, 
        int * w, 
        int * h, 
        bool recolor /* = false */, 
        ImVec4 color /* = ImVec4(0, 0, 0, 0) */, 
        bool rotate /* = false */, 
        float angle /* = 0.0 */
    ) {
        auto image = nsvgParseFromFile(
            path, 
            "px", 
            96.0f
        );
        if (image == nullptr) return GLuint(-1);
        if (recolor) {
            image->shapes->fill.type = NSVG_PAINT_COLOR;
            image->shapes->fill.color = ImGui::GetColorU32(color);
            image->shapes->stroke.color = ImGui::GetColorU32(color);
        }

        if (rotate) {
            float cx = image->width * 0.5f;
            float cy = image->height * 0.5f;
            for (auto shape = image->shapes; 
                shape != nullptr;
                shape = shape->next
            ) {
                for (auto path = shape->paths; 
                    path != nullptr; 
                    path = path->next
                ) {
                    for (int i=0; i<path->npts*2; i+=2) {
                        auto& x = path->pts[i];
                        auto& y = path->pts[i + 1];
                        float s = sinf(angle);
                        float c = cosf(angle);

                        x -= cx;
                        y -= cy;

                        float nx = x * c - y * s;
                        float ny = x * s + y * c;

                        x = cx + nx;
                        y = cy + ny;
                    }
                }
            }
        }

        auto rast = nsvgCreateRasterizer();
        if (rast == nullptr) {
            nsvgDelete(image);
            return GLuint(-1);
        }

        std::vector<unsigned char> img(image->width * image->height * 4);
        nsvgRasterize(
            rast, 
            image, 
            0.0, 
            0.0, 
            1.0, 
            img.data(), 
            image->width, 
            image->height, 
            image->width * 4
        );

        GLuint texture;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(
            GL_TEXTURE_2D, 
            GL_TEXTURE_MIN_FILTER, 
            GL_LINEAR
        );
        glTexParameteri(
            GL_TEXTURE_2D, 
            GL_TEXTURE_MAG_FILTER, 
            GL_LINEAR
        );

        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            image->width, 
            image->height, 
            0, 
            GL_RGBA, 
            GL_UNSIGNED_BYTE, 
            img.data()
        );

        *w = image->width;
        *h = image->height;

        nsvgDeleteRasterizer(rast);
        nsvgDelete(image);

        return texture;
    }
}