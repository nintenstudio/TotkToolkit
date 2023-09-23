#include <TotkToolkit/Rendering/TextureCompression.h>

namespace TotkToolkit::Rendering {
    void TextureCompression::Init() {
        astcenc_config_init(astcenc_profile::ASTCENC_PRF_LDR, 4, 4, 1, 50.f, NULL, &mASTC4x4Config);
		astcenc_context_alloc(&mASTC4x4Config, 1, &mASTC4x4Context);

		astcenc_config_init(astcenc_profile::ASTCENC_PRF_LDR_SRGB, 4, 4, 1, 50.f, NULL, &mASTC4x4SRGBConfig);
		astcenc_context_alloc(&mASTC4x4SRGBConfig, 1, &mASTC4x4SRGBContext);

		astcenc_config_init(astcenc_profile::ASTCENC_PRF_LDR, 4, 5, 1, 50.f, NULL, &mASTC5x4Config);
		astcenc_context_alloc(&mASTC5x4Config, 1, &mASTC5x4Context);

		astcenc_config_init(astcenc_profile::ASTCENC_PRF_LDR_SRGB, 4, 5, 1, 50.f, NULL, &mASTC5x4SRGBConfig);
		astcenc_context_alloc(&mASTC5x4SRGBConfig, 1, &mASTC5x4SRGBContext);
    }

    bool TextureCompression::Load(GLuint textureId, GLenum target, GLint width, GLint height, GLint border, Formats::Texture::Format format, std::shared_ptr<F_U8[]> compressedData, F_UT compressedDataSize) {
        std::shared_ptr<F_U8[]> data = compressedData;
		F_UT dataSize = compressedDataSize;
		GLenum internalFormat;

		switch (format) {
			case Formats::Texture::Format::BC1_UNORM:
				if (GLAD_GL_EXT_texture_compression_s3tc)
					internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				else
					return false;
				break;
			case Formats::Texture::Format::BC1_UNORM_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_EXT_texture_compression_s3tc)
					internalFormat = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
				else
					return false;
				break;
			case Formats::Texture::Format::BC2_UNORM:
				if (GLAD_GL_EXT_texture_compression_s3tc)
					internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				else
					return false;
				break;
			case Formats::Texture::Format::BC2_UNORM_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_EXT_texture_compression_s3tc)
					internalFormat = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
				else
					return false;
				break;
			case Formats::Texture::Format::BC3_UNORM:
				if (GLAD_GL_EXT_texture_compression_s3tc)
					internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				else
					return false;
				break;
			case Formats::Texture::Format::BC3_UNORM_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_EXT_texture_compression_s3tc)
					internalFormat = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;
				else
					return false;
				break;
			case Formats::Texture::Format::BC4_UNORM:
			case Formats::Texture::Format::BC4_TYPELESS:
				internalFormat = GL_COMPRESSED_RED_RGTC1;
				break;
			case Formats::Texture::Format::BC4_SNORM:
				internalFormat = GL_COMPRESSED_SIGNED_RED_RGTC1;
				break;
			case Formats::Texture::Format::BC5_UNORM:
			case Formats::Texture::Format::BC5_TYPELESS:
				internalFormat = GL_COMPRESSED_RG_RGTC2;
				break;
			case Formats::Texture::Format::BC5_SNORM:
			    internalFormat = GL_COMPRESSED_SIGNED_RG_RGTC2;
				break;
			case Formats::Texture::Format::BC6H_UF16:
			case Formats::Texture::Format::BC6H_TYPELESS:
				internalFormat = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT;
				break;
			case Formats::Texture::Format::BC6H_SF16:
				internalFormat = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT;
				break;
			case Formats::Texture::Format::BC7_UNORM:
			case Formats::Texture::Format::BC7_TYPELESS:
				internalFormat = GL_COMPRESSED_RGBA_BPTC_UNORM;
				break;
			case Formats::Texture::Format::BC7_UNORM_SRGB:
				internalFormat = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM;
				break;
			case Formats::Texture::Format::ASTC_4x4_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_4x4_KHR;
				else
					DecompressASTC(compressedData, compressedDataSize, mASTC4x4Context, &data, &dataSize);
				break;
			case Formats::Texture::Format::ASTC_4x4_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR;
				else
					DecompressASTC(compressedData, compressedDataSize, mASTC4x4SRGBContext, &data, &dataSize);
				break;
			case Formats::Texture::Format::ASTC_5x4_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_5x4_KHR;
				else
					DecompressASTC(compressedData, compressedDataSize, mASTC5x4Context, &data, &dataSize);
				break;
			case Formats::Texture::Format::ASTC_5x4_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR;
				else
					DecompressASTC(compressedData, compressedDataSize, mASTC5x4SRGBContext, &data, &dataSize);
				break;
			case Formats::Texture::Format::ASTC_5x5_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_5x5_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_5x5_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_6x5_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_6x5_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_6x5_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_6x6_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_6x6_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_6x6_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_8x5_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_8x5_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_8x5_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_8x6_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_8x6_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_8x6_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_8x8_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_8x8_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_8x8_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_10x5_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_10x5_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_10x5_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_10x6_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_10x6_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_10x6_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_10x8_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_10x8_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_10x8_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_10x10_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_10x10_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_10x10_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_12x10_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_12x10_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_12x10_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_12x12_UNORM:
				if (GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_RGBA_ASTC_12x12_KHR;
				else
					return false;
				break;
			case Formats::Texture::Format::ASTC_12x12_SRGB:
				if (GLAD_GL_EXT_texture_sRGB && GLAD_GL_KHR_texture_compression_astc_ldr)
					internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR;
				else
					return false;
				break;
		}

	
		glBindTexture(target, textureId);
		glCompressedTexImage2D(target, 0, internalFormat, width, height, border, dataSize, data.get());
    
		return true;
	}

	void TextureCompression::DecompressASTC(std::shared_ptr<F_U8[]> compressedData, F_UT compressedDataSize, astcenc_context* context, std::shared_ptr<F_U8[]>* decompressedDataOut, F_UT* decompressedSizeOut) {
		astcenc_image decompressed;
		astcenc_swizzle swizzle {
			ASTCENC_SWZ_R,
			ASTCENC_SWZ_G,
			ASTCENC_SWZ_B,
			ASTCENC_SWZ_A
		};
		astcenc_decompress_image(context, compressedData.get(), compressedDataSize, &decompressed, &swizzle, 0);
		*decompressedDataOut = std::shared_ptr<F_U8[]>((F_U8*)(decompressed.data[0]));
	}

	astcenc_config TextureCompression::mASTC4x4Config;
	astcenc_context* TextureCompression::mASTC4x4Context;

	astcenc_config TextureCompression::mASTC4x4SRGBConfig;
	astcenc_context* TextureCompression::mASTC4x4SRGBContext;

	astcenc_config TextureCompression::mASTC5x4Config;
	astcenc_context* TextureCompression::mASTC5x4Context;
	
	astcenc_config TextureCompression::mASTC5x4SRGBConfig;
	astcenc_context* TextureCompression::mASTC5x4SRGBContext;
}