#include "transformation3d.h"
#include <math.h>
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

void Transformation3D::initCameraTransform(const QVector3D &target, const QVector3D &up)
{
    QVector3D n = target;
    n.normalize();
    QVector3D u = up;
    u = QVector3D::crossProduct(u, n);
    u.normalize();
    QVector3D v = QVector3D::crossProduct(n, u);

    camera_rotate_trans.setRow(0, QVector4D(u.x(), u.y(), u.z(), 0.0f));
    camera_rotate_trans.setRow(1, QVector4D(v.x(), v.y(), v.z(), 0.0f));
    camera_rotate_trans.setRow(2, QVector4D(n.x(), n.y(), n.z(), 0.0f));
    camera_rotate_trans.setRow(3, QVector4D(0.0f, 0.0f, 0.0f, 1.0f));
}

void Transformation3D::setPerspectiveProj(const perspective_t proj)
{
    m_dirty = true;
    m_pers_proj = proj;
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

        //object transformations matrixes
        m_world.translate(m_translation);
        m_world.rotate(m_rotation);
        m_world.scale(m_scale);


        //camera transformation matrixes
        camera_translation_trans.setToIdentity();
        camera_translation_trans.translate(-m_camera.pos().x(), -m_camera.target().y(), -m_camera.pos().z());
        initCameraTransform(m_camera.target(), m_camera.up());

        //perspective translation
        QMatrix4x4 tmp;
        tmp.setToIdentity();
        tmp.perspective(m_pers_proj.fov, m_pers_proj.ar, m_pers_proj.z_near, m_pers_proj.z_far);
        m_world = tmp * camera_rotate_trans * camera_translation_trans * m_world;
    }

    return m_world;
}
