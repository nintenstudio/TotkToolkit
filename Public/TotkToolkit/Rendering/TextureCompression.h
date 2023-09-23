#pragma once

#include <Formats/Texture/Format.h>
#include <astcenc.h>
#include <glad/glad.h>
#include <memory>

namespace TotkToolkit::Rendering {
    class TextureCompression {
    public:
        static void Init();

        static bool Load(GLuint textureId, GLenum target, GLint width, GLint height, GLint border, Formats::Texture::Format format, std::shared_ptr<F_U8[]> compressedData, F_UT compressedDataSize);
    protected:
        static void DecompressASTC(std::shared_ptr<F_U8[]> compressedData, F_UT compressedDataSize, astcenc_context* context, std::shared_ptr<F_U8[]>* decompressedDataOut, F_UT* decompressedSizeOut);

        static astcenc_config mASTC4x4Config;
        static astcenc_context* mASTC4x4Context;

        static astcenc_config mASTC4x4SRGBConfig;
        static astcenc_context* mASTC4x4SRGBContext;

        static astcenc_config mASTC5x4Config;
        static astcenc_context* mASTC5x4Context;

        static astcenc_config mASTC5x4SRGBConfig;
        static astcenc_context* mASTC5x4SRGBContext;
    };
}