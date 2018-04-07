#include "camera.h"
#include <QKeyEvent>


bool Camera::OnKeyboard(int key)
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
