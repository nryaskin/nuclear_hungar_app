#include "camera.h"
#include <QKeyEvent>
#include <QMatrix4x4>

Camera::Camera(int windowWidth, int windowHeight, const QVector3D &pos, const QVector3D &target, const QVector3D &up)
{
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    m_pos = pos;

    m_target = target;
    m_target.normalize();

    m_up = up;
    m_up.normalize();

    init();
}

Camera::Camera(int windowWidth, int windowHeight) : Camera(windowWidth, windowHeight, QVector3D(1.0f, 1.0f, -3.0f), QVector3D(0.45f, 0.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f))
{
}

float Camera::toDegree(float rad)
{
    float res = 0.0f;
    res = (rad * 180.0f) / M_PI;
    return res;
}

bool Camera::onKeyboard(int key)
{
    bool ret = false;

        switch (key) {

        case Qt::Key_Up:
        {
            m_pos += (m_target * step_size);
            ret = true;
        }
        break;

        case Qt::Key_Down:
        {
            m_pos -= (m_target * step_size);
            ret = true;
        }
        break;

        case Qt::Key_Left:
        {
            QVector3D left = m_target.crossProduct(m_target, m_up);
            left.normalize();
            left *= step_size;
            m_pos += left;
            ret = true;
        }
        break;

        case Qt::Key_Right:
        {
            QVector3D right = m_up.crossProduct(m_up, m_target);
            right.normalize();
            right *= step_size;
            m_pos += right;
            ret = true;
        }
        break;
        }

        return ret;
}

void Camera::onMouseMove(int x, int y)
{
    const int DeltaX = x - m_mousePos.x();
    const int DeltaY = y - m_mousePos.y();

    m_mousePos.setX(x);
    m_mousePos.setY(y);

    m_AngleH += (float)DeltaX / 20.0f;
    m_AngleV += (float)DeltaY / 20.0f;

    if (DeltaX == 0) {
           if (x <= MARGIN) {
               m_OnLeftEdge = true;
           }
           else if (x >= (m_windowWidth - MARGIN)) {
               m_OnRightEdge = true;
           }
       }
    else {
           m_OnLeftEdge = false;
           m_OnRightEdge = false;
       }

    if (DeltaY == 0) {
           if (y <= MARGIN) {
               m_OnUpperEdge = true;
           }
           else if (y >= (m_windowHeight - MARGIN)) {
               m_OnLowerEdge = true;
           }
       }
    else {
           m_OnUpperEdge = false;
           m_OnLowerEdge = false;
       }
    update();
}

void Camera::init(){
    QVector3D hTarget(m_target.x(), 0.0, m_target.z());
        hTarget.normalize();

        if (hTarget.z() >= 0.0f)
        {
            if (hTarget.x() >= 0.0f)
            {
                m_AngleH = 360.0f - toDegree(asin(hTarget.z()));
            }
            else
            {
                m_AngleH = 180.0f + toDegree(asin(hTarget.z()));
            }
        }
        else
        {
            if (hTarget.x() >= 0.0f)
            {
                m_AngleH = toDegree(asin(-hTarget.z()));
            }
            else
            {
                m_AngleH = 180.0f - toDegree(asin(-hTarget.z()));
            }
        }

        m_AngleV = -toDegree(asin(m_target.y()));

        m_OnUpperEdge = false;
        m_OnLowerEdge = false;
        m_OnLeftEdge = false;
        m_OnRightEdge = false;
        m_mousePos.setX(m_windowWidth / 2);
        m_mousePos.setY(m_windowHeight / 2);
}

void Camera::update()
{
    const QVector3D vaxis(0.0f, 1.0f, 0.0f);

    // Rotate the view vector by the horizontal angle around the vertical axis
    QVector3D view(1.0f, 0.0f, 0.0f);
    QMatrix4x4 m_H;
    m_H.setToIdentity();
    m_H.rotate(m_AngleH, vaxis);
    view = m_H * view;
    view.normalize();

    // Rotate the view vector by the vertical angle around the horizontal axis
    QVector3D haxis = vaxis.crossProduct(vaxis, view);
    haxis.normalize();
    QMatrix4x4 m_V;
    m_V.setToIdentity();
    m_V.rotate(m_AngleV, haxis);
    view = m_V * view;
    view.normalize();

    m_target = view;
    m_target.normalize();

    m_up = m_target.crossProduct(m_target, haxis);
    m_up.normalize();
}

void Camera::onRender()
{
    bool shouldUpdate = false;

       if (m_OnLeftEdge) {
           m_AngleH -= 0.1f;
           shouldUpdate = true;
       }
       else if (m_OnRightEdge) {
           m_AngleH += 0.1f;
           shouldUpdate = true;
       }

       if (m_OnUpperEdge) {
           if (m_AngleV > -90.0f) {
               m_AngleV -= 0.1f;
               shouldUpdate = true;
           }
       }
       else if (m_OnLowerEdge) {
           if (m_AngleV < 90.0f) {
               m_AngleV += 0.1f;
               shouldUpdate = true;
           }
       }

       if (shouldUpdate) {
           update();
       }
}
