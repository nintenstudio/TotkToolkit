#pragma once

#include <imgui.h>

namespace TotkToolkit::UI::ImGuiUtil {
	void TextCentered(const char* fmt, float min, float max) {
		float availWidth = max - min;

		float textWidth = ImGui::CalcTextSize(fmt).x;
		ImGui::SetCursorPosX(((availWidth - textWidth) * 0.5f) + min);

		ImGui::Text(fmt);
	}

	void TextCenteredWrapped(const char* fmt, float min, float max) {
		char* line = new char[strlen(fmt) + 1];
		memset(line, '\0', strlen(fmt) + 1);
		unsigned int lineIndex = 0;
		for (unsigned int i = 0; fmt[i] != '\0';) {
			line[lineIndex] = fmt[i];
			if (ImGui::CalcTextSize(line).x > (max - min)) {
				line[lineIndex] = '\0';
				TextCentered(line, min, max);
				memset(line, '\0', strlen(fmt) + 1);
				lineIndex = 0;
			}
			else {
				lineIndex++;
				i++;
			}
		}
		if (lineIndex != 0) {
			line[lineIndex] = '\0';
			TextCentered(line, min, max);
		}

		delete[] line;
	}
}