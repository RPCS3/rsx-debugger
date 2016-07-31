#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <fstream>
#include "state.h"
#include <cereal/archives/binary.hpp>
#include <Emu/RSX/rsx_trace.h>
#include <algorithm>

QList<QObject*> load_command_trace()
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
        size_t index_list_size = draw_state.index.size();
        switch (draw_state.state.index_type())
        {
        case rsx::index_array_type::u16:
            for (size_t i = 0; i < index_list_size / 2; i++)
            {
                const u16* ptr = reinterpret_cast<const u16*>(draw_state.index.data());
                tmp->_index_list.append(QVariant::fromValue(ptr[i]));
            }
            break;
        case rsx::index_array_type::u32:
            for (size_t i = 0; i < index_list_size / 4; i++)
            {
                const u32* ptr = reinterpret_cast<const u32*>(draw_state.index.data());
                tmp->_index_list.append(QVariant::fromValue(ptr[i]));
            }
            break;
        }
        st.append(tmp);
    }

    return st;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();
    QList<QObject*> st = load_command_trace();
    ctx->setContextProperty("stateList", QVariant::fromValue(st));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    return app.exec();
}
