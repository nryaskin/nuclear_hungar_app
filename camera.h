#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>

class Camera {

public:
    Q_DECL_CONSTEXPR Camera();
    Q_DECL_CONSTEXPR Camera(const QVector3D& pos, const QVector3D& target, const QVector3D& up);
    bool OnKeyboard(int key);

    void setPos(const QVector3D &pos);
    void setTarget(const QVector3D &target);
    void setUp(const QVector3D &up);

    Q_DECL_CONSTEXPR const QVector3D& pos() const;
    Q_DECL_CONSTEXPR const QVector3D& target() const;
    Q_DECL_CONSTEXPR const QVector3D& up() const;

    static const int step_size = 1;


private:
    QVector3D m_pos;
    QVector3D m_target;
    QVector3D m_up;
};

Q_DECL_CONSTEXPR inline Camera::Camera() {}
Q_DECL_CONSTEXPR inline Camera::Camera(const QVector3D &pos, const QVector3D &target, const QVector3D &up) : m_pos(pos), m_target(target), m_up(up) {}

Q_DECL_CONSTEXPR inline const QVector3D& Camera::pos() const {return m_pos;}
Q_DECL_CONSTEXPR inline const QVector3D& Camera::target() const {return m_target;}
Q_DECL_CONSTEXPR inline const QVector3D& Camera::up() const {return m_up;}
void inline Camera::setPos(const QVector3D &pos) {m_pos = pos;}
void inline Camera::setTarget(const QVector3D &target) {m_target = target;}
void inline Camera::setUp(const QVector3D &up) {m_up = up;}

#endif // CAMERA_H
