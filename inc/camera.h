#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QVector2D>
#include <QQuaternion>
#include <math.h>

class Camera {

public:
    Camera(int windowWidth, int windowHeight);
    Camera(int windowWidth, int windowHeight, const QVector3D& pos, const QVector3D& target, const QVector3D& up);
    bool onKeyboard(int key);
    void onMouseMove(int x, int y);

    void init();
    void update();
    void onRender();



    void setPos(const QVector3D &pos);
    void setTarget(const QVector3D &target);
    void setUp(const QVector3D &up);
    void setWindowWidth(const int width);
    void setWindowHeight(const int height);

    const QVector3D& pos() const;
    const QVector3D& target() const;
    const QVector3D& up() const;
    QVector2D& mousePos();
    int windowWidth();
    int windowHeight();

    static const int step_size = 1000;
    static const int MARGIN = 10;

private:
    float toDegree(float rad);

    QVector3D m_pos;
    QVector3D m_target;
    QVector3D m_up;
    int m_windowWidth;
    int m_windowHeight;

    //mouse elements
    float m_AngleH;
    float m_AngleV;
    bool m_OnUpperEdge;
    bool m_OnLowerEdge;
    bool m_OnLeftEdge;
    bool m_OnRightEdge;
    QVector2D m_mousePos;
};

inline const QVector3D& Camera::pos() const {return m_pos;}
inline const QVector3D& Camera::target() const {return m_target;}
inline const QVector3D& Camera::up() const {return m_up;}
inline QVector2D &Camera::mousePos() {return m_mousePos;}
inline int Camera::windowWidth() {return m_windowWidth;}
inline int Camera::windowHeight() {return m_windowHeight;}

void inline Camera::setPos(const QVector3D &pos) {m_pos = pos;}
void inline Camera::setTarget(const QVector3D &target) {m_target = target;}
void inline Camera::setUp(const QVector3D &up) {m_up = up;}
void inline Camera::setWindowWidth(const int width) { m_windowHeight = width;}
void inline Camera::setWindowHeight(const int height) {m_windowHeight = height;}

#endif // CAMERA_H
