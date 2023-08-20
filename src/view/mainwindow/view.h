#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cmath>
#include <cctype>
#include "../graphlib/qcustomplot.h"
#include "../../controller/controller.h"

QT_BEGIN_NAMESPACE
/*! QT namespace */
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {
/*! Window height. */
#define WINHEIGHT 480
/*! Window width. */
#define WINWIDTH 821
/*! Maximum string length. */
#define MAXLEN 65
/*! Default font size. */
#define DEFAULTSIZE 26
/*! Minimum font size. */
#define MINSIZE 12
/*!
    \author Julieanb
    \brief The base class of the view.
         
    The view class allows the user to form a request, which is then sent to the controller.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*! Displays simple actions that do not require brackets. */
    void PrintButtonSimpleText();
    /*! Displays complex actions that requires brackets. */
    void PrintButtonHardText();
    /*! Tracks changes to the row the user is working on. Decreases/increases the font size as needed. */
    void on_lineEdit_main_textChanged(const QString &arg1);
    /*! All clear button. */
    void on_pushButton_ac_clicked();
    /*! Clear last symbol button. */
    void on_pushButton_c_clicked();
    /*! The private slot outputs a bracket. Automatically determines which bracket is needed at the moment. */
    void on_pushButton_brackets_clicked();
    /*! Sends an expression to the controller. */
    void on_pushButton_equal_clicked();
    /*! Performs the unary minus or plus operation. */
    void on_pushButton_uno_clicked();
    /*! Performs drawing of the graph. */
    void on_pushButton_graph_clicked();
    /*! The slot is associated with a string that stores the last expression that was counted. 
    When you click on the button, it allows you to return the expression to the main line. */
    void on_pushButton_last_expr_clicked();
    /*! The slot allows you to draw a graph in the form of points, if desired by the user. */
    void on_checkBox_dotDrawing_stateChanged(int arg1);
    /*! The slot allows you to draw a chart by the minimum and maximum y values, ignoring the range specified by the user. */
    void on_checkBox_isAdaptive_stateChanged(int arg1);

private:
    /* QT UI object. */
    Ui::MainWindow *ui;
    /*! An object of the controller's base class. */
    s21::Controller controller_;
    /*! A variable that determines whether the '=' button has been pressed recently. 
    It is necessary so that in certain circumstances, 
    when a button is pressed, the previous text is automatically erased. */
    bool got_answer_;
    /*! Stores the colors for drawing the graph. */
    QPen graph_pen;
    /*! 
        \brief Initialization method.

        Initializes a button group with "simple actions" and numbers.
    */
    void ConnectButtonSimpleText();
    /*! 
        \brief Initialization method.

        Initializes a button group with "complex actions".
    */
    void ConnectButtonHardText();
    /*! 
        \brief Initialization method.

        Sets the color palette for the graph.
    */
    void InitColorTheme();
    /*! 
        \brief Initialization method.

        Sets ranges for x and y.
    */
    void InitGraphSettings();
    /*! 
        \brief Initialization method.

        Sets the size of the window.
    */
    void InitWindowSettings();
    /*! 
        \brief Main initialization method.

        Calls all existing initialization methods.
    */
    void InitView();
    /*! The method draws a graph. */
    void DrawGraph();
};

} // namespace s21

#endif // MAINWINDOW_H
