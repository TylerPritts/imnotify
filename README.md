# Imnotify
[![GitHub all releases](https://img.shields.io/github/downloads/TylerPritts/imnotify/total)](https://github.com/TylerPritts/imnotify/releases)
[![GitHub release (with filter)](https://img.shields.io/github/v/release/TylerPritts/imnotify)](https://github.com/TylerPritts/imnotify/releases/latest)
![GitHub](https://img.shields.io/github/license/TylerPritts/imnotify?color=blue)


This is a header-only wrapper made to create notifications with [Dear ImGui](https://github.com/ocornut/imgui). We will use [Font Awesome 5](https://fontawesome.com/) for icons.
<br>All credit goes to [patrickcjk/imgui-notify](https://github.com/patrickcjk/imgui-notify) as they created the original and this is an augmentation of theirs.



## Requirements
- You must use a font other than the default one. Font-Awesome icons used in this library cannot be merged with default font. You can use Tahoma (provided in the example project).
- If you load the font using AddFontFromMemoryTTF (from memory, instead of from a file on disk) and memory is read-only as in the example, you must pass a ImFontConfig structure with FontDataOwnedByAtlas = false to prevent imgui from attempting to free the buffer (which will lead into a crash).

## Usage
### Include
```c++
#include "imgui_notify.h"
#include "tahoma.h" // <-- Required font!
```
### Initialisation (after impl call, e.g ImGui_ImplDX12_Init)
```c++
ImGuiIO* io = &ImGui::GetIO();

ImFontConfig font_cfg;
font_cfg.FontDataOwnedByAtlas = false;
io.Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &font_cfg);

// Initialize notify
ImNotify::MergeIconsWithLatestFont(16.f, false);

// If you use multiple fonts, repeat the same thing!
// io.Fonts->AddFontFromMemoryTTF((void*)another_font, sizeof(another_font), 17.f, &font_cfg);
// ImNotify::MergeIconsWithLatestFont(16.f, false);
```
### Create notifications
```c++
// A few examples... (no title provided, default one used!)
ImNotify::InsertNotification({ ImGuiToastType_Success, 3000, "Hello World! This is a success! %s", "We can also format here:)" });
ImNotify::InsertNotification({ ImGuiToastType_Warning, 3000, "Hello World! This is a warning! %d", 0x1337 });
ImNotify::InsertNotification({ ImGuiToastType_Error, 3000, "Hello World! This is an error! 0x%X", 0xDEADBEEF });
ImNotify::InsertNotification({ ImGuiToastType_Info, 3000, "Hello World! This is an info!" });
ImNotify::InsertNotification({ ImGuiToastType_Info, 3000, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation" });

// Now using a custom title...
ImGuiToast toast(ImGuiToastType_Success, 3000); // <-- content can also be passed here as above
toast.set_title("This is a %s title", "wonderful");
toast.set_content("Lorem ipsum dolor sit amet");
ImNotify::InsertNotification(toast);
```
### Rendering
```c++
// Render toasts on top of everything, at the end of your code!
// You should push style vars here
ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f); // Round borders
ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f)); // Background color
ImNotify::RenderNotifications(); // <-- Here we render all notifications
ImGui::PopStyleVar(1); // Don't forget to Pop()
ImGui::PopStyleColor(1);
```

## Showcase
![Showcase](https://i.imgur.com/ckcpOHJ.gif)
