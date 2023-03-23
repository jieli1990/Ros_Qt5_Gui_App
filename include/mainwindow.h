#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDateTime>
#include <QMainWindow>

#include "QTimer"
#include "dashboard.h"
#include "rclcomm.h"
#include "roboGLWidget.h"
#include "roboImg.h"
#include "roboItem.h"
#include "ui_mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  rclcomm *commNode;
 public slots:
  void onRecvData(QString);
  void updateRobotPose(RobotPose pose);
  void updateOdomInfo(RobotState);
 private:
  void initUi();
  void closeEvent(QCloseEvent *event);  // Overloaded function
  void setCurrentMenu(QPushButton *cur_btn);
void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
 private:
  Ui::MainWindowDesign *ui;
    QPoint pLast;
  bool m_bPressed;
  QPoint clickPos;
  bool m_bresize = false;
  QGraphicsScene *m_qGraphicScene = nullptr;
  roboItem *m_roboItem = nullptr;
  roboImg *m_roboImg = nullptr;
  DashBoard *m_speedDashBoard;
  QTimer *m_timerCurrentTime;
  roboGLWidget *m_roboGLWidget;
};
#endif  // MAINWINDOW_H
