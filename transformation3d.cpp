#include "transformation3d.h"

void Transformation3D::translate(const QVector3D &dt)
{
    m_dirty = true;
    m_translation += dt;
}

void Transformation3D::rotate(const QQuaternion &dr)
{
    m_dirty = true;
    m_rotation *= dr;
}

void Transformation3D::scale(const QVector3D &ds)
{
   m_dirty = true;
   m_scale *= ds;
}

void Transformation3D::grow(const QVector3D &ds)
{
    m_dirty = true;
    m_scale += ds;
}

void Transformation3D::setTranslation(const QVector3D &t)
{
    m_dirty = true;
    m_translation = t;
}

void Transformation3D::setRotation(const QQuaternion &dr)
{
    m_dirty = true;
    m_rotation = dr;
}

void Transformation3D::setScale(const QVector3D &s)
{
    m_dirty = true;
    m_scale = s;
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
