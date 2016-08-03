#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <fstream>
#include "state.h"
#include <cereal/archives/binary.hpp>
#include <Emu/RSX/rsx_trace.h>
#include <algorithm>
//#include <Emu/RSX/Common/BufferUtils.h>
#include <Emu/RSX/gcm_printing.h>


namespace
{
template<typename T>
void fill_variant_vector(std::vector<gsl::byte> values,
                         const rsx::frame_capture_data::draw_state &draw_state,
                         QList<QVariant> &lst)
{
    return;
    /*
    std::vector<gsl::byte> readable_index(values.size());
    write_index_array_data_to_buffer(readable_index, values,
        draw_state.state.index_type(), rsx::primitive_type::triangles, false, -1, {{0, values.size() / sizeof(T)}},
        [](auto) { return false; });
    gsl::span<T> casted_readable_index = {reinterpret_cast<T*>(values.data()), gsl::narrow<int>(values.size() / sizeof(T))};
    std::for_each(casted_readable_index.begin(), casted_readable_index.end(),
                  [&lst](auto v) {lst.append(QVariant::fromValue(v));});*/
}
}

std::tuple<QList<QObject*>, QStringList> load_command_trace()
{
    // Unfortunatly QTextStream isn't compatible with std::iostream
    std::fstream f("../bin/capture.txt", std::ios::in | std::ios::binary);

    cereal::BinaryInputArchive archive(f);
    rsx::frame_capture_data frame_debug;
    archive(frame_debug);

    QList<QObject*> st;
    for (const rsx::frame_capture_data::draw_state &draw_state : frame_debug.draw_calls)
    {
        auto *tmp = new qt_rsx_state;
        *tmp = draw_state.state;
        tmp->_name = QString::fromStdString(draw_state.name);
        tmp->_transform_program = QString::fromStdString(draw_state.programs.first);
        tmp->_shader_program = QString::fromStdString(draw_state.programs.second);

        switch (draw_state.state.index_type())
        {
        case rsx::index_array_type::u16:
            fill_variant_vector<u16>(draw_state.index, draw_state, tmp->_index_list);
            break;
        case rsx::index_array_type::u32:
            fill_variant_vector<u32>(draw_state.index, draw_state, tmp->_index_list);
            break;
        }

        st.append(tmp);
    }
    QStringList commands;
    std::transform(frame_debug.command_queue.begin(), frame_debug.command_queue.end(),
                   std::back_inserter(commands),
                   [](const std::pair<u32, u32> pair){ return QString::fromStdString(rsx::get_pretty_printing_function(pair.first)(pair.second));});
    return std::make_tuple(st, commands);
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();
    std::tuple<QList<QObject*>, QStringList > st = load_command_trace();
    ctx->setContextProperty("commandList", std::get<1>(st));
    ctx->setContextProperty("stateList", QVariant::fromValue(std::get<0>(st)));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    return app.exec();
}
