#include <TotkToolkit/UI/Windows/Editors/TXTG.h>

#include <imgui.h>
#include <glad/glad.h>

namespace TotkToolkit::UI::Windows::Editors {
	TXTG::TXTG(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open) : TotkToolkit::UI::Windows::Editors::Texture(fileHandle, name, open) {
		
	}

	bool TXTG::Parse() {
		mTXTG = Formats::Resources::TXTG::TXTG::Factory(mFileHandle.GetReadStream());
		if (mTXTG == nullptr)
			return false;

		std::shared_ptr<Formats::Resources::TXTG::Surface> surface = mTXTG->GetSurface(0, 0);
		std::shared_ptr<F_U8[]> data = surface->GetData();

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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTXTG->GetWidth(), mTXTG->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, data.get());

		mTextureID = (ImTextureID)texId;

		return true;
	}

	bool TXTG::Serialize() {
		mTXTG->SetStream(mFileHandle.GetWriteStream());
		return mTXTG->Serialize();
	}
}