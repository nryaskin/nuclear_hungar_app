#include "transformation3d.h"

void Transformation3D::translate(const QVector3D &dt)
{
    m_dirty = true;
    m_translation += dt;
}

void Transformation3D::setTranslation(const QVector3D &t)
{
    m_dirty = true;
    m_translation = t;
}

void Transformation3D::rotate(const QQuaternion &dr)
{
    m_dirty = true;
    m_rotation *= dr;
}

void Transformation3D::setRotation(const QQuaternion &dr)
{
    m_dirty = true;
    m_rotation = dr;
}

const QMatrix4x4& Transformation3D::toMatrix()
{
    if(m_dirty)
    {
        m_dirty = false;
        m_world.setToIdentity();
        m_world.rotate(m_rotation);
    }

    return m_world;
}
