#ifndef TRANSFORMATION3D_H
#define TRANSFORMATION3D_H

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

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


    // Accessors
    const QVector3D& translation() const;
    const QQuaternion& rotation() const;
    const QVector3D& scale() const;
    const QMatrix4x4& toMatrix();
private:
    bool m_dirty;
    QVector3D m_translation;
    QVector3D m_scale;
    QQuaternion m_rotation;
    QMatrix4x4 m_world;
};
Q_DECLARE_TYPEINFO(Transformation3D, Q_MOVABLE_TYPE);

inline Transformation3D::Transformation3D() : m_dirty(true) {}
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

// Accessors
inline const QVector3D& Transformation3D::translation() const { return m_translation; }
inline const QQuaternion& Transformation3D::rotation() const { return m_rotation; }
inline const QVector3D& Transformation3D::scale() const { return m_scale; }
#endif // TRANSFORMATION3D_H
