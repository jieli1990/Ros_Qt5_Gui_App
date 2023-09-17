/*
 * @Author: chengyang chengyangkj@outlook.com
 * @Date: 2023-04-10 15:38:40
 * @LastEditors: chengyang chengyangkj@outlook.com
 * @LastEditTime: 2023-04-20 16:44:15
 * @FilePath: ////src/display/laser_points.cpp
 * @Description:
 */
#include "display/display_path.h"
DisplayPath::DisplayPath(const std::string &display_name, const int &z_value)
    : VirtualDisplay(display_name, z_value) {}
QRectF DisplayPath::boundingRect() const { return bounding_rect_; }
void DisplayPath::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
  drawPath(painter);
}

DisplayPath::~DisplayPath() {}
bool DisplayPath::SetDisplayConfig(const std::string &config_name,
                                   const std::any &config_data) {
  if (config_name == "Color") {
    Display::Color color;
    GetAnyData(Display::Color, config_data, color);
    color_ = QColor(color[0], color[1], color[2]);
  } else {
    return false;
  }
  return true;
}
bool DisplayPath::UpdateData(const std::any &data) {
  try {
    auto path_data = std::any_cast<Display::PathData>(data);
    path_points_.clear();
    for (auto one_path : path_data) {
      path_points_.push_back(QPointF(one_path[0], one_path[1]));
    }
    update();
  } catch (const std::bad_any_cast &e) {
    std::cout << e.what() << '\n';
  }
}
void DisplayPath::drawPath(QPainter *painter) {
  painter->setRenderHint(QPainter::Antialiasing, true);
  painter->setPen(QPen(color_, 1));
  painter->drawPoints(path_points_);
}
void DisplayPath::computeBoundRect(const Display::PathData &path) {
  if (path.empty())
    return;
  float xmax, xmin, ymax, ymin;

  xmax = xmin = path[0][0];
  ymax = ymin = path[0][1];
  for (auto p : path) {
    xmax = xmax > p[0] ? xmax : p[0];
    xmin = xmin < p[0] ? xmin : p[0];
    ymax = ymax > p[1] ? ymax : p[1];
    ymin = ymin < p[1] ? ymin : p[1];
  }
  // std::cout << "xmax:" << xmax << "xmin:" << xmin << "ymax:" << ymax
  //           << "ymin:" << ymin << std::endl;
  bounding_rect_ = QRectF(xmin, ymin, xmax - xmin, ymax - ymin);
}