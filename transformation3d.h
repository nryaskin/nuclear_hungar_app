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


    // Transform To (Setters)
    void setTranslation(const QVector3D &t);
    void setTranslation(float x, float y, float z);

    // Accessors
    const QVector3D& translation() const;
    const QMatrix4x4& toMatrix();
private:
    bool m_dirty;
    QVector3D m_translation;

    QMatrix4x4 m_world;
};
Q_DECLARE_TYPEINFO(Transformation3D, Q_MOVABLE_TYPE);

inline Transformation3D::Transformation3D() : m_dirty(true) {}
// Transform By (Add/Scale)
inline void Transformation3D::translate(float dx, float dy,float dz) { translate(QVector3D(dx, dy, dz)); }


// Transform To (Setters)
inline void Transformation3D::setTranslation(float x, float y, float z) { setTranslation(QVector3D(x, y, z)); }

// Accessors
inline const QVector3D& Transformation3D::translation() const { return m_translation; }

#endif // TRANSFORMATION3D_H
