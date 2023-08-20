#include "view.h"

#include "ui_view.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  InitView();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::InitView() {
  InitColorTheme();
  InitWindowSettings();
  InitGraphSettings();
  ConnectButtonSimpleText();
  ConnectButtonHardText();
  got_answer_ = false;
}

void MainWindow::InitWindowSettings() {
  this->setWindowTitle("SmartCalc_V2.0");
  this->setFixedHeight(WINHEIGHT);
  this->setFixedWidth(WINWIDTH);
  ui->lineEdit_xval->setPlaceholderText("Put x value");
}

void MainWindow::InitGraphSettings() {
  ui->spinBox_minx->setMinimum(-1000000);
  ui->spinBox_maxx->setMaximum(1000000);
  ui->spinBox_miny->setMinimum(-1000000);
  ui->spinBox_maxy->setMaximum(1000000);
  ui->spinBox_minx->setValue(-10);
  ui->spinBox_maxx->setValue(10);
  ui->spinBox_miny->setValue(-10);
  ui->spinBox_maxy->setValue(10);
}

void MainWindow::InitColorTheme() {
  ui->widget_graph->setBackground(QBrush(QColor(50, 50, 50)));
  ui->widget_graph->xAxis->setTickLabelColor(Qt::white);
  ui->widget_graph->xAxis->setBasePen(QPen(Qt::white));
  ui->widget_graph->xAxis->setLabelColor(Qt::white);
  ui->widget_graph->xAxis->setTickPen(QPen(Qt::white));
  ui->widget_graph->xAxis->setSubTickPen(QPen(Qt::white));
  ui->widget_graph->yAxis->setTickLabelColor(Qt::white);
  ui->widget_graph->yAxis->setBasePen(QPen(Qt::white));
  ui->widget_graph->yAxis->setLabelColor(Qt::white);
  ui->widget_graph->yAxis->setTickPen(QPen(Qt::white));
  ui->widget_graph->yAxis->setSubTickPen(QPen(Qt::white));
  graph_pen.setColor(QColor(252, 152, 38));
}

void MainWindow::ConnectButtonSimpleText() {
  connect(ui->pushButton_0, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this,
          SLOT(PrintButtonSimpleText()));
}

void MainWindow::ConnectButtonHardText() {
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(PrintButtonHardText()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(PrintButtonHardText()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(PrintButtonHardText()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(PrintButtonHardText()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(PrintButtonHardText()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(PrintButtonHardText()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(PrintButtonHardText()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(PrintButtonHardText()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(PrintButtonHardText()));
}

void MainWindow::PrintButtonSimpleText() {
  QPushButton *button = (QPushButton *)sender();
  if (got_answer_ && std::isdigit(button->text().toStdString()[0])) {
    ui->lineEdit_main->setText("");
    got_answer_ = false;
  }
  if (button->text().toStdString() == "∙")
    ui->lineEdit_main->setText(ui->lineEdit_main->text() + "*");
  else if (button->text().toStdString() == "÷")
    ui->lineEdit_main->setText(ui->lineEdit_main->text() + "/");
  else
    ui->lineEdit_main->setText(ui->lineEdit_main->text() + button->text());
}

void MainWindow::PrintButtonHardText() {
  QPushButton *button = (QPushButton *)sender();
  ui->lineEdit_main->setText(ui->lineEdit_main->text() + button->text() + "(");
}

void MainWindow::DrawGraph() {
  ui->widget_graph->clearPlottables();
  QVector<double> x, y;
  double x_begin = ui->spinBox_minx->value();
  double x_end = ui->spinBox_maxx->value();
  double step = 0.001 * x_end;
  double min_y = 0, max_y = 0;
  std::string str = ui->lineEdit_main->text().toStdString();
  ui->widget_graph->xAxis->setRange(x_begin, x_end);
  ui->widget_graph->yAxis->setRange(ui->spinBox_miny->value(),
                                    ui->spinBox_maxy->value());
  for (double X = x_begin; X <= x_end; X += step) {
    try {
      std::string res = controller_.CountExpressionWithX(str, X);
      if (res == "SYNTAX ERROR") {
        ui->lineEdit_main->setText(QString::fromStdString(res));
        return;
      }
      y.push_back(std::stod(res));
      if (min_y > y.back()) min_y = y.back();
      if (max_y < y.back()) max_y = y.back();
      x.push_back(X);
    } catch (...) {
      continue;
    }
  }
  ui->widget_graph->addGraph();
  ui->widget_graph->graph(0)->setPen(graph_pen);
  ui->widget_graph->graph(0)->addData(x, y);
  if (ui->checkBox_isAdaptive->isChecked()) {
    if (y.size() < 100 && std::fabs(x_begin) > 0 && std::fabs(x_end) > 0) {
      ui->spinBox_minx->setValue(ui->spinBox_minx->value() / 10);
      ui->spinBox_maxx->setValue(ui->spinBox_maxx->value() / 10);
      DrawGraph();
      ui->spinBox_minx->setValue(x_begin);
      ui->spinBox_maxx->setValue(x_end);
    } else {
      ui->widget_graph->yAxis->setRange(min_y, max_y);
      ui->widget_graph->xAxis->setRange(x[0], x.back());
    }
  }
  if (ui->checkBox_dotDrawing->isChecked())
    ui->widget_graph->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
  ui->widget_graph->replot();
  x.clear();
  y.clear();
}

void MainWindow::on_lineEdit_main_textChanged(const QString &arg1) {
  QFont f = ui->lineEdit_main->font();
  double len = arg1.length();
  double coeff = len / MAXLEN;
  if (coeff < 1) coeff = 1;
  double nwsize = std::floor(DEFAULTSIZE / coeff);
  if (nwsize < MINSIZE) nwsize = MINSIZE;
  f.setPointSize(nwsize);
  ui->lineEdit_main->setFont(f);
  got_answer_ = false;
}

void MainWindow::on_pushButton_ac_clicked() { ui->lineEdit_main->setText(""); }

void MainWindow::on_pushButton_c_clicked() {
  ui->lineEdit_main->setText(
      ui->lineEdit_main->text().left(ui->lineEdit_main->text().length() - 1));
}

void MainWindow::on_pushButton_brackets_clicked() {
  int cnt = 0;
  for (auto it : ui->lineEdit_main->text()) {
    if (it == '(') cnt++;
    if (it == ')') cnt--;
  }
  if (cnt <= 0)
    ui->lineEdit_main->setText(ui->lineEdit_main->text() + "(");
  else {
    if (ui->lineEdit_main->text().back().isDigit() ||
        ui->lineEdit_main->text().back() == ')' ||
        ui->lineEdit_main->text().back() == 'x') {
      ui->lineEdit_main->setText(ui->lineEdit_main->text() + ")");
    } else {
      ui->lineEdit_main->setText(ui->lineEdit_main->text() + "(");
    }
  }
}

void MainWindow::on_pushButton_equal_clicked() {
  ui->textEdit_last_expr->setText(ui->lineEdit_main->text());
  std::string expr = ui->lineEdit_main->text().toStdString();
  if (expr.find('x') != std::string::npos) {
    DrawGraph();
    if (!ui->lineEdit_xval->text().toStdString().empty()) {
      try {
        ui->lineEdit_main->setText(
            QString::fromStdString(controller_.CountExpressionWithX(
                expr, std::stod(ui->lineEdit_xval->text().toStdString()))));
      } catch (...) {
        ui->lineEdit_main->setText("X VALUE ERROR");
      }
    }
  } else {
    ui->lineEdit_main->setText(
        QString::fromStdString(controller_.CountExpression(expr)));
  }
  got_answer_ = true;
}

void MainWindow::on_pushButton_uno_clicked() {
  std::string expr = ui->lineEdit_main->text().toStdString();
  ui->lineEdit_main->setText(
      QString::fromStdString(controller_.UnoOperation(expr)));
}

void MainWindow::on_pushButton_graph_clicked() {
  ui->textEdit_last_expr->setText(ui->lineEdit_main->text());
  DrawGraph();
}

void MainWindow::on_pushButton_last_expr_clicked() {
  ui->lineEdit_main->setText(ui->textEdit_last_expr->toPlainText());
}

void MainWindow::on_checkBox_dotDrawing_stateChanged(int arg1) {
  if (!ui->lineEdit_main->text().toStdString().empty()) DrawGraph();
}

void MainWindow::on_checkBox_isAdaptive_stateChanged(int arg1) {
  if (!ui->lineEdit_main->text().toStdString().empty()) DrawGraph();
}

}  // namespace s21
