#include "imgui.h"
#include "imgui_notify.h"


namespace ImNotify
{
    static void ShowDemoWindow(bool* p_open = NULL)
    {
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");

        // Demonstrate the various window flags. Typically you would just use the default!
        static bool no_titlebar = false;
        static bool no_scrollbar = false;
        static bool no_menu = true;
        static bool no_move = false;
        static bool no_resize = false;
        static bool no_collapse = false;
        static bool no_close = false;
        static bool no_nav = false;
        static bool no_background = false;
        static bool no_bring_to_front = false;
        static bool no_docking = false;
        static bool unsaved_document = false;

        ImGuiWindowFlags window_flags = 0;
        if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
        if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
        if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
        if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
        if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
        if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
        if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
        if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
        if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;
        if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
        if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

        // We specify a default position/size in case there's no data in the .ini file.
        // We only do it to make the demo applications a little more welcoming, but typically this isn't required.
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

        // Main body of the Demo window starts here.
        ImGui::Begin("ImNotify Demo", p_open, window_flags);

		ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

		ImGui::Text("ImNotify says hello. (0.3)");

		if (ImGui::CollapsingHeader("Examples without title", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::Button("Success"))
			{
				ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Hello World! This is a success! %s", "We can also format here:)" });
			}

			ImGui::SameLine();
			if (ImGui::Button("Warning"))
			{
				ImGui::InsertNotification({ ImGuiToastType_Warning, 3000, "Hello World! This is a warning!" });
			}

			ImGui::SameLine();
			if (ImGui::Button("Error"))
			{
				ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Hello World! This is an error!" });
			}

			ImGui::SameLine();
			if (ImGui::Button("Info"))
			{
				ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "Hello World! This is an info!" });
			}

			ImGui::SameLine();
			if (ImGui::Button("Info long"))
			{
				ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation" });
			}
		}

		if (ImGui::CollapsingHeader("Do it yourself", ImGuiTreeNodeFlags_DefaultOpen))
		{
			static char title[4096] = "A wonderful quote!";
			ImGui::InputTextMultiline("Title", title, sizeof(title));

			static char content[4096] = "Ours is a friendship forged once in this life, and again in the next. Goodbye, my brother. \n- Dembe Zuma";
			ImGui::InputTextMultiline("Content", content, sizeof(content));

			static int duration = 5000; // 5 seconds
			ImGui::InputInt("Duration (ms)", &duration, 100);
			if (duration < 0) duration = 0; // Shouldn't be negative

			static char* type_str[] = { "None", "Success", "Warning", "Error", "Info" };
			static ImGuiToastType type = ImGuiToastType_Success;
			IM_ASSERT(type < ImGuiToastType_COUNT);

			if (ImGui::BeginCombo("Type", type_str[type]))
			{
				for (auto n = 0; n < IM_ARRAYSIZE(type_str); n++)
				{
					const bool is_selected = (type == n);

					if (ImGui::Selectable(type_str[n], is_selected))
						type = n;

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			static bool enable_title = true, enable_content = true;
			ImGui::Checkbox("Enable title", &enable_title);
			ImGui::SameLine();
			ImGui::Checkbox("Enable content", &enable_content);

			if (ImGui::Button("Show"))
			{
				ImGuiToast toast(type, duration);

				if (enable_title)
					toast.set_title(title);

				if (enable_content)
					toast.set_content(content);

				ImGui::InsertNotification(toast);
			}
		}

        ImGui::End();
    };
}
