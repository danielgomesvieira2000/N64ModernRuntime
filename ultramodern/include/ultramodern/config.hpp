#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <string>
#include <optional>

#include "json/json.hpp"

namespace ultramodern {
    namespace renderer {
        enum class Resolution {
            Original,      // 1x native internal resolution
            Original2x,    // 2x native
            Auto,          // match the window (integer scale)
            Native3x,      // 3x native
            Native4x,      // 4x native
            Native6x,      // 6x native
            Native8x,      // 8x native
            OptionCount
        };
        enum class WindowMode {
            Windowed,
            Fullscreen,
            OptionCount
        };
        enum class HUDRatioMode {
            Original,
            Clamp16x9,
            Full,
            OptionCount
        };
        enum class GraphicsApi {
            Auto,
            D3D12,
            Vulkan,
            Metal,
            OptionCount
        };
        enum class AspectRatio {
            Original,
            Expand,
            Manual,
            OptionCount
        };
        enum class Antialiasing {
            None,
            MSAA2X,
            MSAA4X,
            MSAA8X,
            OptionCount
        };
        enum class RefreshRate {
            Original,
            Display,
            Manual,
            OptionCount
        };
        enum class HighPrecisionFramebuffer {
            Auto,
            On,
            Off,
            OptionCount
        };
        // BAR seam fix (TODO #2B): N64 VI "divot" filter that fills 1px cracks between polygons.
        // Auto = follow the game's VI divotEnable bit (on for BAR's LAN1 mode).
        enum class DivotFilter {
            Auto,
            On,
            Off,
            OptionCount
        };
        // BAR letterbox control: how the 4:3 image is fit to a window of a different aspect ratio.
        //   Pillarbox = keep aspect + black bars (default; only visible when the window isn't 4:3).
        //   Crop      = keep aspect, fill the window, crop the overflow (removes the left/right pillars).
        //   Stretch   = fill the window, distort to its aspect.
        // Pairs with ar_option=Expand (widen 3D FOV) so Crop/Stretch show more scene instead of just zooming.
        enum class PresentFillMode {
            Pillarbox,
            Crop,
            Stretch,
            OptionCount
        };
        enum class PresentationMode {
            Console,
            SkipBuffering,
            PresentEarly
        };

        class GraphicsConfig {
        public:
            bool developer_mode;
            Resolution res_option;
            WindowMode wm_option;
            HUDRatioMode hr_option;
            GraphicsApi api_option;
            AspectRatio ar_option;
            Antialiasing msaa_option;
            RefreshRate rr_option;
            HighPrecisionFramebuffer hpfb_option;
            int rr_manual_value;
            int ds_option;
            DivotFilter divot_option;
            PresentFillMode pfm_option;   // BAR: window-fit mode (pillarbox/crop/stretch) for the final present

            virtual ~GraphicsConfig() = default;

            auto operator<=>(const GraphicsConfig& rhs) const = default;
        };

        const GraphicsConfig& get_graphics_config();
        void set_graphics_config(const GraphicsConfig& new_config);

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::Resolution, {
            {ultramodern::renderer::Resolution::Original, "Original"},
            {ultramodern::renderer::Resolution::Original2x, "Original2x"},
            {ultramodern::renderer::Resolution::Auto, "Auto"},
            {ultramodern::renderer::Resolution::Native3x, "Native3x"},
            {ultramodern::renderer::Resolution::Native4x, "Native4x"},
            {ultramodern::renderer::Resolution::Native6x, "Native6x"},
            {ultramodern::renderer::Resolution::Native8x, "Native8x"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::WindowMode, {
            {ultramodern::renderer::WindowMode::Windowed, "Windowed"},
            {ultramodern::renderer::WindowMode::Fullscreen, "Fullscreen"}
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::HUDRatioMode, {
            {ultramodern::renderer::HUDRatioMode::Original, "Original"},
            {ultramodern::renderer::HUDRatioMode::Clamp16x9, "Clamp16x9"},
            {ultramodern::renderer::HUDRatioMode::Full, "Full"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::GraphicsApi, {
            {ultramodern::renderer::GraphicsApi::Auto, "Auto"},
            {ultramodern::renderer::GraphicsApi::D3D12, "D3D12"},
            {ultramodern::renderer::GraphicsApi::Vulkan, "Vulkan"},
            {ultramodern::renderer::GraphicsApi::Metal, "Metal"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::AspectRatio, {
            {ultramodern::renderer::AspectRatio::Original, "Original"},
            {ultramodern::renderer::AspectRatio::Expand, "Expand"},
            {ultramodern::renderer::AspectRatio::Manual, "Manual"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::Antialiasing, {
            {ultramodern::renderer::Antialiasing::None, "None"},
            {ultramodern::renderer::Antialiasing::MSAA2X, "MSAA2X"},
            {ultramodern::renderer::Antialiasing::MSAA4X, "MSAA4X"},
            {ultramodern::renderer::Antialiasing::MSAA8X, "MSAA8X"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::RefreshRate, {
            {ultramodern::renderer::RefreshRate::Original, "Original"},
            {ultramodern::renderer::RefreshRate::Display, "Display"},
            {ultramodern::renderer::RefreshRate::Manual, "Manual"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::HighPrecisionFramebuffer, {
            {ultramodern::renderer::HighPrecisionFramebuffer::Auto, "Auto"},
            {ultramodern::renderer::HighPrecisionFramebuffer::On, "On"},
            {ultramodern::renderer::HighPrecisionFramebuffer::Off, "Off"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::DivotFilter, {
            {ultramodern::renderer::DivotFilter::Auto, "Auto"},
            {ultramodern::renderer::DivotFilter::On, "On"},
            {ultramodern::renderer::DivotFilter::Off, "Off"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::PresentFillMode, {
            {ultramodern::renderer::PresentFillMode::Pillarbox, "Pillarbox"},
            {ultramodern::renderer::PresentFillMode::Crop, "Crop"},
            {ultramodern::renderer::PresentFillMode::Stretch, "Stretch"},
        });
    }
}

#endif
