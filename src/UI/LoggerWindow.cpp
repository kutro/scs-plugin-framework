#include "SPF/UI/LoggerWindow.hpp"

#include <imgui.h>

#include "SPF/Events/EventDispatcher.hpp"
#include "SPF/Logger/Logger.hpp"

SPF_NS_BEGIN

namespace
{
class ImGuiLogger : public Logger
{
private:
    ImGuiTextBuffer _buf;
    ImGuiTextFilter _filter;
    ImVector<int> _lineOffsets; // Index to lines offset
    bool _autoScroll;

public:
    ImGuiLogger() : _autoScroll(true)
    {
    }

    void log(Level level, const std::string& message) override
    {
        int old_size = _buf.size();
        _buf.appendf("[%s] %s\n", level == Level::Info ? "info" : (level == Level::Warning ? "warn" : "error"), message.c_str());
        for (int new_size = _buf.size(); old_size < new_size; old_size++)
            if (_buf[old_size] == '\n')
                _lineOffsets.push_back(old_size);
    }

    void imguiRender()
    {
        if (ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar))
        {
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::Selectable("Clear")) _buf.clear();
                ImGui::EndPopup();
            }

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            const char* buf = _buf.begin();
            const char* buf_end = _buf.end();
            if (_filter.IsActive())
            {
                for (int i = 0; i < _lineOffsets.Size; i++)
                {
                    const char* line_start = buf + _lineOffsets[i];
                    const char* line_end = (i + 1 < _lineOffsets.Size) ? (buf + _lineOffsets[i + 1] - 1) : buf_end;
                    if (_filter.PassFilter(line_start, line_end))
                    {
                        ImGui::TextUnformatted(line_start, line_end);
                    }
                }
            }
            else
            {
                ImGuiListClipper clipper;
                clipper.Begin(_lineOffsets.Size);
                while (clipper.Step())
                {
                    for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                    {
                        const char* line_start = buf + _lineOffsets[i];
                        const char* line_end = (i + 1 < _lineOffsets.Size) ? (buf + _lineOffsets[i + 1] - 1) : buf_end;
                        ImGui::TextUnformatted(line_start, line_end);
                    }
                }
                clipper.End();
            }
            ImGui::PopStyleVar();

            if (_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);
        }
        ImGui::EndChild();
    }
};

static ImGuiLogger g_ImGuiLogger;

} // namespace

LoggerWindow::LoggerWindow(EventDispatcher& eventMgr)
    : _eventMgr(eventMgr)
{
    // Connect ImGuiLogger to EventDispatcher's log signal
    // This assumes EventDispatcher has a log signal, which it doesn't yet.
    // We will add this later when we implement LoggerFactory fully.
}

void LoggerWindow::imguiRender()
{
    if (!_isEnabled) return;

    ImGui::SetNextWindowBgAlpha(_opacity);
    ImGui::SetNextWindowSize({ 400, 300 }, ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Log", &_isEnabled))
    {
        g_ImGuiLogger.imguiRender();
    }
    ImGui::End();
}

void LoggerWindow::setEnabled(bool enabled)
{
    _isEnabled = enabled;
}

void LoggerWindow::setOpacity(float opacity)
{
    _opacity = opacity;
}

    SPF_NS_END
