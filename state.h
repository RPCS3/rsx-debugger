#ifndef STATE_H
#define STATE_H

#include <QAbstractListModel>
#include <Utilities/types.h>
#include <Utilities/StrFmt.h>
#include <Utilities/BEType.h>
#include <Utilities/Macro.h>
#include <Utilities/Atomic.h>
#include <unordered_map>
#include <Emu/RSX/rsx_methods.h>
#include <qdebug.h>
#include <QString>

class qt_rsx_state : public QObject, public rsx::rsx_state
{
    Q_OBJECT

    Q_PROPERTY(quint16 ViewportWidth READ viewport_width CONSTANT)
    Q_PROPERTY(quint16 ViewportHeight READ viewport_height CONSTANT)
    Q_PROPERTY(quint16 ViewportOriginX READ viewport_origin_x CONSTANT)
    Q_PROPERTY(quint16 ViewportOriginY READ viewport_origin_y CONSTANT)

    Q_PROPERTY(quint16 ScissorWidth READ scissor_width CONSTANT)
    Q_PROPERTY(quint16 ScissorHeight READ scissor_height CONSTANT)
    Q_PROPERTY(quint16 ScissorOriginX READ scissor_origin_x CONSTANT)
    Q_PROPERTY(quint16 ScissorOriginY READ scissor_origin_y CONSTANT)

    Q_PROPERTY(quint16 surfaceWidth READ getSurfaceWidth CONSTANT)
    Q_PROPERTY(quint16 surfaceHeight READ getSurfaceHeight CONSTANT)
    Q_PROPERTY(quint16 widthRole READ surface_clip_width CONSTANT)
    Q_PROPERTY(quint16 heightRole READ surface_clip_height CONSTANT)
    Q_PROPERTY(quint16 originX READ surface_clip_origin_x CONSTANT)
    Q_PROPERTY(quint16 originY READ surface_clip_origin_y CONSTANT)
    Q_PROPERTY(QString surfaceTarget READ getSurfaceTarget CONSTANT)
    Q_PROPERTY(QString surfaceColorFormat READ getSurfaceColorFormat CONSTANT)
    Q_PROPERTY(QString surfaceDepthFormat READ getSurfaceDepthStencilFormat CONSTANT)

    Q_PROPERTY(quint32 offsetA READ surface_a_offset CONSTANT)
    Q_PROPERTY(quint32 offsetB READ surface_b_offset CONSTANT)
    Q_PROPERTY(quint32 offsetC READ surface_c_offset CONSTANT)
    Q_PROPERTY(quint32 offsetD READ surface_d_offset CONSTANT)
    Q_PROPERTY(quint32 pitchA READ surface_a_pitch CONSTANT)
    Q_PROPERTY(quint32 pitchB READ surface_b_pitch CONSTANT)
    Q_PROPERTY(quint32 pitchC READ surface_c_pitch CONSTANT)
    Q_PROPERTY(quint32 pitchD READ surface_d_pitch CONSTANT)

    Q_PROPERTY(bool twoSidedLighting READ two_side_light_en CONSTANT)
    Q_PROPERTY(float fogP0 READ fog_params_0 CONSTANT)
    Q_PROPERTY(float fogP1 READ fog_params_1 CONSTANT)
    Q_PROPERTY(bool cullEnabled READ cull_face_enabled CONSTANT)
    Q_PROPERTY(bool restartIndexEnabled READ restart_index_enabled CONSTANT)
    Q_PROPERTY(quint32 restartIndex READ restart_index CONSTANT)
    Q_PROPERTY(float viewportScaleX READ viewport_scale_x CONSTANT)
    Q_PROPERTY(float viewportScaleY READ viewport_scale_y CONSTANT)
    Q_PROPERTY(float viewportScaleZ READ viewport_scale_z CONSTANT)
    Q_PROPERTY(float viewportScaleW READ viewport_scale_w CONSTANT)
    Q_PROPERTY(float viewportOffsetX READ viewport_offset_x CONSTANT)
    Q_PROPERTY(float viewportOffsetY READ viewport_offset_y CONSTANT)
    Q_PROPERTY(float viewportOffsetZ READ viewport_offset_z CONSTANT)
    Q_PROPERTY(float viewportOffsetW READ viewport_offset_w CONSTANT)
    Q_PROPERTY(quint32 vertexBaseOffset READ vertex_data_base_offset CONSTANT)
    Q_PROPERTY(quint32 vertexBaseIndex READ vertex_data_base_index CONSTANT)
    Q_PROPERTY(QVariantList indexList READ getIndexList CONSTANT)

    Q_PROPERTY(bool depthTest READ depth_test_enabled CONSTANT)
    Q_PROPERTY(QString depthFunc READ getDepthFunc CONSTANT)
    Q_PROPERTY(bool depthWrite READ depth_write_enabled CONSTANT)
    Q_PROPERTY(bool alphaTest READ alpha_test_enabled CONSTANT)
    Q_PROPERTY(QString alphaFunc READ getAlphaFunc CONSTANT)
    Q_PROPERTY(bool logicOp READ logic_op_enabled CONSTANT)
    Q_PROPERTY(QString logicFunc READ getLogicFunc CONSTANT)
    Q_PROPERTY(bool stencilTest READ stencil_test_enabled CONSTANT)
    Q_PROPERTY(bool twoSidedStencil READ two_sided_stencil_test_enabled CONSTANT)
    Q_PROPERTY(bool colorMaskA READ color_mask_a CONSTANT)
    Q_PROPERTY(bool colorMaskR READ color_mask_r CONSTANT)
    Q_PROPERTY(bool colorMaskG READ color_mask_g CONSTANT)
    Q_PROPERTY(bool colorMaskB READ color_mask_b CONSTANT)
    Q_PROPERTY(bool depthBound READ depth_bounds_test_enabled CONSTANT)
    Q_PROPERTY(bool ditherEnabled READ dither_enabled CONSTANT)
    Q_PROPERTY(bool blendEnabled READ blend_enabled CONSTANT)
    Q_PROPERTY(bool blendSurface1 READ blend_enabled_surface_1 CONSTANT)
    Q_PROPERTY(bool blendSurface2 READ blend_enabled_surface_2 CONSTANT)
    Q_PROPERTY(bool blendSurface3 READ blend_enabled_surface_3 CONSTANT)
    Q_PROPERTY(QString blendEquationRGB READ getBlendEquationRGB CONSTANT)
    Q_PROPERTY(QString blendEquationA READ getBlendEquationA CONSTANT)
    Q_PROPERTY(QString blendSFactorRGB READ getBlendSFactorRGB CONSTANT)
    Q_PROPERTY(QString blendSFactorA READ getBlendSFactorA CONSTANT)
    Q_PROPERTY(QString blendDFactorRGB READ getBlendDFactorRGB CONSTANT)
    Q_PROPERTY(QString blendDFactorA READ getBlendDFactorA CONSTANT)
    Q_PROPERTY(bool lineSmoothEnabled READ line_smooth_enabled CONSTANT)
    Q_PROPERTY(bool polySmoothEnabled READ line_smooth_enabled CONSTANT)
    Q_PROPERTY(bool polyOffsetPoint READ poly_offset_point_enabled CONSTANT)
    Q_PROPERTY(bool polyOffsetLine READ poly_offset_line_enabled CONSTANT)
    Q_PROPERTY(bool polyOffsetFill READ poly_offset_fill_enabled CONSTANT)
    Q_PROPERTY(float polyOffsetScale READ poly_offset_scale CONSTANT)
    Q_PROPERTY(float polyOffsetBias READ poly_offset_bias CONSTANT)
    Q_PROPERTY(quint16 alphaRef READ alpha_ref CONSTANT)

    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString transformProgram READ getTransformProgram CONSTANT)
    Q_PROPERTY(QString shaderProgram READ getShaderProgram CONSTANT)


public:
    QString _name;
    QString _transform_program;
    QString _shader_program;
    QVariantList _index_list;

    QString getName() const
    {
        return _name;
    }

    QString getTransformProgram() const
    {
        return _transform_program;
    }

    QString getShaderProgram() const
    {
        return _shader_program;
    }

    quint16 getSurfaceWidth() const
    {
        return 1 << surface_log2_width();
    }

    quint16 getSurfaceHeight() const
    {
        return 1 << surface_log2_height();
    }

    QVariantList getIndexList() const
    {
        return _index_list;
    }

    QString getDepthFunc() const
    {
        return QString::fromStdString(rsx::to_string(depth_func()));
    }

    QString getAlphaFunc() const
    {
        return QString::fromStdString(rsx::to_string(alpha_func()));
    }

    QString getLogicFunc() const
    {
        return QString::fromStdString(rsx::to_string(logic_operation()));
    }

    QString getBlendEquationRGB() const
    {
        return QString::fromStdString(rsx::to_string(blend_equation_rgb()));
    }

    QString getBlendEquationA() const
    {
        return QString::fromStdString(rsx::to_string(blend_equation_a()));
    }

    QString getBlendSFactorRGB() const
    {
        return QString::fromStdString(rsx::to_string(blend_func_sfactor_rgb()));
    }

    QString getBlendSFactorA() const
    {
        return QString::fromStdString(rsx::to_string(blend_func_sfactor_a()));
    }

    QString getBlendDFactorRGB() const
    {
        return QString::fromStdString(rsx::to_string(blend_func_dfactor_rgb()));
    }

    QString getBlendDFactorA() const
    {
        return QString::fromStdString(rsx::to_string(blend_func_dfactor_a()));
    }

    QString getSurfaceTarget() const
    {
        return QString::fromStdString(rsx::to_string(surface_color_target()));
    }

    QString getSurfaceColorFormat() const
    {
        return QString::fromStdString(rsx::to_string(surface_color()));
    }

    QString getSurfaceDepthStencilFormat() const
    {
        return QString::fromStdString(rsx::to_string(surface_depth_fmt()));
    }

    qt_rsx_state& operator=(const rsx::rsx_state& in)
    {
        rsx::rsx_state::operator =(in);
        return *this;
    }
};

#endif // STATE_H
