#include <TotkToolkit/UI/Windows/Editors/TXTG.h>

#include <TotkToolkit/Rendering/TextureCompression.h>
#include <imgui.h>
#include <glad/glad.h>

namespace TotkToolkit::UI::Windows::Editors {
	TXTG::TXTG(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open) : TotkToolkit::UI::Windows::Editors::Texture(fileHandle, name, open) {
		
	}
	TXTG::TXTG(std::shared_ptr<Formats::Resources::TXTG::TXTG> txtg, std::string name, bool* open) : TotkToolkit::UI::Windows::Editors::Texture(txtg, name, open), mTXTG(txtg) {
		
	}

	void TXTG::DrawContents() {
		ImGui::PushID(GetIdentifier().c_str());

		ImGui::SliderInt("mip level", &mMipSliderValue, 0, mTXTG->GetMipCount() - 1);
		mTextureID = mMips[mMipSliderValue];

		Texture::DrawContents();
		ImGui::PopID();
	}

	bool TXTG::Parse() {
		if (mTXTG == nullptr) {
			if (mFileHandle.IsNull())
				return false;
			mTXTG = Formats::Resources::TXTG::TXTG::Factory(mFileHandle.GetReadStream());
			if (mTXTG == nullptr)
				return false;
		}

		for (F_U32 i = 0; i < mTXTG->GetMipCount(); i++) {
			std::shared_ptr<Formats::Resources::TXTG::Surface> surface = mTXTG->GetSurface(0, i);
			std::shared_ptr<F_U8[]> data = surface->GetData();
			F_UT dataSize = surface->GetDataSize();

			GLuint texId;
			glGenTextures(1, &texId);
			glBindTexture(GL_TEXTURE_2D, texId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			#if defined(GL_UNPACK_ROW_LENGTH)
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			#endif
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTXTG->GetWidth(), mTXTG->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.get());

			TotkToolkit::Rendering::TextureCompression::Load(texId, GL_TEXTURE_2D, surface->GetWidth(), surface->GetHeight(), 0, mTXTG->GetFormat(), data, dataSize);
			
			mMips.push_back((ImTextureID)texId);

			//if (GLAD_GL_EXT_texture_compression_s3tc) {
			//	GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
			//}
		}
		return true;
	}

	bool TXTG::Serialize() {
		mTXTG->SetStream(mFileHandle.GetWriteStream());
		return mTXTG->Serialize();
	}
}