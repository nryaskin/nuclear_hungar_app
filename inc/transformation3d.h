#ifndef TRANSFORMATION3D_H
#define TRANSFORMATION3D_H

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include "projection_util.h"
#include "camera.h"

class Transformation3D
{
public:
    Transformation3D();

    // Transform By (Add/Scale)
    void translate(const QVector3D &dt);
    void translate(float dx, float dy, float dz);
    void rotate(const QQuaternion &dr);
    void rotate(float angle, const QVector3D &axis);
    void rotate (float angle, float ax, float ay, float az);
    void scale(const QVector3D &ds);
    void scale(float dx, float dy, float dz);
    void scale(float factor);
    void grow(const QVector3D &ds);
    void grow(float dx, float dy, float dz);
    void grow(float factor);

    // Transform To (Setters)
    void setTranslation(const QVector3D &t);
    void setTranslation(float x, float y, float z);
    void setRotation(const QQuaternion &dr);
    void setRotation(float angle, const QVector3D &axis);
    void setRotation(float angle, float ax, float ay, float az);
    void setScale(const QVector3D &s);
    void setScale(float x, float y, float z);
    void setScale(float k);

    //Perspective proj
    void setPerspectiveProj(float angle, float width, float height, float znear, float zfar);
    void setPerspectiveProj(perspective_t pers);

    //camera classes
    void initCameraTransform(const QVector3D &target, const QVector3D &up);
    void setCamera(const Camera &camera);

    // Accessors
    const QVector3D& translation() const;
    const QQuaternion& rotation() const;
    const QVector3D& scale() const;
    Camera& camera();
    const QMatrix4x4& toMatrix();
private:
    bool m_dirty;
    QVector3D m_translation;
    QVector3D m_scale;
    QQuaternion m_rotation;
    QMatrix4x4 m_world;
    QMatrix4x4 camera_translation_trans;
    QMatrix4x4 camera_rotate_trans;
    Camera m_camera;
    perspective_t m_pers_proj;
};
Q_DECLARE_TYPEINFO(Transformation3D, Q_MOVABLE_TYPE);

inline Transformation3D::Transformation3D() : m_dirty(true), m_scale(1.0f, 1.0f, 1.0f), m_camera(800, 600) {camera_translation_trans.setToIdentity(); camera_translation_trans.setToIdentity();}
// Transform By (Add/Scale)
inline void Transformation3D::translate(float dx, float dy,float dz) { translate(QVector3D(dx, dy, dz)); }
inline void Transformation3D::rotate(float angle, const QVector3D &axis) { rotate(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Transformation3D::rotate(float angle, float ax, float ay,float az) { rotate(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }
inline void Transformation3D::scale(float dx, float dy,float dz) { scale(QVector3D(dx, dy, dz)); }
inline void Transformation3D::scale(float factor) { scale(QVector3D(factor, factor, factor)); }
inline void Transformation3D::grow(float dx, float dy, float dz) { grow(QVector3D(dx, dy, dz)); }
inline void Transformation3D::grow(float factor) { grow(QVector3D(factor, factor, factor)); }

// Transform To (Setters)
inline void Transformation3D::setTranslation(float x, float y, float z) { setTranslation(QVector3D(x, y, z)); }
inline void Transformation3D::setRotation(float angle, const QVector3D &axis) { setRotation(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Transformation3D::setRotation(float angle, float ax, float ay, float az) { setRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }
inline void Transformation3D::setScale(float x, float y, float z) { setScale(QVector3D(x, y, z)); }
inline void Transformation3D::setScale(float k) { setScale(QVector3D(k, k, k)); }
inline void Transformation3D::setPerspectiveProj(float angle, float width, float height, float znear, float zfar) {setPerspectiveProj(perspective_t{angle, width/height, znear, zfar});}
inline void Transformation3D::setCamera(const Camera &camera) { m_camera = camera;}
// Accessors
inline const QVector3D& Transformation3D::translation() const { return m_translation; }
inline const QQuaternion& Transformation3D::rotation() const { return m_rotation; }
inline const QVector3D& Transformation3D::scale() const { return m_scale; }
inline Camera &Transformation3D::camera() { return m_camera;}
#endif // TRANSFORMATION3D_H
